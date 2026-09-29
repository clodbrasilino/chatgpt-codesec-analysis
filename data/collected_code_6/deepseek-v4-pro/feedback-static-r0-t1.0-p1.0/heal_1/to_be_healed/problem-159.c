#include <stdio.h>
#include <stdlib.h>

void print_season(int month, int day) {
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        fprintf(stderr, "Invalid date\n");
        exit(EXIT_FAILURE);
    }

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        fprintf(stderr, "Invalid date\n");
        exit(EXIT_FAILURE);
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'month==2' is not redundant
     */
    if (month == 2) {
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (day > 29) {
            fprintf(stderr, "Invalid date\n");
            exit(EXIT_FAILURE);
        }
        /* Possible weaknesses found:
         *  Condition 'month==2' is always true
         *  Condition 'month==2' is always true [knownConditionTrueFalse]
         */
        if (day == 29 && month == 2) {
            fprintf(stderr, "Invalid date\n");
            exit(EXIT_FAILURE);
        }
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

int main(void) {
    int month, day;

    printf("Enter month (1-12): ");
    if (scanf("%d", &month) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter day (1-31): ");
    if (scanf("%d", &day) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    print_season(month, day);

    return 0;
}