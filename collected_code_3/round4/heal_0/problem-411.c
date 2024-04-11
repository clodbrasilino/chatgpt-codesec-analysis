#include <stdio.h>
#include <ctype.h>
#include <string.h>

void toCamelCase(char *str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] == '_') {
            str[j] = toupper(str[++i]);
        } else {
            str[j] = str[i];
        }
        i++;
        j++;
    }
    str[j] = '\0';
}

int main() {
    char str[] = "this_is_a_snake_case_string";
    toCamelCase(str);
    printf("%s\n", str);
    return 0;
}