#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LEN 256

bool contains_all_vowels(const char *str)
{
    bool found[5] = { false, false, false, false, false };
    size_t i;
    size_t len;

    if (str == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

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

    printf("Enter a string: ");

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if ((len > 0U) && (input[len - 1U] == '\n')) {
        input[len - 1U] = '\0';
    }

    if (contains_all_vowels(input)) {
        printf("Accepted: the string contains all vowels\n");
    } else {
        printf("Rejected: the string does not contain all vowels\n");
    }

    return 0;
}