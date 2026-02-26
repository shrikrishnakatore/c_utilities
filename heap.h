
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// implementation of MAX heap
typedef struct HeapType{
    int* data;
    int capacity;
    int size;
} Heap;



Heap *create_heap(int capacity);
void delete_heap(Heap *h);
void insert_node(Heap *h, int val);
int extract_node(Heap *h);
void printheap(Heap* h);

