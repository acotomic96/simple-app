all: myapp

SRC_DIR = bmp.c
SRC_DIR2 = imageProcessing.c
INC_DIR = ./../include
	
myapp: bmp.c imageProcessing.c main_bitmap.c
	gcc -o myapp main_bitmap.c bmp.c imageProcessing.c -I$(INC_DIR) -lm

clean: 
	rm myapp

