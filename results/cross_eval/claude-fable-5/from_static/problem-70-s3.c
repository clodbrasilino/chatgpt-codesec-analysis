#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

bool all_tuples_equal_length(const Tuple *tuples, size_t count, size_t expected_length, bool *result)
{
    size_t i;

    if ((tuples == NULL) || (result == NULL)) {
        return false;
    }

    *result = true;

    for (i = 0U; i < count; i++) {
        if (tuples[i].length != expected_length) {
            *result = false;
            break;
        }
    }

    return true;
}

int main(void)
{
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5, 6};
    int data3[] = {7, 8, 9};
    int data4[] = {1, 2};

    Tuple set1[3];
    Tuple set2[3];
    bool result = false;

    set1[0].elements = data1;
    set1[0].length = 3U;
    set1[1].elements = data2;
    set1[1].length = 3U;
    set1[2].elements = data3;
    set1[2].length = 3U;

    set2[0].elements = data1;
    set2[0].length = 3U;
    set2[1].elements = data4;
    set2[1].length = 2U;
    set2[2].elements = data3;
    set2[2].length = 3U;

    if (all_tuples_equal_length(set1, 3U, 3U, &result)) {
        if (result) {
            (void)printf("Set 1: All tuples have equal length\n");
        } else {
            (void)printf("Set 1: Tuples do not have equal length\n");
        }
    } else {
        (void)fprintf(stderr, "Error: invalid input for set 1\n");
        return EXIT_FAILURE;
    }

    if (all_tuples_equal_length(set2, 3U, 3U, &result)) {
        if (result) {
            (void)printf("Set 2: All tuples have equal length\n");
        } else {
            (void)printf("Set 2: Tuples do not have equal length\n");
        }
    } else {
        (void)fprintf(stderr, "Error: invalid input for set 2\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}