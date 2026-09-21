#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void find_sequences(const char *str, size_t max_len)
{
    size_t i = 0;
    size_t len = 0;

    if (str == NULL) {
        fprintf(stderr, "Error: NULL input string\n");
        return;
    }

    while (len < max_len && str[len] != '\0') {
        len++;
    }

    while (i < len) {
        if (isupper((unsigned char)str[i])) {
            size_t start = i;
            size_t end = i + 1;

            while (end < len && islower((unsigned char)str[end])) {
                end++;
            }

            if (end > start + 1) {
                printf("Sequence found: ");
                for (size_t j = start; j < end; j++) {
                    putchar(str[j]);
                }
                putchar('\n');
            }

            i = end;
        } else {
            i++;
        }
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    find_sequences(buffer, sizeof(buffer));

    return EXIT_SUCCESS;
}