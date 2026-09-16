#include <stdio.h>
#include <string.h>

char *intToRoman(int num, char *roman) {
    const char *romanNumerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    roman[0] = '\0';

    if (num < 1 || num > 3999) {
        return "";
    }

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            strcat(roman, romanNumerals[i]);
            num -= values[i];
        }
    }

    return roman;
}

int main() {
    int number = 1994;
    char roman[20];
    printf("%s\n", intToRoman(number, roman));

    number = 1;
    printf("%s\n", intToRoman(number, roman));

    /* Possible weaknesses found:
     *  Assignment 'number=0', assigned value is 0
     */
    number = 0;
    /* Possible weaknesses found:
     *  Condition 'number<1' is always true [knownConditionTrueFalse]
     *  Condition 'number<1' is always true
     */
    if (number < 1 || number > 3999) {
        printf("Invalid input: Number must be between 1 and 3999.\n");
    } else {
        printf("%s\n", intToRoman(number, roman));
    }

    number = 4;
    printf("%s\n", intToRoman(number, roman));

    return 0;
}