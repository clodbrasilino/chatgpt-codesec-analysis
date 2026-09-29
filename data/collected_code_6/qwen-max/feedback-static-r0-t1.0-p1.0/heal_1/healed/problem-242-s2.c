#include <stdio.h>
#include <string.h>

size_t count_chars(const char *str, size_t max_length) {
    size_t length = 0;
    while (max_length-- > 0 && *str++) {
        length++;
    }
    return length;
}

int main() {
    const char input[] = "Hello, world!";
    size_t length = count_chars(input, sizeof(input) - 1);
    printf("Total characters: %zu\n", length);
    return 0;
}