#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int value;
} Tuple;

int extract_min_index(Tuple *tuples, size_t count, Tuple *result) {
    if (tuples == NULL || result == NULL || count == 0) {
        return -1;
    }

    size_t min_pos = 0;
    for (size_t i = 1; i < count; i++) {
        if (tuples[i].value < tuples[min_pos].value) {
            min_pos = i;
        }
    }

    *result = tuples[min_pos];
    return 0;
}

int main(void) {
    Tuple data[] = {
        {0, 42},
        {1, 17},
        {2, 65},
        {3, 8},
        {4, 23}
    };
    size_t data_count = sizeof(data) / sizeof(data[0]);

    Tuple min_record;
    int status = extract_min_index(data, data_count, &min_record);

    if (status == 0) {
        printf("Index: %d, Value: %d\n", min_record.index, min_record.value);
    } else {
        printf("Extraction failed.\n");
    }

    return 0;
}