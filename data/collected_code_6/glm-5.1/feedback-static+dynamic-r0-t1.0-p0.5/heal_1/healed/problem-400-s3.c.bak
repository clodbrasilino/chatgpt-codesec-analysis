#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple key;
    int count;
} TupleMap;

int compare_tuples(const void *p1, const void *p2) {
    const Tuple *t1 = (const Tuple *)p1;
    const Tuple *t2 = (const Tuple *)p2;
    if (t1->a != t2->a) {
        return t1->a - t2->a;
    }
    return t1->b - t2->b;
}

int compare_map(const void *p1, const void *p2) {
    return compare_tuples(&((const TupleMap *)p1)->key, &((const TupleMap *)p2)->key);
}

TupleMap* extract_unique_frequencies(Tuple *tuples, size_t len, size_t *out_len) {
    if (tuples == NULL || out_len == NULL || len == 0) {
        if (out_len != NULL) {
            *out_len = 0;
        }
        return NULL;
    }

    Tuple *sorted = (Tuple *)malloc(len * sizeof(Tuple));
    if (sorted == NULL) {
        *out_len = 0;
        return NULL;
    }

    memcpy(sorted, tuples, len * sizeof(Tuple));
    qsort(sorted, len, sizeof(Tuple), compare_tuples);

    size_t unique_count = 1;
    for (size_t i = 1; i < len; i++) {
        if (compare_tuples(&sorted[i], &sorted[i - 1]) != 0) {
            unique_count++;
        }
    }

    TupleMap *map = (TupleMap *)malloc(unique_count * sizeof(TupleMap));
    if (map == NULL) {
        free(sorted);
        *out_len = 0;
        return NULL;
    }

    map[0].key = sorted[0];
    map[0].count = 1;
    size_t idx = 0;

    for (size_t i = 1; i < len; i++) {
        if (compare_tuples(&sorted[i], &map[idx].key) == 0) {
            map[idx].count++;
        } else {
            idx++;
            map[idx].key = sorted[i];
            map[idx].count = 1;
        }
    }

    free(sorted);
    *out_len = unique_count;
    return map;
}

int main() {
    Tuple data[] = {{1, 2}, {3, 4}, {1, 2}, {5, 6}, {3, 4}, {1, 2}};
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t out_len = 0;

    TupleMap *result = extract_unique_frequencies(data, len, &out_len);

    if (result != NULL) {
        for (size_t i = 0; i < out_len; i++) {
            printf("(%d, %d): %d\n", result[i].key.a, result[i].key.b, result[i].count);
        }
        free(result);
    }

    return 0;
}