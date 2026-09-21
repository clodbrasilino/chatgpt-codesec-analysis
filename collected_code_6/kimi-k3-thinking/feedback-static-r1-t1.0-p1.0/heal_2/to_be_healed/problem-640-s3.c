#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 256

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t len;

    len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char *remove_parenthesis_area(const char *str, size_t max_len)
{
    char *result;
    size_t i;
    size_t j;
    size_t len;
    int depth;

    if (str == NULL) {
        return NULL;
    }

    len = bounded_strlen(str, max_len);
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LEN];
    char *cleaned;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    printf("Enter a string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    input[sizeof(input) - 1] = '\0';
    input[strcspn(input, "\n")] = '\0';

    cleaned = remove_parenthesis_area(input, sizeof(input));
    if (cleaned == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Result: %s\n", cleaned);

    free(cleaned);
    cleaned = NULL;

    return EXIT_SUCCESS;
}