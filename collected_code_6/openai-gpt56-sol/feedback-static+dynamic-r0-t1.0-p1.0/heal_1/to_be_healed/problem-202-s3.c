#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_even_characters(char *string)
{
    size_t read_index;
    size_t write_index;
    size_t length;

    if (string == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(string);
    write_index = 0;

    for (read_index = 0; read_index < length; read_index += 2) {
        string[write_index++] = string[read_index];
    }

    string[write_index] = '\0';
    return 0;
}

int main(void)
{
    char *string = NULL;
    size_t capacity = 0;
    ssize_t length;

    length = getline(&string, &capacity, stdin);
    if (length < 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (length > 0 && string[length - 1] == '\n') {
        string[length - 1] = '\0';
    }

    if (remove_even_characters(string) != 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}