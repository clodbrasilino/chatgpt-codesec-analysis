#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Record;

typedef struct {
    int id;
    Record *records;
    size_t record_count;
} Tuple;

int find_max_in_tuple_records(Tuple *tuples, size_t tuple_count) {
    if (tuples == NULL || tuple_count == 0) {
        return -1;
    }

    int max_val = tuples[0].records[0].b;
    for (size_t i = 0; i < tuple_count; i++) {
        if (tuples[i].records == NULL || tuples[i].record_count == 0) {
            continue;
        }
        for (size_t j = 0; j < tuples[i].record_count; j++) {
            if (tuples[i].records[j].b > max_val) {
                max_val = tuples[i].records[j].b;
            }
        }
    }
    return max_val;
}

int main(void) {
    Record recs1[] = {{1, 10}, {2, 45}, {3, 22}};
    Record recs2[] = {{4, 5}, {5, 88}, {6, 33}};
    Record recs3[] = {{7, 99}, {8, 12}};
    Record recs4[] = {{9, 77}, {10, 100}};
    
    Tuple tuples[] = {
        {100, recs1, sizeof(recs1) / sizeof(recs1[0])},
        {200, recs2, sizeof(recs2) / sizeof(recs2[0])},
        {300, recs3, sizeof(recs3) / sizeof(recs3[0])},
        {400, recs4, sizeof(recs4) / sizeof(recs4[0])}
    };
    
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    
    int max_val = find_max_in_tuple_records(tuples, tuple_count);
    
    printf("%d\n", max_val);
    
    return 0;
}