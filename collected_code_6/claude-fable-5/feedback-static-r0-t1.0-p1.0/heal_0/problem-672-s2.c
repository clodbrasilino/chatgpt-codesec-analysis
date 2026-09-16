#include <stdio.h>
#include <stdlib.h>

int max_of_three(int a, int b, int c);

int max_of_three(int a, int b, int c)
{
    int max = a;

    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }

    return max;
}

int main(void)
{
    int a;
    int b;
    int c;
    int result;

    printf("Enter three integers: ");

    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    result = max_of_three(a, b, c);

    printf("Maximum: %d\n", result);

    return EXIT_SUCCESS;
}