#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_LEN 256U
#define DISCARD_GUARD_LIMIT 1048576U

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t i = 0U;

    if (str == NULL) {
        return 0U;
    }

    while ((i < max_len) && (str[i] != '\0')) {
        i++;
    }

    return i;
}

static bool contains_all_vowels(const char *str, size_t max_len)
{
    bool found[5] = { false, false, false, false, false };
    size_t i;
    size_t len;

    if (str == NULL) {
        return false;
    }

    len = bounded_strlen(str, max_len);

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

static void discard_remaining_input(void)
{
    int ch;
    size_t guard = 0U;

    do {
        ch = getchar();
        guard++;
    } while ((ch != '\n') && (ch != EOF) && (guard < DISCARD_GUARD_LIMIT));
}

int main(void)
{
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

    len = bounded_strlen(input, sizeof(input));
    if ((len > 0U) && (input[len - 1U] == '\n')) {
        input[len - 1U] = '\0';
    } else if (len == (sizeof(input) - 1U)) {
        discard_remaining_input();
    }

    if (contains_all_vowels(input, sizeof(input))) {
        (void)printf("Accepted: the string contains all vowels\n");
    } else {
        (void)printf("Rejected: the string does not contain all vowels\n");
    }

    return EXIT_SUCCESS;
}