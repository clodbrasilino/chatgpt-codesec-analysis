#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int *extract_continuous_elements(const int *list, size_t list_len, size_t start, size_t count) {
    if (list == NULL || list_len == 0 || count == 0) {
        return NULL;
    }
    if (start >= list_len) {
        return NULL;
    }
    if (count > list_len - start) {
        return NULL;
    }
    if (count > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int *result = malloc(count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, list + start, count * sizeof(int));
    return result;
}

int main(void) {
    int data[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    size_t data_len = sizeof(data) / sizeof(data[0]);
    size_t start_idx = 2;
    size_t num_elements = 4;

    int *sub_list = extract_continuous_elements(data, data_len, start_idx, num_elements);
    if (sub_list != NULL) {
        for (size_t i = 0; i < num_elements; i++) {
            printf("%d ", sub_list[i]);
        }
        printf("\n");
        free(sub_list);
    }

    const int *invalid_test = extract_continuous_elements(data, data_len, 8, 5);
    if (invalid_test == NULL) {
        printf("Boundary check passed.\n");
    }

    return 0;
}