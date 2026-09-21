#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_whitespace(char *str)
{
    if (str == NULL) {
        return;
    }

    size_t read_index = 0;
    size_t write_index = 0;

    while (str[read_index] != '\0') {
        if (!isspace((unsigned char)str[read_index])) {
            str[write_index] = str[read_index];
            write_index++;
        }
        read_index++;
    }
    str[write_index] = '\0';
}

int main(void)
{
    const char *original = "  Hello,   World! \t This is a test.\n";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(original);

    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, original, len + 1);

    remove_whitespace(buffer);

    if (printf("Original: \"%s\"\n", original) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }
    if (printf("Result:   \"%s\"\n", buffer) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}