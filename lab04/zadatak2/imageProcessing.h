#ifndef IMAGEPROCESSING_H_
#define IMAGEPROCESSING_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct average_colors
{
	uint_least32_t R;
    uint_least32_t G;
	uint_least32_t B;
} AverageColors;


void adjustImageBrightness(uint_least8_t* iData, int_least32_t iWidth, int_least32_t iHeight, bool brighten, uint_least8_t adjustmentValue);

void bwImage(uint_least8_t* iData, int_least32_t iWidth, int_least32_t iHeight);

void effect(uint_least8_t* iData, int_least32_t iWidth, int_least32_t iHeight);

AverageColors* average_colors_f(uint_least8_t* iData, int_least32_t iWidth, int_least32_t iHeight, AverageColors* RGB);

void mean_filter(uint_least8_t* iData, int_least32_t iWidth, int_least32_t iHeight);

#endif /* IMAGEPROCESSING_H_ */
