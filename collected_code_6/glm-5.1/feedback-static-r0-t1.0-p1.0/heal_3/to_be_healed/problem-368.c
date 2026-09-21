#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* repeat_tuple(const void* tuple, size_t tuple_size, size_t n) {
    if (tuple == NULL || tuple_size == 0) {
        return NULL;
    }

    size_t total_size = tuple_size * n;
    if (n != 0 && total_size / n != tuple_size) {
        return NULL;
    }

    if (total_size == 0) {
        void* zero_result = malloc(1);
        return zero_result;
    }

    void* result = malloc(total_size);
    if (result == NULL) {
        return NULL;
    }

    const unsigned char* src = (const unsigned char*)tuple;
    unsigned char* dest = (unsigned char*)result;

    if (tuple_size > total_size) {
        free(result);
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dest, src, tuple_size);

    size_t copied = tuple_size;
    while (copied < total_size) {
        /* Possible weaknesses found:
         *  Assignment 'next_copy=(copied<total_size-copied)?copied:total_size-copied', assigned value is less than symbolic=total_size-copied+1
         */
        size_t next_copy = (copied < total_size - copied) ? copied : total_size - copied;
        /* Possible weaknesses found:
         *  Condition 'next_copy>total_size-copied' is always false [knownConditionTrueFalse]
         *  Condition 'next_copy>total_size-copied' is always false
         */
        if (next_copy > total_size - copied) {
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest + copied, dest, next_copy);
        copied += next_copy;
    }

    return result;
}

int main() {
    int original_tuple[] = {1, 2, 3};
    size_t tuple_size = sizeof(original_tuple);
    size_t n = 4;

    int* repeated = (int*)repeat_tuple(original_tuple, tuple_size, n);
    if (repeated == NULL) {
        return 1;
    }

    size_t total_elements = (tuple_size / sizeof(int)) * n;
    for (size_t i = 0; i < total_elements; i++) {
        printf("%d ", repeated[i]);
    }
    printf("\n");

    free(repeated);
    repeated = NULL;

    return 0;
}