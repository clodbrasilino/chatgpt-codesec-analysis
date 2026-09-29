#include <stdio.h>
#include <stdlib.h>

static int has_30_days(int month)
{
    return month == 4 || month == 6 || month == 9 || month == 11;
}

int main(void)
{
    int month;

    if (scanf("%d", &month) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (month < 1 || month > 12) {
        fprintf(stderr, "Month must be between 1 and 12\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", has_30_days(month) ? "Yes" : "No");

    return EXIT_SUCCESS;
}