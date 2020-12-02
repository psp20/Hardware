#pragma once
#include <stdint.h>

using namespace std;

namespace V4
{
    enum class SteinOwner
    {
        NONE    = 'N',
        RED     = 'R',
        YELLOW  = 'Y'
    };

    struct Stein
    {
        Stein(SteinOwner _owner = SteinOwner::NONE, uint8_t _row = 0, uint8_t _col = 0);

        SteinOwner owner;
        uint8_t row, col;
    };

} // namespace V4
