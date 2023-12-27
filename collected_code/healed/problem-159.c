#include <stdio.h>

void printSeason(int month, int day) {
    if ((month == 12 && day >= 21) || (month == 1 && day <= 31) || (month == 2 && day <= 28) || (month == 3 && day <= 20 )) {
        printf("Winter\n");
    } else if ((month == 3 && day >= 21) || (month >= 4 && month <= 5) || (month == 6 && day <= 20)) {
        printf("Spring\n");
    } else if ((month == 6 && day >= 21) || (month >= 7 && month <= 8) || (month == 9 && day <= 22)) {
        printf("Summer\n");
    } else {
        printf("Fall\n");
    }
}

int main() {
    int month = 0, day = 0;
    printf("Enter the month (1-12): ");
    scanf("%d", &month);
    printf("Enter the day (1-31): ");
    scanf("%d", &day);

    if ((month >= 1 && month <= 12) && (day >= 1 && day <= 31)) {
        printSeason(month, day);
    } else {
        printf("Invalid input!\n");
    }

    return 0;
}