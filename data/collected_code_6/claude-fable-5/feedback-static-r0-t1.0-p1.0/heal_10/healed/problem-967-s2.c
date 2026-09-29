#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LEN 256U

static bool contains_all_vowels(const char *str, size_t max_size)
{
    bool found[5] = { false, false, false, false, false };
    size_t i;
    size_t len;

    if (str == NULL) {
        return false;
    }

    len = strnlen(str, max_size);

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
    char input[MAX_LEN];
    size_t len;

    (void)memset(input, 0, sizeof(input));

    printf("Enter a string: ");
    (void)fflush(stdout);

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    input[sizeof(input) - 1U] = '\0';

    len = strnlen(input, sizeof(input));
    if ((len > 0U) && (input[len - 1U] == '\n')) {
        input[len - 1U] = '\0';
    }

    if (contains_all_vowels(input, sizeof(input))) {
        printf("Accepted: the string contains all vowels\n");
    } else {
        printf("Rejected: the string does not contain all vowels\n");
    }

    return 0;
}