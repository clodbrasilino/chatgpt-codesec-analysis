#include <stdio.h>
#include <ctype.h>
#include <string.h>

void print_numbers_and_positions(const char *str) {
    if (str == NULL) return;
    for (size_t i = 0; i < strlen(str); ++i) {
        if (isdigit((unsigned char)str[i])) {
            printf("Number: %c, Position: %zu\n", str[i], i);
        }
    }
}

int main() {
    const char *input = "a1b2c3d4";
    print_numbers_and_positions(input);
    return 0;
}