/**
 * @file LedStripCommandHandler.c
 * 
 */
#include <stdio.h>
#include <stdint.h>
#include "tim.h"
#include "LedStripCommandHandler.h"

/**
 * @brief Abstraction function that set the LED on the strip to a particular Color and brightness.
 * 
 * @param ledNum 
 * @param intensity 
 * @param ledColor 
 */
void LedSendColor(uint8_t ledNum, uint8_t intensity, uint8_t ledColor)
{
     LedStripHandler(ledNum, intensity, ledColor);
}