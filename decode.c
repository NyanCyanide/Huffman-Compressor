#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

char findCharacter(TABLE *head, unsigned int number, int size)
{
    TABLE *cur = head;
    while(cur != NULL)
    {
        if((cur -> num == number) && (cur -> size == size))
        {
            // printf("%c ", cur -> character);
            return cur -> character;
        }
        cur = cur -> next;
    }
    return NULL;
}

void decode(TABLE **head, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    // TABLE *cur = *head;
    {
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
        
        unsigned char c1, c2;
        c1 = fgetc(fp);
        c2 = fgetc(fp);
        int index = 0;
        unsigned int tempch = 0b0;
        char mych;
        int size = 0;
        int overflow = 8;
        FILE *noice = fopen("./decode.huff", "w+");
        while (!(c1 == '#' && c2 == '#'))
        {
            printf("%x %d  ",c1, index++);
            while(overflow != 0)
            {
                if((c1 & (1 << (overflow - 1))) == 0) 
                {
                    tempch = tempch << 1;
                    // printf("0");
                }
                else
                {
                    tempch = (tempch << 1) + 0b1;
                    // printf("1");
                }
                size++;
                overflow--;
                if((mych = findCharacter(*head, tempch, size)) != NULL)
                {
                    fprintf(noice, "%c", mych);
                    tempch = 0b0;
                    size = 0;
                }
            }
            overflow = 8;
            c1 = c2;
            c2 = fgetc(fp);
        }
    }
}
