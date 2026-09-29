#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN 256

static size_t bounded_length(const char *str, size_t max_len)
{
    size_t i = 0;

    if (str == NULL) {
        return 0;
    }

    while (i < max_len && str[i] != '\0') {
        i++;
    }

    return i;
}

int contains_all_vowels(const char *str, size_t max_len)
{
    int found[5] = {0, 0, 0, 0, 0};
    size_t i;
    size_t len;

    if (str == NULL) {
        return 0;
    }

    len = bounded_length(str, max_len);

    for (i = 0; i < len; i++) {
        int c = tolower((unsigned char)str[i]);
        switch (c) {
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
    char buffer[MAX_LEN];
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = bounded_length(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    if (contains_all_vowels(buffer, sizeof(buffer))) {
        printf("Accepted: the string contains all vowels\n");
    } else {
        printf("Rejected: the string does not contain all vowels\n");
    }

    return EXIT_SUCCESS;
}