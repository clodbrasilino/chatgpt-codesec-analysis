#include <stdio.h>

void print_season(int month, int day) {
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        printf("Invalid date\n");
        return;
    }

    if ((month == 4 && day >= 1) || month == 5 || (month == 6 && day <= 20)) {
        printf("Spring\n");
    } else if ((month == 6 && day >= 21) || month == 7 || month == 8 || (month == 9 && day <= 21)) {
        printf("Summer\n");
    } else if ((month == 9 && day >= 22) || month == 10 || month == 11 || (month == 12 && day <= 20)) {
        printf("Autumn\n");
    } else {
        printf("Winter\n");
    }
}

int main(void) {
    int month, day;

    printf("Enter month and day: ");
    if (scanf("%d %d", &month, &day) != 2) {
        printf("Invalid input\n");
        return 1;
    }

    print_season(month, day);

    return 0;
}