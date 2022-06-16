#ifndef HUFFMAN_H
#define HUFFMAN_H

// Struture Data Types
typedef struct node{
    char character;
    int frequency;
    int id;
    struct node *next;
}NODE;


// Function Names

/* 
  * Prints the correct format to be used to run the program
*/
void message();

/*
  * Starts the process of encoding or decoding
  * encode() => converts the file to .huff extension
  * decode() => converts the file to respective extension
*/
void process(char * argv[]);

/*
  * Starts the process of encoding the file
  * Uses Linked List and Tree Structure to encode the file
  * Uses method of Huffman Encoding
*/
void encode(NODE **head, const char *filename);

/*
  * Starts the process of encoding the file
  * Uses Linked List and Tree Structure to encode the file
*/
void decode(NODE **head, const char *filename);

/*
  * Implication of Linked List Merge Sort
  * Time Complexity => O(n*log(n))
*/

/*
  * MergeSort Function 
  * Keeps calling split function recursively
  * Applies merge sort when there is two nodes
*/
void mergeSort(NODE **head);

/*
  * SortedMerged Function
  * Combines both small linked list into bigger one 
  * according to ascending order
*/
NODE *sortedMerge(NODE *a, NODE *b);

/*
  * Split Function
  * Splits the linked list into two 
  * Similar method to hare and tortise method
*/
void split(NODE *source, NODE **fhead, NODE **bhead);



/* 
  * Function that checks if file exists 
  * returns 1 if file exists and 0 if file doesn't exist
*/
int fileExists(char *filename);

/*
  * Checks correct file extension used for a file
  * returns 1 if extension is present else 0
*/
int checkExtension(char *filename, char *extension);

/*
  * Function that goes through if the parameters and file names are correct
  * returns 1 if error else 0
  * argv[1] = -encode or -decode
  * argv[2] = <file name>
*/
int conditions(char * argv[]);

#endif