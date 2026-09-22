#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_parenthesis_area(const char *str, size_t len)
{
    if (str == NULL) return NULL;
    if (len == 0) {
        char *empty = malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }
    size_t open_pos = (size_t)-1;
    size_t close_pos = (size_t)-1;
    size_t balance = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '(') {
            if (balance == 0) open_pos = i;
            balance++;
        } else if (str[i] == ')') {
            if (balance > 0) {
                balance--;
                if (balance == 0) {
                    close_pos = i;
                    break;
                }
            }
        }
    }
    if (open_pos == (size_t)-1 || close_pos == (size_t)-1) {
        char *result = malloc(len + 1);
        if (result) {
            memcpy(result, str, len);
            result[len] = '\0';
        }
        return result;
    }
    size_t inner_len = close_pos - open_pos - 1;
    char *result = malloc(inner_len + 1);
    if (result) {
        memcpy(result, str + open_pos + 1, inner_len);
        result[inner_len] = '\0';
    }
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
        size_t len = strlen(str);
        char *cleaned = remove_parenthesis_area(str, len);
        if (cleaned) {
            printf("\"%s\" -> \"%s\"\n", str, cleaned);
            free(cleaned);
        } else {
            printf("\"%s\" -> allocation failure\n", str);
        }
    }
    return 0;
}