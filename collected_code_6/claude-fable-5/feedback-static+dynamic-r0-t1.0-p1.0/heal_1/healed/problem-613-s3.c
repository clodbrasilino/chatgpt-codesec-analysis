#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct Record {
    const int *values;
    size_t count;
};

bool find_max_in_records(const struct Record *records, size_t record_count, int *result)
{
    bool found = false;
    int max_value = INT_MIN;

    if (records == NULL || result == NULL || record_count == 0U) {
        return false;
    }

    for (size_t i = 0U; i < record_count; i++) {
        if (records[i].values == NULL) {
            continue;
        }
        for (size_t j = 0U; j < records[i].count; j++) {
            if (!found || records[i].values[j] > max_value) {
                max_value = records[i].values[j];
                found = true;
            }
        }
    }

    if (found) {
        *result = max_value;
    }

    return found;
}

int main(void)
{
    static const int list1[] = { 100, 142, 65 };
    static const int list2[] = { 98, 233, 23 };
    static const int list3[] = { 45, 165, 78 };

    const struct Record records[] = {
        { list1, sizeof(list1) / sizeof(list1[0]) },
        { list2, sizeof(list2) / sizeof(list2[0]) },
        { list3, sizeof(list3) / sizeof(list3[0]) }
    };

    const size_t record_count = sizeof(records) / sizeof(records[0]);
    int max_value = 0;

    if (find_max_in_records(records, record_count, &max_value)) {
        if (printf("Maximum value in record lists: %d\n", max_value) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (fprintf(stderr, "No values found in records.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}