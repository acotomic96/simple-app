#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "imageProcessing.h"

static const int ARG_NUM = 2;

int main(int argc, char* argv[])
{
    int_fast32_t err = 0;
    BITMAPFILEHEADER bitmapFileHeader;
    BITMAPINFOHEADER bitmapInfoHeader;
    uint_least8_t* bitmapData;
    char mes[50];
    char key[8] = {1, 2, 3, 5, 8, 13, 21, 34};
    char mes_res[50];
    // Check the input arguments
    if ( argc != ARG_NUM )
    {
    	printf("Enter input file path \n");
    	return EXIT_FAILURE;
    }
    printf("Messages: ");
    scanf("%s", mes);
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // Example #1 - Image encryption
    printf("Image encryption\n");

    // Load image
    //bitmapData = LoadBitmapFile(argv[1],&bitmapFileHeader, &bitmapInfoHeader);
    bitmapData = load_image(argv[1], bitmapData, &bitmapFileHeader, &bitmapInfoHeader);
    if(!bitmapData)
    {
    	printf("Error! Can't open input bitmap file: %s\n", argv[1]);
    	return EXIT_FAILURE;
    }

    // Invoke processing function
    encrypt(bitmapData, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, mes, key);

    // Save the result
    char *out = "out_image.bmp";
    err = save_image(bitmapData, out, &bitmapFileHeader, &bitmapInfoHeader);
    if (err)
    {
    	printf("Error trying to save bitmap\n");
    }

    // Free image data
    free(bitmapData);

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // Example #2 - Image decryption
    printf("Image decryption\n");

    // Load image

    bitmapData = load_image(out, bitmapData, &bitmapFileHeader, &bitmapInfoHeader);

    if(!bitmapData)
    {
        printf("Error! Can't open input bitmap file: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    int length_mes;

    // Invoke processing function
    length_mes = decrypt(bitmapData, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight, mes_res, key);

    printf("Decryption messages: %.*s\n", length_mes, mes_res);


    // Free image data
    free(bitmapData);

    return EXIT_SUCCESS;
}
