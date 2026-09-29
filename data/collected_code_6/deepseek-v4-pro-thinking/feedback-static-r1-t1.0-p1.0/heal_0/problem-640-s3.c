#include <stdio.h>

void remove_parenthesis_area(char *str) {
    if (str == NULL) {
        return;
    }

    int depth = 0;
    char *src = str;
    char *dst = str;

    while (*src != '\0') {
        if (*src == '(') {
            depth++;
            src++;
            continue;
        }

        if (*src == ')') {
            if (depth > 0) {
                depth--;
                src++;
                continue;
            }
        }

        if (depth == 0) {
            *dst++ = *src;
        }

        src++;
    }

    *dst = '\0';
}

int main(void) {
    char s1[] = "Hello (world) from (C)";
    remove_parenthesis_area(s1);
    printf("%s\n", s1);

    char s2[] = "No parentheses here";
    remove_parenthesis_area(s2);
    printf("%s\n", s2);

    char s3[] = "Nested (a (b) c) end";
    remove_parenthesis_area(s3);
    printf("%s\n", s3);

    char s4[] = "Unmatched (oops";
    remove_parenthesis_area(s4);
    printf("%s\n", s4);

    char s5[] = "Extra ) close";
    remove_parenthesis_area(s5);
    printf("%s\n", s5);

    char s6[] = "(start) end (again)";
    remove_parenthesis_area(s6);
    printf("%s\n", s6);

    remove_parenthesis_area(NULL);

    return 0;
}