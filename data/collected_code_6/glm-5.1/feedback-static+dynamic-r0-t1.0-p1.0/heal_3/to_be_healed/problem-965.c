#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python_program', got <no output>
  *  test case 1 failed: expected 'python_language', got <no output>
  *  test case 2 failed: expected 'programming_language', got <no output>
  */

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(camel_str);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    size_t max_snake_len = len * 2 + 1;
    char *snake_str = malloc(max_snake_len);
    if (snake_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)camel_str[i])) {
            if (i > 0) {
                snake_str[j++] = '_';
            }
            snake_str[j++] = tolower((unsigned char)camel_str[i]);
        } else {
            snake_str[j++] = camel_str[i];
        }
    }

    snake_str[j] = '\0';

    char *shrunk = realloc(snake_str, j + 1);
    if (shrunk != NULL) {
        snake_str = shrunk;
    }

    return snake_str;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        char *result = camel_to_snake(buffer);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
    }
    return 0;
}