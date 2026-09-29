#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void add_spaces(char *str) {
    if(str == NULL)
        return;

    size_t str_len = strlen(str);
    if(str_len == 0)
        return;

    regex_t regex;
    if(regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0)
        return;

    char *result = (char *) calloc(2 * str_len + 1, sizeof(char));
    if(result == NULL)
        return;

    size_t i = 0;
    while (i < str_len) {
        if (regexec(&regex, str + i, 0, NULL, 0) == REG_NOMATCH) {
            result[i] = str[i];
        } else {
            result[2*i] = ' ';
            result[2*i + 1] = str[i];
        }
        i++;
    }

    result[2*str_len] = '\0';
    str_len = strlen(result);
    if(str_len > 0)
        memmove(str, result, str_len + 1);
    else
        str[0] = '\0';

    free(result);
}

int main() {
    char str[] = "WriteACFunctionToPutSpacesBetweenWordsStartingWithCapitalLetters";
    add_spaces(str);
    printf("%s\n", str);
    return 0;
}
