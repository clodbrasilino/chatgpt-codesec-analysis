#include <stdio.h>
#include <ctype.h>

void separate_and_print_numbers(const char *str) {
    if (str == NULL) {
        return;
    }

    size_t i = 0;

    while (str[i] != '\0') {
        if (isdigit((unsigned char)str[i])) {
            size_t start_pos = i;

            while (str[i] != '\0' && isdigit((unsigned char)str[i])) {
                i++;
            }

            printf("Number: ");
            for (size_t j = start_pos; j < i; j++) {
                putchar(str[j]);
            }
            printf(", Position: %zu\n", start_pos);
        } else {
            i++;
        }
    }
}

int main(void) {
    const char *text = "abc123def456ghi789xyz";
    separate_and_print_numbers(text);
    return 0;
}