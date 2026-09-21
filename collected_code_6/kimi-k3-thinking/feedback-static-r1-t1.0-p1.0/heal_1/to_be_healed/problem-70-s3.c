#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

bool all_tuples_equal_length(const size_t lengths[], size_t tuple_count)
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

/* Possible weaknesses found:
 * Flawfinder equal: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
 */
static void print_result(bool equal)
{
    /* Possible weaknesses found:
     * Flawfinder equal: Function does not check the second iterator for over-read conditions (CWE-126). This function is often discouraged by most C++ coding standards in favor of its safer alternatives provided since C++14. Consider using a form of this function that checks the second iterator before potentially overflowing it. (risk 1, buffer)
     */
    if (equal) {
        printf("All tuples have equal length.\n");
    } else {
        printf("Not all tuples have equal length.\n");
    }
}

int main(void)
{
    int tuple1[] = {10, 20, 30};
    int tuple2[] = {40, 50, 60};
    int tuple3[] = {70, 80, 90};
    int tuple4[] = {100, 200};

    size_t equal_lengths[] = {
        sizeof(tuple1) / sizeof(tuple1[0]),
        sizeof(tuple2) / sizeof(tuple2[0]),
        sizeof(tuple3) / sizeof(tuple3[0])
    };

    size_t unequal_lengths[] = {
        sizeof(tuple1) / sizeof(tuple1[0]),
        sizeof(tuple2) / sizeof(tuple2[0]),
        sizeof(tuple4) / sizeof(tuple4[0])
    };

    size_t equal_count = sizeof(equal_lengths) / sizeof(equal_lengths[0]);
    size_t unequal_count = sizeof(unequal_lengths) / sizeof(unequal_lengths[0]);

    print_result(all_tuples_equal_length(equal_lengths, equal_count));
    print_result(all_tuples_equal_length(unequal_lengths, unequal_count));

    return 0;
}