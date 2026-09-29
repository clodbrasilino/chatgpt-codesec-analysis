#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_char_occurrences(char *str, char ch) {
    if (str == NULL) return;

    int len = 0;
    while (str[len] != '\0' && str[len] != ch) len++;

    if (len == 0 || str[len] == '\0') return;

    char *first_occurrence = strchr(str, ch);
    char *last_occurrence = strrchr(str, ch);

    if (first_occurrence == last_occurrence) {
        memmove(first_occurrence, first_occurrence + 1, strlen(str) - (first_occurrence - str));
        str[strlen(str) - 1] = '\0';
    } else {
        memmove(first_occurrence, first_occurrence + 1, last_occurrence - first_occurrence);
        memmove(last_occurrence - 1, last_occurrence, strlen(str) - (last_occurrence - str) + 1);
    }
}

int main() {
    char str[] = "hello world";
    char ch = 'l';

    printf("Original string: %s\n", str);
    remove_char_occurrences(str, ch);
    printf("Modified string: %s\n", str);

    return 0;
}