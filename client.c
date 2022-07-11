#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

/*gcc -Wall -save-temps "client.c" "encode.c" "decode.c" "huffman.c" -o "Huffman.exe"*/

int main(int argc, char *argv[])
{
    argc == 3 ? (conditions(argv) ? exit(EXIT_FAILURE) : process(argv)) : message();
    exit(EXIT_FAILURE);
}
