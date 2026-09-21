#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

bool all_tuples_same_length(const size_t lengths[], size_t tuple_count)
{
    size_t expected_length;
    size_t i;

    if (lengths == NULL || tuple_count == 0) {
        return false;
    }

    expected_length = lengths[0];

    for (i = 1; i < tuple_count; i++) {
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
        printf("Tuple lengths differ.\n");
    }
}

int main(void)
{
    int tuple1[] = {10, 20, 30};
    int tuple2[] = {40, 50, 60};
    int tuple3[] = {70, 80, 90};
    int tuple4[] = {100, 200};

    size_t uniform_lengths[] = {
        sizeof(tuple1) / sizeof(tuple1[0]),
        sizeof(tuple2) / sizeof(tuple2[0]),
        sizeof(tuple3) / sizeof(tuple3[0])
    };

    size_t mixed_lengths[] = {
        sizeof(tuple1) / sizeof(tuple1[0]),
        sizeof(tuple2) / sizeof(tuple2[0]),
        sizeof(tuple4) / sizeof(tuple4[0])
    };

    size_t uniform_count = sizeof(uniform_lengths) / sizeof(uniform_lengths[0]);
    size_t mixed_count = sizeof(mixed_lengths) / sizeof(mixed_lengths[0]);

    print_result(all_tuples_same_length(uniform_lengths, uniform_count));
    print_result(all_tuples_same_length(mixed_lengths, mixed_count));

    return 0;
}