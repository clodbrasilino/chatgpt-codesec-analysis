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
    if (regcomp(&regex, "_([a-z])", REG_EXTENDED | REG_NOSUB) != 0) {
        free(camel_str);
        return NULL;
    }

    int offset = 0;
    while (regexec(&regex, camel_str + offset, 2, matches, 0) == 0) {
        int match_pos = matches[1].rm_so + offset;
        camel_str[match_pos - 1] = '\0';
        char *tmp = malloc(strlen(camel_str) + 2 - match_pos);
        strcpy(tmp, camel_str + match_pos);
        /* Possible weaknesses found:
         *  include the header <ctype.h> or explicitly provide a declaration for 'toupper'
         *  call to undeclared library function 'toupper' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'toupper' [-Wimplicit-function-declaration]
         */
        camel_str[match_pos - 1] = toupper(tmp[0]);
        strcat(camel_str + match_pos - 1, tmp);
        free(tmp);
        offset = match_pos + 1;
    }

    regfree(&regex);
    return camel_str;
}

int main() {
    const char *test_str = "this_is_a_snake_case_string";
    char *camel_str = snake_to_camel(test_str);
    if (camel_str) {
        printf("%s\n", camel_str);
        free(camel_str);
    }
    return 0;
}