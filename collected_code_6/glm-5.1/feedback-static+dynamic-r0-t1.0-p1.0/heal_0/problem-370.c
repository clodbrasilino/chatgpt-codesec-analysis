#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    float value;
    char label[16];
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
            capacity *= 2;
            Tuple *temp = (Tuple *)realloc(tuples, capacity * sizeof(Tuple));
            if (temp == NULL) {
                free(tuples);
                return 1;
            }
            tuples = temp;
        }
        tuples[count].id = (int)i;
        tuples[count].value = (float)input[i] / 2.0f;
        snprintf(tuples[count].label, sizeof(tuples[count].label), "item_%zu", i);
        count++;
    }

    qsort(tuples, count, sizeof(Tuple), compare_tuples);

    for (size_t i = 0; i < count; i++) {
        printf("id: %d, value: %.2f, label: %s\n", tuples[i].id, tuples[i].value, tuples[i].label);
    }

    free(tuples);
    tuples = NULL;

    return 0;
}