#include "debugger.hpp"
#include "disassembler.hpp"
#include "system.hpp"
#include "exception.hpp"

#include <sstream>
#include <iomanip>
#include <cctype>

namespace gameboy
{

Debugger::Debugger(System *s)
    : system_ {s}
{
    if (!system_)
        throw Bad_debugger {"Could not attach system to debugger", __FILE__, __LINE__};
    memory_map_ = dump_mapped_memory();
}

void Debugger::run()
{
    while (!paused_)
    {
        if (at_breakpoint())
            break;
        if (log_)
            write_log();
        step(1);
        ++steps_;
    }
}

void Debugger::pause()
{
    paused_ = true;
}

void Debugger::step(size_t n)
{
    for (size_t i {0}; i < n; ++i)
    {
        if (at_breakpoint())
            break;
        if (log_)
            write_log();
        system_->step(1);
        ++steps_;
    }
    memory_changed_ = system_->memory_.was_written();
}

void Debugger::reset()
{
    system_->reset();
    steps_ = 0;
    memory_map_ = dump_mapped_memory();
    memory_changed_ = false;
}

void Debugger::add_breakpoint(uint16_t adr)
{
    breaks_[adr] = true;
}

void Debugger::delete_breakpoint(uint16_t adr)
{
    breaks_[adr] = false;
}

void Debugger::enable_logging(bool b)
{
    log_ = b;
}

void Debugger::set_log_file(const std::string &s)
{
    log_path_ = s;
}

void Debugger::write_log()
{
    static std::ofstream log {log_path_};
    log << Debugger::log() << '\n';
}

std::string Debugger::log()
{
    std::ostringstream out {};
    Cpu_values dump {dump_cpu()};
    Disassembler ds {};
    Assembly as {ds.disassemble_op(dump.next_ops, dump.pc)};
    uint8_t a = dump.af >> 8;
    uint8_t f = dump.af & 0xff;
    uint8_t b = dump.bc >> 8;
    uint8_t c = dump.bc & 0xff;
    uint8_t d = dump.de >> 8;
    uint8_t e = dump.de & 0xff;
    uint8_t h = dump.hl >> 8;
    uint8_t l = dump.hl & 0xff;
    uint8_t ly = system_->memory_read(0xff44);
    std::array<std::string, 24> flag_char // flag register in character format
    {{
        "----", "---C", "--H-", "--HC",
        "-N--", "-N-C", "-NH-", "-NHC",
        "Z---", "Z--C", "Z-H-", "Z-HC",
        "ZN--", "ZN-C", "ZNH-", "ZNHC",
    }};

    // begin output
    out << std::nouppercase << std::right << std::hex << std::setfill('0')
        << "A:" << std::setw(2) << static_cast<int>(a) << ' '
        << "F:" << flag_char[(f >> 4)] << ' '
        << "BC:" << std::setw(2) << static_cast<int>(b) << std::setw(2) << static_cast<int>(c) << ' '
        << "DE:" << std::setw(2) << static_cast<int>(d) << std::setw(2) << static_cast<int>(e) << ' '
        << "HL:" << std::setw(2) << static_cast<int>(h) << std::setw(2) << static_cast<int>(l) << ' '
        << "SP:" << std::setw(4) << dump.sp << ' '
        << "PC:" << std::setw(4) << dump.pc << ' '
        << "LY:" << std::setw(2) << static_cast<int>(ly) << ' '
        << "(cy: " << std::dec << dump.cycles << ") ";

    out << std::nouppercase << std::right << std::setfill('0') << std::hex
        << std::setw(4) << dump.pc << ":  "; // PC
    std::ostringstream ops {}; // so we can set fixed width for variable
                               // number of ops
    for (uint8_t x : as.ops)
        ops << std::nouppercase << std::setfill('0') << std::hex << std::setw(2)
            << static_cast<int>(x) << ' ';
    // format 1
    std::string ins {as.code};
    for (auto &c : ins)
        c = std::tolower(c);
    out << std::left << std::setfill(' ') << std::setw(10) << ops.str() // bytes
        << std::setw(20) << ins; // instruction
    /*
        << std::nouppercase << std::right << std::hex << std::setfill('0') // registers
        << "AF:" << std::setw(2) << static_cast<int>(a) << std::setw(2) << static_cast<int>(f) << ' '
        << "BC:" << std::setw(2) << static_cast<int>(b) << std::setw(2) << static_cast<int>(c) << ' '
        << "DE:" << std::setw(2) << static_cast<int>(d) << std::setw(2) << static_cast<int>(e) << ' '
        << "HL:" << std::setw(2) << static_cast<int>(h) << std::setw(2) << static_cast<int>(l) << ' '
        << "SP:" << std::setw(4) << dump.sp << "  "
        << "Cy:" << std::dec << dump.cycles;
    */
    return out.str();
}

size_t Debugger::steps() const
{
    return steps_;
}

bool Debugger::paused() const
{
    return paused_;
}

std::vector<uint8_t> Debugger::dump_memory() const
{
    std::map<std::string, Memory_range> mem {dump_mapped_memory()};
    std::vector<uint8_t> out {};
    for (const std::string &r : Memory_range_names)
        out.insert(out.end(), mem[r].data.begin(), mem[r].data.end());
    return out;
}

std::map<std::string, Memory_range> Debugger::dump_mapped_memory() const
{
    std::map<std::string, Memory_range> out {system_->memory_.dump()};
    std::vector<uint8_t> echo_ram {out["WRM0"].data};
    echo_ram.insert(echo_ram.end(), out["WRMX"].data.begin(), out["WRMX"].data.begin() + 0x0e00);
    out["ECHO"] = {"ECHO", echo_ram};
    out["XXXX"] = {"UNUS", std::vector<uint8_t>(0x60)};
    return out;
}

std::string Debugger::dump_formatted_memory(Dump_format d) const
{
    static std::map<std::string, Memory_range> mem {dump_mapped_memory()};
    if (memory_changed())
        mem = dump_mapped_memory();
    std::ostringstream dump {};
    std::ostringstream out {};
    out << std::hex << std::setfill('0');
    size_t i {0};
    switch (d)
    {
        case Dump_format::Hex:
        {
            for (const std::string &r : Memory_range_names)
            {
                const std::vector<uint8_t> &v {mem[r].data};
                // rows + data
                for (size_t j {0}; j < v.size(); j += 16, i += 16)
                {
                    // row marker
                    out << std::setfill(' ') << std::setw(4) << mem[r].name << ':'
                        << std::setw(4) << std::setfill('0') << std::hex
                        << i << ' ';
                    // line of 16 bytes
                    std::string line;
                    for (unsigned short k {0}; k < 16; ++k)
                    {
                        const uint8_t c {v[j+k]};
                        if (c < 32 || c > 126) // non-printable ASCII
                            line += '.';
                        else
                            line += static_cast<char>(c);
                        out << std::setw(2) << std::setfill('0') << std::hex
                            << static_cast<int>(c) << ' ';
                    }
                    out << line << '\n';
                }
            }
        } break;
        case Dump_format::Stack:
        {
            i = 0xfffe;
            for (auto n {Memory_range_names.rbegin()};
                 n != Memory_range_names.rend();
                 ++n)
            {
                const std::vector<uint8_t> &v {mem[*n].data};
                for (auto j {v.rbegin()}; j != v.rend(); ++j, --i)
                {
                    out << std::setfill(' ') << std::setw(4) << mem[*n].name << ':'
                        << std::setw(4) << std::setfill('0') << std::hex
                        << i << ' '
                        << std::setw(2) << static_cast<int>(*j)
                        << '\n';
                }
            }
        } break;
    }
    return out.str();
}

bool Debugger::memory_changed() const
{
    return system_->memory_changed_;
}

std::vector<uint8_t> Debugger::dump_rom() const noexcept
{
    return system_->memory_.dump_rom();
}

Cpu_values Debugger::dump_cpu() const noexcept
{
    return system_->cpu_.dump();
}

void Debugger::draw_framebuffer()
{
    system_->ppu_.draw_framebuffer();
}

std::string Debugger::hex_dump() const
{
    const std::vector<uint8_t> &ops {dump_memory()};
    uint8_t len {0};
    std::ostringstream out {};
    for (uint32_t pc {0}; pc < ops.size(); pc += len)
    {
        Instruction ins {instructions[ops[pc]]};
        len = ins.length;
        std::ostringstream bytes {};
        for (uint8_t i {0}; i < ins.length; ++i) // opcodes
            bytes << std::setfill('0') << ' ' << std::hex
                  << std::setw(2) << static_cast<int>(ops[pc+i]);
        const std::string operand1 {ins.operand1.empty() ? "" : ins.operand1};
        const std::string operand2 {ins.operand2.empty() ? "" : ins.operand2};
        out << std::setfill('0') << std::setw(4) << std::hex << std::right << pc; // address
        out << std::setfill(' ') << std::setw(10) << std::left << bytes.str() // opcodes
            << ' ' << std::setw(4) << ins.name; // instruction
        if (!operand1.empty())
        {
            out << ' ' << operand1;
            if (!operand2.empty())
                out << ',' << operand2;
        }
        out << '\n';
    }
    return out.str();
}

class Hex // for more convenient formatting
{
    public:
    explicit Hex(int x) : x_ {x} {}
    friend std::ostream &operator<<(std::ostream &os, const Hex &h)
    {
        os << std::right << std::hex << std::setfill('0')
           << std::uppercase << std::setw(2) << h.x_;
        return os;
    }

    private:
    int x_;
};

Assembly Debugger::disassemble_op() const
{
    return disassemble_op(dump_cpu().pc);
}

Assembly Debugger::disassemble_op(uint16_t adr) const
{
    const std::array<uint8_t, 3> &ops
    {{
        system_->memory_read(adr),
        system_->memory_read(adr+1),
        system_->memory_read(adr+2)
    }};
    Instruction ins;
    if (ops[0] == 0xcb)
        ins = cb_instructions[ops[1]];
    else
        ins = instructions[ops[0]];
    std::ostringstream code {};
    const std::string operand1 {ins.operand1.empty() ? "" : ins.operand1};
    const std::string operand2 {ins.operand2.empty() ? "" : ins.operand2};
    code << std::setfill(' ') << std::left << std::setw(4) << ins.name; // instruction
    if (!operand1.empty())
    {
        code << ' ' << parse_operand(ops, operand1, adr);
        if (!operand2.empty())
        {
            code << ',' << parse_operand(ops, operand2, adr);
        }
    }
    std::vector<uint8_t> ops_used(ins.length);
    for (uint8_t i {0}; i < ops.size(); ++i)
        ops_used[i] = ops[i];
    return Assembly {ops_used, ins, code.str()};
}

std::vector<Assembly> Debugger::disassemble() const
{
    const std::vector<uint8_t> &ops {dump_memory()};
    std::vector<Assembly> out {};
    for (uint16_t i {0}; i < ops.size(); i += instructions[ops[i]].length)
    {
        out.push_back(disassemble_op(i));
    }
    return out;
}

bool Debugger::at_breakpoint()
{
    uint16_t pc {dump_cpu().pc};
    if (breaks_[pc])
        return true;
    return false;
}

std::string Debugger::parse_operand(const std::array<uint8_t, 3> &ops,
                                    const std::string &operand,
                                    uint16_t adr) const
{
    std::ostringstream out {};
    if (operand == "a16" || operand == "d16") // 16-bit immediate
        out << '#' << Hex(ops[2]) << Hex(ops[1]) << 'h';
    else if (operand == "r8") // 8-bit signed immediate
        out << '#' << Hex(static_cast<int8_t>(adr+ops[1])) << 'h';
    else if (operand == "d8") // 8-bit unsigned immediate
        out << '#' << Hex(ops[1]) << 'h';
    else if (operand == "(a8)") // 8-bit unsigned indexing
        out << "(#" << Hex(ops[1]) << "h)";
    else if (operand == "(a16)" || operand == "(d16)") // 16-bit direct
        out << "(#" << Hex(ops[2]) << Hex(ops[1]) << "h)";
    else
        out << operand;
    return out.str();
}

}
