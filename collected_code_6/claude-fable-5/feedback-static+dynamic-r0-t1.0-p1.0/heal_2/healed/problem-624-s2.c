#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 256

char *string_to_upper(char *str, size_t max_len)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return NULL;
    }

    len = strnlen(str, max_len);
    if (len == max_len) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        str[i] = (char)toupper((unsigned char)str[i]);
    }

    return str;
}

int main(void)
{
    char buffer[MAX_INPUT_LEN];
    char *result;

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    result = string_to_upper(buffer, sizeof(buffer));
    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("Uppercase: %s\n", result);

    return EXIT_SUCCESS;
}