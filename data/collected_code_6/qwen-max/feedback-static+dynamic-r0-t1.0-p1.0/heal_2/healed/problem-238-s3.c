#include <stdio.h>
#include <string.h>

long countNonEmptySubstrings(const char *str, size_t len) {
    return (len * (len + 1)) / 2;
}

int main() {
    const char input[] = "test";
    size_t input_len = sizeof(input) - 1;
    long result = countNonEmptySubstrings(input, input_len);
    printf("Number of non-empty substrings: %ld\n", result);
    return 0;
}