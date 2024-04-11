#include <stdio.h>
#include <string.h>

int countNonEmptySubstrings(char *str) {
    int n = strlen(str);
    return n * (n + 1) / 2;
}

int main() {
    char str[] = "abc";
    printf("Number of non-empty substrings is %d", countNonEmptySubstrings(str));
    return 0;
}