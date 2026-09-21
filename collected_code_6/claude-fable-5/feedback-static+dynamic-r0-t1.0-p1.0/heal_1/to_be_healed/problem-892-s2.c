#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_multiple_spaces(char *str)
{
    size_t read_index = 0;
    size_t write_index = 0;
    int previous_was_space = 0;

    if (str == NULL) {
        return;
    }

    while (str[read_index] != '\0') {
        if (str[read_index] == ' ') {
            if (previous_was_space == 0) {
                str[write_index] = str[read_index];
                write_index++;
            }
            previous_was_space = 1;
        } else {
            str[write_index] = str[read_index];
            write_index++;
            previous_was_space = 0;
        }
        read_index++;
    }

    str[write_index] = '\0';
}

int main(void)
{
    char input[] = "This   is  a    string   with     multiple spaces";
    char *buffer = NULL;
    size_t length = 0;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(input) + 1;
    buffer = malloc(length);
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, input, length);

    printf("Before: \"%s\"\n", buffer);
    remove_multiple_spaces(buffer);
    printf("After:  \"%s\"\n", buffer);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}