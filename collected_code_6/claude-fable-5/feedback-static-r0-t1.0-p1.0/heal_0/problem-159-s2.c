#include <stdio.h>
#include <stdlib.h>

static int days_in_month(int month)
{
    static const int days[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month < 1 || month > 12) {
        return 0;
    }
    return days[month - 1];
}

static int is_valid_date(int month, int day)
{
    if (month < 1 || month > 12) {
        return 0;
    }
    if (day < 1 || day > days_in_month(month)) {
        return 0;
    }
    return 1;
}

static const char *get_season(int month, int day)
{
    if ((month == 12 && day >= 21) || month == 1 || month == 2 ||
        (month == 3 && day < 21)) {
        return "Winter";
    }
    if ((month == 3 && day >= 21) || month == 4 || month == 5 ||
        (month == 6 && day < 21)) {
        return "Spring";
    }
    if ((month == 6 && day >= 21) || month == 7 || month == 8 ||
        (month == 9 && day < 21)) {
        return "Summer";
    }
    return "Autumn";
}

static int print_season(int month, int day)
{
    const char *season;

    if (!is_valid_date(month, day)) {
        fprintf(stderr, "Invalid date: month=%d day=%d\n", month, day);
        return -1;
    }

    season = get_season(month, day);
    if (printf("The season for %d/%d is %s\n", month, day, season) < 0) {
        return -1;
    }
    return 0;
}

int main(void)
{
    int month;
    int day;

    printf("Enter month (1-12): ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }
    if (scanf("%d", &month) != 1) {
        fprintf(stderr, "Failed to read month\n");
        return EXIT_FAILURE;
    }

    printf("Enter day: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }
    if (scanf("%d", &day) != 1) {
        fprintf(stderr, "Failed to read day\n");
        return EXIT_FAILURE;
    }

    if (print_season(month, day) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}