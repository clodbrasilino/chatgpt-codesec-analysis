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
    int len = strlen(camel_str);
    int i, j;

    if (regcomp(&regex, "_([a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(camel_str);
        return NULL;
    }

    for (i = 0; i < len; ) {
        if (regexec(&regex, camel_str + i, 2, matches, 0) == 0) {
            for (j = i + matches[1].rm_so; j < len; ++j) {
                camel_str[j] = camel_str[j + 1];
            }
            /* Possible weaknesses found:
             *  implicit declaration of function 'toupper' [-Wimplicit-function-declaration]
             *  call to undeclared library function 'toupper' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  include the header <ctype.h> or explicitly provide a declaration for 'toupper'
             */
            camel_str[j - 1] = toupper(camel_str[j - 1]);
            --len;
            i += matches[1].rm_so;
        } else {
            break;
        }
    }

    regfree(&regex);
    return camel_str;
}

int main() {
    const char *snake_str = "this_is_a_snake_case_string";
    char *camel_str = snake_to_camel(snake_str);

    if (camel_str) {
        printf("Camel case: %s\n", camel_str);
        free(camel_str);
    } else {
        printf("Failed to convert to camel case.\n");
    }

    return 0;
}