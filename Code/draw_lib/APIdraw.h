//------------------------------------------------------------------------
//  File:   APIdraw.h
//------------------------------------------------------------------------

//------------------------------------------------------------------------
#ifndef APIdraw_h
#define APIdraw_h
//------------------------------------------------------------------------

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "misc.h"
#include "stm32f4xx_dma.h"
#include "stm32_ub_vga_screen.h"

//--------------------------------------------------------------
// color designation
// 8bit color (R3G3B2)
// Red   (3bit) -> Bit7-Bit5
// Green (3bit) -> Bit4-Bit2
// Blue  (2bit) -> Bit1-Bit0
//--------------------------------------------------------------
#define 	ZWART          	0x00
#define 	WIT          	0xFF
#define 	GRIJS			0X4D
#define 	BLAUW          	0x03
#define 	LICHT_BLAUW		0X73
#define 	GROEN          	0x1C
#define		LICHT_GROEN		0X1D
#define 	ROOD           	0xE0
#define		LICHT_ROOD		0XE9
#define 	CYAAN          	0x1F
#define		LICHT_CYAAN		0X9B
#define 	MAGENTA        	0xE3
#define		LICHT_MAGENTA	0XEE
#define 	GEEL         	0xFC
#define		BRUIN			0X68

//------------------------------------------------------------------------
#endif // APIdraw_h
