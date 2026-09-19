#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'toupper'
  */

char *snake_to_camel(const char *snake_str) {
    regex_t regex;
    regmatch_t matches[2];
    char *camel_str = strdup(snake_str);
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    int i, offset = 0;

    if (regcomp(&regex, "(_[a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(camel_str);
        return NULL;
    }

    while (regexec(&regex, camel_str + offset, 2, matches, 0) == 0) {
        i = matches[1].rm_so + offset;
        /* Possible weaknesses found:
         *  implicit declaration of function 'toupper' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'toupper' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <ctype.h> or explicitly provide a declaration for 'toupper'
         */
        camel_str[i] = toupper(camel_str[i + 1]);
        memmove(camel_str + i + 1, camel_str + i + 2, strlen(camel_str + i + 2) + 1);
        offset = i + 1;
    }

    regfree(&regex);
    return camel_str;
}

int main() {
    const char *snake_str = "this_is_a_snake_case_string";
    char *camel_str = snake_to_camel(snake_str);

    if (camel_str) {
        printf("%s\n", camel_str);
        free(camel_str);
    } else {
        printf("Error converting string.\n");
    }

    return 0;
}