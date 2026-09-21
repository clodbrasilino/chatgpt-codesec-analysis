#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_NAME_LEN 64

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[MAX_NAME_LEN];
} Tuple;

static bool is_valid_order(const int *order, size_t order_count, size_t tuple_count) {
    bool *seen = calloc(tuple_count, sizeof(bool));
    if (seen == NULL) {
        return false;
    }
    
    for (size_t i = 0; i < order_count; i++) {
        if (order[i] < 0 || (size_t)order[i] >= tuple_count) {
            free(seen);
            return false;
        }
        if (seen[order[i]]) {
            free(seen);
            return false;
        }
        seen[order[i]] = true;
    }
    
    free(seen);
    return true;
}

int rearrange_tuples(Tuple *tuples, size_t tuple_count, const int *order, size_t order_count) {
    if (tuples == NULL || order == NULL || tuple_count == 0 || order_count == 0) {
        return -1;
    }
    
    if (order_count > tuple_count) {
        return -1;
    }
    
    if (tuple_count > SIZE_MAX / sizeof(Tuple)) {
        return -1;
    }
    
    if (!is_valid_order(order, order_count, tuple_count)) {
        return -1;
    }
    
    Tuple *temp = malloc(tuple_count * sizeof(Tuple));
    if (temp == NULL) {
        return -1;
    }
    
    for (size_t i = 0; i < order_count; i++) {
        temp[i] = tuples[order[i]];
    }
    
    for (size_t i = order_count; i < tuple_count; i++) {
        temp[i] = tuples[i];
    }
    
    size_t copy_size = tuple_count * sizeof(Tuple);
    if (copy_size > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tuples, temp, copy_size);
    }
    
    free(temp);
    return 0;
}

static int safe_string_copy(char *dest, size_t dest_size, const char *src) {
    if (dest == NULL || src == NULL || dest_size == 0) {
        return -1;
    }
    
    size_t src_len = strnlen(src, dest_size);
    if (src_len >= dest_size) {
        return -1;
    }
    
    if (src_len + 1 > dest_size) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, src_len + 1);
    return 0;
}

int main(void) {
    Tuple tuples[4];
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    
    tuples[0].id = 1;
    if (safe_string_copy(tuples[0].name, sizeof(tuples[0].name), "Apple") != 0) {
        fprintf(stderr, "Error: Failed to initialize tuple name\n");
        return EXIT_FAILURE;
    }
    
    tuples[1].id = 2;
    if (safe_string_copy(tuples[1].name, sizeof(tuples[1].name), "Banana") != 0) {
        fprintf(stderr, "Error: Failed to initialize tuple name\n");
        return EXIT_FAILURE;
    }
    
    tuples[2].id = 3;
    if (safe_string_copy(tuples[2].name, sizeof(tuples[2].name), "Cherry") != 0) {
        fprintf(stderr, "Error: Failed to initialize tuple name\n");
        return EXIT_FAILURE;
    }
    
    tuples[3].id = 4;
    if (safe_string_copy(tuples[3].name, sizeof(tuples[3].name), "Date") != 0) {
        fprintf(stderr, "Error: Failed to initialize tuple name\n");
        return EXIT_FAILURE;
    }
    
    int order[] = {2, 0, 3, 1};
    size_t order_count = sizeof(order) / sizeof(order[0]);
    
    printf("Original tuples:\n");
    for (size_t i = 0; i < tuple_count; i++) {
        printf("ID: %d, Name: %s\n", tuples[i].id, tuples[i].name);
    }
    
    if (rearrange_tuples(tuples, tuple_count, order, order_count) != 0) {
        fprintf(stderr, "Error: Failed to rearrange tuples\n");
        return EXIT_FAILURE;
    }
    
    printf("\nRearranged tuples:\n");
    for (size_t i = 0; i < tuple_count; i++) {
        printf("ID: %d, Name: %s\n", tuples[i].id, tuples[i].name);
    }
    
    return EXIT_SUCCESS;
}