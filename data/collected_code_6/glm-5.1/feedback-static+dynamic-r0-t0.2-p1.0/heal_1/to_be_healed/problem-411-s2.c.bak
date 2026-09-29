#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'toupper'
  */

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    regex_t regex;
    regmatch_t match;
    int ret = regcomp(&regex, "_([a-z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char *camel_str = (char *)malloc(len + 1);
    if (camel_str == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t src_idx = 0;
    size_t dest_idx = 0;
    const char *cursor = snake_str;

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so > 0) {
            size_t copy_len = (size_t)match.rm_so;
            memcpy(camel_str + dest_idx, cursor, copy_len);
            dest_idx += copy_len;
            src_idx += copy_len;
        }

        if (match.rm_eo - match.rm_so > 1) {
            /* Possible weaknesses found:
             *  implicit declaration of function 'toupper' [-Wimplicit-function-declaration]
             *  include the header <ctype.h> or explicitly provide a declaration for 'toupper'
             *  call to undeclared library function 'toupper' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             */
            camel_str[dest_idx++] = (char)toupper((unsigned char)cursor[match.rm_so + 1]);
        }

        src_idx += (size_t)match.rm_eo;
        cursor += match.rm_eo;
    }

    size_t remaining_len = len - src_idx;
    if (remaining_len > 0) {
        memcpy(camel_str + dest_idx, cursor, remaining_len);
        dest_idx += remaining_len;
    }

    camel_str[dest_idx] = '\0';

    regfree(&regex);
    return camel_str;
}

int main(void) {
    const char *input = "convert_this_snake_case_string";
    char *output = snake_to_camel(input);
    
    if (output != NULL) {
        printf("%s\n", output);
        free(output);
    }

    return 0;
}