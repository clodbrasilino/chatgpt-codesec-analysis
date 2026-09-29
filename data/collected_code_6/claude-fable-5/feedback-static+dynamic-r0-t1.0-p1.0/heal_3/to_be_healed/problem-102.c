#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'ProgrammingLanguage', got <no output>
  *  test case 0 failed: expected 'PythonProgram', got <no output>
  *  test case 1 failed: expected 'PythonLanguage', got <no output>
  */

char *snake_to_camel(const char *snake)
{
    size_t len;
    size_t i;
    size_t j;
    char *camel;
    int capitalize_next;

    if (snake == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(snake);
    camel = malloc(len + 1);
    if (camel == NULL) {
        return NULL;
    }

    capitalize_next = 1;
    j = 0;
    for (i = 0; i < len; i++) {
        if (snake[i] == '_') {
            capitalize_next = 1;
        } else {
            if (capitalize_next != 0) {
                camel[j] = (char)toupper((unsigned char)snake[i]);
                capitalize_next = 0;
            } else {
                camel[j] = (char)tolower((unsigned char)snake[i]);
            }
            j++;
        }
    }
    camel[j] = '\0';

    return camel;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    char *result;
    size_t len;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "No input provided\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    while (len > 0 && (input[len - 1] == '\n' || input[len - 1] == '\r')) {
        input[len - 1] = '\0';
        len--;
    }

    result = snake_to_camel(input);
    if (result == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}