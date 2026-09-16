#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int value;
} Record;

int find_max_value(const Record *records, size_t count, int *result)
{
    size_t i;
    int max;

    if (records == NULL || result == NULL || count == 0) {
        return -1;
    }

    max = records[0].value;
    for (i = 1; i < count; i++) {
        if (records[i].value > max) {
            max = records[i].value;
        }
    }

    *result = max;
    return 0;
}

int main(void)
{
    Record records[] = {
        {1, 10},
        {2, 45},
        {3, 23},
        {4, 89},
        {5, 17}
    };
    size_t count = sizeof(records) / sizeof(records[0]);
    int max_value = 0;

    if (find_max_value(records, count, &max_value) != 0) {
        fprintf(stderr, "Error: invalid input to find_max_value\n");
        return EXIT_FAILURE;
    }

    printf("Maximum value: %d\n", max_value);
    return EXIT_SUCCESS;
}