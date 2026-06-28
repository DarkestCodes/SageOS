#ifndef FAULTHANDLERS_H
#define FAULTHANDLERS_H

#include <stdint.h>
#include "../../Headers/isr.h"



extern const char *exception_names[];


void exception_handler(registers_t *regs);

#endif