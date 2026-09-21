#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 256

int contains_all_vowels(const char *str, size_t max_len)
{
    int found[5] = {0, 0, 0, 0, 0};
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        switch (tolower((unsigned char)str[i])) {
        case 'a':
            found[0] = 1;
            break;
        case 'e':
            found[1] = 1;
            break;
        case 'i':
            found[2] = 1;
            break;
        case 'o':
            found[3] = 1;
            break;
        case 'u':
            found[4] = 1;
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

    printf("Enter a string: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    if (contains_all_vowels(input, sizeof(input))) {
        printf("Accepted: the string contains all vowels\n");
    } else {
        printf("Rejected: the string does not contain all vowels\n");
    }

    return 0;
}