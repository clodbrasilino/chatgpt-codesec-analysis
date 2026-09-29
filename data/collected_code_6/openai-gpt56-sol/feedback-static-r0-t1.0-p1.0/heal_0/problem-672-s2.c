#include <stdio.h>
#include <stdlib.h>

static int maximum_of_three(int first, int second, int third)
{
    int maximum = first;

    if (second > maximum) {
        maximum = second;
    }

    if (third > maximum) {
        maximum = third;
    }

    return maximum;
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

    printf("%d\n", maximum_of_three(first, second, third));

    return EXIT_SUCCESS;
}