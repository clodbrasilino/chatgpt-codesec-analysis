#include <stdio.h>
#include <ctype.h>
#include <string.h>

void separate_and_print_numbers(const char *str) {
    if (str == NULL) {
        return;
    }

    size_t len = strlen(str);
    size_t i = 0;

    while (i < len) {
        if (isdigit((unsigned char)str[i])) {
            size_t start = i;
            size_t num_start = i;
            while (i < len && isdigit((unsigned char)str[i])) {
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