#include <stdio.h>

int calculate_odd_days(int year) {
    if (year < 1) {
        return -1;
    }

    int hundreds = year / 100;
    int remaining = year % 100;

    int hundreds_odd = (hundreds % 4) * 100;
    hundreds_odd = (hundreds_odd / 100) + (hundreds_odd % 100);

    hundreds_odd = (hundreds_odd % 400) / 100;

    int remaining_odd = remaining + (remaining / 4);
    remaining_odd = remaining_odd % 7;

    int total_odd = hundreds_odd + remaining_odd;

    return total_odd % 7;
}

int main() {
    int year;
    if (scanf("%d", &year) != 1) {
        return 1;
    }

    int result = calculate_odd_days(year);
    
    if (result == -1) {
        return 1;
    }

    printf("%d\n", result);
    return 0;
}