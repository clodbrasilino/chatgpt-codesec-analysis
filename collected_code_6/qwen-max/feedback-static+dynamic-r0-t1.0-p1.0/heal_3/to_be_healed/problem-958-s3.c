#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'L', got <no output>
  *  test case 0 failed: expected 'I', got <no output>
  *  test case 2 failed: expected 'IV', got <no output>
  */

char *intToRoman(int num) {
    const char *romanNumerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    static char roman[20];
    roman[0] = '\0';

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
    printf("%s\n", intToRoman(number));

    number = 1;
    printf("%s\n", intToRoman(number));

    /* Possible weaknesses found:
     *  Assignment 'number=0', assigned value is 0
     */
    number = 0;
    /* Possible weaknesses found:
     *  Condition 'number==0' is always true [knownConditionTrueFalse]
     *  Condition 'number==0' is always true
     */
    if (number == 0) {
        printf("Invalid input: Number must be between 1 and 3999.\n");
    } else {
        printf("%s\n", intToRoman(number));
    }

    number = 4;
    printf("%s\n", intToRoman(number));

    return 0;
}