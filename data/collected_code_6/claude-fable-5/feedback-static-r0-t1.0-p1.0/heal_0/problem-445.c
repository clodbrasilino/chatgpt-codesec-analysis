#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int safe_multiply(int a, int b, int *result)
{
    if (a > 0) {
        if (b > 0) {
            if (a > INT_MAX / b) {
                return -1;
            }
        } else {
            if (b < INT_MIN / a) {
                return -1;
            }
        }
    } else {
        if (b > 0) {
            if (a < INT_MIN / b) {
                return -1;
            }
        } else {
            if (a != 0 && b < INT_MAX / a) {
                return -1;
            }
        }
    }
    *result = a * b;
    return 0;
}

int multiply_tuples(const Tuple *t1, const Tuple *t2, size_t count, Tuple *out)
{
    size_t i;

    if (t1 == NULL || t2 == NULL || out == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (safe_multiply(t1[i].first, t2[i].first, &out[i].first) != 0) {
            return -1;
        }
        if (safe_multiply(t1[i].second, t2[i].second, &out[i].second) != 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    Tuple tuple1[] = { {1, 3}, {4, 5}, {2, 9}, {1, 10} };
    Tuple tuple2[] = { {6, 7}, {3, 9}, {1, 1}, {7, 3} };
    size_t count = sizeof(tuple1) / sizeof(tuple1[0]);
    Tuple *result;
    size_t i;

    result = malloc(count * sizeof(Tuple));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (multiply_tuples(tuple1, tuple2, count, result) != 0) {
        fprintf(stderr, "Multiplication failed\n");
        free(result);
        return EXIT_FAILURE;
    }

    printf("Result: ");
    for (i = 0; i < count; i++) {
        printf("(%d, %d) ", result[i].first, result[i].second);
    }
    printf("\n");

    free(result);
    return EXIT_SUCCESS;
}