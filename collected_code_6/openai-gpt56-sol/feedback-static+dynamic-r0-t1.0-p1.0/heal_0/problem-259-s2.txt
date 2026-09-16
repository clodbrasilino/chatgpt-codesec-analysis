#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static int maximize_tuples(const Tuple *left, const Tuple *right, Tuple *result)
{
    if (left == NULL || right == NULL || result == NULL) {
        return -1;
    }

    result->first = left->first > right->first ? left->first : right->first;
    result->second = left->second > right->second ? left->second : right->second;

    return 0;
}

int main(void)
{
    Tuple left;
    Tuple right;
    Tuple result;

    if (scanf("%d %d", &left.first, &left.second) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (scanf("%d %d", &right.first, &right.second) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (maximize_tuples(&left, &right, &result) != 0) {
        fputs("Unable to maximize tuples\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("(%d, %d)\n", result.first, result.second) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}