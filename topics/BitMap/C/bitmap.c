#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

// we expect 0 <= n < b->bits, but it is not verified

void bitmap_set(bitmap *b, int n){
    // 定位到第n个bit所在的word
    int word = n >> bitmap_shift;   // n / bitmap_wordlength
    // 定位到第n个bit在(所属word的)第几个比特位
    // n低位与mask取&就相当于求余操作
    int position = n & bitmap_mask;  // n % bitmap_wordlength
    // 利用(x | 0 = x), (x | 1 = 1), x为0或1
    b->array[word] |= bitmap_one << position;
}

void bitmap_clear(bitmap *b, int n){
    int word = n >> bitmap_shift;   // n / bitmap_wordlength
    int position = n & bitmap_mask; // n % bitmap_wordlength
    // 利用(x & 1 = x), (x & 0 = 0), x为0或1
    b->array[word] &= ~(bitmap_one << position);
}

int bitmap_read(bitmap *b, int n){
    int word = n >> bitmap_shift;
    int position = n & bitmap_mask;
    // 利用(x & 1 = x)
    return (b->array[word] >> position) & 1;
}

bitmap * bitmap_allocate(int bits){
    // error-checking should be better
    bitmap * b = malloc(sizeof(bitmap));
    b->bits = bits;
    // divide, but round up for the ceiling
    b->words =(bits + bitmap_wordlength - 1) / bitmap_wordlength;
    // calloc: 分配b->words个，大小为sizeof(bitmap_type)的内存
    b->array = calloc(b->words, sizeof(bitmap_type));
    return b;
}

void bitmap_deallocate(bitmap *b){
    // error-checking should be better
    free(b->array);
    free(b);
}

void bitmap_print(bitmap *b){
    for(int i=0; i < b->words; i++){
        printf(" " bitmap_fmt, b->array[i]);
    }
    printf("\n");
}


