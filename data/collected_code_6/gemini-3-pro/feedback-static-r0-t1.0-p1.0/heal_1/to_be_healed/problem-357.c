#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'TupleRecord::id' is never used. [unusedStructMember]
     */
    int id;
    int *values;
    size_t num_values;
} TupleRecord;

int find_maximum_element(TupleRecord *records, size_t num_records, int *max_value) {
    if (records == NULL || max_value == NULL || num_records == 0) {
        return -1;
    }

    int global_max = INT_MIN;
    int found_any = 0;

    for (size_t i = 0; i < num_records; ++i) {
        if (records[i].values != NULL && records[i].num_values > 0) {
            for (size_t j = 0; j < records[i].num_values; ++j) {
                if (records[i].values[j] > global_max) {
                    global_max = records[i].values[j];
                    found_any = 1;
                }
            }
        }
    }

    if (!found_any) {
        return -1;
    }

    *max_value = global_max;
    return 0;
}

int main(void) {
    int vals1[] = {1, 5, 3};
    int vals2[] = {4, 9, 2};
    int vals3[] = {-1, 0};

    TupleRecord records[3] = {
        {1, vals1, 3},
        {2, vals2, 3},
        {3, vals3, 2}
    };

    int max_val;
    if (find_maximum_element(records, 3, &max_val) == 0) {
        printf("Maximum element: %d\n", max_val);
    } else {
        printf("Failed to find maximum element.\n");
    }

    return 0;
}