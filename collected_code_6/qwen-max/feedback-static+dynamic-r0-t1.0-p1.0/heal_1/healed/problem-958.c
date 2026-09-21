#include <stdio.h>
#include <string.h>

void intToRoman(int num, char *roman, size_t len) {
    const char *ones[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    const char *tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    const char *hundreds[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    const char *thousands[] = {"", "M", "MM", "MMM"};

    snprintf(roman, len, "%s%s%s%s%s", thousands[num / 1000], hundreds[(num % 1000) / 100], tens[(num % 100) / 10], ones[num % 10]);
}

int main() {
    int number;
    char roman[16] = "";

    printf("Enter an integer: ");
    if (scanf("%d", &number) == 1 && number > 0 && number < 4000) {
        intToRoman(number, roman, sizeof(roman));
        printf("Roman numeral: %s\n", roman);
    } else {
        printf("Invalid input. Please enter an integer between 1 and 3999.\n");
    }

    return 0;
}