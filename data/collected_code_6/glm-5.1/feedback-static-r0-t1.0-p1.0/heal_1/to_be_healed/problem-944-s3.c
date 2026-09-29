#include <stdio.h>
#include <ctype.h>

void separate_and_print_numbers(const char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     *  Variable 'pos' is assigned a value that is never used. [unreadVariable]
     */
    size_t pos = 0;
    size_t i = 0;

    while (str[i] != '\0') {
        if (isdigit((unsigned char)str[i])) {
            size_t start_pos = i;
            size_t start_idx = i;

            while (str[i] != '\0' && isdigit((unsigned char)str[i])) {
                i++;
            }

            printf("Number: ");
            for (size_t j = start_idx; j < i; j++) {
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