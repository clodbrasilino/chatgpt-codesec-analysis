#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parenthesis_area(const char *str)
{
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t pos = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] != '(' && str[i] != ')') {
            result[pos++] = str[i];
        }
    }
    result[pos] = '\0';

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