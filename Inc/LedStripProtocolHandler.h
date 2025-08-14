/**
 * @file LedStripProtocolHandler.h
 * 
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "math.h"
#include "tim.h"

#define LED_MAX          4
#define PI               3.14159265

void LedStripSetLed (uint8_t ledNum, uint8_t red, uint8_t green, uint8_t blue);
void LedStripSetBrightness (uint8_t ledNum, uint8_t brightness);
void LedStripSendColor (void);
void LedStripHandler(uint8_t ledNum, uint8_t intensity, uint8_t ledColor);
