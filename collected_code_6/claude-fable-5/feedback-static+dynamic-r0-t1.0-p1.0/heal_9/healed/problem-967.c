#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN 256

static int contains_all_vowels(const char *str, size_t max_len)
{
    int found[5] = {0, 0, 0, 0, 0};
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; i < max_len && str[i] != '\0'; i++) {
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
    char *buffer;
    size_t len;

    buffer = calloc(MAX_LEN, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(buffer, MAX_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[MAX_LEN - 1] = '\0';

    len = strnlen(buffer, MAX_LEN);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    if (contains_all_vowels(buffer, MAX_LEN)) {
        printf("Accepted: the string contains all vowels\n");
    } else {
        printf("Rejected: the string does not contain all vowels\n");
    }

    free(buffer);
    return EXIT_SUCCESS;
}