#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 256

static size_t safe_strnlen(const char *str, size_t max_len)
{
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            break;
        }
    }

    return i;
}

char *string_to_upper(char *str, size_t max_len)
{
    size_t i;
    size_t len;

    if (str == NULL || max_len == 0) {
        return NULL;
    }

    len = safe_strnlen(str, max_len);
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
    size_t newline_pos;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");
    if (fflush(stdout) != 0) {
        fprintf(stderr, "Error flushing output\n");
        return EXIT_FAILURE;
    }

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    newline_pos = strcspn(buffer, "\n");
    if (newline_pos < sizeof(buffer)) {
        buffer[newline_pos] = '\0';
    }

    result = string_to_upper(buffer, sizeof(buffer));
    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("Uppercase: %s\n", result);

    return EXIT_SUCCESS;
}