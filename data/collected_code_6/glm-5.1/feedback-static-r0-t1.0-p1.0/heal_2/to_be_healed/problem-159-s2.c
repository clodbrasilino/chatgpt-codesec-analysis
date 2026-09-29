#include <stdio.h>
#include <stdlib.h>

int is_valid_date(int month, int day) {
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return 0;
    if (month == 2 && day > 29) return 0;
    return 1;
}

void print_season(int month, int day) {
    if (!is_valid_date(month, day)) {
        fprintf(stderr, "Invalid date\n");
        return;
    }

    if ((month == 12 && day >= 21) || (month == 1) || (month == 2) || (month == 3 && day <= 19)) {
        printf("Winter\n");
    } else if ((month == 3 && day >= 20) || (month == 4) || (month == 5) || (month == 6 && day <= 20)) {
        printf("Spring\n");
    } else if ((month == 6 && day >= 21) || (month == 7) || (month == 8) || (month == 9 && day <= 22)) {
        printf("Summer\n");
    } else if ((month == 9 && day >= 23) || (month == 10) || (month == 11) || (month == 12 && day <= 20)) {
        printf("Autumn\n");
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <month> <day>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_month;
    long month_long = strtol(argv[1], &endptr_month, 10);
    if (*endptr_month != '\0' || month_long < 1 || month_long > 12) {
        fprintf(stderr, "Invalid month\n");
        return EXIT_FAILURE;
    }

    char *endptr_day;
    long day_long = strtol(argv[2], &endptr_day, 10);
    if (*endptr_day != '\0' || day_long < 1 || day_long > 31) {
        fprintf(stderr, "Invalid day\n");
        return EXIT_FAILURE;
    }

    print_season((int)month_long, (int)day_long);

    return EXIT_SUCCESS;
}