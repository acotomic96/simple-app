#include "imageProcessing.h"
#include "bmp.h"
#include <math.h>

void encrypt(uint_least8_t* iData, int_least32_t iWidth, int_least32_t iHeight, char mes[], const char key[])
{
    int_least32_t i;
    int_least32_t j;
    int_least32_t B = 2;

    int_least8_t length_mes = strlen(mes);
    int_least8_t max_mes = 8;
    int_least16_t size = length_mes * 8;
    size += max_mes;

    char binary_mes[size];

    add_length_mes_to_mes(length_mes, binary_mes);
    converte_mes_to_binary(mes, binary_mes, max_mes, size);

    int_least32_t bit_mes = 0;
    int_least8_t fib;
    int_least32_t pixel;

    for (i=0; i < iHeight; i++)
    {
        for (j=0; j < iWidth; j++)
        {
            pixel = (i * iWidth + j) % 35;
            if(pixel == 0)
                fib = 0;

            if(key[fib] == pixel && size != 0)
            {
                iData[i * iWidth * 3 + j * 3 + B] = new_component(iData[i * iWidth * 3 + j * 3 + B], binary_mes[bit_mes++]);
                fib++;
                size--;
            }

        }
    }

}

uint_least8_t new_component(uint_least8_t iData, char bit_mes)
{
    if(bit_mes)
        iData |= 0x01;
    else
        iData &= ~(0x01);

    return iData;
}

void converte_mes_to_binary(const char mes[], char binary_mes[], int_least16_t max_mes, int_least16_t size)
{
    int_least8_t i;
    int_least16_t k = max_mes;
    int_least16_t m = size / 8;

    for(int j = 0; j < m; j++)
    {
        int str_hex = (int)(mes[j]);
        for(i = 7; 0 <= i; i--)
        {
            binary_mes[k++] = (str_hex >> i) & 0x01;
        }
    }
}
void add_length_mes_to_mes(int length_mes, char binary_mes[])
{
    int_least8_t i;
    int_least16_t k = 0;

    for(i = 7; 0 <= i; i --)
    {
        binary_mes[k++] = (length_mes >> i) & 0x01;
    }

}

int decrypt(uint_least8_t* iData, int_least32_t iWidth, int_least32_t iHeight, char mes_res[], const char key[])
{
    int_least32_t i;
    int_least32_t j;
    int_least32_t B = 2;

    int_least8_t k = 0;
    int_least8_t fib;
    int_least16_t pixel;

    int_least8_t length_mes = read_length_mes(iData, iHeight, iWidth, key) + 8;
    char mes_res_binary[length_mes];

    int_least8_t length_mes2 = length_mes;

    for (i=0; i < iHeight; i++)
    {
        if(length_mes2 == 0)
            break;
        for (j=0; j < iWidth; j++)
        {
            pixel = (i * iWidth + j) % 35;
            if(pixel == 0)
                fib = 0;

            if(key[fib] == pixel && length_mes2 != 0)
            {
                mes_res_binary[k++] = read_component(iData[i * iWidth * 3 + j * 3 + B]);
                fib++;
                length_mes2--;
            }
            if(length_mes2 == 0)
                break;

        }
    }
    char mes_fin[length_mes/8];

    messages_finish(mes_res_binary, length_mes, mes_fin);

    int_least8_t m = 0;

    for(m = 0; m < length_mes / 8; m++)
        mes_res[m] = mes_fin[m];

    return ((length_mes / 8) - 1);
}

void messages_finish(char mes_res_binary[], int_least16_t length_mes, char mes_fin[])
{
    char pom[8];
    int_least8_t k = 0;
    int_least8_t j = 0;
    for(int i = 8; i < length_mes; i++)
    {
        pom[k++] = mes_res_binary[i];

        if(k == 8)
        {
            mes_fin[j++] = (char)(bin_to_int_digit(pom, 8));
            k = 0;
        }
    }
}
int read_length_mes(uint_least8_t* iData, int iHeight, int iWidth, const char key[])
{
    int_least32_t i;
    int_least32_t j;
    int_least32_t B = 2;

    char bit_mes[8];
    int_least16_t k = 0;
    int_least8_t fib;
    int_least32_t pixel;

    int_least8_t size = 8;

    for (i=0; i < iHeight; i++)
    {
        if(size == 0)
            break;
        for (j=0; j<iWidth; j++)
        {
            pixel = (i * iWidth + j) % 35;
            if(pixel == 0)
                fib = 0;

            if(key[fib] == pixel && size != 0)
            {
                bit_mes[k++] = read_component(iData[i * iWidth * 3 + j * 3 + B]);
                fib++;
                size--;
            }
            if(size == 0)
                break;
        }
    }
    int_least8_t length_mes = bin_to_int_digit(bit_mes, 8) * 8;

    return length_mes;
}

int_least8_t bin_to_int_digit(char in[], int_least8_t length)
{
    int_least8_t exp = 0;
    int_least8_t i;
    int_least32_t bin = 0;
    for (i = length - 1; i >= 0; i--)
    {
        bin += in[i] * pow(2, exp);
        exp += 1;
    }
    return bin;
}

char read_component(uint_least8_t iData)
{
    char bit_mes;

    bit_mes = iData & 0x01;

    return bit_mes;
}

