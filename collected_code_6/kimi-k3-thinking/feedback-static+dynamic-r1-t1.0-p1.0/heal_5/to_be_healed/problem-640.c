#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

static size_t safe_strlen(const char *s, size_t max)
{
    size_t n = 0;

    if (s == NULL) {
        return 0;
    }

    while (n < max && s[n] != '\0') {
        n++;
    }

    return n;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got �S1	
  *  test case 0 failed: expected 'python', got 
  *  test case 2 failed: expected 'alpha', got  T1	
  */

char *remove_parentheses(const char *str)
{
    size_t len;
    size_t i;
    size_t j = 0;
    int depth = 0;
    char *result;

    if (str == NULL) {
        return NULL;
    }

    len = safe_strlen(str, MAX_INPUT_LEN);

    result = (char *)calloc(len + 1, sizeof(char));
    if (result == NULL) {
        return NULL;
    }

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

    while (j > 0 && (result[j - 1] == ' '  ||
                     result[j - 1] == '\t' ||
                     result[j - 1] == '\n' ||
                     result[j - 1] == '\r')) {
        j--;
    }

    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *inputs[] = {
        "python (chrome)",
        "string (abcd)",
        "alpha (beta)"
    };
    size_t count = sizeof(inputs) / sizeof(inputs[0]);
    size_t k;

    for (k = 0; k < count; k++) {
        char *output = remove_parentheses(inputs[k]);

        if (output == NULL) {
            fprintf(stderr, "Error: failed to process string\n");
            return EXIT_FAILURE;
        }

        printf("%s\n", output);

        free(output);
        output = NULL;
    }

    return EXIT_SUCCESS;
}