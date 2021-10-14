#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "c6502.h"
#define CHIPS_IMPL
#include "m6502.h"

#define M6502_GET_RW(p) ((uint8_t)((p & M6502_RW)>>24))
#define M6502_GET_SYNC(p) ((uint8_t)((p & M6502_SYNC)>>25))
#define M6502_GET_IRQ(p) ((uint8_t)((p & M6502_IRQ)>>26))
#define M6502_GET_NMI(p) ((uint8_t)((p & M6502_NMI)>>27))
#define M6502_GET_RDY(p) ((uint8_t)((p & M6502_RDY)>>28))
#define M6502_GET_RES(p) ((uint8_t)((p & M6502_RES)>>30))

#define M6502_SET_RES(p) ((uint8_t)((p & M6502_RES)>>30))

static m6502_t cpu;
static uint64_t pins;

void c6502_init(void)
{
    pins = m6502_init(&cpu, &(m6502_desc_t){0});
}

void c6502_deinit(void)
{
    // nothing here for now
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
    interface->sync = M6502_GET_SYNC(pins);
    interface->irq = M6502_GET_IRQ(pins);
    interface->nmi = M6502_GET_NMI(pins);
    interface->rdy = M6502_GET_RDY(pins);
    interface->res = M6502_GET_RES(pins);
    interface->a = m6502_a(&cpu);
    interface->x = m6502_x(&cpu);
    interface->y = m6502_y(&cpu);
    interface->s = m6502_s(&cpu);
    interface->p = m6502_p(&cpu);
    interface->pc = m6502_pc(&cpu);
    interface->ir = cpu.IR >> 3;
    interface->c = cpu.IR & 0x07;
}
