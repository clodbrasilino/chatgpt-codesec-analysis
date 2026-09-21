#include <stdio.h>
#include <stdlib.h>

static int is_valid_date(int month, int day)
{
    static const int days_in_month[] = {
        31, 29, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    return month >= 1 && month <= 12 &&
           day >= 1 && day <= days_in_month[month - 1];
}

static const char *get_season(int month, int day)
{
    int date = month * 100 + day;

    if (date >= 1221 || date < 320) {
        return "Winter";
    }

    if (date < 621) {
        return "Spring";
    }

    if (date < 923) {
        return "Summer";
    }

    return "Autumn";
}

int main(void)
{
    char input[128];
    int month;
    int day;
    char trailing;

    fputs("Enter month and day: ", stdout);
    fflush(stdout);

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sscanf(input, " %d %d %c", &month, &day, &trailing) != 2) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!is_valid_date(month, day)) {
        fputs("Invalid date.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%s\n", get_season(month, day));
    return EXIT_SUCCESS;
}