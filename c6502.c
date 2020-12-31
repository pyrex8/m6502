#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "c6502.h"
#include "m6502.h"

m6502_t cpu;
uint64_t pins;

#define M6502_GET_RW(a) (((a) & M6502_RW) ? 1 : 0)

void c6502_init(void)
{
    pins = m6502_init(&cpu, &(m6502_desc_t){ });
}

void c6502_deinit(void)
{
    // nothing here for now
}

void c6502_update(C6502_interface *interface)
{
    pins = m6502_tick(&cpu, pins);

    interface->data = M6502_GET_DATA(pins);
    interface->address =  M6502_GET_ADDR(pins);
    interface->rw = M6502_GET_RW(pins);
}