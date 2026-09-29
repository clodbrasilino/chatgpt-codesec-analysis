#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isAlternating(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (str == NULL || strlen(str) < 2) {
        return false;
    }

    char first = str[0];
    char second = str[1];

    if (first == second) {
        return false;
    }

    /* Possible weaknesses found:
     *  Assignment 'i=2', assigned value is 2
     *  Array index out of bounds
     *  Array 'str[2]' accessed at index 2, which is out of bounds. [arrayIndexOutOfBounds]
     */
    for (size_t i = 2; str[i] != '\0'; i++) {
        if (i % 2 == 0) {
            if (str[i] != first) {
                return false;
            }
        } else {
            if (str[i] != second) {
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    const char *test1 = "ababab";
    const char *test2 = "abcabc";
    const char *test3 = "a";
    const char *test4 = "aaaa";
    
    if (isAlternating(test1)) {
        printf("test1 is alternating\n");
    } else {
        printf("test1 is not alternating\n");
    }

    if (isAlternating(test2)) {
        printf("test2 is alternating\n");
    } else {
        printf("test2 is not alternating\n");
    }

    if (isAlternating(test3)) {
        printf("test3 is alternating\n");
    } else {
        printf("test3 is not alternating\n");
    }

    if (isAlternating(test4)) {
        printf("test4 is alternating\n");
    } else {
        printf("test4 is not alternating\n");
    }

    return 0;
}