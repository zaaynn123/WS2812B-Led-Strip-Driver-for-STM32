/**
 * @file LedStripProtocolHandler.c
 * 
 */
#include "LedStripProtocolHandler.h"
#include <stdbool.h>


uint8_t LED_Data[LED_MAX][4];
uint8_t LED_Mod[LED_MAX][4];
uint16_t pwmData[(24*LED_MAX)+50];

bool datasentflag = false;
/**
 * @brief Different Color Schemes used in the LED
 * 
 */
uint8_t ColorChannel [8][3] = {{255,0,0}, {255,100,0}, {255,200,0},{0,255,0},{0,0,255},{75,0,130},{148,0,211},{0,0,0}};

/**
 * @brief This function sets a particular LED in the Strip to a Color with its RGB value.
 * 
 * @param ledNum 
 * @param red 
 * @param green 
 * @param blue 
 */
void LedStripSetLed (uint8_t ledNum, uint8_t red, uint8_t green, uint8_t blue)
{
	LED_Data[ledNum][0] = ledNum;
	LED_Data[ledNum][1] = green;
	LED_Data[ledNum][2] = red;
	LED_Data[ledNum][3] = blue;
}

/**
 * @brief This fuction sets the Brightness of a particular LED on the strip
 * 
 * @param ledNum 
 * @param brightness 
 */
void LedStripSetBrightness (uint8_t ledNum, uint8_t brightness)  // 0-45
{
	if (brightness > 45) brightness = 45;
		LED_Mod[ledNum][0] = LED_Data[ledNum][0];
		for (int j=1; j<4; j++)
		{
			float angle = 90-brightness;  // in degrees
			angle = angle*PI / 180;  // in rad
			LED_Mod[ledNum][j] = (LED_Data[ledNum][j])/(tan(angle));
		}
}

/**
 * @brief This function sends the color selected toward the LED Strip by mimicking the particular 1's and 0's required for a color using PWM
 * 
 */
void LedStripSendColor (void)
{
	uint32_t indx=0;
	uint32_t color;


	for (int i= 0; i<LED_MAX; i++)
	{
		color = ((LED_Mod[i][1]<<16) | (LED_Mod[i][2]<<8) | (LED_Mod[i][3]));
		for (int i=23; i>=0; i--)
		{
			if (color&(1<<i))
			{
				pwmData[indx] = 15;  // 3/4 of 20
			}

			else pwmData[indx] = 5;  // 1/4 of 20

			indx++;
		}

	}

	for (int i=0; i<50; i++)
	{
		pwmData[indx] = 0;
		indx++;
	}

	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)pwmData, indx);
	while (!datasentflag){};
	datasentflag = false;
}

/**
 * @brief This functions takes the particular color and brightness level of a particular Led on the strip
 * 
 * @param ledNum 
 * @param intensity 
 * @param ledColor 
 */
void LedStripHandler(uint8_t ledNum, uint8_t intensity, uint8_t ledColor)
{
    uint8_t * color = ColorChannel[ledColor];
    LedStripSetLed(ledNum, color[0], color[1], color[2]);
    LedStripSetBrightness(ledNum, intensity);
    LedStripSendColor();
}

/**
 * @brief This is a particular callback function used to stop the DMA to stop the tranmission of PWM signal for a colors on LED
 * 
 * @param htim 
 */
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
	datasentflag = true;
}
