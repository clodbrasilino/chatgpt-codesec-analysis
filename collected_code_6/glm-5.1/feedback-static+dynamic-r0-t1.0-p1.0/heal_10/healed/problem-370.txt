#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int id;
    float value;
    size_t label_len;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    if (ta->value < tb->value) return -1;
    if (ta->value > tb->value) return 1;
    return 0;
}

int main() {
    Tuple *tuples = NULL;
    size_t capacity = 4;
    size_t count = 0;
    int input[] = {3, 1, 4, 1, 5};
    size_t input_size = sizeof(input) / sizeof(input[0]);

    tuples = (Tuple *)malloc(capacity * sizeof(Tuple));
    if (tuples == NULL) {
        return 1;
    }

    for (size_t i = 0; i < input_size; i++) {
        if (count == capacity) {
            if (capacity > SIZE_MAX / 2) {
                for (size_t j = 0; j < count; j++) free(tuples[j].label);
                free(tuples);
                return 1;
            }
            size_t new_capacity = capacity * 2;
            if (new_capacity > SIZE_MAX / sizeof(Tuple)) {
                for (size_t j = 0; j < count; j++) free(tuples[j].label);
                free(tuples);
                return 1;
            }
            Tuple *temp = (Tuple *)realloc(tuples, new_capacity * sizeof(Tuple));
            if (temp == NULL) {
                for (size_t j = 0; j < count; j++) free(tuples[j].label);
                free(tuples);
                return 1;
            }
            tuples = temp;
            capacity = new_capacity;
        }
        tuples[count].id = (int)i;
        tuples[count].value = (float)input[i] / 2.0f;
        const char *fmt = "item_%zu";
        size_t len = snprintf(NULL, 0, fmt, i);
        tuples[count].label = (char *)malloc(len + 1);
        if (tuples[count].label == NULL) {
            for (size_t j = 0; j < count; j++) free(tuples[j].label);
            free(tuples);
            return 1;
        }
        snprintf(tuples[count].label, len + 1, fmt, i);
        tuples[count].label_len = len;
        count++;
    }

    qsort(tuples, count, sizeof(Tuple), compare_tuples);

    for (size_t i = 0; i < count; i++) {
        printf("id: %d, value: %.2f, label: %s\n", tuples[i].id, tuples[i].value, tuples[i].label);
    }

    for (size_t i = 0; i < count; i++) {
        free(tuples[i].label);
    }
    free(tuples);
    tuples = NULL;

    return 0;
}