#include <stdio.h>

void printSeason(int month, int day) {
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        printf("Invalid date\n");
        return;
    }

    if ((month == 12 && day >= 21) || (month == 1) || (month == 2) || (month == 3 && day < 20)) {
        printf("Winter\n");
    } else if ((month == 3 && day >= 20) || (month == 4) || (month == 5) || (month == 6 && day < 21)) {
        printf("Spring\n");
    } else if ((month == 6 && day >= 21) || (month == 7) || (month == 8) || (month == 9 && day < 23)) {
        printf("Summer\n");
    } else if ((month == 9 && day >= 23) || (month == 10) || (month == 11) || (month == 12 && day < 21)) {
        printf("Autumn\n");
    }
}

int main(void) {
    int month, day;

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

    printSeason(month, day);

    return 0;
}