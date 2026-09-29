#include <stdio.h>

void print_season(int month, int day) {
    if (month == 1 || month == 2 || (month == 3 && day <= 20)) {
        printf("Winter\n");
    } else if (month == 3 && day > 20 || month == 4 || month == 5 || (month == 6 && day <= 20)) {
        printf("Spring\n");
    } else if (month == 6 && day > 20 || month == 7 || month == 8 || (month == 9 && day <= 22)) {
        printf("Summer\n");
    } else if (month == 9 && day > 22 || month == 10 || month == 11 || (month == 12 && day <= 21)) {
        printf("Autumn\n");
    } else if (month == 12 && day > 21) {
        printf("Winter\n");
    }
}

int main() {
    int month, day;
    printf("Enter month and day: ");
    scanf("%d %d", &month, &day);

    if (month >= 1 && month <= 12 && day >= 1 && day <= 31) {
        print_season(month, day);
    } else {
        printf("Invalid date\n");
    }

    return 0;
}