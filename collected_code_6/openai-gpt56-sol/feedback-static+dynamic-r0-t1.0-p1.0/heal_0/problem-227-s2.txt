#include <stdio.h>
#include <stdlib.h>

static int minimum_of_three(int first, int second, int third)
{
    int minimum = first;

    if (second < minimum) {
        minimum = second;
    }

    if (third < minimum) {
        minimum = third;
    }

    return minimum;
}

int main(void)
{
    int first;
    int second;
    int third;

    if (scanf("%d %d %d", &first, &second, &third) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%d\n", minimum_of_three(first, second, third));

    return EXIT_SUCCESS;
}