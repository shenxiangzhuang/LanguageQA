#ifdef bitmap_64
    #define bitmap_type unsigned long long int
#else  // assumed to be 32 bits
    #define bitmap_type unsigned int
#endif


#ifdef bitmap_64
    #define bitmap_type unsigned long long int
    // n >> 6 equals n / 64
    #define bitmap_shift       6
    // 63 in binary is 11111111
    #define bitmap_mask       63
    #define bitmap_wordlength 64
    // 016表示至少用16位数字表示，不够的话前面补0
    // ll表示参数将被解释为long long int, x表示十六进制
    #define bitmap_fmt "%016llx"
#else   // assumed to be 32 bits
    #define bitmap_type unsigned int
    #define bitmap_shift       5
    #define bitmap_mask       31
    #define bitmap_wordlength 32
    #define bitmap_fmt "%08x"
#endif

// get the types right
#define bitmap_one  (bitmap_type) 1

typedef struct{
    int bits;     // number of bits in the array
    int words;    // number of words in the array
    bitmap_type *array;
} bitmap;

void bitmap_set  (bitmap *b, int n);   // n is a bit index
void bitmap_clear(bitmap *b, int n);
int bitmap_read (bitmap *b, int n);

bitmap * bitmap_allocate(int bits);
void bitmap_deallocate(bitmap *b);

void bitmap_print(bitmap *b);

