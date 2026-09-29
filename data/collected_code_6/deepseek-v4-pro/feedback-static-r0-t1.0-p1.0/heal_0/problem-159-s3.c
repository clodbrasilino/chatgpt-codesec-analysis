#include <stdio.h>
#include <stdlib.h>

void print_season(int month, int day) {
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        printf("Invalid date\n");
        return;
    }

    int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (day > days_in_month[month]) {
        printf("Invalid date\n");
        return;
    }

    if ((month == 3 && day >= 20) || (month > 3 && month < 6) || (month == 6 && day <= 20)) {
        printf("Spring\n");
    } else if ((month == 6 && day >= 21) || (month > 6 && month < 9) || (month == 9 && day <= 21)) {
        printf("Summer\n");
    } else if ((month == 9 && day >= 22) || (month > 9 && month < 12) || (month == 12 && day <= 20)) {
        printf("Autumn\n");
    } else {
        printf("Winter\n");
    }
}

int main(void) {
    int month, day;
    
    if (scanf("%d %d", &month, &day) != 2) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }

    print_season(month, day);
    return EXIT_SUCCESS;
}