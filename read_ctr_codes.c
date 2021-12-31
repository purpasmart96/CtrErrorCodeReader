// Copyright(c) 2016 Purpasmart
// The MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#ifndef u8
typedef uint8_t u8;
#endif
#ifndef s8
typedef int8_t s8;
#endif
#ifndef u16
typedef uint16_t u16;
#endif
#ifndef s16
typedef int16_t s16;
#endif
#ifndef u32
typedef uint32_t u32;
#endif
#ifndef s32
typedef int32_t s32;
#endif
#ifndef u64
typedef uint64_t u64;
#endif
#ifndef s64
typedef int64_t s64;
#endif


// Self reminder about bits
// & 1 // the last bit.
// & 0x3 // the last two bits
// & 0x7 // the last three bits.
// & 0xF // the last four bits.
// & 0x1F // the last five bits.
// & 0x3F // the last six bits.
// & 0x7F // the last seven bits.
// & 0xFF // the last eight bits.
// & 0x1FF // the last nine bits
// & 0x3FF // the last ten bits
// & 0x7FF // the last eleven bits
// & 0xFFF // the last twelve bits.
// & 0x1FFF // the last thrirteen bits


static u32 GetDescriptionBits(u32 hex)
{
    return hex & 0x3FF;
}

static u32 GetModuleBits(u32 hex)
{
    return (hex >> 10) & 0xFF;
}

static u32 GetSummaryBits(u32 hex)
{
    return (hex >> 21) & 0x3F;
}

static u32 GetLevelBits(u32 hex)
{
    return (hex >> 27) & 0x1F;
}

static bool HandleIsProcess(u32 hex)
{
    return hex & 1;
}

static u16 GetSlot(u32 handle)
{
    return handle >> 15;
}

static u16 GetGeneration(u32 handle)
{
    return handle & 0x7FFF;
}

static void ReadErrorCode(u32 code)
{
    u32 description = GetDescriptionBits(code);
    u32 module = GetModuleBits(code);
    u32 summary = GetSummaryBits(code);
    u32 level = GetLevelBits(code);

    printf("ErrorCode:                          0x%08X\n", code);
    printf("Description:                        %d\n", description);
    printf("Module:                             %d\n", module);
    printf("Summary:                            %d\n", summary);
    printf("Level:                              %d\n", level);
}

static void ReadHandle(u32 handle)
{
    u16 slot        =  GetSlot(handle);
    u16 generation  =  GetGeneration(handle);
    bool is_process =  HandleIsProcess(handle);

    printf("Handle:                             0x%08X\n", handle);
    printf("Slot:                               0x%04X\n", slot);
    printf("Generation:                         0x%04X\n", generation);
    printf("Process:                            %d\n", is_process);
}


int main(int argc, char *argv[])
{
    u32 error_code = strtoul(argv[1], NULL, 0);
    ReadErrorCode(error_code);
    //u32 handle = strtoul(argv[1], NULL, 0);
    //ReadHandle(handle);

    return 0;
}
