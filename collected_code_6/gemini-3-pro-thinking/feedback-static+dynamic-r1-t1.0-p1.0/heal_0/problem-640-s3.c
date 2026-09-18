#include <stdio.h>
#include <stddef.h>

void remove_parentheses(char *str);

void remove_parentheses(char *str) {
    if (str == NULL) {
        return;
    }

    size_t read_idx = 0;
    size_t write_idx = 0;
    int paren_count = 0;

    while (str[read_idx] != '\0') {
        if (str[read_idx] == '(') {
            paren_count++;
        } else if (str[read_idx] == ')') {
            if (paren_count > 0) {
                paren_count--;
            } else {
                str[write_idx] = str[read_idx];
                write_idx++;
            }
        } else {
            if (paren_count == 0) {
                str[write_idx] = str[read_idx];
                write_idx++;
            }
        }
        read_idx++;
    }
    str[write_idx] = '\0';
}

int main(void) {
    char str1[] = "This is a (test) string.";
    char str2[] = "Nested (level one (level two)) test.";
    char str3[] = "Unmatched closing ) parenthesis.";
    char str4[] = "(Starting) parenthesis.";
    char str5[] = "Ending (parenthesis)";
    char *str6 = NULL;

    remove_parentheses(str1);
    remove_parentheses(str2);
    remove_parentheses(str3);
    remove_parentheses(str4);
    remove_parentheses(str5);
    remove_parentheses(str6);

    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%s\n", str3);
    printf("%s\n", str4);
    printf("%s\n", str5);

    return 0;
}