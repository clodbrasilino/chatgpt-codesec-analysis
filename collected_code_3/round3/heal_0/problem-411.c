#include <stdio.h>
#include <ctype.h>
#include <string.h>

void snakeToCamel(char str[]) {
    int resInd = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] == '_') {
            str[i] = toupper(str[i + 1]);
            str[i + 1] = '\0';
        }
        else
            str[resInd++] = str[i];
    }
    str[resInd] = '\0';
}

int main() {
    char str[] = "this_is_a_snake_case_string";
    snakeToCamel(str);
    printf("%s", str);
    return 0;
}