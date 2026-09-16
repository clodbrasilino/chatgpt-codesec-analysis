#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parenthesis_area(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);

    if (len == 0) {
        char *empty = malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    size_t *stack = calloc(len, sizeof(size_t));
    if (stack == NULL) {
        return NULL;
    }

    unsigned char *remove_mask = calloc(len, 1);
    if (remove_mask == NULL) {
        free(stack);
        return NULL;
    }

    size_t top = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '(') {
            stack[top++] = i;
        } else if (str[i] == ')') {
            if (top > 0) {
                size_t start = stack[--top];
                for (size_t j = start; j <= i; j++) {
                    remove_mask[j] = 1;
                }
            }
        }
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        free(remove_mask);
        free(stack);
        return NULL;
    }

    size_t pos = 0;

    for (size_t i = 0; i < len; i++) {
        if (remove_mask[i] == 0) {
            result[pos++] = str[i];
        }
    }

    result[pos] = '\0';

    free(remove_mask);
    free(stack);

    return result;
}

int main(void)
{
    const char *tests[] = {
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