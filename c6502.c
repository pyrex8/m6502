#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "c6502.h"
#define CHIPS_IMPL
#include "m6502.h"

#define M6502_GET_RW(p) ((uint8_t)((p & M6502_RW)>>24))

static m6502_t cpu;
static uint64_t pins;

void c6502_init(void)
{
    pins = m6502_init(&cpu, &(m6502_desc_t){0});
}

void c6502_reset(C6502_interface *interface)
{
    pins |= M6502_RES;
}

void c6502_update(C6502_interface *interface)
{
    if (pins & M6502_RW)
    {
        M6502_SET_DATA(pins,interface->data);
    }
    pins = m6502_tick(&cpu, pins);
    interface->data = M6502_GET_DATA(pins);
    interface->address =  M6502_GET_ADDR(pins);
    interface->rw = M6502_GET_RW(pins);
}
