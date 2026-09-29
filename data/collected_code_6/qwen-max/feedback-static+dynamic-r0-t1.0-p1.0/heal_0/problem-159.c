#include <stdio.h>

char *get_season(int month, int day) {
    if (month == 1 || month == 2 || (month == 3 && day < 20) || (month == 12 && day >= 21)) return "Winter";
    if (month == 3 && day >= 20 || month == 4 || month == 5 || (month == 6 && day < 21)) return "Spring";
    if (month == 6 && day >= 21 || month == 7 || month == 8 || (month == 9 && day < 22)) return "Summer";
    if (month == 9 && day >= 22 || month == 10 || month == 11 || (month == 12 && day < 21)) return "Autumn";
    return "Invalid Date";
}

int main() {
    int month = 0;
    int day = 0;
    printf("Enter month (1-12) and day (1-31): ");
    scanf("%d %d", &month, &day);
    if (month >= 1 && month <= 12 && day >= 1 && day <= 31) {
        char *season = get_season(month, day);
        printf("The season is: %s\n", season);
    } else {
        printf("Invalid input. Please enter a valid month (1-12) and day (1-31).\n");
    }
    return 0;
}