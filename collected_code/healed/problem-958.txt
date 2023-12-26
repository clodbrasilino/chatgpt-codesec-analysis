#include <stdio.h>

void convertToRoman(int num) {
    int i;
    int decimals[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    char *roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    for (i = 0; i < sizeof(decimals) / sizeof(decimals[0]); i++) {
        while (num >= decimals[i]) {
            printf("%s", roman[i]);
            num -= decimals[i];
        }
    }
}

int main() {
    int number = 0;

    printf("Enter a number: ");
    scanf("%d", &number);

    if (number > 0) {
        printf("Roman numeral: ");
        convertToRoman(number);
        printf("\n");
    } else {
        printf("Invalid number\n");
    }

    return 0;
}