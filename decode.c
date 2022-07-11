#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

char findCharacter(TABLE *head, unsigned int number, int size)
{
    TABLE *cur = head;
    while (cur != NULL)
    {
        if ((cur->num == number) && (cur->size == size))
        {
            // printf("%c ", cur -> character);
            return cur->character;
        }
        cur = cur->next;
    }
    return '\0';
}

void decode(TABLE **head, const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    // TABLE *cur = *head;

    char fch = fgetc(fp);
    char sch = fgetc(fp);
    unsigned int val;
    int number;
    while (!(fch == '#' && sch == '#'))
    {
        TABLE *temp = getTableNode();
        temp->character = fch;
        sch = fgetc(fp);
        val = sch - '0';
        sch = fgetc(fp);
        while (sch != ':')
        {
            val = (val * 10) + (sch - '0');
            fch = sch;
            sch = fgetc(fp);
        }
        temp->num = val;
        sch = fgetc(fp);
        number = sch - '0';
        sch = fgetc(fp);
        while (sch != ' ')
        {
            number = (number * 10) + (sch - '0');
            sch = fgetc(fp);
        }
        temp->size = number;
        sch = fgetc(fp);
        fch = sch;
        sch = fgetc(fp);
        if (*head == NULL)
        {
            *head = temp;
        }
        else
        {
            temp->next = *head;
            *head = temp;
        }
    }
    printTable(*head);
    sch = fgetc(fp);

    unsigned char c1, c2, c0;
    c0 = fgetc(fp);
    c1 = fgetc(fp);
    c2 = fgetc(fp);
    unsigned int tempch = 0b0;
    char mych;
    int size = 0;
    int overflow = 8;
    FILE *noice = fopen("./decode.huff", "w+");
    while (!(c1 == '#' && c2 == '#'))
    {
        while (overflow != 0)
        {
            if ((c0 & (1 << (overflow - 1))) == 0)
            {
                tempch = tempch << 1;
            }
            else
            {
                tempch = (tempch << 1) + 0b1;
            }
            size++;
            overflow--;
            if ((mych = findCharacter(*head, tempch, size)) != '\0')
            {
                fprintf(noice, "%c", mych);
                tempch = 0b0;
                size = 0;
            }
        }
        overflow = 8;
        c0 = c1;
        c1 = c2;
        c2 = fgetc(fp);
    }

    overflow = 8;
    fseek(fp, -1, SEEK_END);
    char asdch = fgetc(fp);
    int gotch = (asdch - '0');
    // size = size + gotch;
    fseek(fp, -4, SEEK_END);
    asdch = fgetc(fp);
    while(gotch != 0)
    {
        if ((asdch & (1 << (overflow - 1))) == 0)
        {
            tempch = tempch << 1;
        }
        else
        {
            tempch = (tempch << 1) + 0b1;
        }
        overflow--;
        gotch--;
        size++;
        if ((mych = findCharacter(*head, tempch, size)) != '\0')
        {
            fprintf(noice, "%c", mych);
            tempch = 0b0;
            size = 0;
        }
    }

    printf("File Decoded Successfully\n");
}
