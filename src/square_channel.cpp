#include "square_channel.hpp"
#include <cstdint>

using namespace gameboy;

void Square_channel::tick(size_t cycles)
{
    timer_ -= cycles;
    if (timer_ <= 0)
    {
        timer_ = freq() + timer_; // reload timer when it hits zero
        duty_ptr_ = (duty_ptr_ + 1) & 7;
    }
    // check if enabled and DAC enabled
    if (enabled_ && (ff17_ & 0xf8) != 0)
        output_ = volume_;
    else
        output_ = 0;
    if (!DUTY_PATTERNS[duty_pattern()][duty_ptr_])
        output_ = 0;
}

uint8_t Square_channel::read_reg(uint16_t adr)
{
    uint8_t b = 0xff;
    switch (adr)
    {
        case 0xff16: b = ff16_; break;
        case 0xff17: b = ff17_; break;
        case 0xff18: b = ff18_; break;
        case 0xff19: b = ff19_; break;
    }
    return b;
}

void Square_channel::write_reg(uint8_t b, uint16_t adr)
{
    switch (adr)
    {
        case 0xff16: ff16_ = b; break;
        case 0xff17: ff17_ = b; break;
        case 0xff18: ff18_ = b; break;
        case 0xff19: ff19_ = b; break;
    }
}

void Square_channel::length_tick()
{
    bool length_enable = ff19_ & (1 << 6);
    if (length_timer_ > 0 && length_enable)
    {
        --length_timer_;
        if (length_timer_ == 0)
            enabled_ = false;
    }
}

void Square_channel::envelope_tick()
{
    if (--envelope_timer_ <= 0)
    {
        // reload
        uint8_t env_initial = ff17_
        envelope_timer_ =
    }
}

uint8_t Square_channel::volume()
{
    return output_;
}

uint16_t Square_channel::freq()
{
    uint16_t f = static_cast<uint16_t>((ff19_ & 3) << 8 | ff18_);
    return (2048-f)*4;
}

uint8_t Square_channel::duty_pattern()
{
    return ff16_ >> 6;
}
