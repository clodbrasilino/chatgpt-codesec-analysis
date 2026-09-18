#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    int element;
    int count;
} Frequency;

int* extract_single_elements(const Tuple* tuples, size_t num_tuples, size_t* out_size);

int* extract_single_elements(const Tuple* tuples, size_t num_tuples, size_t* out_size) {
    if (!tuples || !out_size) {
        return NULL;
    }

    *out_size = 0;

    if (num_tuples == 0) {
        return NULL;
    }

    size_t max_elements = num_tuples * 2;
    Frequency* freqs = (Frequency*)calloc(max_elements, sizeof(Frequency));
    if (!freqs) {
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < num_tuples; ++i) {
        const int values[2] = {tuples[i].first, tuples[i].second};
        
        for (int v = 0; v < 2; ++v) {
            int found = 0;
            for (size_t j = 0; j < unique_count; ++j) {
                if (freqs[j].element == values[v]) {
                    freqs[j].count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                freqs[unique_count].element = values[v];
                freqs[unique_count].count = 1;
                unique_count++;
            }
        }
    }

    size_t single_count = 0;
    for (size_t i = 0; i < unique_count; ++i) {
        if (freqs[i].count == 1) {
            single_count++;
        }
    }

    int* result = NULL;
    if (single_count > 0) {
        result = (int*)malloc(single_count * sizeof(int));
        if (!result) {
            free(freqs);
            return NULL;
        }

        size_t idx = 0;
        for (size_t i = 0; i < unique_count; ++i) {
            if (freqs[i].count == 1) {
                result[idx++] = freqs[i].element;
            }
        }
        *out_size = single_count;
    }

    free(freqs);
    return result;
}

int main(void) {
    Tuple tuples[] = {
        {1, 2},
        {3, 2},
        {4, 5},
        {1, 6}
    };
    
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    size_t out_size = 0;

    int* singles = extract_single_elements(tuples, num_tuples, &out_size);

    if (singles) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%d\n", singles[i]);
        }
        free(singles);
    }

    return EXIT_SUCCESS;
}