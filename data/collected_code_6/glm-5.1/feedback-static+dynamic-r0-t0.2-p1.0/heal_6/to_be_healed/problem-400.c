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
     *  Assuming condition 'tuples==NULL' is false
     *  Assuming condition 'num_tuples<=0' is false
     */
    if (tuples == NULL || num_tuples <= 0 || unique_count == NULL) {
        if (unique_count != NULL) {
            *unique_count = 0;
        }
        return NULL;
    }

    Tuple* sorted_tuples = (Tuple*)malloc(num_tuples * sizeof(Tuple));
    /* Possible weaknesses found:
     *  Assuming condition is false
     *  Assuming condition 'sorted_tuples==NULL' is false
     */
    if (sorted_tuples == NULL) {
        *unique_count = 0;
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'tuples!=NULL' is always true [knownConditionTrueFalse]
     *  Condition 'num_tuples>0' is always true
     *  Condition 'sorted_tuples!=NULL' is always true
     *  Condition 'num_tuples>0' is always true [knownConditionTrueFalse]
     *  Condition 'tuples!=NULL' is always true
     *  Condition 'sorted_tuples!=NULL' is always true [knownConditionTrueFalse]
     */
    if (num_tuples > 0 && tuples != NULL && sorted_tuples != NULL) {
        /* Possible weaknesses found:
         *  'copy_size' is assigned value 'num_tuples*sizeof(struct Tuple)' here.
         */
        size_t copy_size = num_tuples * sizeof(Tuple);
        /* Possible weaknesses found:
         *  'src_size' is assigned value 'num_tuples*sizeof(struct Tuple)' here.
         */
        size_t src_size = num_tuples * sizeof(Tuple);
        /* Possible weaknesses found:
         *  The comparison 'src_size <= copy_size' is always true because 'src_size' and 'copy_size' represent the same value. [knownConditionTrueFalse]
         *  The comparison 'src_size <= copy_size' is always true because 'src_size' and 'copy_size' represent the same value.
         */
        if (src_size <= copy_size) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(sorted_tuples, tuples, copy_size);
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
    for (int i = 0; i < num_tuples; i++) {
        if (count > 0 && compare_tuples(&sorted_tuples[i], &map[count - 1].key) == 0) {
            map[count - 1].count++;
        } else {
            if (count >= capacity) {
                capacity *= 2;
                TupleMap* temp = (TupleMap*)realloc(map, capacity * sizeof(TupleMap));
                if (temp == NULL) {
                    free(map);
                    free(sorted_tuples);
                    *unique_count = 0;
                    return NULL;
                }
                map = temp;
            }
            map[count].key = sorted_tuples[i];
            map[count].count = 1;
            count++;
        }
    }

    free(sorted_tuples);
    *unique_count = count;

    TupleMap* result = (TupleMap*)realloc(map, count * sizeof(TupleMap));
    if (result != NULL) {
        return result;
    }
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