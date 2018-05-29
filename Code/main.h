#ifndef __STM32F4_UB_MAIN_H
#define __STM32F4_UB_MAIN_H


#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_dma.h"

#include <stdio.h>
#include <stdlib.h>

#include "string.h"
#include "uart.h"

#include "stm32_ub_vga_screen.h"
//#include "APIdraw.h"

#include "front_layer.h"
#include "logic_layer.h"
#include "io_layer.h"

/* Zet debug aan om de werking van de functies in front layer te controleren*/
#define DEBUG_USER_INPUT 1

#endif // __STM32F4_UB_MAIN_H




