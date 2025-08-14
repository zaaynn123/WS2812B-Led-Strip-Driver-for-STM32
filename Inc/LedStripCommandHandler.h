/**
 * @file LedStripCommandHandler.h
 * 
 */
#include "LedStripProtocolHandler.h"

/**
 * @brief Brightness level to be set
 * 
 */
typedef enum {

    KHIGH = 45,
    KMEDIUM = 20,
    KLOW = 5,

}brightnessLevel;

/**
 * @brief The color to be sent to the LED on the Strip.
 * 
 */
typedef enum {

    KRED,
    KORANGE,
    KYELLOW,
    KGREEN,
    KBLUE,
    KINDIGO,
    KVOILET,
    KNONE,

}ledColor;

void LedSendColor(uint8_t ledNum, uint8_t intensity, uint8_t ledColor);
