#include <stdio.h>
#include <string.h>

long countNonEmptySubstrings(const char *s) {
    long n = strlen(s);
    return (n * (n + 1)) / 2;
}

int main() {
    const char *str = "test";
    long count = countNonEmptySubstrings(str);
    printf("Number of non-empty substrings: %ld\n", count);
    return 0;
}