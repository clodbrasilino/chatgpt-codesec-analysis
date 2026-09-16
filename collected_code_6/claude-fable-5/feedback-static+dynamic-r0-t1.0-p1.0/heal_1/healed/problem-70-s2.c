#include <stdio.h>
#include <stddef.h>

typedef struct {
    const int *elements;
    size_t length;
} Tuple;

int all_tuples_equal_length(const Tuple *tuples, size_t count, size_t expected)
{
    size_t i;

    if (tuples == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (tuples[i].elements == NULL) {
            return 0;
        }
        if (tuples[i].length != expected) {
            return 0;
        }
    }

    return 1;
}

int print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;
    size_t j;

    if (tuples == NULL) {
        return 1;
    }

    for (i = 0; i < count; i++) {
        if (tuples[i].elements == NULL) {
            return 1;
        }
        if (printf("Tuple %zu:", i) < 0) {
            return 1;
        }
        for (j = 0; j < tuples[i].length; j++) {
            if (printf(" %d", tuples[i].elements[j]) < 0) {
                return 1;
            }
        }
        if (printf("\n") < 0) {
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    const int t1[] = {11, 22, 33};
    const int t2[] = {44, 55, 66};
    const int t3[] = {77, 88};

    const Tuple set1[] = {
        {t1, sizeof(t1) / sizeof(t1[0])},
        {t2, sizeof(t2) / sizeof(t2[0])}
    };

    const Tuple set2[] = {
        {t1, sizeof(t1) / sizeof(t1[0])},
        {t3, sizeof(t3) / sizeof(t3[0])}
    };

    if (print_tuples(set1, sizeof(set1) / sizeof(set1[0])) != 0) {
        return 1;
    }

    if (all_tuples_equal_length(set1, sizeof(set1) / sizeof(set1[0]), 3)) {
        if (printf("All tuples have same length\n") < 0) {
            return 1;
        }
    } else {
        if (printf("All tuples do not have same length\n") < 0) {
            return 1;
        }
    }

    if (print_tuples(set2, sizeof(set2) / sizeof(set2[0])) != 0) {
        return 1;
    }

    if (all_tuples_equal_length(set2, sizeof(set2) / sizeof(set2[0]), 3)) {
        if (printf("All tuples have same length\n") < 0) {
            return 1;
        }
    } else {
        if (printf("All tuples do not have same length\n") < 0) {
            return 1;
        }
    }

    return 0;
}