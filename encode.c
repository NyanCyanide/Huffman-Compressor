#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int id = 0;

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
    node->id = id++;
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
            printf("id:%d => '%c':%d\n",head->id, head->character, head->frequency);
            head = head->next;
        }
    }
}

/*
// Merge Sort Function
// void mergeSort(NODE **head)
// {
//     NODE *cur = *head;
//     NODE *a, *b;

//     if((cur == NULL) || (cur -> next == NULL))
//     {
//         return;
//     }

//     split(*head, &a, &b);

//     mergeSort(&a);
//     mergeSort(&b);

//     *head = sortedMerge(a, b);
// }

// NODE *sortedMerge(NODE *a, NODE *b)
// {
//     NODE *result = NULL;
//     if(a == NULL)
//     {
//         return b;
//     }
//     else if(b == NULL)
//     {
//         return a;
//     }

//     if (a -> frequency <= b -> frequency)
//     {
//         result = a;
//         result -> next = sortedMerge(a -> next, b);
//     }
//     else
//     {
//         result = b;
//         result -> next = sortedMerge(a, b -> next);
//     }
//     return result;
// }

// void split(NODE *source, NODE **fhead, NODE **bhead)
// {
//     NODE *fast;
//     NODE *slow;
//     slow = source;
//     fast = source -> next;

//     while(fast != NULL)
//     {
//         fast = fast -> next;
//         if(fast != NULL)
//         {
//             slow = slow -> next;
//             fast = fast -> next;
//         }
//     }

//     *fhead = source;
//     *bhead = slow -> next;
//     slow -> next = NULL;

// }
*/

void encode(NODE **head, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    NODE *cur = *head;
    char ch;
    while (!feof(fp))
    {
        ch = fgetc(fp);
        if (ch != EOF)
        {
            cur = addList(ch, cur);
        }
    }
    printList(cur);
    // mergeSort(&cur);
    // printList(cur);
    // createTree(&cur);
    // minHeap(&cur);
}