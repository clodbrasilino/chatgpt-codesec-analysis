#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

void add_spaces(char *str) {
    regex_t regex;
    regcomp(&regex, "[A-Z]", REG_EXTENDED);
    
    char *result = (char *) malloc(2 * strlen(str) * sizeof(char));
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
    
    strcpy(str, result);
    free(result);
}

int main() {
    char str[] = "WriteACFunctionToPutSpacesBetweenWordsStartingWithCapitalLetters";
    add_spaces(str);
    printf("%s\n", str);
    return 0;
}