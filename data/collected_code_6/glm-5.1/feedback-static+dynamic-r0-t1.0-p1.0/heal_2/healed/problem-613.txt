#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int b;
} Record;

typedef struct {
    Record *records;
    size_t record_count;
} Tuple;

int find_max_in_tuple_records(Tuple *tuples, size_t tuple_count) {
    if (tuples == NULL || tuple_count == 0) {
        return INT_MIN;
    }

    int max_val = INT_MIN;
    for (size_t i = 0; i < tuple_count; i++) {
        if (tuples[i].records == NULL || tuples[i].record_count == 0) {
            continue;
        }
        if (tuples[i].records[0].b > max_val) {
            max_val = tuples[i].records[0].b;
        }
        for (size_t j = 1; j < tuples[i].record_count; j++) {
            if (tuples[i].records[j].b > max_val) {
                max_val = tuples[i].records[j].b;
            }
        }
    }
    return max_val;
}

int main(void) {
    Record recs1[] = {{10}, {45}, {22}};
    Record recs2[] = {{5}, {88}, {33}};
    Record recs3[] = {{99}, {12}};
    Record recs4[] = {{77}, {100}};
    
    Tuple tuples[] = {
        {recs1, sizeof(recs1) / sizeof(recs1[0])},
        {recs2, sizeof(recs2) / sizeof(recs2[0])},
        {recs3, sizeof(recs3) / sizeof(recs3[0])},
        {recs4, sizeof(recs4) / sizeof(recs4[0])}
    };
    
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    
    int max_val = find_max_in_tuple_records(tuples, tuple_count);
    
    printf("%d\n", max_val);
    
    return 0;
}