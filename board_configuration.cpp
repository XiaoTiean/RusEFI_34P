#include "pch.h"
#include "defaults.h"
#include "34P_meta.h"
#include "board_overrides.h"

Gpio getCommsLedPin() {
	return Gpio::Unassigned;
}

Gpio getRunningLedPin() {
	return Gpio::Unassigned;
}

Gpio getWarningLedPin() {
	return Gpio::Unassigned;
}

// board-specific configuration setup
static void customBoardDefaultConfiguration() {
    engineConfiguration->injectionPins[0] = Gpio::Unassigned;
	engineConfiguration->injectionPins[1] = Gpio::Unassigned;
	engineConfiguration->injectionPins[2] = Gpio::Unassigned;
	engineConfiguration->injectionPins[3] = Gpio::Unassigned;
	
    engineConfiguration->ignitionPins[0] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[1] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[2] = Gpio::Unassigned;
	engineConfiguration->ignitionPins[3] = Gpio::Unassigned;
//====================================================================//
	#ifdef EFI_KLINE
    if (!engineConfiguration->enableKline) {
        return;
    }
#if EFI_PROD_CODE
    efiSetPadMode("K-Line UART RX", Gpio::A10, PAL_MODE_ALTERNATE(TS_SERIAL_AF));
    efiSetPadMode("K-Line UART TX", Gpio::A9, PAL_MODE_ALTERNATE(TS_SERIAL_AF));
#endif /* EFI_PROD_CODE */
 
    static SerialConfig cfg = {
        #if EFI_PROD_CODE
            .speed = 0,
            .cr1 = 0,
            .cr2 = USART_CR2_STOP1_BITS | USART_CR2_LINEN,
            .cr3 = 0
        #endif // EFI_PROD_CODE
    };
 
    if (engineConfiguration->kLineBaudRate < 100)
        engineConfiguration->kLineBaudRate = KLINE_BAUD_RATE;
    cfg.speed = engineConfiguration->kLineBaudRate;
 
    sdStart(klDriver, &cfg);
#endif // EFI_KLINE
	
//====================================================================//
	
//  engineConfiguration->triggerInputPins[0] = Gpio::B1;
//	engineConfiguration->triggerInputPins[1] = Gpio::Unassigned;

//	engineConfiguration->map.sensor.hwChannel = EFI_ADC_3;

//	engineConfiguration->clt.adcChannel = EFI_ADC_1;

//	engineConfiguration->iat.adcChannel = EFI_ADC_2;


    // 470 high side/910 low side = 1.56 ratio divider
 	engineConfiguration->analogInputDividerCoefficient = 1.936f;

    // 10k high side/ 1k low side
  	engineConfiguration->vbattDividerCoeff = (10 + 1) / 1;
	
	// ADC voltage referent
	engineConfiguration->adcVcc = 3.3f;

	engineConfiguration->clt.config.bias_resistor = 2400;
	engineConfiguration->iat.config.bias_resistor = 2400;

	
}
/**
static Gpio 34P_OUTPUTS[] = {
34P_LSHC_1,
34P_LSHC_2,
34P_LSHC_3,
34P_LSHC_4,
34P_LSHV_1,
34P_LSHV_2,
34P_LSHV_3,
34P_LSHV_4,
34P_GPIO_1,
34P_GPIO_2,
34P_GPIO_3,
34P_GPIO_4,
34P_GPIO_5,
34P_GPIO_6,
};
*/
void setup_custom_board_overrides() {
    custom_board_DefaultConfiguration = customBoardDefaultConfiguration;
}
