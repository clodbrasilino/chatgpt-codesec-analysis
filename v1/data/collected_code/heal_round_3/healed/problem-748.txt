#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void add_spaces(char *str) {
    if(str == NULL || str[0] == '\0')
        return;

    size_t str_len = strlen(str);
    regex_t regex;

    if(regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0)
        return;

    char *result = (char *) calloc(2 * str_len + 1, sizeof(char));
 
    if(result == NULL)
        return;

    size_t i = 0, j = 0;
    while (i < str_len) {
        if (regexec(&regex, str + i, 0, NULL, 0) == REG_NOMATCH) {
            result[j++] = str[i];
        } else {
            result[j++] = ' ';
            result[j++] = str[i];
        }
        i++;
    }

    if(strlen(result) == 0) {
        str[0] = '\0';
    } else {
        memcpy(str, result, strlen(result) + 1);
    }

    free(result);
    regfree(&regex);
}

int main() {
    char str[100] = "WriteACFunctionToPutSpacesBetweenWordsStartingWithCapitalLetters";
    add_spaces(str);
    printf("%s\n", str);
    return 0;
}