#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int pentagon_perimeter(const int sides[static 5], int *result)
{
    int perimeter = 0;

    if (sides == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0U; i < 5U; ++i) {
        if (sides[i] <= 0 || perimeter > INT_MAX - sides[i]) {
            return 0;
        }

        perimeter += sides[i];
    }

    *result = perimeter;
    return 1;
}

int main(void)
{
    int sides[5];
    int perimeter;

    for (size_t i = 0U; i < 5U; ++i) {
        if (scanf("%d", &sides[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            return EXIT_FAILURE;
        }
    }

    if (!pentagon_perimeter(sides, &perimeter)) {
        fprintf(stderr, "Unable to calculate the perimeter.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", perimeter);
    return EXIT_SUCCESS;
}