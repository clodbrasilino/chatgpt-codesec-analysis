#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int compare(const void *a, const void *b) {
    const char **str1 = (const char **)a;
    const char **str2 = (const char **)b;

    long num1 = strtol(*str1, NULL, 10);
    if (num1 > INT_MAX) num1 = INT_MAX;
    if (num1 < INT_MIN) num1 = INT_MIN;

    long num2 = strtol(*str2, NULL, 10);
    if (num2 > INT_MAX) num2 = INT_MAX;
    if (num2 < INT_MIN) num2 = INT_MIN;

    return (int)num1 - (int)num2;
}

void sortStrings(char *strings[], const int numStrings) {
    qsort(strings, numStrings, sizeof(char *), compare);
}

int main() {
    char *strings[] = {"10", "2", "5", "1", "7"};
    int numStrings = sizeof(strings) / sizeof(strings[0]);

    sortStrings(strings, numStrings);

    for (int i = 0; i < numStrings; i++) {
        printf("%s\n", strings[i]);
    }

    return 0;
}