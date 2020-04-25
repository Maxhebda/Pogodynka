#include "board.h"
#include "bme280.h"

/*
 * 1.19 SSEL
 * 1.20 SCK
 * 1.21 MISO
 * 1.22 MOSI
 
 teraz wazne. zepnij kablami i uruchom w trybie debug (ustaw sobie breakpoint na printf w funkcji wysylajacej i dodaj semihost w opcjach). jak uruchomisz debugowanie i przejdziesz do dwoch printfow w funkcji to powinno ci  wkonsoli wywyalic z pierwszego printfa wartosc 0, z drugiego 96. jak tak bedzie to komunikacja dziala jak talala
 
 */

static inline void setSSELLow(void)
{
	Chip_GPIO_SetPinOutLow(LPC_GPIO_PORT, 1, 19);
}

static inline void setSSELHigh(void)
{
	Chip_GPIO_SetPinOutHigh(LPC_GPIO_PORT, 1, 19);
}

static inline void sendFrame(uint16_t frame) {
	setSSELLow();
	while(!Chip_SSP_GetStatus(LPC_SSP1, SSP_STAT_TNF));
	Chip_SSP_SendFrame(LPC_SSP1, frame);
	Chip_SSP_SendFrame(LPC_SSP1, 0);
	while(Chip_SSP_GetStatus(LPC_SSP1, SSP_STAT_BSY));
	setSSELHigh();

	printf("Chip response is: %d", LPC_SSP1->DR);
	printf("Chip response is: %d", LPC_SSP1->DR);
}

int main(void)
{
	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();

	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 19, IOCON_FUNC0);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 1, 19);
	setSSELHigh();

	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 20, (IOCON_FUNC2 | IOCON_MODE_PULLUP));
	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 21, (IOCON_FUNC2 | IOCON_MODE_PULLUP));
	Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 22, (IOCON_FUNC2 | IOCON_MODE_PULLUP));

	Chip_SSP_Init(LPC_SSP1);
	Chip_SSP_SetMaster(LPC_SSP1, 1);
	Chip_SSP_SetClockRate(LPC_SSP1, 4, 254);
	Chip_SSP_SetFormat(LPC_SSP1, SSP_BITS_8, SSP_FRAMEFORMAT_SPI, SSP_CLOCK_CPHA0_CPOL0);
	Chip_SSP_Enable(LPC_SSP1);

	sendFrame(0xD0 | 1 << 8);

	while (1) {
		__WFI();
	}
}
