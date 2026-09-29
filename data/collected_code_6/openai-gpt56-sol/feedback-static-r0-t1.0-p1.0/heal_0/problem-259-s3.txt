#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

static Tuple maximize_tuples(Tuple left, Tuple right)
{
    Tuple result = {
        .first = left.first > right.first ? left.first : right.first,
        .second = left.second > right.second ? left.second : right.second
    };

    return result;
}

int main(void)
{
    Tuple left;
    Tuple right;

    if (scanf("%d %d", &left.first, &left.second) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (scanf("%d %d", &right.first, &right.second) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    Tuple result = maximize_tuples(left, right);

    if (printf("(%d, %d)\n", result.first, result.second) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}