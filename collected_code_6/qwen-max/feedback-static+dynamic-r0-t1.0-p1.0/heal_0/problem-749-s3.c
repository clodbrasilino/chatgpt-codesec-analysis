#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void sort_strings(char **strings, int count) {
    qsort(strings, count, sizeof(char *), compare);
}

int main() {
    char *strings[] = {"2", "10", "4", "0"};
    int count = 4;
    sort_strings(strings, count);
    for (int i = 0; i < count; ++i) {
        printf("%s\n", strings[i]);
    }
    return 0;
}