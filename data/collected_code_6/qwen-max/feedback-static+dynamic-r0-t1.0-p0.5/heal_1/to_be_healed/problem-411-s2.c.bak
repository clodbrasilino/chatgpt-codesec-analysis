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
    char *camel_str = malloc(strlen(snake_str) + 1);
    if (camel_str == NULL) {
        return NULL;
    }
    strcpy(camel_str, snake_str);

    if (regcomp(&regex, "_([a-z])", REG_EXTENDED | REG_NEWLINE) != 0) {
        free(camel_str);
        return NULL;
    }

    int pos = 0;
    while (regexec(&regex, camel_str + pos, 2, matches, 0) == 0) {
        int match_start = matches[1].rm_so + pos;
        /* Possible weaknesses found:
         *  call to undeclared library function 'toupper' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'toupper' [-Wimplicit-function-declaration]
         *  include the header <ctype.h> or explicitly provide a declaration for 'toupper'
         */
        camel_str[match_start] = toupper(camel_str[match_start]);
        memmove(camel_str + match_start - 1, camel_str + match_start, strlen(camel_str + match_start) + 1);
        pos = match_start;
    }

    regfree(&regex);
    return camel_str;
}

int main() {
    const char *snake_str = "this_is_a_snake_case_string";
    char *camel_str = snake_to_camel(snake_str);
    if (camel_str != NULL) {
        printf("%s\n", camel_str);
        free(camel_str);
    } else {
        printf("Error converting string.\n");
    }
    return 0;
}