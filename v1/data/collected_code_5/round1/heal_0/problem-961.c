#include <stdio.h>
#include <string.h>

int value(char roman) {
    switch (roman) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            return -1;
    }
}

int romanToDecimal(char *roman) {
    int i = 0;
    int total = 0;
    while (roman[i]) {
        int current_symbol = value(roman[i]);
        if (current_symbol < 0) {
            return -1;
        }

        if (i+1 < strlen(roman)) {
            int next_symbol = value(roman[i+1]);
            if (next_symbol < 0) {
                return -1;
            }

            if (current_symbol >= next_symbol) {
                total = total + current_symbol;
            } else {
                total = total + next_symbol - current_symbol;
                i++;
            }
        } else {
            total = total + current_symbol;
        }

        i++;
    }

    return total;
}

int main() {
    char roman[1000];
    printf("Enter a Roman Numeral: ");
    scanf("%s", roman);

    int result = romanToDecimal(roman);

    if (result < 0) {
        printf("Invalid Roman numeral\n");
    } else {
        printf("Roman Numeral converts to %d\n", result);
    }

    return 0;
}