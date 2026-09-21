#include <stdio.h>
#include <stdlib.h>

char *remove_parenthesis_area(const char *str, size_t len)
{
    if (str == NULL) {
        return NULL;
    }
    if (len == 0) {
        char *empty = malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    size_t open = 0;
    size_t close = 0;
    int found = 0;
    size_t balance = 0;
    size_t start = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '(') {
            if (balance == 0) {
                start = i;
            }
            balance++;
        } else if (str[i] == ')') {
            if (balance > 0) {
                balance--;
                if (balance == 0) {
                    open = start;
                    close = i;
                    found = 1;
                    break;
                }
            }
        }
    }

    if (!found) {
        char *empty = malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }

    size_t length = close - open - 1;
    char *result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < length; i++) {
        result[i] = str[open + 1 + i];
    }
    result[length] = '\0';

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
        const char *str = tests[i];
        size_t len = 0;
        while (str[len] != '\0') {
            len++;
        }
        char *cleaned = remove_parenthesis_area(str, len);
        if (cleaned != NULL) {
            printf("\"%s\" -> \"%s\"\n", str, cleaned);
            free(cleaned);
        } else {
            printf("\"%s\" -> allocation failure\n", str);
        }
    }

    return 0;
}