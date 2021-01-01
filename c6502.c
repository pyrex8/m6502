#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "c6502.h"
#define CHIPS_IMPL
#include "m6502.h"

m6502_t cpu;
uint64_t pins;

#define M6502_GET_RW(a) (((a) & M6502_RW) ? 1 : 0)

void c6502_init(void)
{
    pins = m6502_init(&cpu, &(m6502_desc_t){ });
    pins |= (0x5DULL<<24); 
}

void c6502_deinit(void)
{
    // nothing here for now
}

void c6502_update(C6502_interface *interface)
{
    M6502_SET_DATA(pins,interface->data);
    pins = m6502_tick(&cpu, pins);
    interface->data = M6502_GET_DATA(pins);
    interface->address =  M6502_GET_ADDR(pins);
    interface->rw = M6502_GET_RW(pins);
//    printf("control c6502 = %02X\n", ((pins >> 24)& 0xFF));
}