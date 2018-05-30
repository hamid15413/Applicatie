/* includes */
#include "main.h"

/**
 * @brief 	Het initialiseren van de VGA module
 * @param 	Geen
 * @retval	Geen
 */
void init_VGA_API()
{
	UB_VGA_Screen_Init();
}

/**
 * @brief	Het initialiseren van UART
 * @param	Geen
 * @retval	Geen
 */
void init_UART_API()
{
	UART_init();
}

/**
 * @brief	instellen van microcontoller systeem
 * @param	Geen
 * @retval	Geen
 */
void init_system_API()
{
	SystemInit();
}

