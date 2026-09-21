#include <stdio.h>
#include <string.h>
#include <stddef.h>

static int isVowel(char c) {
    switch (c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            return 1;
        default:
            return 0;
    }
}

void reverseVowels(char *str) {
    if (str == NULL) {
        return;
    }

    size_t left = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t right = strlen(str);

    while (left < right) {
        if (!isVowel(str[left])) {
            left++;
        } else if (!isVowel(str[right - 1])) {
            right--;
        } else {
            char temp = str[left];
            str[left] = str[right - 1];
            str[right - 1] = temp;
            left++;
            right--;
        }
    }
}

int main(void) {
    char str[] = "leetcode";

    reverseVowels(str);
    printf("%s\n", str);

    return 0;
}