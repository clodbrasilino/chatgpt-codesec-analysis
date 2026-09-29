#include <stdio.h>
#include <stdlib.h>

void print_season(int month, int day) {
    static const int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        fprintf(stderr, "Invalid date\n");
        exit(EXIT_FAILURE);
    }

    if (day > days_in_month[month]) {
        fprintf(stderr, "Invalid date\n");
        exit(EXIT_FAILURE);
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