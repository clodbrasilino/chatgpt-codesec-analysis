#include <stdio.h>

void print_season(int month, int day) {
    if (month == 1 || (month == 2 && day < 20) || (month == 12 && day >= 21)) {
        printf("Winter\n");
    } else if ((month == 2 && day >= 20) || month == 3 || (month == 4 && day < 20)) {
        printf("Spring\n");
    } else if ((month == 4 && day >= 20) || month == 5 || month == 6 || (month == 7 && day < 21)) {
        printf("Summer\n");
    } else if ((month == 7 && day >= 21) || month == 8 || (month == 9 && day < 22)) {
        printf("Autumn\n");
    } else {
        printf("Unknown\n");
    }
}

int main() {
    int month, day;
    printf("Enter month (1-12) and day (1-31): ");
    if (scanf("%d %d", &month, &day) != 2 || month < 1 || month > 12 || day < 1 || day > 31) {
        printf("Invalid input.\n");
        return 1;
    }
    print_season(month, day);
    return 0;
}