#ifndef HUFFMAN_H
#define HUFFMAN_H

// Struture Data Types
typedef struct node
{
  char character;
  int frequency;
  struct node *left;
  struct node *right;
  struct node *next;
} NODE;

typedef struct table
{
  char character;
  unsigned int num;
  int size;
  struct table *next;
} TABLE;

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
void process(char *argv[]);

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
void decode(TABLE **head, const char *filename);

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
 * Prints the binary tree
 * Uses recursion to print the tree
 * Prints in the format <- Left -> <- Right -> <- Root -> (Post Order Traversal)
 */
void printTree(NODE *cur);

/*
 * Function that converts Linked list into Tree Structure
 * Takes input as a Linked list and returns a Tree Structure
 */
void createTree(NODE **head);

/*
 * Function that updates list
 * Function that takes subtree and adds to the linked list in ascending order
 */
void updateList(NODE **head, NODE *node);

/*
 * Function that creates a node
 * Takes two node with minimum frequency of character and creates a new node
 * making a subtree
 */
NODE *addNode(NODE *node1, NODE *node2);

/*
 * Function that creates a table node
 * Takes a character, character encoded value, and size of it
 * which is used to make a linked list
 */
TABLE *getTableNode();

/*
 * Function that creates a table
 * Takes a character and character encoded value, and size of it
 * value is 'unsigned int' calculated in binary
 */
void createTable(TABLE **header, NODE *cur, unsigned int number, int size);

/*
 * Function that prints the table
 * Takes a table and prints the table in the format
 */
void printTable(TABLE *head);

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
int conditions(char *argv[]);

/*
 * On work in naming the output file
 */
char *fileName(const char *filename);

/*
 * Function that finds the node that search based on the character
 */
TABLE *findNode(TABLE *head, char c);

/*
 * Function that startes the process of encoding the file
 * Writes the data to the file in the form of binary
 * Contains the table data and encoded data and also the offset of last character
 */
void fileEncoding(TABLE *head, const char *filename);

/*
 * Function that release the memory of NODE structure data type
 */
void freeSpace(NODE **head);

/*
 * Function that release the memory of TABLE structure data type
 */
void freeTable(TABLE **head);

char findCharacter(TABLE *head, unsigned int number, int size);

#endif