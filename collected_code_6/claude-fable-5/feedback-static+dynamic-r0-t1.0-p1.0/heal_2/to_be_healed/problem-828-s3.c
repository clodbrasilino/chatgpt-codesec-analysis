#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

struct char_counts {
    size_t alphabets;
    size_t digits;
    size_t specials;
};

static void count_characters(const char *str, size_t max_len, struct char_counts *counts)
{
    size_t i;

    if (counts == NULL) {
        return;
    }

    counts->alphabets = 0;
    counts->digits = 0;
    counts->specials = 0;

    if (str == NULL) {
        return;
    }

    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];

        if (isalpha(c)) {
            counts->alphabets++;
        } else if (isdigit(c)) {
            counts->digits++;
        } else if (!isspace(c)) {
            counts->specials++;
        }
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    struct char_counts counts;
    size_t len;

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'len' is assigned a value that is never used. [unreadVariable]
         */
        len--;
    }

    count_characters(buffer, sizeof(buffer), &counts);

    printf("Alphabets: %zu\n", counts.alphabets);
    printf("Digits: %zu\n", counts.digits);
    printf("Special characters: %zu\n", counts.specials);

    return EXIT_SUCCESS;
}