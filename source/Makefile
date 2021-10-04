all: myapp

SRC_DIR = bmp.c
SRC_DIR2 = imageProcessing.c
INC_DIR = ./../include
	
myapp: bmp.o imageProcessing.o main_bitmap.o
	gcc -o app main_bitmap.o bmp.o imageProcessing.o -I$(INC_DIR) -lm

bmp.o: $(SRC_DIR)
	gcc -c $(SRC_DIR) -I$(INC_DIR)

imageProcessing.o: $(SRC_DIR2)
	gcc -c $(SRC_DIR2) -I$(INC_DIR)

main_bitmap.o: main_bitmap.c
	gcc -c main_bitmap.c -I$(INC_DIR)

clean: 
	rm myapp

