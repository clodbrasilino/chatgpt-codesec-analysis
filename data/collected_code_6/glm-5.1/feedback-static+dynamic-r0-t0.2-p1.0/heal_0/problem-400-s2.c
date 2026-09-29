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

TupleMap* extract_unique_frequencies(Tuple* tuples, int length, int* unique_count) {
    if (tuples == NULL || length <= 0 || unique_count == NULL) {
        if (unique_count != NULL) {
            *unique_count = 0;
        }
        return NULL;
    }

    Tuple* sorted = (Tuple*)malloc(length * sizeof(Tuple));
    if (sorted == NULL) {
        *unique_count = 0;
        return NULL;
    }

    memcpy(sorted, tuples, length * sizeof(Tuple));
    qsort(sorted, length, sizeof(Tuple), compare_tuples);

    int capacity = 16;
    TupleMap* map = (TupleMap*)malloc(capacity * sizeof(TupleMap));
    if (map == NULL) {
        free(sorted);
        *unique_count = 0;
        return NULL;
    }

    int count = 0;
    int i = 0;
    while (i < length) {
        int j = i;
        while (j < length && compare_tuples(&sorted[i], &sorted[j]) == 0) {
            j++;
        }

        if (count >= capacity) {
            capacity *= 2;
            TupleMap* temp = (TupleMap*)realloc(map, capacity * sizeof(TupleMap));
            if (temp == NULL) {
                free(sorted);
                free(map);
                *unique_count = 0;
                return NULL;
            }
            map = temp;
        }

        map[count].key = sorted[i];
        map[count].count = j - i;
        count++;
        i = j;
    }

    free(sorted);
    *unique_count = count;
    return map;
}

int main() {
    Tuple data[] = {{1, 2}, {3, 4}, {1, 2}, {5, 6}, {3, 4}, {1, 2}};
    int length = sizeof(data) / sizeof(data[0]);
    int unique_count = 0;

    TupleMap* result = extract_unique_frequencies(data, length, &unique_count);

    if (result != NULL) {
        for (int i = 0; i < unique_count; i++) {
            printf("(%d, %d): %d\n", result[i].key.a, result[i].key.b, result[i].count);
        }
        free(result);
    }

    return 0;
}