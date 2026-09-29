#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_char_occurrences(char *str, char ch) {
    if (str == NULL) return;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    if (len == 0) return;

    char *first_occurrence = strchr(str, ch);
    char *last_occurrence = strrchr(str, ch);

    if (first_occurrence == NULL || last_occurrence == NULL) return;

    if (first_occurrence == last_occurrence) {
        memmove(first_occurrence, first_occurrence + 1, len - (first_occurrence - str));
        str[len - 1] = '\0';
    } else {
        memmove(first_occurrence, first_occurrence + 1, last_occurrence - first_occurrence);
        memmove(last_occurrence - 1, last_occurrence, len - (last_occurrence - str) + 1);
    }
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[100] = "hello world";
    char ch = 'l';

    printf("Original string: %s\n", str);
    remove_char_occurrences(str, ch);
    printf("Modified string: %s\n", str);

    return 0;
}