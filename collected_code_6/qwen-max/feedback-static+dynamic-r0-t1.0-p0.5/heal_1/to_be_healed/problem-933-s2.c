#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'tolower'
  */

char *camel_to_snake(const char *input) {
    regex_t regex;
    regmatch_t matches[2];
    char *output = strdup(input);
    int len = strlen(output);

    if (regcomp(&regex, "([a-z0-9])([A-Z])", REG_EXTENDED) != 0) {
        free(output);
        return NULL;
    }

    for (int i = 0; i < len; i++) {
        if (regexec(&regex, output + i, 2, matches, 0) == 0) {
            memmove(output + i + 1 + matches[1].rm_so, output + i + matches[1].rm_so, len - (i + matches[1].rm_so) + 1);
            output[i + matches[1].rm_so] = '_';
            /* Possible weaknesses found:
             *  include the header <ctype.h> or explicitly provide a declaration for 'tolower'
             *  call to undeclared library function 'tolower' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'tolower' [-Wimplicit-function-declaration]
             */
            output[i + matches[1].rm_so + 1] = tolower(output[i + matches[1].rm_so + 1]);
            len++;
            i += matches[1].rm_so;
        }
    }

    regfree(&regex);
    return output;
}

int main() {
    const char *input = "ThisIsCamelCase";
    char *result = camel_to_snake(input);
    if (result) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Error converting string.\n");
    }
    return 0;
}