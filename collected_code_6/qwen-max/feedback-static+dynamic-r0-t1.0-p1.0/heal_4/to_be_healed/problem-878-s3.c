#include <stdio.h>
#include <stdlib.h>

int has_k_elements(const void *tuple, size_t element_size, size_t k) {
    if (tuple == NULL) {
        return 0;
    }
    for (size_t i = 0; i < k; ++i) {
        const char *element = (const char *)tuple + i * element_size;
        if (element == NULL) {
            return 0;
        }
    }
    const char *next_element = (const char *)tuple + k * element_size;
    /* Possible weaknesses found:
     * UBSan: load of misaligned address 0x7ff7b8d4a46c for type 'const void *', which requires 8 byte alignment
     */
    return next_element == NULL || *(const void **)next_element == NULL;
}

int main() {
    const int tuple[] = {1, 2, 3, 0};
    size_t k = 3;
    size_t element_size = sizeof(tuple[0]);
    if (has_k_elements(tuple, element_size, k)) {
        printf("Tuple has exactly %zu elements.\n", k);
    } else {
        printf("Tuple does not have exactly %zu elements.\n", k);
    }
    return 0;
}