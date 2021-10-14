#ifndef _C6502_H_
#define _C6502_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
// pins
uint8_t     data;
uint16_t    address;
bool        rw;
bool        sync;
bool        irq;
bool        nmi;
bool        rdy;
bool        res;
bool        clk0;
// registers
uint8_t     ir; // instruction register
uint8_t     c;  // instruction cycle count
uint8_t     a;
uint8_t     x;
uint8_t     y;
uint8_t     p;
uint8_t     s;
uint16_t    pc;
} C6502_interface;

void c6502_init(void);
void c6502_deinit(void);
void c6502_reset(C6502_interface *interface);
void c6502_update(C6502_interface *interface);

#endif /* _C6502_ */
