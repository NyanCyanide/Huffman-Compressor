#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "huffman.h"

// int id = 0;

NODE *getNode()
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (node == NULL)
    {
        printf("Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->next = NULL;
    node->frequency = 1;
    // node->id = id++;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TABLE *getTableNode()
{
    TABLE *node = (TABLE*)malloc(sizeof(TABLE));
    if(node == NULL)
    {
        printf("Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node -> next = NULL;
    return node;
}

int isPresent(char c, NODE *head)
{
    if (head == NULL)
    {
        return 0;
    }
    else
    {
        while (head != NULL)
        {
            if (head->character == c)
            {
                (head->frequency)++;
                return 1;
            }
            head = head->next;
        }
        return 0;
    }
}

NODE *addList(char c, NODE *head)
{
    if (!isPresent(c, head))
    {
        NODE *temp = getNode();
        temp->character = c;

        if (head == NULL)
        {
            head = temp;
        }
        else
        {
            temp->next = head;
            head = temp;
        }
    }
    return head;
}

void printList(NODE *head)
{
    if (head == NULL)
    {
        printf("List is empty\n");
    }
    else
    {
        while (head != NULL)
        {
            printf("'%c':%d\n", head->character, head->frequency);
            head = head->next;
        }
    }
}

// Merge Sort Function
void mergeSort(NODE **head)
{
    NODE *cur = *head;
    NODE *a, *b;

    if ((cur == NULL) || (cur->next == NULL))
    {
        return;
    }

    split(*head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *head = sortedMerge(a, b);
}

NODE *sortedMerge(NODE *a, NODE *b)
{
    NODE *result = NULL;
    if (a == NULL)
    {
        return b;
    }
    else if (b == NULL)
    {
        return a;
    }

    if (a->frequency <= b->frequency)
    {
        result = a;
        result->next = sortedMerge(a->next, b);
    }
    else
    {
        result = b;
        result->next = sortedMerge(a, b->next);
    }
    return result;
}

void split(NODE *source, NODE **fhead, NODE **bhead)
{
    NODE *fast;
    NODE *slow;
    slow = source;
    fast = source->next;

    while (fast != NULL)
    {
        fast = fast->next;
        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *fhead = source;
    *bhead = slow->next;
    slow->next = NULL;
}

void encode(NODE **head, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    NODE *cur = *head;
    TABLE *header = NULL;
    char ch;
    while((ch = fgetc(fp)) != EOF)
    {
        cur = addList(ch, cur);
    }
    fclose(fp);
    mergeSort(&cur);
    // printList(cur);
    createTree(&cur);
    // printTree(cur);
    createTable(&header, cur, 0b0, 0);
    freeSpace(&cur);
    // printTable(header);
    fileEncoding(header, filename);
    // freeTable(&header);
    printf("Successfully Encoded\n");
    exit(EXIT_SUCCESS);
}

void freeSpace(NODE **head)
{
    while(*head != NULL)
    {
        NODE *temp = *head;
        *head = (*head)->next;
        temp -> next = NULL;
        free(temp);
    }
}

void freeTable(TABLE **head)
{
    while(*head != NULL)
    {
        TABLE *temp = *head;
        *head = (*head)->next;
        temp -> next = NULL;
        free(temp);
    }
}


TABLE *findNode(TABLE *head, char c)
{
    TABLE *cur = head;
    while(cur != NULL)
    {
        if(cur -> character == c)
        {
            return cur;
        }
        cur = cur -> next;
    }
}

void fileEncoding(TABLE *head, const char *filename)
{
    FILE *srcfp = fopen(filename, "r");
    FILE *dstfp = fopen("./encode.huff", "wb+");
    char ch;
    unsigned char byte = 0b0;
    int overflow = 0;
    TABLE *temp = head;
    while(temp != NULL)
    {
        fprintf(dstfp, "%c:%d:%d ", temp -> character, temp -> num, temp -> size);
        temp = temp -> next;
    }
    fprintf(dstfp, "##\n");
    while((ch = fgetc(srcfp)) != EOF)
    {
        TABLE *cur = findNode(head, ch);
        int size = cur -> size;
        unsigned int value = cur -> num;
        while(size != 0)
        {
            int add = value & (1 << (size - 1));
            if(add != 0)
            {
                byte = byte | (1 << (7 - overflow));
            }
            overflow++;
            if(overflow == 8)
            {
                fwrite(&byte, sizeof(unsigned char), 1, dstfp);
                byte = 0b0;
                overflow = 0;
            }
            size--;
        }
    }
    if(overflow != 0)
    {
        fwrite(&byte, sizeof(unsigned char), 1, dstfp);
    }
    fprintf(dstfp, " #%d", overflow);
}



void createTable(TABLE** header, NODE *cur, unsigned int number, int size)
{
    if(cur != NULL)
    {
        createTable(header, cur -> left, number<<1, size+1);
        createTable(header, cur -> right, (number<<1) + 0b1, size+1);
        if(cur -> left == NULL && cur -> right == NULL)
        {
            if(*header == NULL)
            {
                *header = getTableNode();
                (*header) -> character = cur -> character;
                (*header) -> num = number;
                (*header) -> size = size;
            }
            else
            {
                TABLE *temp = getTableNode();
                temp -> character = cur -> character;
                temp -> num = number;
                temp -> size = size;
                temp -> next = *header;
                *header = temp;
            }
        }

    }
}


void printTable(TABLE *head)
{
    while(head != NULL)
    {
        printf("Character = '%c' Number = '%d' Size = '%d'\n", head -> character, head -> num, head -> size);
        head = head -> next;
    }
}



void printTree(NODE *cur)
{
    if (cur != NULL)
    {
        printTree(cur->left);
        printTree(cur->right);
        if(cur -> left == NULL && cur -> right == NULL)
        {
            printf("%c:%d\n", cur->character, cur->frequency);
        }
    }
}

NODE *addNode(NODE *node1, NODE *node2)
{
    NODE *node = getNode();
    node->frequency = node1->frequency + node2->frequency;
    node->left = node1;
    node->right = node2;
    return node;
}

void updateList(NODE **head, NODE *node)
{
    NODE *cur = *head;
    if (cur->frequency >= node->frequency)
    {
        node->next = cur;
        *head = node;
        return;
    }
    else
    {
        NODE *temp = cur;
        cur = cur->next;
        while (cur != NULL)
        {
            if (cur->frequency >= node->frequency)
            {
                node->next = cur;
                temp->next = node;
                return;
            }
            temp = cur;
            cur = cur->next;
        }
        temp->next = node;
    }
}

void createTree(NODE **head)
{
    NODE *cur1 = *head;
    NODE *temp1;
    NODE *temp2;
    NODE *temp3;
    if (cur1->next != NULL)
    {
        while (cur1 != NULL)
        {
            temp1 = cur1;
            temp2 = cur1->next;
            cur1 = temp2->next;
            temp1->next = NULL;
            temp2->next = NULL;
            temp3 = addNode(temp1, temp2);
            if (cur1 != NULL)
            {
                updateList(&cur1, temp3);
            }
        }
        *head = temp3;
    }
}