#
# Small makefile
#
CC = g++

HyperboloideVBOShader: projetimage.o shader.o
	$(CC) -o projetimage projetimage.o shader.o -lGL -lGLU -lGLEW -lglut -lm
	./projetimage
all: projetimage

#Compilation avec Cygwin
#g++ -std=c++1y projetimage.cpp shader.cpp -lGL -lGLU -lGLEW -lglut -lm
#startxwin ./a.exe
