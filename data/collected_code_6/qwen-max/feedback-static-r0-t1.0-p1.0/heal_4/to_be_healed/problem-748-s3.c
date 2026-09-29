#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int add_spaces_between_capital_words(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];

    if (regcomp(&regex, "([A-Z])", REG_EXTENDED) != 0) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *original_str = str, *new_str = malloc(len * 2 + 1);
    if (new_str == NULL) {
        regfree(&regex);
        return -1;
    }
    
    while (regexec(&regex, str, 1, pmatch, 0) == 0) {
        size_t offset = pmatch[0].rm_so;
        if (str[pmatch[0].rm_so] >= 'A' && str[pmatch[0].rm_so] <= 'Z') {
            memmove(new_str + offset + 1, new_str + offset, original_str + len - (str + offset));
            new_str[offset] = ' ';
        }
        str += offset + 1; 
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(original_str, new_str);
    free(new_str);
    regfree(&regex);
    return 0;
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    if (add_spaces_between_capital_words(str) != -1) {
        printf("%s\n", str);
    } else {
        perror("Regex error");
        exit(EXIT_FAILURE);
    }
    return 0;
}