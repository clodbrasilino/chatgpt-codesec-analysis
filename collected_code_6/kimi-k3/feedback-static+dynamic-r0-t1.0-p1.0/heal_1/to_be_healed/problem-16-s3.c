#include <stdio.h>
#include <string.h>
#include <ctype.h>

void find_lowercase_underscore_sequences(const char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t i = 0;
    int found = 0;

    while (i < len) {
        if (islower((unsigned char)str[i])) {
            size_t start = i;
            size_t count = 0;

            while (i < len && (islower((unsigned char)str[i]) || str[i] == '_')) {
                if (str[i] == '_') {
                    count++;
                }
                i++;
            }

            if (count > 0 && i > start && str[i - 1] != '_') {
                printf("Found sequence: ");
                for (size_t j = start; j < i; j++) {
                    putchar(str[j]);
                }
                putchar('\n');
                found = 1;
            }
        } else {
            i++;
        }
    }

    if (!found) {
        printf("No sequences found.\n");
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    find_lowercase_underscore_sequences(input);

    return 0;
}