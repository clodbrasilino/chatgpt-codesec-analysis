#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int compare_numeric_strings(const void *a, const void *b) {
    long num1 = strtol(*(const char **)a, NULL, 10);
    long num2 = strtol(*(const char **)b, NULL, 10);
    if (num1 == LONG_MAX || num1 == LONG_MIN || num2 == LONG_MAX || num2 == LONG_MIN) {
        return strcmp(*(const char **)a, *(const char **)b);
    }
    if (num1 < num2) return -1;
    if (num1 > num2) return 1;
    return 0;
}

void sort_strings_numerically(char **strings, int count) {
    qsort(strings, count, sizeof(char *), compare_numeric_strings);
}

int main() {
    char *strings[] = {"10", "2", "35", "4", "100"};
    int count = 5;

    sort_strings_numerically(strings, count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }

    return 0;
}