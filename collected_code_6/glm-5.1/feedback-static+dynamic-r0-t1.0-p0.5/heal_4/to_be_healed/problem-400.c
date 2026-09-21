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
        return (t1->a > t2->a) - (t1->a < t2->a);
    }
    return (t1->b > t2->b) - (t1->b < t2->b);
}

int compare_map(const void *p1, const void *p2) {
    return compare_tuples(&((const TupleMap *)p1)->key, &((const TupleMap *)p2)->key);
}

TupleMap* extract_unique_frequencies(Tuple* tuples, int num_tuples, int* unique_count) {
    /* Possible weaknesses found:
     *  Assuming condition 'num_tuples<=0' is false
     *  Assuming condition 'tuples==NULL' is false
     */
    if (tuples == NULL || num_tuples <= 0 || unique_count == NULL) {
        if (unique_count != NULL) {
            *unique_count = 0;
        }
        return NULL;
    }

    Tuple* sorted_tuples = (Tuple*)malloc(num_tuples * sizeof(Tuple));
    /* Possible weaknesses found:
     *  Assuming condition 'sorted_tuples==NULL' is false
     *  Assuming condition is false
     */
    if (sorted_tuples == NULL) {
        *unique_count = 0;
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'tuples!=NULL' is always true
     *  Condition 'sorted_tuples!=NULL' is always true [knownConditionTrueFalse]
     *  Condition 'num_tuples>0' is always true
     *  Condition 'sorted_tuples!=NULL' is always true
     *  Condition 'num_tuples>0' is always true [knownConditionTrueFalse]
     *  Condition 'tuples!=NULL' is always true [knownConditionTrueFalse]
     */
    if (num_tuples > 0 && tuples != NULL && sorted_tuples != NULL) {
        size_t copy_size = (size_t)num_tuples * sizeof(Tuple);
        Tuple* dest = sorted_tuples;
        const Tuple* src = tuples;
        if (dest < src) {
            for (size_t i = 0; i < copy_size; i++) {
                *((char*)dest + i) = *((char*)src + i);
            }
        } else {
            for (size_t i = copy_size; i > 0; i--) {
                *((char*)dest + i - 1) = *((char*)src + i - 1);
            }
        }
    }

    qsort(sorted_tuples, num_tuples, sizeof(Tuple), compare_tuples);

    int capacity = 16;
    TupleMap* map = (TupleMap*)malloc(capacity * sizeof(TupleMap));
    if (map == NULL) {
        free(sorted_tuples);
        *unique_count = 0;
        return NULL;
    }

    int count = 0;
    int i = 0;
    while (i < num_tuples) {
        int j = i;
        while (j < num_tuples && compare_tuples(&sorted_tuples[i], &sorted_tuples[j]) == 0) {
            j++;
        }

        if (count >= capacity) {
            capacity *= 2;
            TupleMap* new_map = (TupleMap*)realloc(map, capacity * sizeof(TupleMap));
            if (new_map == NULL) {
                free(sorted_tuples);
                free(map);
                *unique_count = 0;
                return NULL;
            }
            map = new_map;
        }

        map[count].key = sorted_tuples[i];
        map[count].count = j - i;
        count++;
        i = j;
    }

    free(sorted_tuples);
    *unique_count = count;
    return map;
}

int main() {
    Tuple data[] = {{1, 2}, {3, 4}, {1, 2}, {5, 6}, {3, 4}, {1, 2}};
    int num_tuples = sizeof(data) / sizeof(data[0]);
    int unique_count = 0;

    TupleMap* frequencies = extract_unique_frequencies(data, num_tuples, &unique_count);

    if (frequencies != NULL) {
        for (int i = 0; i < unique_count; i++) {
            printf("(%d, %d): %d\n", frequencies[i].key.a, frequencies[i].key.b, frequencies[i].count);
        }
        free(frequencies);
    }

    return 0;
}