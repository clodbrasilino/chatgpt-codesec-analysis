#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int count;
} Frequency;

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int* get_frequencies(int* list, size_t size, size_t* out_size) {
    if (list == NULL || out_size == NULL || size == 0) {
        if (out_size != NULL) {
            *out_size = 0;
        }
        return NULL;
    }

    Frequency* freqs = (Frequency*)malloc(size * sizeof(Frequency));
    if (freqs == NULL) {
        *out_size = 0;
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < size; i++) {
        int found = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (freqs[j].key == list[i]) {
                freqs[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            freqs[unique_count].key = list[i];
            freqs[unique_count].count = 1;
            unique_count++;
        }
    }

    int* result = (int*)malloc(unique_count * 2 * sizeof(int));
    if (result == NULL) {
        free(freqs);
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < unique_count; i++) {
        result[i * 2] = freqs[i].key;
        result[i * 2 + 1] = freqs[i].count;
    }

    free(freqs);
    *out_size = unique_count * 2;

    return result;
}

int main(void) {
    int list[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t out_size = 0;

    int* frequencies = get_frequencies(list, size, &out_size);

    if (frequencies != NULL) {
        for (size_t i = 0; i < out_size; i += 2) {
            printf("%d: %d\n", frequencies[i], frequencies[i + 1]);
        }
        free(frequencies);
    }

    return 0;
}