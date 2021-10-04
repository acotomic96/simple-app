#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

///////////////////////////////////////////////Encryption///////////////////////////////////////////////////

void encrypt(uint_least8_t* iData, int_least32_t iWidth, int_least32_t iHeight, char mes[], const char key[]);

uint_least8_t new_component(uint_least8_t iData, char bit_mes);

void converte_mes_to_binary(const char mes[], char binary_mes[], int_least16_t max_mes, int_least16_t size);

void add_length_mes_to_mes(int length_mes, char binary_mes[]);

///////////////////////////////////////////////Decryption///////////////////////////////////////////////////

int decrypt(uint_least8_t* iData, int_least32_t iWidth, int_least32_t iHeight, char mes_res[], const char key[]);

int read_length_mes(uint_least8_t* iData, int iHeight, int iWidth, const char key[]);

int_least8_t bin_to_int_digit(char in[], int_least8_t length);

char read_component(uint_least8_t iData);

void messages_finish(char mes_res_binary[], int_least16_t length_mes, char mes_fin[]);
