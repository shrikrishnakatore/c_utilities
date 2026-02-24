/******************************************************************************

MAX heap Library

*******************************************************************************/
#include "heap.h"

void swap(int* a, int* b){
    int t= *a;
    *a= *b;
    *b=t;
}

Heap *create_heap(int capacity){//creat an heap  of max capacity; allocate memory
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->data = (int *)malloc(sizeof(int)* capacity);
    h->capacity = capacity;
    h->size = 0;
    return h;
}

void delete_heap(Heap *h){//delte heap; delete the memory allocated for heap
    if(h == NULL)
        return;
    free(h->data);
    free(h);
}

void insert_node(Heap *h, int val){// insert an elemnt to heap
    if(h == NULL){
        printf("Invalid Heap!\r\n");
        return;
    }
    if(h->size == h->capacity){
        printf("heap overflow!\r\n");
        return;
    }
    
    int i=h->size;
    h->data[i] = val;
    h->size++;
    
    while( ( i != 0 ) && ( h->data[(i-1)/2] < h->data[i])){// max heap 
        swap(&h->data[(i-1)/2], &h->data[i]);
        i=(i-1)/2;
    }
}

void heapify(Heap *h, int i){
    if(h == NULL){
        printf("Invalid Heap!\r\n");
        return;
    }
    int largest=i;
    int left= (i*2) +1;
    int right=(i*2) +2;
    
    if((left < h->size) && ( h->data[left] > h->data[largest]))
        largest = left;
        
    if((right < h->size) && ( h->data[right] > h->data[largest]))
        largest = right;
    
    if(largest != i){
        swap(&h->data[i], &h->data[largest]);
        heapify(h, largest);
    }
}

void printheap(Heap* h){
    if(h == NULL){
        printf("Invalid Heap!\r\n");
        return;
    }
    if( h-> size ==0){
        printf("Empty Heap!\r\n");
        return;
    }
    printf("Heap =");
    for(int i=0;i < h->size; i++){
        printf(" %d ", h->data[i]);
    }
    printf("\n");
}

int extract_node(Heap *h){// get an element from heap
    if(h == NULL){
        printf("Invalid Heap!\r\n");
        return INT_MIN;
    }
        
    if(h->size <= 0){
        printf("heap underflow!\r\n");
        return INT_MIN;
    }
    
    if(h->size==1){
        h->size--;
        return h->data[0];
    }
    
    int root = h->data[0];
    h->size--;
    h->data[0] = h->data[h->size];
    
    heapify(h, 0);
    
    return root;
    
}

// Use
/*
int main()
{
    Heap *heap = create_heap(10);

    insert_node(heap, 3);
    insert_node(heap, 2);
    insert_node(heap, 15);
    insert_node(heap, 5);
    insert_node(heap, 4);
    insert_node(heap, 45);

    printf("Max Heap array: ");
    printheap(heap);

    printf("Extracted max value: %d\n", extract_node(heap));
    printf("Max Heap array after extraction: ");
    printheap(heap);
    
    delete_heap(heap);
    return 0;
}
*/
