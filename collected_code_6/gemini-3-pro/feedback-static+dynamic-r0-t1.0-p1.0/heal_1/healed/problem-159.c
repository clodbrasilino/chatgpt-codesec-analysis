#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

void print_season(int month, int day) {
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        printf("Invalid date\n");
        return;
    }

    if ((month == 3 && day >= 20) || month == 4 || month == 5 || (month == 6 && day < 21)) {
        printf("Spring\n");
    } else if ((month == 6 && day >= 21) || month == 7 || month == 8 || (month == 9 && day < 22)) {
        printf("Summer\n");
    } else if ((month == 9 && day >= 22) || month == 10 || month == 11 || (month == 12 && day < 21)) {
        printf("Autumn\n");
    } else {
        printf("Winter\n");
    }
}

int main(int argc, const char * const argv[]) {
    long month = 0;
    long day = 0;
    char *endptr;

    if (argc == 3) {
        errno = 0;
        month = strtol(argv[1], &endptr, 10);
        if (errno != 0 || *endptr != '\0' || month < 1 || month > 12) {
            printf("Invalid date\n");
            return EXIT_FAILURE;
        }

        errno = 0;
        day = strtol(argv[2], &endptr, 10);
        if (errno != 0 || *endptr != '\0' || day < 1 || day > 31) {
            printf("Invalid date\n");
            return EXIT_FAILURE;
        }
    } else {
        printf("Usage: %s <month> <day>\n", argv[0]);
        return EXIT_FAILURE;
    }

    print_season((int)month, (int)day);

    return EXIT_SUCCESS;
}