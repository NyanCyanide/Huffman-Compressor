#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

/*gcc -o "huffman" "client.c" "huffman.c" "encode.c"*/

int main(int argc, char *argv[])
{
    argc == 3 ? (conditions(argv) ? exit(EXIT_FAILURE) : process(argv)) : message() ; exit(EXIT_FAILURE);
}
