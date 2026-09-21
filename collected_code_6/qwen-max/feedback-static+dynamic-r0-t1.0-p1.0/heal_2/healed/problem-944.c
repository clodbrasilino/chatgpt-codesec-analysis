#include <stdio.h>
#include <ctype.h>

void print_numbers_and_positions(const char *str, size_t len) {
    if (str == NULL) return;
    for (size_t i = 0; i < len; ++i) {
        if (isdigit((unsigned char)str[i])) {
            printf("Number: %c, Position: %zu\n", str[i], i);
        }
    }
}

int main() {
    const char input[] = "a1b2c3d4";
    size_t input_len = sizeof(input) - 1;
    print_numbers_and_positions(input, input_len);
    return 0;
}