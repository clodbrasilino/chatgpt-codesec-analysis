#include <stdio.h>
#include <stdlib.h>

static int is_valid_date(int month, int day)
{
    static const int days_in_month[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    return month >= 1 && month <= 12 &&
           day >= 1 && day <= days_in_month[month - 1];
}

static const char *get_season(int month, int day)
{
    if ((month == 3 && day >= 20) || month == 4 || month == 5 ||
        (month == 6 && day < 21)) {
        return "Spring";
    }

    if ((month == 6 && day >= 21) || month == 7 || month == 8 ||
        (month == 9 && day < 22)) {
        return "Summer";
    }

    if ((month == 9 && day >= 22) || month == 10 || month == 11 ||
        (month == 12 && day < 21)) {
        return "Autumn";
    }

    return "Winter";
}

static int print_season(int month, int day)
{
    if (!is_valid_date(month, day)) {
        return -1;
    }

    if (printf("%s\n", get_season(month, day)) < 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    int month;
    int day;
    int extra;

    if (scanf("%d %d", &month, &day) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (scanf(" %c", (char *)&extra) == 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_season(month, day) != 0) {
        fputs("Invalid date\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}