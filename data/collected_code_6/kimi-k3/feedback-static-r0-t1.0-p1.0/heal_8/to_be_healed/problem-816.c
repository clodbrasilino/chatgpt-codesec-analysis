#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 50
#define TUPLE_COUNT 3

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[NAME_SIZE];
    double value;
} Tuple;

void clear_tuple(Tuple *t) {
    if (t != NULL) {
        t->id = 0;
        memset(t->name, 0, sizeof(t->name));
        t->value = 0.0;
    }
}

void clear_tuples(Tuple *tuples, size_t count) {
    if (tuples != NULL && count > 0) {
        for (size_t i = 0; i < count; i++) {
            clear_tuple(&tuples[i]);
        }
    }
}

int safe_string_copy(char *dest, size_t dest_size, const char *src) {
    size_t src_len;
    size_t copy_len;
    
    if (dest == NULL || src == NULL || dest_size == 0) {
        return -1;
    }
    
    src_len = strnlen(src, dest_size);
    if (src_len >= dest_size) {
        copy_len = dest_size - 1;
    } else {
        copy_len = src_len;
    }
    
    if (copy_len > 0) {
        memmove(dest, src, copy_len);
    }
    dest[copy_len] = '\0';
    
    return 0;
}

int main(void) {
    Tuple tuples[TUPLE_COUNT];
    size_t i;
    
    tuples[0].id = 1;
    safe_string_copy(tuples[0].name, sizeof(tuples[0].name), "First");
    tuples[0].value = 10.5;
    
    tuples[1].id = 2;
    safe_string_copy(tuples[1].name, sizeof(tuples[1].name), "Second");
    tuples[1].value = 20.75;
    
    tuples[2].id = 3;
    safe_string_copy(tuples[2].name, sizeof(tuples[2].name), "Third");
    tuples[2].value = 30.25;
    
    printf("Before clearing:\n");
    for (i = 0; i < TUPLE_COUNT; i++) {
        printf("Tuple %zu: id=%d, name=%s, value=%.2f\n", 
               i, tuples[i].id, tuples[i].name, tuples[i].value);
    }
    
    clear_tuples(tuples, TUPLE_COUNT);
    
    printf("\nAfter clearing:\n");
    for (i = 0; i < TUPLE_COUNT; i++) {
        printf("Tuple %zu: id=%d, name=%s, value=%.2f\n", 
               i, tuples[i].id, tuples[i].name, tuples[i].value);
    }
    
    return 0;
}