#include "mylib.h"

void getMinMax(uint32_t *array,uint32_t size,uint32_t * Min, uint32_t * Max){
    *Min=0xffffffff;
    *Max=0x00;
    while(size--){
        if(*array > *Max)
            *Max = *array;
        else if(*array < *Min)
            *Min = *array;
        array++;
    }
}

