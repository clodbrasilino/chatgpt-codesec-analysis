#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LEN 256U

bool contains_all_vowels(const char *str, size_t max_len)
{
    bool found[5] = { false, false, false, false, false };
    size_t i;
    size_t len;

    if (str == NULL) {
        return false;
    }

    len = strnlen(str, max_len);

    for (i = 0U; i < len; i++) {
        int c = tolower((unsigned char)str[i]);

        switch (c) {
        case 'a':
            found[0] = true;
            break;
        case 'e':
            found[1] = true;
            break;
        case 'i':
            found[2] = true;
            break;
        case 'o':
            found[3] = true;
            break;
        case 'u':
            found[4] = true;
            break;
        default:
            break;
        }
    }

    return found[0] && found[1] && found[2] && found[3] && found[4];
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_LEN];
    size_t len;

    (void)memset(input, 0, sizeof(input));

    (void)printf("Enter a string: ");
    (void)fflush(stdout);

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        (void)fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1U] = '\0';

    len = strnlen(input, sizeof(input));
    if ((len > 0U) && (input[len - 1U] == '\n')) {
        input[len - 1U] = '\0';
    } else if (len == (sizeof(input) - 1U)) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (((ch = getchar()) != '\n') && (ch != EOF)) {
        }
    }

    if (contains_all_vowels(input, sizeof(input))) {
        (void)printf("Accepted: the string contains all vowels\n");
    } else {
        (void)printf("Rejected: the string does not contain all vowels\n");
    }

    return EXIT_SUCCESS;
}