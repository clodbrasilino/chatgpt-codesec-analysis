#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STR_SIZE 100

bool isValidString(const char* str) {
    if (!str) {
        return false;
    }

    for (int i = 0; i < MAX_STR_SIZE; i++) {
        if (str[i] == '\0') {
            return true;
        }
    }

    return false;
}

void removeOccurrences(char* str, const char c) {
    if (!isValidString(str)) {
        return;
    }

    int len = strnlen(str, MAX_STR_SIZE);
    int i, j;
    int first = -1;

    for (i = 0; i < len; i++) {
        if (str[i] == c) {
            first = i;
            break;
        }
    }

    if (first == -1) {
        return;
    }

    for (j = first; j < len; j++) {
        if (str[j + 1] == '\0') {
            str[j] = '\0';
            break;
        }
        str[j] = str[j + 1];
    }
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_STR_SIZE] = {0};
    char c;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';  

    printf("Enter a character: ");
    scanf(" %c", &c);

    removeOccurrences(str, c);

    printf("Modified string: %s\n", str);

    return 0;
}