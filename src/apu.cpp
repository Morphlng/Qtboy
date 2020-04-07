#include "apu.hpp"
#include "system.hpp"
#include "speaker.hpp"

#include <vector>

using namespace gameboy;

void Apu::reset()
{
    square1_ = {};
    audio_ = Raw_audio<uint8_t>(2048);
    volume_ = 0x77;
    output_ = 0xf3;
    enable_ = 0xf1;
    downsample_cnt_ = DOWNSAMPLE_FREQ;
}

void Apu::tick(size_t cycles)
{
    while (cycles-- > 0)
    {
        square1_.tick(1);
        // take a sample only once ever DOWNSAMPLE_FREQ cycles
        if (--downsample_cnt_<= 0)
        {
            downsample_cnt_ = DOWNSAMPLE_FREQ;
            audio_.push(square1_.volume());
            if (audio_.size() >= SAMPLE_SIZE)
                speaker_->push_samples(audio_);
        }
    }
}

uint8_t Apu::read_reg(uint16_t adr)
{
    uint8_t b = 0xff;
    if (adr > 0xff14 && adr < 0xff1a)
        b = square1_.read_reg(adr);
    else if (adr == 0xff24)
        b = volume_;
    else if (adr == 0xff25)
        b = output_;
    else if (adr == 0xff26)
        b = enable_;
    return b;
}

void Apu::write_reg(uint8_t b, uint16_t adr)
{
    if (adr > 0xff14 && adr < 0xff1a)
        square1_.write_reg(b, adr);
    else if (adr == 0xff24)
        volume_ = b;
    else if (adr == 0xff25)
        output_ = b;
    else if (adr == 0xff26)
        enable_ = (b >> 7) ? 0xff : enable_; // only bit 7 is writable, sets all
}

void Apu::set_speaker(Speaker *s)
{
    speaker_ = s;
}

