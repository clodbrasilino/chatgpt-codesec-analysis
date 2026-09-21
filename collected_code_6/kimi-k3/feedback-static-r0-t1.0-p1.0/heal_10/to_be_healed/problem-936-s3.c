#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_NAME_LENGTH 50
#define MAX_TUPLE_COUNT 1000000

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[MAX_NAME_LENGTH];
} Tuple;

static bool validate_tuple_name(const char *name) {
    if (name == NULL) {
        return false;
    }
    size_t len = strnlen(name, MAX_NAME_LENGTH);
    return len < MAX_NAME_LENGTH;
}

static bool safe_multiply_size(size_t a, size_t b, size_t *result) {
    if (result == NULL) {
        return false;
    }
    if (a == 0 || b == 0) {
        *result = 0;
        return true;
    }
    if (a > SIZE_MAX / b) {
        return false;
    }
    *result = a * b;
    return true;
}

static bool safe_copy_name(char *dest, size_t dest_size, const char *src) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return false;
    }
    size_t src_len = strnlen(src, dest_size);
    if (src_len >= dest_size) {
        return false;
    }
    if (dest_size < src_len + 1) {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, src_len + 1);
    return true;
}

void rearrange_tuples(Tuple *tuples, size_t tuple_count, const int *order, size_t order_count) {
    if (tuples == NULL || order == NULL || tuple_count == 0 || order_count == 0) {
        return;
    }
    
    if (tuple_count > MAX_TUPLE_COUNT || order_count > MAX_TUPLE_COUNT) {
        return;
    }
    
    if (order_count > tuple_count) {
        return;
    }
    
    size_t alloc_size;
    if (!safe_multiply_size(tuple_count, sizeof(Tuple), &alloc_size)) {
        return;
    }
    
    for (size_t i = 0; i < tuple_count; i++) {
        if (!validate_tuple_name(tuples[i].name)) {
            return;
        }
    }
    
    Tuple *temp = malloc(alloc_size);
    if (temp == NULL) {
        return;
    }
    
    bool *used_indices = calloc(tuple_count, sizeof(bool));
    if (used_indices == NULL) {
        free(temp);
        return;
    }
    
    for (size_t i = 0; i < order_count; i++) {
        if (order[i] < 0 || (size_t)order[i] >= tuple_count) {
            free(used_indices);
            free(temp);
            return;
        }
        if (used_indices[order[i]]) {
            free(used_indices);
            free(temp);
            return;
        }
        used_indices[order[i]] = true;
    }
    
    for (size_t i = 0; i < order_count; i++) {
        temp[i] = tuples[order[i]];
    }
    
    for (size_t i = order_count; i < tuple_count; i++) {
        temp[i] = tuples[i];
    }
    
    memmove(tuples, temp, alloc_size);
    
    free(used_indices);
    free(temp);
}

int main(void) {
    Tuple tuples[] = {
        {1, "Apple"},
        {2, "Banana"},
        {3, "Cherry"},
        {4, "Date"}
    };
    
    int order[] = {2, 0, 3, 1};
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t order_count = sizeof(order) / sizeof(order[0]);
    
    printf("Original tuples:\n");
    for (size_t i = 0; i < tuple_count; i++) {
        printf("ID: %d, Name: %s\n", tuples[i].id, tuples[i].name);
    }
    
    rearrange_tuples(tuples, tuple_count, order, order_count);
    
    printf("\nRearranged tuples:\n");
    for (size_t i = 0; i < tuple_count; i++) {
        printf("ID: %d, Name: %s\n", tuples[i].id, tuples[i].name);
    }
    
    return 0;
}