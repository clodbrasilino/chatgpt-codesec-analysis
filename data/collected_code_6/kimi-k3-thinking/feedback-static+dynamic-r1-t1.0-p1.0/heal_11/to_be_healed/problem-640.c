#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got ��f
  *  test case 0 failed: expected 'python', got ��f
  *  test case 2 failed: expected 'alpha', got �f
  */

char *remove_parentheses(const char *str)
{
    size_t len;
    size_t i;
    size_t j = 0;
    size_t start;
    size_t end;
    char *result;

    if (str == NULL) {
        return NULL;
    }

    len = strlen(str);
    result = (char *)calloc(len + 1, sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (str[i] == '(' || str[i] == ')') {
            continue;
        }
        result[j] = str[i];
        j++;
    }
    result[j] = '\0';

    start = 0;
    while (result[start] == ' ' || result[start] == '\t') {
        start++;
    }
    if (start > 0) {
        memmove(result, result + start, strlen(result + start) + 1);
    }

    end = strlen(result);
    while (end > 0 && (result[end - 1] == ' ' || result[end - 1] == '\t')) {
        result[--end] = '\0';
    }

    return result;
}

int main(int argc, char *argv[])
{
    char buffer[4096];
    const char *input;
    char *output;

    if (argc > 1) {
        input = argv[1];
    } else {
        size_t len;

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            fprintf(stderr, "Error: failed to read input\n");
            return EXIT_FAILURE;
        }
        len = strlen(buffer);
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
            buffer[--len] = '\0';
        }
        input = buffer;
    }

    output = remove_parentheses(input);
    if (output == NULL) {
        fprintf(stderr, "Error: failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", output);

    free(output);
    output = NULL;

    return EXIT_SUCCESS;
}