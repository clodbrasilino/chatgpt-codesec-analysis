#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare (const void * a, const void * b) {
    return ( atoi(a) - atoi(b) );
}

void sortStringsNumerically(size_t numStrings, char *strings[]) {
    qsort(strings, numStrings, sizeof(char*), compare);
}

int main() {
    char* strings[] = {"5", "10", "2", "20", "1"};
    size_t numStrings = sizeof(strings) / sizeof(char*);

    sortStringsNumerically(numStrings, strings);

    for(size_t i = 0; i < numStrings; i++) {
        printf("%s ", strings[i]);
    }

    return 0;
}