#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'python', got �B�
  *  test case 2 failed: expected 'alpha', got `C�
  *  test case 1 failed: expected 'string', got  C�
  */

char *remove_parenthesis_area(const char *str)
{
    char *result;
    size_t i;
    size_t j;
    size_t len;
    int depth;

    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    depth = 0;
    j = 0;
    for (i = 0; i < len; i++) {
        if (str[i] == '(') {
            depth++;
        } else if (str[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            result[j] = str[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t nread;
    char *cleaned;

    nread = getline(&input, &capacity, stdin);
    if (nread < 0) {
        fprintf(stderr, "Error reading input\n");
        free(input);
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    cleaned = remove_parenthesis_area(input);
    free(input);
    input = NULL;
    if (cleaned == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", cleaned);

    free(cleaned);
    cleaned = NULL;

    return EXIT_SUCCESS;
}