main: main.c
		mkdir -p build
		gcc main.c bmp_io.c bmp_rotation.c -o build/main -std=c18 -pedantic -Wall -Werror