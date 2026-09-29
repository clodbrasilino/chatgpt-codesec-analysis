#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

/* Possible weaknesses found:
 *  Shadowed declaration
 */
void insert_spaces(char *str, size_t len) {
    regex_t reg;
    regmatch_t match[1];
    char pattern[] = "([A-Z][^A-Z]*)";

    if (regcomp(&reg, pattern, REG_EXTENDED | REG_NEWLINE) != 0) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    /* Possible weaknesses found:
     *  Variable 'end' can be declared as pointer to const [constVariablePointer]
     */
    char *end = str + len;

    while (regexec(&reg, str, 1, match, 0) == 0 && str < end) {
        /* Possible weaknesses found:
         *  Local variable 'len' shadows outer argument [shadowArgument]
         *  Shadow variable
         */
        size_t len = end - (str + match[0].rm_eo);
        memmove(str + match[0].rm_eo + 1, str + match[0].rm_eo, len + 1);
        str[match[0].rm_eo] = ' ';
        str += match[0].rm_eo + 1;
    }

    regfree(&reg);
}

int main() {
    char str[] = "HelloWorldThisIsATest";
    insert_spaces(str, sizeof(str) - 1);
    printf("%s\n", str);
    return 0;
}