#include <stdio.h>
#include <string.h>

long countNonEmptySubstrings(const char *s, size_t len) {
    return (len * (len + 1)) / 2;
}

int main() {
    const char *str = "test";
    size_t len = strlen(str);
    long count = countNonEmptySubstrings(str, len);
    printf("Number of non-empty substrings: %ld\n", count);
    return 0;
}