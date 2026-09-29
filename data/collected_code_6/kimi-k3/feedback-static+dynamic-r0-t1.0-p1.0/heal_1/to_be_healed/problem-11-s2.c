#include <stdio.h>
#include <string.h>

void removeFirstAndLastOccurrence(char *str, char ch) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return;
    }

    size_t first = len;
    size_t last = len;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == ch) {
            if (first == len) {
                first = i;
            }
            last = i;
        }
    }

    if (first == len) {
        return;
    }

    if (first == last) {
        memmove(str + first, str + first + 1, len - first);
    } else {
        memmove(str + last, str + last + 1, len - last);
        memmove(str + first, str + first + 1, last - first);
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[100];
    char ch;
    int c;

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    printf("Enter a character to remove: ");
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    c = getchar();
    if (c == EOF || c == '\n') {
        return 1;
    }
    ch = (char)c;

    removeFirstAndLastOccurrence(str, ch);

    printf("Result: %s\n", str);

    return 0;
}