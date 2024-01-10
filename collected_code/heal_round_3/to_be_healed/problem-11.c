#include <stdio.h>
#include <string.h>

#define MAX_STR_SIZE 100

void removeOccurrences(char* str, const char c) {
    if (!str || !*str) {
        return;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len = strlen(str);
    int i, j;
    int first = -1;
    int last = -1;

    for (i = 0; i < len; i++) {
        if (str[i] == c) {
            if (first == -1) {
                first = i;
            }
            last = i;
        }
    }

    if (first == -1) {
        return;
    }

    for (j = first; j < len; j++) {
        str[j] = str[j + 1];
    }

    len--;

    for (j = last - 1; j < len; j++) {
        str[j] = str[j + 1];
    }

    str[len] = '\0';
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