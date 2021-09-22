#include "imageProcessing.h"
#include "bmp.h"

static const uint_least8_t bwTreshold = 80;
const int_least16_t brightnessMinimum = 20;
const int_least16_t brightnessMaximum = 220;


void adjustImageBrightness(uint_least8_t* iData, int_least32_t iWidth, int_least32_t iHeight, bool brighten, uint_least8_t adjustmentValue)
{
	uint_least32_t i;
	int_least16_t newValue;

	for (i=0; i<iWidth*iHeight*3; i++)
	{
		newValue = iData[i];
		if(brighten)
		{
			newValue += adjustmentValue;
		}
		else
		{
			newValue -= adjustmentValue;
		}

		if(newValue < brightnessMinimum)
		{
			newValue = brightnessMinimum;
		}
		else if(newValue > brightnessMaximum)
		{
			newValue = brightnessMaximum;
		}

		iData[i] = newValue;
	}
}

void bwImage(uint_least8_t* iData, int_least32_t iWidth, int_least32_t iHeight)
{
	int_least32_t i;
	int_least32_t j;
	int_least32_t k;
	
	for (i=0; i<iHeight; i++)
	{
		for (j=0; j<iWidth; j++)
		{
			uint_least16_t sum = 0;
			for (k=0; k<3; k++)
			{
				sum += iData[i * iWidth * 3 + j * 3 + k];
			}
			sum = sum / 3;

			sum = (sum > bwTreshold)? 255 : 0;

			for (k=0; k<3; k++)
			{
				iData[i * iWidth * 3 + j * 3 + k] = sum;
			}
		}
	}
}

void effect(uint_least8_t* iData, int_least32_t iWidth, int_least32_t iHeight)
{
	int_least32_t i;
	int_least32_t j;
	uint_least8_t* ptr = iData;
	
	for (i=0; i<iHeight; i++)
	{
		for (j=0; j<iWidth; j++)
		{
			if(*ptr > *(ptr+1) && *ptr > *(ptr+2))
			{
				*ptr = 255;
				ptr++;
				*ptr = 0; 
				ptr++;
				*ptr = 0;
				ptr++;
			}
			else
			{
				*ptr = 0;
				ptr++;
				if(*ptr > *(ptr+1))
				{
					*ptr = 255;
					ptr++;
					*ptr = 0; 
					ptr++;
				}
				else
				{
					*ptr = 0;
					ptr++;
					*ptr = 255; 
					ptr++;
				}
			}
		}
	}
}

AverageColors* average_colors_f(uint_least8_t* iData, int_least32_t iWidth, int_least32_t iHeight, AverageColors *RGB)
{
	int_least32_t i;
	int_least32_t j;
	int_least32_t k;
	uint_least8_t* ptr = iData;
	
	uint_least32_t sumR = 0;
	uint_least32_t sumG = 0;
	uint_least32_t sumB = 0;
	
	for (i=0; i<iHeight; i++)
	{
		for (j=0; j<iWidth; j++)
		{
			
			sumR += *ptr;
			ptr++;
			sumG += *ptr;
			ptr++;
			sumB += *ptr;
			ptr++;
		}
	}
	uint_least32_t number_pixels = iHeight*iWidth;
	RGB->R = sumR / number_pixels;
	RGB->G = sumG / number_pixels;
	RGB->B = sumB / number_pixels;
	
	return RGB;
}

/*uint_least8_t get_i_j_pixel(uint_least8_t* iData, int_least32_t iWidth, int_least32_t iHeight, 
int_least32_t i, int_least32_t j, int_least32_t position_i, int_least32_t position_j)
{
	return iData[(i+position_i) * iWidth * 3 + (j+position_j) * 3 + k];
}*/
void mean_filter(uint_least8_t* iData, int_least32_t iWidth, int_least32_t iHeight)
{
	int_least32_t i;
	int_least32_t j;
	int_least32_t k;
	uint_least32_t sumR = 0;
	uint_least32_t sumG = 0;
	uint_least32_t sumB = 0;
	
	for (i=1; i<iHeight-1; i++)
	{
		for (j=1; j<iWidth-1; j++)
		{
			for (k=0; k<3; k++) 
			{
			if(k=0)
			sumR = (iData[(i-1) * iWidth * 3 + (j-1) * 3 + k] + iData[(i-1) * iWidth * 3 + j * 3 + k] + iData[(i-1) * iWidth * 3 + (j+1) * 3 + k] +
				   iData[i * iWidth * 3 + (j-1) * 3 + k] + iData[i * iWidth * 3 + j * 3 + k] + iData[i * iWidth * 3 + (j+1) * 3 + k] +
			       iData[(i+1) * iWidth * 3 + (j-1) * 3 + k] + iData[(i+1) * iWidth * 3 + j * 3 + k] + iData[(i+1) * iWidth * 3 + (j+1) * 3 + k])/9;
			if(k=1)
			sumG = (iData[(i-1) * iWidth * 3 + (j-1) * 3 + k] + iData[(i-1) * iWidth * 3 + j * 3 + k] + iData[(i-1) * iWidth * 3 + (j+1) * 3 + k] +
				   iData[i * iWidth * 3 + (j-1) * 3 + k] + iData[i * iWidth * 3 + j * 3 + k] + iData[i * iWidth * 3 + (j+1) * 3 + k] +
			       iData[(i+1) * iWidth * 3 + (j-1) * 3 + k] + iData[(i+1) * iWidth * 3 + j * 3 + k] + iData[(i+1) * iWidth * 3 + (j+1) * 3 + k])/9;
			if(k=2)
			sumB = (iData[(i-1) * iWidth * 3 + (j-1) * 3 + k] + iData[(i-1) * iWidth * 3 + j * 3 + k] + iData[(i-1) * iWidth * 3 + (j+1) * 3 + k] +
				   iData[i * iWidth * 3 + (j-1) * 3 + k] + iData[i * iWidth * 3 + j * 3 + k] + iData[i * iWidth * 3 + (j+1) * 3 + k] +
			       iData[(i+1) * iWidth * 3 + (j-1) * 3 + k] + iData[(i+1) * iWidth * 3 + j * 3 + k] + iData[(i+1) * iWidth * 3 + (j+1) * 3 + k])/9;
			}      
			for (k=0; k<3; k++)
			{
				if(k=0)
				iData[i * iWidth * 3 + j * 3 + k] = sumR;
				if(k=1)
				iData[i * iWidth * 3 + j * 3 + k] = sumG;
				if(k=2)
				iData[i * iWidth * 3 + j * 3 + k] = sumB;
			}
		}
	}
}
