#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char *argv[]) {
    int month = 0;
    int day = 0;

    if (argc == 3) {
        month = atoi(argv[1]);
        day = atoi(argv[2]);
    } else {
        printf("Usage: %s <month> <day>\n", argv[0]);
        return EXIT_FAILURE;
    }

    print_season(month, day);

    return EXIT_SUCCESS;
}