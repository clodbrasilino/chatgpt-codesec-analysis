#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'tolower'
  */

char* camel_to_snake(const char *input) {
    regex_t regex;
    regmatch_t match[2];
    /* Possible weaknesses found:
     *  Variable 'output_len' is assigned a value that is never used. [unreadVariable]
     */
    size_t output_len = 0;
    /* Possible weaknesses found:
     *  Unused variable: output [unusedVariable]
     */
    char *output, *result;
    /* Possible weaknesses found:
     *  The scope of the variable 'rc' can be reduced. [variableScope]
     */
    int rc;

    if (regcomp(&regex, "([a-z0-9])([A-Z])", REG_EXTENDED)) {
        return NULL;
    }

    result = strdup(input);
    if (!result) {
        return NULL;
    }

    while (1) {
        rc = regexec(&regex, result, 2, match, 0);
        if (rc != 0) break;
        memmove(result + match[0].rm_eo + 1, result + match[0].rm_eo, strlen(result + match[0].rm_eo) + 1);
        *(result + match[0].rm_so + 1) = '_';
        /* Possible weaknesses found:
         *  include the header <ctype.h> or explicitly provide a declaration for 'tolower'
         *  implicit declaration of function 'tolower' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'tolower' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        *(result + match[0].rm_so + 2) = tolower(*(result + match[0].rm_eo));
    }

    regfree(&regex);
    return result;
}

int main() {
    const char *input = "ThisIsCamelCaseString";
    char *output = camel_to_snake(input);
    if (output) {
        printf("%s\n", output);
        free(output);
    } else {
        printf("Conversion failed.\n");
    }
    return 0;
}