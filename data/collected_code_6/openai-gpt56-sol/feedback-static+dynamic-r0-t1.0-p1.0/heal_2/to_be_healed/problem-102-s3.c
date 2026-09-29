#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ProgrammingLanguage', got <no output>
  *  test case 0 failed: expected 'PythonProgram', got <no output>
  *  test case 1 failed: expected 'PythonLanguage', got <no output>
  */

char *snake_to_camel(const char *snake)
{
    size_t length;
    size_t source_index;
    size_t destination_index = 0;
    int capitalize_next = 1;
    char *camel;

    if (snake == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(snake);
    if (length == SIZE_MAX) {
        return NULL;
    }

    camel = malloc(length + 1);
    if (camel == NULL) {
        return NULL;
    }

    for (source_index = 0; source_index < length; ++source_index) {
        unsigned char character = (unsigned char)snake[source_index];

        if (character == (unsigned char)'_') {
            capitalize_next = 1;
        } else if (capitalize_next) {
            camel[destination_index++] = (char)toupper(character);
            capitalize_next = 0;
        } else {
            camel[destination_index++] = (char)character;
        }
    }

    camel[destination_index] = '\0';
    return camel;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *camel;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <snake_case_string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    camel = snake_to_camel(argv[1]);
    if (camel == NULL) {
        fputs("Failed to convert string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(camel) == EOF) {
        free(camel);
        return EXIT_FAILURE;
    }

    free(camel);
    return EXIT_SUCCESS;
}