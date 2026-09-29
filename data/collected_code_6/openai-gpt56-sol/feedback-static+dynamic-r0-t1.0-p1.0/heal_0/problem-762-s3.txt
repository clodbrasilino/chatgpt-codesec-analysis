#include <stdio.h>
#include <stdlib.h>

static int has_30_days(int month)
{
    return month == 4 || month == 6 || month == 9 || month == 11;
}

int main(void)
{
    int month;
    int result;

    if (scanf("%d", &month) != 1) {
        return EXIT_FAILURE;
    }

    if (month < 1 || month > 12) {
        return EXIT_FAILURE;
    }

    result = has_30_days(month);
    printf("%s\n", result ? "Yes" : "No");

    return EXIT_SUCCESS;
}