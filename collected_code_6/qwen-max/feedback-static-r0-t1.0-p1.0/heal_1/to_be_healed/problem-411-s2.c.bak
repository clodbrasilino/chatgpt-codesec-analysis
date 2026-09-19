#include <stdio.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'toupper'
  */

char *snake_to_camel(const char *input) {
    static char output[512];
    memset(output, 0, sizeof(output));
    regex_t preg;
    regmatch_t pmatch[2];
    /* Possible weaknesses found:
     *  The scope of the variable 'nmatch' can be reduced. [variableScope]
     */
    int nmatch = 2;
    if (regcomp(&preg, "_([a-z])", REG_EXTENDED|REG_NEWLINE) == 0) {
        size_t dst = 0;
        for (int i = 0; input[i] != '\0'; ++i) {
            if (regexec(&preg, &input[i], nmatch, pmatch, 0) == 0) {
                /* Possible weaknesses found:
                 *  implicit declaration of function 'toupper' [-Wimplicit-function-declaration]
                 *  call to undeclared library function 'toupper' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 *  include the header <ctype.h> or explicitly provide a declaration for 'toupper'
                 */
                output[dst++] = toupper(input[i+1]);
                i += pmatch[0].rm_eo - pmatch[0].rm_so - 1;
            } else {
                output[dst++] = input[i];
            }
        }
    }
    regfree(&preg);
    return output;
}

int main() {
    const char *snake = "this_is_snake_case";
    char *camel = snake_to_camel(snake);
    printf("Camel case: %s\n", camel);
    return 0;
}