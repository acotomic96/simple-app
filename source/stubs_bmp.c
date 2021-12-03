uint8_t* LoadBitmapFile(char* filename, BITMAPFILEHEADER* bitmapFileHeader, BITMAPINFOHEADER* bitmapInfoHeader)
{ 
	uint8_t* bitmapImage;
	bitmapImage = (uint8_t*)calloc(sizeof(uint8_t), bitmapInfoHeader->biSizeImage);
	return bitmapImage;
}
int_fast8_t SaveBitmapFile(char* filename, BITMAPFILEHEADER *bitmapFileHeader,
	BITMAPINFOHEADER *bitmapInfoHeader, uint8_t *bitmapImage)
{
	return 0;
}
