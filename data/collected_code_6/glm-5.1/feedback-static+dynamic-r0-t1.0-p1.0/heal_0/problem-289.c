#include <stdio.h>
#include <stdlib.h>

int calculate_odd_days(int year) {
    if (year < 1) {
        return -1;
    }

    int odd_days = year % 400;

    int centuries = odd_days / 100;
    int remaining_years = odd_days % 100;

    int century_odd_days = (centuries * 5) % 7;

    int leap_years = remaining_years / 4;
    int normal_years = remaining_years - leap_years;

    int year_odd_days = (normal_years * 1 + leap_years * 2) % 7;

    return (century_odd_days + year_odd_days) % 7;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <year>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long year = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || year < 1 || year > 2147483647) {
        fprintf(stderr, "Invalid year provided.\n");
        return EXIT_FAILURE;
    }

    int result = calculate_odd_days((int)year);

    if (result == -1) {
        fprintf(stderr, "Invalid year provided.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}