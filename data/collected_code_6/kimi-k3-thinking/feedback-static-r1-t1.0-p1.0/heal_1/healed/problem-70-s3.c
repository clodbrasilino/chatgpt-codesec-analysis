#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

static bool tuples_share_length(const size_t lengths[], size_t tuple_count)
{
    if (lengths == NULL || tuple_count == 0) {
        return false;
    }

    size_t expected_length = lengths[0];

    for (size_t i = 1; i < tuple_count; i++) {
        if (lengths[i] != expected_length) {
            return false;
        }
    }

    return true;
}

static void print_result(bool same_length)
{
    if (same_length) {
        printf("All tuples have the same length.\n");
    } else {
        printf("Not all tuples have the same length.\n");
    }
}

int main(void)
{
    int tuple1[] = {10, 20, 30};
    int tuple2[] = {40, 50, 60};
    int tuple3[] = {70, 80, 90};
    int tuple4[] = {100, 200};

    size_t matching_lengths[] = {
        sizeof(tuple1) / sizeof(tuple1[0]),
        sizeof(tuple2) / sizeof(tuple2[0]),
        sizeof(tuple3) / sizeof(tuple3[0])
    };

    size_t mismatched_lengths[] = {
        sizeof(tuple1) / sizeof(tuple1[0]),
        sizeof(tuple2) / sizeof(tuple2[0]),
        sizeof(tuple4) / sizeof(tuple4[0])
    };

    size_t matching_count = sizeof(matching_lengths) / sizeof(matching_lengths[0]);
    size_t mismatched_count = sizeof(mismatched_lengths) / sizeof(mismatched_lengths[0]);

    print_result(tuples_share_length(matching_lengths, matching_count));
    print_result(tuples_share_length(mismatched_lengths, mismatched_count));

    return 0;
}