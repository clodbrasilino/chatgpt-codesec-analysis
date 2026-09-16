#include <stdio.h>

void print_season(int month, int day) {
    if (month < 1 || month > 12) {
        printf("Invalid month\n");
        return;
    }
    if (day < 1 || day > 31) {
        printf("Invalid day\n");
        return;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) {
            printf("Invalid day\n");
            return;
        }
    } else if (month == 2) {
        if (day > 29) {
            printf("Invalid day\n");
            return;
        }
    }

    if ((month == 3 && day >= 20) || (month == 4) || (month == 5) || (month == 6 && day < 21)) {
        printf("Spring\n");
    } else if ((month == 6 && day >= 21) || (month == 7) || (month == 8) || (month == 9 && day < 23)) {
        printf("Summer\n");
    } else if ((month == 9 && day >= 23) || (month == 10) || (month == 11) || (month == 12 && day < 21)) {
        printf("Autumn\n");
    } else {
        printf("Winter\n");
    }
}

int main(void) {
    int month = 0;
    int day = 0;

    printf("Enter month (1-12): ");
    if (scanf("%d", &month) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    printf("Enter day (1-31): ");
    if (scanf("%d", &day) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    print_season(month, day);

    return 0;
}