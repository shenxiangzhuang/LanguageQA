#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"


/*gcc -std=c99 -Wall -Wextra -O  bitmap.c bitmaptest.c -o bitmaptest
 *gcc -std=c99 -Wall -Wextra -O  -Dbitmap_64 bitmap.c bitmaptest.c -o bitmaptest
 *这里-Dbitmap_64就是激活64Bits的预定义
 */

int main(void)
{
  printf("sizeof(bitmap_type) = %zd\n", sizeof(bitmap_type));

  const int testlen = 250;	// number of bits in the bitmap
  bitmap *B = bitmap_allocate(testlen);

  for (int i = 0; i < bitmap_wordlength; i++) { printf("%d", bitmap_read(B, i)); }  printf("\n");
  for (int i = 0; i < bitmap_wordlength; i++) { bitmap_set(B, i); }
  for (int i = 0; i < bitmap_wordlength; i++) { printf("%d", bitmap_read(B, i)); }  printf("\n");
  for (int i = 0; i < bitmap_wordlength; i++) { bitmap_clear(B, i); }
  for (int i = 0; i < bitmap_wordlength; i++) { printf("%d", bitmap_read(B, i)); }  printf("\n");

  bitmap_print(B);
  for (int i = 0; i < testlen; i += 4) { bitmap_set(B, i); }
  bitmap_print(B);
  for (int i = 0; i < testlen; i += 4) { bitmap_set(B, i); }
  bitmap_print(B);
  for (int i = 0; i < testlen; i += 4) { bitmap_set(B, i+1); }
  bitmap_print(B);
  for (int i = 0; i < testlen; i += 4) { bitmap_set(B, i+2); }
  bitmap_print(B);
  for (int i = 0; i < testlen; i += 4) { bitmap_set(B, i+3); }
  bitmap_print(B);
  for (int i = 0; i < testlen; i += 4) { bitmap_clear(B, i+2); }
  bitmap_print(B);
  for (int i = 0; i < testlen; i += 4) { bitmap_clear(B, i); }
  bitmap_print(B);

  bitmap_deallocate(B);
  B = NULL;	// no dangling pointers!

  return 0;
}
