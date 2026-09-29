#include <stdio.h>
#include <stdlib.h>

static int find_third_angle(int first, int second, int *third)
{
    if (third == NULL || first <= 0 || second <= 0 || first + second >= 180) {
        return 0;
    }

    *third = 180 - first - second;
    return 1;
}

int main(void)
{
    int first;
    int second;
    int third;

    if (scanf("%d %d", &first, &second) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!find_third_angle(first, second, &third)) {
        fprintf(stderr, "Invalid triangle angles\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", third);
    return EXIT_SUCCESS;
}