#pragma once

#include <array>
#include <optional>
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <map>

#include "cartridge.hpp"
#include "debug_types.hpp"

namespace gameboy
{

class Timer;

class Memory
{
    static constexpr auto RAM_BANK_SIZE = 0x2000; // 8 KB
    public:

    explicit Memory(Timer &t);

    uint8_t read(uint16_t adr) const;
    void write(uint8_t b, uint16_t adr);
    void load_cartridge(std::istream &is);
    void reset();

    std::vector<uint8_t> dump_rom() const;
    std::map<std::string, Memory_range> dump() const;
    bool was_written();

    private:
    std::optional<Cartridge> cart_ {std::nullopt};
    Video_ram vram_ {}; // 8KB x 2
    Work_ram wram_ {};
    std::array<uint8_t, 0xa0> oam_ {};
    std::array<uint8_t, 0x80> io_ {};
    std::array<uint8_t, 0x7f> hram_ {};
    Timer &timer_; // to access hardware registers
    uint8_t ie_ {};
    bool was_written_ {false};

    void set_ram_size();
    void init_io();

};

}
