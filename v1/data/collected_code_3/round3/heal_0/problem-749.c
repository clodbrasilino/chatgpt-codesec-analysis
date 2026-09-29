#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return atoi(*(char **)a) - atoi(*(char **)b);
}

void sortNumericalStrings(char **strs, int n) {
    qsort(strs, n, sizeof(char *), compare);
}

int main() {
    int n = 5;
    char *strs[] = {"123", "5", "25", "100", "1"};

    sortNumericalStrings(strs, n);

    for(int i = 0; i < n; i++) {
        printf("%s ", strs[i]);
    }

    return 0;
}