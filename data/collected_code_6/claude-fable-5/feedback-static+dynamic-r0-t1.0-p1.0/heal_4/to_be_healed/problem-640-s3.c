#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got  t�
  *  test case 2 failed: expected 'alpha', got `t�
  *  test case 0 failed: expected 'python', got �s�
  */

char *remove_parentheses(const char *input)
{
    size_t len;
    size_t i;
    size_t j;
    int depth;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);

    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    depth = 0;
    j = 0;
    for (i = 0; i < len; i++) {
        if (input[i] == '(') {
            depth++;
        } else if (input[i] == ')') {
            if (depth > 0) {
                depth--;
            }
        } else if (depth == 0) {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

static int process_line(const char *input)
{
    char *output;

    output = remove_parentheses(input);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }
    if (printf("%s\n", output) < 0) {
        free(output);
        return -1;
    }
    free(output);
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[sizeof(buffer) - 1] = '\0';
        size_t len = strnlen(buffer, sizeof(buffer));
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        if (process_line(buffer) != 0) {
            return EXIT_FAILURE;
        }
    }

    if (ferror(stdin)) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}