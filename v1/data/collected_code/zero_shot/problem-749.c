#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    const char **str1 = (const char **)a;
    const char **str2 = (const char **)b;
    return atoi(*str1) - atoi(*str2);
}

void sortStrings(char *strings[], int numStrings) {
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