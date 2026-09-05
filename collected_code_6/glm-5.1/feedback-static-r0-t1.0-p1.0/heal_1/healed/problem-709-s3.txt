#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Tuple;

typedef struct {
    int value;
    int unique_key_count;
} ValueCount;

int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    if (ta->value != tb->value) {
        return (ta->value > tb->value) - (ta->value < tb->value);
    }
    return (ta->key > tb->key) - (ta->key < tb->key);
}

int compare_value_counts(const void *a, const void *b) {
    const ValueCount *va = (const ValueCount *)a;
    const ValueCount *vb = (const ValueCount *)b;
    return (va->value > vb->value) - (va->value < vb->value);
}

ValueCount *count_unique_keys(const Tuple *tuples, size_t num_tuples, size_t *out_size) {
    if (tuples == NULL || out_size == NULL) {
        return NULL;
    }

    if (num_tuples == 0) {
        *out_size = 0;
        return NULL;
    }

    Tuple *sorted = (Tuple *)malloc(num_tuples * sizeof(Tuple));
    if (sorted == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < num_tuples; ++i) {
        sorted[i] = tuples[i];
    }

    qsort(sorted, num_tuples, sizeof(Tuple), compare_tuples);

    size_t capacity = 16;
    ValueCount *results = (ValueCount *)malloc(capacity * sizeof(ValueCount));
    if (results == NULL) {
        free(sorted);
        return NULL;
    }

    size_t count = 0;
    size_t i = 0;

    while (i < num_tuples) {
        int current_value = sorted[i].value;
        int unique_keys = 0;
        int last_key = sorted[i].key;
        unique_keys++;

        size_t j = i + 1;
        while (j < num_tuples && sorted[j].value == current_value) {
            if (sorted[j].key != last_key) {
                unique_keys++;
                last_key = sorted[j].key;
            }
            j++;
        }

        if (count >= capacity) {
            size_t new_capacity = capacity * 2;
            ValueCount *temp = (ValueCount *)realloc(results, new_capacity * sizeof(ValueCount));
            if (temp == NULL) {
                free(results);
                free(sorted);
                return NULL;
            }
            results = temp;
            capacity = new_capacity;
        }

        results[count].value = current_value;
        results[count].unique_key_count = unique_keys;
        count++;

        i = j;
    }

    free(sorted);

    qsort(results, count, sizeof(ValueCount), compare_value_counts);

    *out_size = count;
    return results;
}

int main(void) {
    Tuple data[] = {
        {1, 10}, {2, 10}, {1, 10}, {3, 20}, {4, 20}, {2, 10}, {5, 30}, {5, 30}
    };
    size_t num_tuples = sizeof(data) / sizeof(data[0]);
    size_t out_size = 0;

    ValueCount *results = count_unique_keys(data, num_tuples, &out_size);

    if (results != NULL) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("Value: %d, Unique Keys: %d\n", results[i].value, results[i].unique_key_count);
        }
        free(results);
    }

    return 0;
}