#ifndef INSTRUCTION_INFO_HPP
#define INSTRUCTION_INFO_HPP

#include <array>
#include <string>
#include <optional>

struct Instruction
{
    std::string name;
	uint8_t length;
	uint8_t cycles;
	uint8_t alt_cycles;
    std::string operand1;
    std::string operand2;
};
	
const std::array<Instruction, 256> instructions
{{
    {"NOP", 1, 4, 4, "", ""},
	{"LD", 3, 12, 12, "BC", "d16"},
	{"LD", 1, 8, 8, "(BC)", "A"},
    {"INC", 1, 8, 8, "BC", ""},
    {"INC", 1, 4, 4, "B", ""},
    {"DEC", 1, 4, 4, "B", ""},
	{"LD", 2, 8, 8, "B", "d8"},
    {"RLCA", 1, 4, 4, "", ""},
	{"LD", 3, 20, 20, "(a16)", "SP"},
	{"ADD", 1, 8, 8, "HL", "BC"},
	{"LD", 1, 8, 8, "A", "(BC)"},
    {"DEC", 1, 8, 8, "BC", ""},
    {"INC", 1, 4, 4, "C", ""},
    {"DEC", 1, 4, 4, "C", ""},
	{"LD", 2, 8, 8, "C", "d8"},
    {"RRCA", 1, 4, 4, "", ""},
    {"STOP", 1, 4, 4, "0", ""},
	{"LD", 3, 12, 12, "DE", "d16"},
	{"LD", 1, 8, 8, "(DE)", "A"},
    {"INC", 1, 8, 8, "DE", ""},
    {"INC", 1, 4, 4, "D", ""},
    {"DEC", 1, 4, 4, "D", ""},
	{"LD", 2, 8, 8, "D", "d8"},
    {"RLA", 1, 4, 4, "", ""},
    {"JR", 2, 12, 12, "r8", ""},
	{"ADD", 1, 8, 8, "HL", "DE"},
	{"LD", 1, 8, 8, "A", "(DE)"},
    {"DEC", 1, 8, 8, "DE", ""},
    {"INC", 1, 4, 4, "E", ""},
    {"DEC", 1, 4, 4, "E", ""},
	{"LD", 2, 8, 8, "E", "d8"},
    {"RRA", 1, 4, 4, "", ""},
	{"JR", 2, 12, 8, "NZ", "r8"},
	{"LD", 3, 12, 12, "HL", "d16"},
	{"LD", 1, 8, 8, "(HL+)", "A"},
    {"INC", 1, 8, 8, "HL", ""},
    {"INC", 1, 4, 4, "H", ""},
    {"DEC", 1, 4, 4, "H", ""},
	{"LD", 2, 8, 8, "H", "d8"},
    {"DAA", 1, 4, 4, "", ""},
	{"JR", 2, 12, 8, "Z", "r8"},
	{"ADD", 1, 8, 8, "HL", "HL"},
	{"LD", 1, 8, 8, "A", "(HL+)"},
    {"DEC", 1, 8, 8, "HL", ""},
    {"INC", 1, 4, 4, "L", ""},
    {"DEC", 1, 4, 4, "L", ""},
	{"LD", 2, 8, 8, "L", "d8"},
    {"CPL", 1, 4, 4, "", ""},
	{"JR", 2, 12, 8, "NC", "r8"},
	{"LD", 3, 12, 12, "SP", "d16"},
	{"LD", 1, 8, 8, "(HL-)", "A"},
    {"INC", 1, 8, 8, "SP", ""},
    {"INC", 1, 12, 12, "(HL)", ""},
    {"DEC", 1, 12, 12, "(HL)", ""},
	{"LD", 2, 12, 12, "(HL)", "d8"},
    {"SCF", 1, 4, 4, "", ""},
	{"JR", 2, 12, 8, "C", "r8"},
	{"ADD", 1, 8, 8, "HL", "SP"},
	{"LD", 1, 8, 8, "A", "(HL-)"},
    {"DEC", 1, 8, 8, "SP", ""},
    {"INC", 1, 4, 4, "A", ""},
    {"DEC", 1, 4, 4, "A", ""},
	{"LD", 2, 8, 8, "A", "d8"},
    {"CCF", 1, 4, 4, "", ""},
	{"LD", 1, 4, 4, "B", "B"},
	{"LD", 1, 4, 4, "B", "C"},
	{"LD", 1, 4, 4, "B", "D"},
	{"LD", 1, 4, 4, "B", "E"},
	{"LD", 1, 4, 4, "B", "H"},
	{"LD", 1, 4, 4, "B", "L"},
	{"LD", 1, 8, 8, "B", "(HL)"},
	{"LD", 1, 4, 4, "B", "A"},
	{"LD", 1, 4, 4, "C", "B"},
	{"LD", 1, 4, 4, "C", "C"},
	{"LD", 1, 4, 4, "C", "D"},
	{"LD", 1, 4, 4, "C", "E"},
	{"LD", 1, 4, 4, "C", "H"},
	{"LD", 1, 4, 4, "C", "L"},
	{"LD", 1, 8, 8, "C", "(HL)"},
	{"LD", 1, 4, 4, "C", "A"},
	{"LD", 1, 4, 4, "D", "B"},
	{"LD", 1, 4, 4, "D", "C"},
	{"LD", 1, 4, 4, "D", "D"},
	{"LD", 1, 4, 4, "D", "E"},
	{"LD", 1, 4, 4, "D", "H"},
	{"LD", 1, 4, 4, "D", "L"},
	{"LD", 1, 8, 8, "D", "(HL)"},
	{"LD", 1, 4, 4, "D", "A"},
	{"LD", 1, 4, 4, "E", "B"},
	{"LD", 1, 4, 4, "E", "C"},
	{"LD", 1, 4, 4, "E", "D"},
	{"LD", 1, 4, 4, "E", "E"},
	{"LD", 1, 4, 4, "E", "H"},
	{"LD", 1, 4, 4, "E", "L"},
	{"LD", 1, 8, 8, "E", "(HL)"},
	{"LD", 1, 4, 4, "E", "A"},
	{"LD", 1, 4, 4, "H", "B"},
	{"LD", 1, 4, 4, "H", "C"},
	{"LD", 1, 4, 4, "H", "D"},
	{"LD", 1, 4, 4, "H", "E"},
	{"LD", 1, 4, 4, "H", "H"},
	{"LD", 1, 4, 4, "H", "L"},
	{"LD", 1, 8, 8, "H", "(HL)"},
	{"LD", 1, 4, 4, "H", "A"},
	{"LD", 1, 4, 4, "L", "B"},
	{"LD", 1, 4, 4, "L", "C"},
	{"LD", 1, 4, 4, "L", "D"},
	{"LD", 1, 4, 4, "L", "E"},
	{"LD", 1, 4, 4, "L", "H"},
	{"LD", 1, 4, 4, "L", "L"},
	{"LD", 1, 8, 8, "L", "(HL)"},
	{"LD", 1, 4, 4, "L", "A"},
	{"LD", 1, 8, 8, "(HL)", "B"},
	{"LD", 1, 8, 8, "(HL)", "C"},
	{"LD", 1, 8, 8, "(HL)", "D"},
	{"LD", 1, 8, 8, "(HL)", "E"},
	{"LD", 1, 8, 8, "(HL)", "H"},
	{"LD", 1, 8, 8, "(HL)", "L"},
    {"HALT", 1, 4, 4, "", ""},
	{"LD", 1, 8, 8, "(HL)", "A"},
	{"LD", 1, 4, 4, "A", "B"},
	{"LD", 1, 4, 4, "A", "C"},
	{"LD", 1, 4, 4, "A", "D"},
	{"LD", 1, 4, 4, "A", "E"},
	{"LD", 1, 4, 4, "A", "H"},
	{"LD", 1, 4, 4, "A", "L"},
	{"LD", 1, 8, 8, "A", "(HL)"},
	{"LD", 1, 4, 4, "A", "A"},
	{"ADD", 1, 4, 4, "A", "B"},
	{"ADD", 1, 4, 4, "A", "C"},
	{"ADD", 1, 4, 4, "A", "D"},
	{"ADD", 1, 4, 4, "A", "E"},
	{"ADD", 1, 4, 4, "A", "H"},
	{"ADD", 1, 4, 4, "A", "L"},
	{"ADD", 1, 8, 8, "A", "(HL)"},
	{"ADD", 1, 4, 4, "A", "A"},
	{"ADC", 1, 4, 4, "A", "B"},
	{"ADC", 1, 4, 4, "A", "C"},
	{"ADC", 1, 4, 4, "A", "D"},
	{"ADC", 1, 4, 4, "A", "E"},
	{"ADC", 1, 4, 4, "A", "H"},
	{"ADC", 1, 4, 4, "A", "L"},
	{"ADC", 1, 8, 8, "A", "(HL)"},
	{"ADC", 1, 4, 4, "A", "A"},
    {"SUB", 1, 4, 4, "B", ""},
    {"SUB", 1, 4, 4, "C", ""},
    {"SUB", 1, 4, 4, "D", ""},
    {"SUB", 1, 4, 4, "E", ""},
    {"SUB", 1, 4, 4, "H", ""},
    {"SUB", 1, 4, 4, "L", ""},
    {"SUB", 1, 8, 8, "(HL)", ""},
    {"SUB", 1, 4, 4, "A", ""},
	{"SBC", 1, 4, 4, "A", "B"},
	{"SBC", 1, 4, 4, "A", "C"},
	{"SBC", 1, 4, 4, "A", "D"},
	{"SBC", 1, 4, 4, "A", "E"},
	{"SBC", 1, 4, 4, "A", "H"},
	{"SBC", 1, 4, 4, "A", "L"},
	{"SBC", 1, 8, 8, "A", "(HL)"},
	{"SBC", 1, 4, 4, "A", "A"},
    {"AND", 1, 4, 4, "B", ""},
    {"AND", 1, 4, 4, "C", ""},
    {"AND", 1, 4, 4, "D", ""},
    {"AND", 1, 4, 4, "E", ""},
    {"AND", 1, 4, 4, "H", ""},
    {"AND", 1, 4, 4, "L", ""},
    {"AND", 1, 8, 8, "(HL)", ""},
    {"AND", 1, 4, 4, "A", ""},
    {"XOR", 1, 4, 4, "B", ""},
    {"XOR", 1, 4, 4, "C", ""},
    {"XOR", 1, 4, 4, "D", ""},
    {"XOR", 1, 4, 4, "E", ""},
    {"XOR", 1, 4, 4, "H", ""},
    {"XOR", 1, 4, 4, "L", ""},
    {"XOR", 1, 8, 8, "(HL)", ""},
    {"XOR", 1, 4, 4, "A", ""},
    {"OR", 1, 4, 4, "B", ""},
    {"OR", 1, 4, 4, "C", ""},
    {"OR", 1, 4, 4, "D", ""},
    {"OR", 1, 4, 4, "E", ""},
    {"OR", 1, 4, 4, "H", ""},
    {"OR", 1, 4, 4, "L", ""},
    {"OR", 1, 8, 8, "(HL)", ""},
    {"OR", 1, 4, 4, "A", ""},
    {"CP", 1, 4, 4, "B", ""},
    {"CP", 1, 4, 4, "C", ""},
    {"CP", 1, 4, 4, "D", ""},
    {"CP", 1, 4, 4, "E", ""},
    {"CP", 1, 4, 4, "H", ""},
    {"CP", 1, 4, 4, "L", ""},
    {"CP", 1, 8, 8, "(HL)", ""},
    {"CP", 1, 4, 4, "A", ""},
    {"RET", 1, 20, 8, "NZ", ""},
    {"POP", 1, 12, 12, "BC", ""},
	{"JP", 3, 16, 12, "NZ", "a16"},
    {"JP", 3, 16, 16, "a16", ""},
	{"CALL", 3, 24, 12, "NZ", "a16"},
    {"PUSH", 1, 16, 16, "BC", ""},
	{"ADD", 2, 8, 8, "A", "d8"},
    {"RST", 1, 16, 16, "00H", ""},
    {"RET", 1, 20, 8, "Z", ""},
    {"RET", 1, 16, 16, "", ""},
	{"JP", 3, 16, 12, "Z", "a16"},
    {"PREFIX", 1, 4, 4, "CB", ""},
	{"CALL", 3, 24, 12, "Z", "a16"},
    {"CALL", 3, 24, 24, "a16", ""},
	{"ADC", 2, 8, 8, "A", "d8"},
    {"RST", 1, 16, 16, "08H", ""},
    {"RET", 1, 20, 8, "NC", ""},
    {"POP", 1, 12, 12, "DE", ""},
	{"JP", 3, 16, 12, "NC", "a16"},
    {"Non-existant OP", 1, 0, 0, "", ""},
	{"CALL", 3, 24, 12, "NC", "a16"},
    {"PUSH", 1, 16, 16, "DE", ""},
    {"SUB", 2, 8, 8, "d8", ""},
    {"RST", 1, 16, 16, "10H", ""},
    {"RET", 1, 20, 8, "C", ""},
    {"RETI", 1, 16, 16, "", ""},
	{"JP", 3, 16, 12, "C", "a16"},
    {"Non-existant OP", 1, 0, 0, "", ""},
	{"CALL", 3, 24, 12, "C", "a16"},
    {"Non-existant OP", 1, 0, 0, "", ""},
	{"SBC", 2, 8, 8, "A", "d8"},
    {"RST", 1, 16, 16, "18H", ""},
	{"LDH", 2, 12, 12, "(a8)", "A"},
    {"POP", 1, 12, 12, "HL", ""},
	{"LD", 1, 8, 8, "(C)", "A"},
    {"Non-existant OP", 1, 0, 0, "", ""},
    {"Non-existant OP", 1, 0, 0, "", ""},
    {"PUSH", 1, 16, 16, "HL", ""},
    {"AND", 2, 8, 8, "d8", ""},
    {"RST", 1, 16, 16, "20H", ""},
	{"ADD", 2, 16, 16, "SP", "r8"},
    {"JP", 1, 4, 4, "(HL)", ""},
	{"LD", 3, 16, 16, "(a16)", "A"},
    {"Non-existant OP", 1, 0, 0, "", ""},
    {"Non-existant OP", 1, 0, 0, "", ""},
    {"Non-existant OP", 1, 0, 0, "", ""},
    {"XOR", 2, 8, 8, "d8", ""},
    {"RST", 1, 16, 16, "28H", ""},
	{"LDH", 2, 12, 12, "A", "(a8)"},
    {"POP", 1, 12, 12, "AF", ""},
	{"LD", 1, 8, 8, "A", "(C)"},
    {"DI", 1, 4, 4, "", ""},
    {"Non-existant OP", 1, 0, 0, "", ""},
    {"PUSH", 1, 16, 16, "AF", ""},
    {"OR", 2, 8, 8, "d8", ""},
    {"RST", 1, 16, 16, "30H", ""},
	{"LD", 2, 12, 12, "HL", "SP+r8"},
	{"LD", 1, 8, 8, "SP", "HL"},
	{"LD", 3, 16, 16, "A", "(a16)"},
    {"EI", 1, 4, 4, "", ""},
    {"Non-existant OP", 1, 0, 0, "", ""},
    {"Non-existant OP", 1, 0, 0, "", ""},
    {"CP", 2, 8, 8, "d8", ""},
    {"RST", 1, 16, 16, "38H", ""}
}};

const std::array<Instruction, 256> cb_instructions
{{
    {"RLC", 2, 8, 8, "B", ""},
    {"RLC", 2, 8, 8, "C", ""},
    {"RLC", 2, 8, 8, "D", ""},
    {"RLC", 2, 8, 8, "E", ""},
    {"RLC", 2, 8, 8, "H", ""},
    {"RLC", 2, 8, 8, "L", ""},
    {"RLC", 2, 16, 16, "(HL)", ""},
    {"RLC", 2, 8, 8, "A", ""},
    {"RRC", 2, 8, 8, "B", ""},
    {"RRC", 2, 8, 8, "C", ""},
    {"RRC", 2, 8, 8, "D", ""},
    {"RRC", 2, 8, 8, "E", ""},
    {"RRC", 2, 8, 8, "H", ""},
    {"RRC", 2, 8, 8, "L", ""},
    {"RRC", 2, 16, 16, "(HL)", ""},
    {"RRC", 2, 8, 8, "A", ""},
    {"RL", 2, 8, 8, "B", ""},
    {"RL", 2, 8, 8, "C", ""},
    {"RL", 2, 8, 8, "D", ""},
    {"RL", 2, 8, 8, "E", ""},
    {"RL", 2, 8, 8, "H", ""},
    {"RL", 2, 8, 8, "L", ""},
    {"RL", 2, 16, 16, "(HL)", ""},
    {"RL", 2, 8, 8, "A", ""},
    {"RR", 2, 8, 8, "B", ""},
    {"RR", 2, 8, 8, "C", ""},
    {"RR", 2, 8, 8, "D", ""},
    {"RR", 2, 8, 8, "E", ""},
    {"RR", 2, 8, 8, "H", ""},
    {"RR", 2, 8, 8, "L", ""},
    {"RR", 2, 16, 16, "(HL)", ""},
    {"RR", 2, 8, 8, "A", ""},
    {"SLA", 2, 8, 8, "B", ""},
    {"SLA", 2, 8, 8, "C", ""},
    {"SLA", 2, 8, 8, "D", ""},
    {"SLA", 2, 8, 8, "E", ""},
    {"SLA", 2, 8, 8, "H", ""},
    {"SLA", 2, 8, 8, "L", ""},
    {"SLA", 2, 16, 16, "(HL)", ""},
    {"SLA", 2, 8, 8, "A", ""},
    {"SRA", 2, 8, 8, "B", ""},
    {"SRA", 2, 8, 8, "C", ""},
    {"SRA", 2, 8, 8, "D", ""},
    {"SRA", 2, 8, 8, "E", ""},
    {"SRA", 2, 8, 8, "H", ""},
    {"SRA", 2, 8, 8, "L", ""},
    {"SRA", 2, 16, 16, "(HL)", ""},
    {"SRA", 2, 8, 8, "A", ""},
    {"SWAP", 2, 8, 8, "B", ""},
    {"SWAP", 2, 8, 8, "C", ""},
    {"SWAP", 2, 8, 8, "D", ""},
    {"SWAP", 2, 8, 8, "E", ""},
    {"SWAP", 2, 8, 8, "H", ""},
    {"SWAP", 2, 8, 8, "L", ""},
    {"SWAP", 2, 16, 16, "(HL)", ""},
    {"SWAP", 2, 8, 8, "A", ""},
    {"SRL", 2, 8, 8, "B", ""},
    {"SRL", 2, 8, 8, "C", ""},
    {"SRL", 2, 8, 8, "D", ""},
    {"SRL", 2, 8, 8, "E", ""},
    {"SRL", 2, 8, 8, "H", ""},
    {"SRL", 2, 8, 8, "L", ""},
    {"SRL", 2, 16, 16, "(HL)", ""},
    {"SRL", 2, 8, 8, "A", ""},
	{"BIT", 2, 8, 8, "0", "B"},
	{"BIT", 2, 8, 8, "0", "C"},
	{"BIT", 2, 8, 8, "0", "D"},
	{"BIT", 2, 8, 8, "0", "E"},
	{"BIT", 2, 8, 8, "0", "H"},
	{"BIT", 2, 8, 8, "0", "L"},
	{"BIT", 2, 16, 16, "0", "(HL)"},
	{"BIT", 2, 8, 8, "0", "A"},
	{"BIT", 2, 8, 8, "1", "B"},
	{"BIT", 2, 8, 8, "1", "C"},
	{"BIT", 2, 8, 8, "1", "D"},
	{"BIT", 2, 8, 8, "1", "E"},
	{"BIT", 2, 8, 8, "1", "H"},
	{"BIT", 2, 8, 8, "1", "L"},
	{"BIT", 2, 16, 16, "1", "(HL)"},
	{"BIT", 2, 8, 8, "1", "A"},
	{"BIT", 2, 8, 8, "2", "B"},
	{"BIT", 2, 8, 8, "2", "C"},
	{"BIT", 2, 8, 8, "2", "D"},
	{"BIT", 2, 8, 8, "2", "E"},
	{"BIT", 2, 8, 8, "2", "H"},
	{"BIT", 2, 8, 8, "2", "L"},
	{"BIT", 2, 16, 16, "2", "(HL)"},
	{"BIT", 2, 8, 8, "2", "A"},
	{"BIT", 2, 8, 8, "3", "B"},
	{"BIT", 2, 8, 8, "3", "C"},
	{"BIT", 2, 8, 8, "3", "D"},
	{"BIT", 2, 8, 8, "3", "E"},
	{"BIT", 2, 8, 8, "3", "H"},
	{"BIT", 2, 8, 8, "3", "L"},
	{"BIT", 2, 16, 16, "3", "(HL)"},
	{"BIT", 2, 8, 8, "3", "A"},
	{"BIT", 2, 8, 8, "4", "B"},
	{"BIT", 2, 8, 8, "4", "C"},
	{"BIT", 2, 8, 8, "4", "D"},
	{"BIT", 2, 8, 8, "4", "E"},
	{"BIT", 2, 8, 8, "4", "H"},
	{"BIT", 2, 8, 8, "4", "L"},
	{"BIT", 2, 16, 16, "4", "(HL)"},
	{"BIT", 2, 8, 8, "4", "A"},
	{"BIT", 2, 8, 8, "5", "B"},
	{"BIT", 2, 8, 8, "5", "C"},
	{"BIT", 2, 8, 8, "5", "D"},
	{"BIT", 2, 8, 8, "5", "E"},
	{"BIT", 2, 8, 8, "5", "H"},
	{"BIT", 2, 8, 8, "5", "L"},
	{"BIT", 2, 16, 16, "5", "(HL)"},
	{"BIT", 2, 8, 8, "5", "A"},
	{"BIT", 2, 8, 8, "6", "B"},
	{"BIT", 2, 8, 8, "6", "C"},
	{"BIT", 2, 8, 8, "6", "D"},
	{"BIT", 2, 8, 8, "6", "E"},
	{"BIT", 2, 8, 8, "6", "H"},
	{"BIT", 2, 8, 8, "6", "L"},
	{"BIT", 2, 16, 16, "6", "(HL)"},
	{"BIT", 2, 8, 8, "6", "A"},
	{"BIT", 2, 8, 8, "7", "B"},
	{"BIT", 2, 8, 8, "7", "C"},
	{"BIT", 2, 8, 8, "7", "D"},
	{"BIT", 2, 8, 8, "7", "E"},
	{"BIT", 2, 8, 8, "7", "H"},
	{"BIT", 2, 8, 8, "7", "L"},
	{"BIT", 2, 16, 16, "7", "(HL)"},
	{"BIT", 2, 8, 8, "7", "A"},
	{"RES", 2, 8, 8, "0", "B"},
	{"RES", 2, 8, 8, "0", "C"},
	{"RES", 2, 8, 8, "0", "D"},
	{"RES", 2, 8, 8, "0", "E"},
	{"RES", 2, 8, 8, "0", "H"},
	{"RES", 2, 8, 8, "0", "L"},
	{"RES", 2, 16, 16, "0", "(HL)"},
	{"RES", 2, 8, 8, "0", "A"},
	{"RES", 2, 8, 8, "1", "B"},
	{"RES", 2, 8, 8, "1", "C"},
	{"RES", 2, 8, 8, "1", "D"},
	{"RES", 2, 8, 8, "1", "E"},
	{"RES", 2, 8, 8, "1", "H"},
	{"RES", 2, 8, 8, "1", "L"},
	{"RES", 2, 16, 16, "1", "(HL)"},
	{"RES", 2, 8, 8, "1", "A"},
	{"RES", 2, 8, 8, "2", "B"},
	{"RES", 2, 8, 8, "2", "C"},
	{"RES", 2, 8, 8, "2", "D"},
	{"RES", 2, 8, 8, "2", "E"},
	{"RES", 2, 8, 8, "2", "H"},
	{"RES", 2, 8, 8, "2", "L"},
	{"RES", 2, 16, 16, "2", "(HL)"},
	{"RES", 2, 8, 8, "2", "A"},
	{"RES", 2, 8, 8, "3", "B"},
	{"RES", 2, 8, 8, "3", "C"},
	{"RES", 2, 8, 8, "3", "D"},
	{"RES", 2, 8, 8, "3", "E"},
	{"RES", 2, 8, 8, "3", "H"},
	{"RES", 2, 8, 8, "3", "L"},
	{"RES", 2, 16, 16, "3", "(HL)"},
	{"RES", 2, 8, 8, "3", "A"},
	{"RES", 2, 8, 8, "4", "B"},
	{"RES", 2, 8, 8, "4", "C"},
	{"RES", 2, 8, 8, "4", "D"},
	{"RES", 2, 8, 8, "4", "E"},
	{"RES", 2, 8, 8, "4", "H"},
	{"RES", 2, 8, 8, "4", "L"},
	{"RES", 2, 16, 16, "4", "(HL)"},
	{"RES", 2, 8, 8, "4", "A"},
	{"RES", 2, 8, 8, "5", "B"},
	{"RES", 2, 8, 8, "5", "C"},
	{"RES", 2, 8, 8, "5", "D"},
	{"RES", 2, 8, 8, "5", "E"},
	{"RES", 2, 8, 8, "5", "H"},
	{"RES", 2, 8, 8, "5", "L"},
	{"RES", 2, 16, 16, "5", "(HL)"},
	{"RES", 2, 8, 8, "5", "A"},
	{"RES", 2, 8, 8, "6", "B"},
	{"RES", 2, 8, 8, "6", "C"},
	{"RES", 2, 8, 8, "6", "D"},
	{"RES", 2, 8, 8, "6", "E"},
	{"RES", 2, 8, 8, "6", "H"},
	{"RES", 2, 8, 8, "6", "L"},
	{"RES", 2, 16, 16, "6", "(HL)"},
	{"RES", 2, 8, 8, "6", "A"},
	{"RES", 2, 8, 8, "7", "B"},
	{"RES", 2, 8, 8, "7", "C"},
	{"RES", 2, 8, 8, "7", "D"},
	{"RES", 2, 8, 8, "7", "E"},
	{"RES", 2, 8, 8, "7", "H"},
	{"RES", 2, 8, 8, "7", "L"},
	{"RES", 2, 16, 16, "7", "(HL)"},
	{"RES", 2, 8, 8, "7", "A"},
	{"SET", 2, 8, 8, "0", "B"},
	{"SET", 2, 8, 8, "0", "C"},
	{"SET", 2, 8, 8, "0", "D"},
	{"SET", 2, 8, 8, "0", "E"},
	{"SET", 2, 8, 8, "0", "H"},
	{"SET", 2, 8, 8, "0", "L"},
	{"SET", 2, 16, 16, "0", "(HL)"},
	{"SET", 2, 8, 8, "0", "A"},
	{"SET", 2, 8, 8, "1", "B"},
	{"SET", 2, 8, 8, "1", "C"},
	{"SET", 2, 8, 8, "1", "D"},
	{"SET", 2, 8, 8, "1", "E"},
	{"SET", 2, 8, 8, "1", "H"},
	{"SET", 2, 8, 8, "1", "L"},
	{"SET", 2, 16, 16, "1", "(HL)"},
	{"SET", 2, 8, 8, "1", "A"},
	{"SET", 2, 8, 8, "2", "B"},
	{"SET", 2, 8, 8, "2", "C"},
	{"SET", 2, 8, 8, "2", "D"},
	{"SET", 2, 8, 8, "2", "E"},
	{"SET", 2, 8, 8, "2", "H"},
	{"SET", 2, 8, 8, "2", "L"},
	{"SET", 2, 16, 16, "2", "(HL)"},
	{"SET", 2, 8, 8, "2", "A"},
	{"SET", 2, 8, 8, "3", "B"},
	{"SET", 2, 8, 8, "3", "C"},
	{"SET", 2, 8, 8, "3", "D"},
	{"SET", 2, 8, 8, "3", "E"},
	{"SET", 2, 8, 8, "3", "H"},
	{"SET", 2, 8, 8, "3", "L"},
	{"SET", 2, 16, 16, "3", "(HL)"},
	{"SET", 2, 8, 8, "3", "A"},
	{"SET", 2, 8, 8, "4", "B"},
	{"SET", 2, 8, 8, "4", "C"},
	{"SET", 2, 8, 8, "4", "D"},
	{"SET", 2, 8, 8, "4", "E"},
	{"SET", 2, 8, 8, "4", "H"},
	{"SET", 2, 8, 8, "4", "L"},
	{"SET", 2, 16, 16, "4", "(HL)"},
	{"SET", 2, 8, 8, "4", "A"},
	{"SET", 2, 8, 8, "5", "B"},
	{"SET", 2, 8, 8, "5", "C"},
	{"SET", 2, 8, 8, "5", "D"},
	{"SET", 2, 8, 8, "5", "E"},
	{"SET", 2, 8, 8, "5", "H"},
	{"SET", 2, 8, 8, "5", "L"},
	{"SET", 2, 16, 16, "5", "(HL)"},
	{"SET", 2, 8, 8, "5", "A"},
	{"SET", 2, 8, 8, "6", "B"},
	{"SET", 2, 8, 8, "6", "C"},
	{"SET", 2, 8, 8, "6", "D"},
	{"SET", 2, 8, 8, "6", "E"},
	{"SET", 2, 8, 8, "6", "H"},
	{"SET", 2, 8, 8, "6", "L"},
	{"SET", 2, 16, 16, "6", "(HL)"},
	{"SET", 2, 8, 8, "6", "A"},
	{"SET", 2, 8, 8, "7", "B"},
	{"SET", 2, 8, 8, "7", "C"},
	{"SET", 2, 8, 8, "7", "D"},
	{"SET", 2, 8, 8, "7", "E"},
	{"SET", 2, 8, 8, "7", "H"},
	{"SET", 2, 8, 8, "7", "L"},
	{"SET", 2, 16, 16, "7", "(HL)"},
	{"SET", 2, 8, 8, "7", "A"}
}};

#endif
