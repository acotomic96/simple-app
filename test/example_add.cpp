#include <gtest/gtest.h>

#include "example.h"
#include "imageProcessing.h"
#include "bmp.h"

///////////////////////////////////////////////Encryption///////////////////////////////////////////////////

TEST(imageProcessing, encrypt) {
  uint_least8_t bitmapData[420] = {0};
  uint_least8_t res[420] = {0};
  char mes[50] = "aco";
  const char key[8] = {1, 2, 3, 5, 8, 13, 21, 34};
  
  int_least32_t iWidth = 7;
  int_least32_t iHeight = 20;
  
  res[65] = 1;
  res[104] = 1;
  res[113] = 1;
  res[116] = 1;
  res[209] = 1;
  res[218] = 1;
  res[221] = 1;
  res[275] = 1;
  res[314] = 1;
  res[323] = 1;
  res[326] = 1;
  res[341] = 1;
  res[356] = 1;
  res[380] = 1;
  res[419] = 1;
  uint_least8_t* iData = bitmapData;

  encrypt(iData, iWidth, iHeight, mes, key);
  
  for(int i = 0; i < iWidth*iHeight*3; i++)
	ASSERT_EQ(res[i], bitmapData[i]);
}


TEST(imageProcessing, new_component) {
  uint_least8_t res;
  uint_least8_t iData = 200;
  char bit_mes = 0;
  res = new_component(iData, bit_mes);
  ASSERT_EQ(res, 200);
}

TEST(imageProcessing, add_length_mes_to_mes) {
  char res[8];
  int size = 7;	
  add_length_mes_to_mes(size, res);

  char ok[8] = {0, 0, 0, 0, 0, 1, 1, 1};

  for(int i = 0; i < 8; i++)
      ASSERT_EQ(res[i], ok[i]);
}

TEST(imageProcessing, converte_mes_to_binary) {
  char res[16];
  const char mes[] = "a";
  int_least16_t max_mes = 8; 
  int_least16_t size = 16;	
  converte_mes_to_binary(mes, res, max_mes, size);

  char ok[16] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1};

  for(int i = max_mes; i < 16; i++)
     ASSERT_EQ(res[i], ok[i]);
}

///////////////////////////////////////////////Decryption///////////////////////////////////////////////////

TEST(imageProcessing, decrypt) {
  uint_least8_t bitmapData[420] = {0};
  char res[5] = "aco";
  char mes[5];
  const char key[8] = {1, 2, 3, 5, 8, 13, 21, 34};
  
  int_least32_t iWidth = 7;
  int_least32_t iHeight = 20;
  
  bitmapData[65] = 1;
  bitmapData[104] = 1;
  bitmapData[113] = 1;
  bitmapData[116] = 1;
  bitmapData[209] = 1;
  bitmapData[218] = 1;
  bitmapData[221] = 1;
  bitmapData[275] = 1;
  bitmapData[314] = 1;
  bitmapData[323] = 1;
  bitmapData[326] = 1;
  bitmapData[341] = 1;
  bitmapData[356] = 1;
  bitmapData[380] = 1;
  bitmapData[419] = 1;

  uint_least8_t* iData = bitmapData;

  int k = decrypt(bitmapData, iWidth, iHeight, mes, key);
  
  for(int i = 0; i < k; i++)
	ASSERT_EQ(res[i], mes[i]);
}


TEST(imageProcessing, bin_to_int_digit) {
  char in[] = {0, 1, 1, 0, 0, 0, 0, 1};
  int_least8_t length = 8;
  int_least32_t res;	
  res = bin_to_int_digit(in, length);

  int ok = 97;

  ASSERT_EQ(res, ok);
}

TEST(imageProcessing, read_component) {
  int_least8_t iData = 200;
  int_least32_t res;	
  res = read_component(iData);

  int ok = 0;

  ASSERT_EQ(res, ok);
}

TEST(imageProcessing, messages_finish) {
  char mes_res_binary[] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1};
  int_least16_t length_mes = 16;
  int size = length_mes/8;
  char res[size];	
  messages_finish(mes_res_binary, length_mes, res);

  char ok[] = {'a'};

  for(int i = 0; i < size-1; i++)
     ASSERT_EQ(res[i], ok[i]);
}

TEST(imageProcessing, read_length_mes) {
  uint_least8_t bitmapData[420] = {0};
  char mes[5];
  const char key[8] = {1, 2, 3, 5, 8, 13, 21, 34};
  
  int_least32_t iWidth = 7;
  int_least32_t iHeight = 20;
  
  bitmapData[65] = 1;
  bitmapData[104] = 1;
  
  uint_least8_t* iData = bitmapData;

  int res = read_length_mes(bitmapData, iWidth, iHeight, key);

  ASSERT_EQ(res, 24);
}

TEST(imageProcessing, load_image) {

  char *argv1 = "Image.bmp";
  uint_least8_t bitmapData[420] = {0};
  BITMAPFILEHEADER * bitmapFileHeader; 
  BITMAPINFOHEADER * bitmapInfoHeader;
  
  uint_least8_t* res = load_image(argv1, bitmapData, bitmapFileHeader, bitmapInfoHeader);

  for(int i = 0; i < 420; i++)
     ASSERT_EQ(res[i], bitmapData[i]);
}

TEST(imageProcessing, save_image) {

  char *out = "Image_out.bmp";
  uint_least8_t bitmapData[420] = {0};
  BITMAPFILEHEADER * bitmapFileHeader; 
  BITMAPINFOHEADER * bitmapInfoHeader;
  
  int_fast32_t res = save_image(bitmapData, out, bitmapFileHeader, bitmapInfoHeader);

  ASSERT_EQ(res, 0);
}


