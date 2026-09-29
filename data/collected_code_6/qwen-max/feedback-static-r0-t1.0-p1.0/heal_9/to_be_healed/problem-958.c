#include <stdio.h>
#include <string.h>

void intToRoman(int num, char *roman, size_t size) {
    const char *ones[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    const char *tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    const char *hundreds[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    const char *thousands[] = {"", "M", "MM", "MMM"};

    snprintf(roman, size, "%s%s%s%s",
             thousands[num / 1000],
             hundreds[(num % 1000) / 100],
             tens[(num % 100) / 10],
             ones[num % 10]);
}

int main() {
    int number;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     *  The scope of the variable 'roman' can be reduced. [variableScope]
     */
    char roman[16] = "";

    printf("Enter an integer: ");
    if (scanf("%d", &number) == 1 && number >= 1 && number <= 3999) {
        intToRoman(number, roman, sizeof(roman) - 1);
        printf("Roman numeral: %s\n", roman);
    } else {
        printf("Invalid input. Please enter an integer between 1 and 3999.\n");
    }

    return 0;
}