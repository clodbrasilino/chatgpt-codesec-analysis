#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'str' can be declared as pointer to const [constParameterPointer]
 */
int minSwaps(char *str) {
    int len = 0;
    while (str[len] != '\0') len++;
    int open = 0, close = 0, swaps = 0, imbalance = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == '[') open++;
        else if (str[i] == ']') close++;

        if (close > open) {
            imbalance++;
            swaps += imbalance;
        }
    }

    if (open != close) return -1; // Unbalanced string

    return swaps;
}

int main() {
    char str[] = "[]][][";
    int result = minSwaps(str);
    if (result == -1)
        printf("The input string is not balanced.\n");
    else
        printf("Minimum number of swaps required: %d\n", result);

    return 0;
}