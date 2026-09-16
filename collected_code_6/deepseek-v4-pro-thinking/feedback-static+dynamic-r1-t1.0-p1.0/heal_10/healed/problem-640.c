#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *dup_str(const char *s)
{
    if (!s) return NULL;
    size_t len = strlen(s);
    char *d = malloc(len + 1);
    if (d) memcpy(d, s, len + 1);
    return d;
}

char *remove_parenthesis_area(const char *str)
{
    if (!str) return NULL;
    const char *open = strchr(str, '(');
    if (!open) return dup_str(str);
    int depth = 1;
    const char *p = open + 1;
    while (*p) {
        if (*p == '(') depth++;
        else if (*p == ')') {
            if (--depth == 0) break;
        }
        p++;
    }
    if (depth != 0) return dup_str(str);
    size_t content_len = (size_t)(p - open - 1);
    char *result = malloc(content_len + 1);
    if (result) {
        if (content_len > 0) memcpy(result, open + 1, content_len);
        result[content_len] = '\0';
    }
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
        if (cleaned) {
            printf("\"%s\" -> \"%s\"\n", tests[i], cleaned);
            free(cleaned);
        } else {
            printf("\"%s\" -> allocation failure\n", tests[i]);
        }
    }
    return 0;
}