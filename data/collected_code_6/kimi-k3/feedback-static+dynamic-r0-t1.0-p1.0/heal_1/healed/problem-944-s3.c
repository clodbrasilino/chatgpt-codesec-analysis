#include <stdio.h>
#include <ctype.h>

void separate_and_print_numbers(const char *str) {
    if (str == NULL) {
        return;
    }

    size_t i = 0;
    size_t start = 0;
    size_t num_start = 0;

    while (str[i] != '\0') {
        if (isdigit((unsigned char)str[i])) {
            start = i;
            num_start = i;
            while (str[i] != '\0' && isdigit((unsigned char)str[i])) {
                i++;
            }
            printf("Number: %.*s, Position: %zu\n", (int)(i - num_start), str + num_start, start);
        } else {
            i++;
        }
    }
}

int main(void) {
    const char *input = "abc123def456ghi789";
    separate_and_print_numbers(input);
    return 0;
}