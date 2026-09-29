#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int *extract_continuous(const int *list, size_t list_len, size_t start, size_t count, size_t *out_len) {
    if (list == NULL || out_len == NULL) {
        return NULL;
    }
    
    if (count == 0 || start >= list_len || start + count > list_len || count > SIZE_MAX / sizeof(int)) {
        *out_len = 0;
        return NULL;
    }

    int *result = malloc(count * sizeof(int));
    if (result == NULL) {
        *out_len = 0;
        return NULL;
    }

    memcpy(result, list + start, count * sizeof(int));
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