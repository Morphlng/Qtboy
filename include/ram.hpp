#pragma once

#include <array>
#include <vector>

#include "debug_types.hpp"

namespace qtboy
{

template <uint16_t bank_sz>
class Ram
{
    public:
    static const uint16_t BANK_SIZE = bank_sz;
	using Bank = std::array<uint8_t, bank_sz>; // 8 KB
    explicit Ram(uint8_t banks = 0,
                 const std::vector<uint8_t> &load = {});

	uint8_t read(uint8_t bank, uint16_t adr) const;
    void write(uint8_t b, uint8_t bank, uint16_t adr);
    void load(const std::vector<uint8_t> &load);
    std::vector<uint8_t> dump(uint8_t bank) const; // dump one bank
    std::vector<uint8_t> dump() const; // dump all banks
	void resize(uint8_t nbanks);
    size_t size() const;
    void reset();
	
	private:
    std::vector<Bank> data_ {};
	
};

// explicit template instantiations
extern template class Ram<0x2000>;
extern template class Ram<0x1000>;

using Work_ram = Ram<0x1000>;
using Video_ram = Ram<0x2000>;
using External_ram = Ram<0x2000>;

	
}
