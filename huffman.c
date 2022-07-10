#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "huffman.h"

void message()
{
    printf("Usage:\n\tcompress.exe <type> <filename>\n\ttype:\n\t\t-encode\n\t\t-decode\n\textension:\n\t\t.txt\n\t\t.huff\n\t\t.json\n");
}

int checkExtension(char *filename, char *extension)
{
    return strcmp(filename + strlen(filename) - strlen(extension), extension) == 0;
}

int fileExists(char *filename)
{
    struct stat st;
    return (stat(filename, &st) == 0);
}

int conditions(char *argv[])
{
    int flag = 0;
    if (fileExists(argv[2]) == 0)
    {
        printf("File doesn't exist\n");
        flag = 1;
    }
    else if (strcmp(argv[1], "-decode") == 0)
    {
        if (checkExtension(argv[2], ".huff") == 0)
        {
            printf("File extension is not .huff\n");
            flag = 1;
        }
    }
    else if (strcmp(argv[1], "-encode") == 0)
    {
        flag = 0;
    }
    else
    {
        printf("Invalid Flag\n");
        flag = 1;
    }
    return flag;
}

void process(char *argv[])
{
    if (strcmp(argv[1], "-encode") == 0)
    {
        NODE *head = NULL;
        encode(&(head), argv[2]);
    }
    else if (strcmp(argv[1], "-decode") == 0)
    {
        TABLE *head = NULL;
        decode(&(head), argv[2]);
    }
}


