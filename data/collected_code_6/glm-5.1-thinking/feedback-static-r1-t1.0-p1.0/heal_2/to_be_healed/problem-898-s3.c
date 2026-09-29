#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int *extract_continuous(const int *list, size_t list_len, size_t start, size_t count, size_t *out_len) {
    if (list == NULL || out_len == NULL) {
        return NULL;
    }
    
    if (count == 0 || start >= list_len || count > SIZE_MAX - start || start + count > list_len || count > SIZE_MAX / sizeof(int)) {
        *out_len = 0;
        return NULL;
    }

    size_t alloc_size = count * sizeof(int);
    int *result = malloc(alloc_size);
    if (result == NULL) {
        *out_len = 0;
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, list + start, alloc_size);
    *out_len = count;
    
    return result;
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    size_t start = 3;
    size_t count = 4;
    size_t out_len = 0;

    int *extracted = extract_continuous(arr, arr_len, start, count, &out_len);

    if (extracted != NULL) {
        for (size_t i = 0; i < out_len; i++) {
            printf("%d ", extracted[i]);
        }
        printf("\n");
        free(extracted);
    }

    return 0;
}