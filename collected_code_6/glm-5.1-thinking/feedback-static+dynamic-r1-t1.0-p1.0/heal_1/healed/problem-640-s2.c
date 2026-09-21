#include <stdio.h>

char *remove_parenthesis(char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t write_idx = 0;

    for (size_t read_idx = 0; str[read_idx] != '\0'; ++read_idx) {
        if (str[read_idx] != '(' && str[read_idx] != ')') {
            str[write_idx++] = str[read_idx];
        }
    }

    str[write_idx] = '\0';
    return str;
}

int main(void) {
    char str1[] = "Hello (World)!";
    char str2[] = "(Nested (Parentheses)) Example";
    char str3[] = "Unbalanced ( Open";
    char str4[] = "Unbalanced ) Close";

    remove_parenthesis(str1);
    remove_parenthesis(str2);
    remove_parenthesis(str3);
    remove_parenthesis(str4);

    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%s\n", str3);
    printf("%s\n", str4);

    return 0;
}