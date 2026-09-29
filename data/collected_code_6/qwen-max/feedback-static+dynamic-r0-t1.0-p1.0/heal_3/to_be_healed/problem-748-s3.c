#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int add_spaces_between_capital_words(char *str) {
    regex_t regex;
    regmatch_t pmatch[1];
    int reti = regcomp(&regex, "([A-Z])", REG_EXTENDED);
    if (reti != 0) {
        return -1;
    }

    char *src = str, *dest = str;
    /* Possible weaknesses found:
     *  Variable 'len' is assigned a value that is never used. [unreadVariable]
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);

    while (regexec(&regex, src, 1, pmatch, 0) == 0) {
        size_t distance = pmatch[0].rm_so;
        /* Possible weaknesses found:
         *  invalid operands to binary expression ('char *' and 'void *')
         *  invalid operands to binary + (have 'char *' and 'void *')
         */
        dest += memmove(dest, src, distance);
        *dest++ = ' ';
        src += distance + 1;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(dest, src);

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