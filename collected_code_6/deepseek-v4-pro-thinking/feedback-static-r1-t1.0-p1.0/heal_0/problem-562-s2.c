#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int key;
    size_t value;
    int occupied;
} HashEntry;

static size_t hash_int(int key, size_t capacity