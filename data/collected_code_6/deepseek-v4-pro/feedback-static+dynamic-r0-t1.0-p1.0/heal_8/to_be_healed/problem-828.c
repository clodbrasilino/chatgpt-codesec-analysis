#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define STR_SIZE 512

void count_chars(const char *str, int *alphabets, int *digits, int *specials) {
    *alphabets = 0;
    *digits = 0;
    *specials = 0;

    if (str == NULL) {
        return;
    }

    for (const char *p = str; *p != '\0'; p++) {
        if (isalpha((unsigned char)*p)) {
            (*alphabets)++;
        }
        else if (isdigit((unsigned char)*p)) {
            (*digits)++;
        }
        else {
            (*specials)++;
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[STR_SIZE];
    int alphabets, digits, specials;
    size_t len;

    printf("Enter a string: ");
    if (fgets(str, STR_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    len = strnlen(str, STR_SIZE);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    else {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF && c != '\0') {
        }
    }

    count_chars(str, &alphabets, &digits, &specials);

    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special characters: %d\n", specials);

    return 0;
}