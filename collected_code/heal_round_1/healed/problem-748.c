#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

void add_spaces(char *str) {
    if(str == NULL)
        return;

    regex_t regex;
    regcomp(&regex, "[A-Z]", REG_EXTENDED);

    size_t str_len = strlen(str);
    char *result = (char *) calloc(2 * str_len + 1, sizeof(char));

    if(result == NULL)
        return;

    size_t i = 0;
    while (*str != '\0') {
        if (regexec(&regex, str, 0, NULL, 0) == REG_NOMATCH) {
            result[i++] = *str++;
        } else {
            result[i++] = ' ';
            result[i++] = *str++;
        }
    }

    result[i] = '\0';
    strncpy(str, result, str_len+1);
    free(result);
}

int main() {
    char str[] = "WriteACFunctionToPutSpacesBetweenWordsStartingWithCapitalLetters";
    add_spaces(str);
    printf("%s\n", str);
    return 0;
}