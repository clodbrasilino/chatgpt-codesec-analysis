#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'AndroidTv', got androidTv
  *  test case 1 failed: expected 'GooglePixel', got googlePixel
  *  test case 2 failed: expected 'AppleWatch', got appleWatch
  */

char* snake_to_camel(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char* result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    int capitalize_next = 0;

    while (i < len) {
        if (input[i] == '_') {
            capitalize_next = 1;
            i++;
        } else {
            if (capitalize_next) {
                result[j++] = input[i] - 32;
                capitalize_next = 0;
            } else {
                result[j++] = input[i];
            }
            i++;
        }
    }

    result[j] = '\0';
    return result;
}

int main(void) {
    const char* input = "hello_world_this_is_c";
    char* output = snake_to_camel(input);

    if (output == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", output);
    free(output);
    return EXIT_SUCCESS;
}