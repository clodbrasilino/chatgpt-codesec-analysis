#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'string', got @e�
  *  test case 2 failed: expected 'alpha', got �e�
  *  test case 0 failed: expected 'python', got 
  */

char *remove_parenthesis_area(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    const char *open = strchr(str, '(');
    if (open == NULL) {
        size_t len = strlen(str);
        char *result = malloc(len + 1);
        if (result == NULL) {
            return NULL;
        }
        memcpy(result, str, len + 1);
        return result;
    }

    int depth = 1;
    const char *close = open + 1;
    while (*close != '\0') {
        if (*close == '(') {
            depth++;
        } else if (*close == ')') {
            depth--;
            if (depth == 0) {
                break;
            }
        }
        close++;
    }

    if (depth != 0) {
        close = str + strlen(str);
    }

    size_t prefix_len = open - str;
    size_t suffix_len = strlen(close + 1);
    size_t new_len = prefix_len + suffix_len;
    char *result = malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, str, prefix_len);
    memcpy(result + prefix_len, close + 1, suffix_len);
    result[new_len] = '\0';

    return result;
}

int main(void)
{
    const char *tests[] = {
        "(python)",
        "(string)",
        "(alpha)",
        "Hello (world) test",
        "No parenthesis here",
        "Nested (a (b) c) end",
        "Unmatched (open",
        "Unmatched close) here",
        "Empty () case",
        "Multiple (one) and (two)",
        "(a)(b)(c)",
        "((()))",
        NULL
    };

    for (size_t i = 0; tests[i] != NULL; i++) {
        char *cleaned = remove_parenthesis_area(tests[i]);
        if (cleaned != NULL) {
            printf("\"%s\" -> \"%s\"\n", tests[i], cleaned);
            free(cleaned);
        } else {
            printf("\"%s\" -> allocation failure\n", tests[i]);
        }
    }

    return 0;
}