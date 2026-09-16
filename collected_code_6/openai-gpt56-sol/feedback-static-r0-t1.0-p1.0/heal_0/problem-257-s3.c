#include <stdio.h>
#include <stdlib.h>

static void swap(int *const first, int *const second)
{
    const int temporary = *first;
    *first = *second;
    *second = temporary;
}

int main(void)
{
    int first;
    int second;

    if (printf("Enter two integers: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%d %d", &first, &second) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    swap(&first, &second);

    if (printf("After swapping: %d %d\n", first, second) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}