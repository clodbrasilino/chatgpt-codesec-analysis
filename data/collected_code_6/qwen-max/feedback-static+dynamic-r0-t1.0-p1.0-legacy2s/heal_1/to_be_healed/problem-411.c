#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'toupper'
  */

char* snake_to_camel(const char* snake) {
    regex_t regex;
    regmatch_t pmatch[2];
    int nmatch = 2;
    const size_t len = strlen(snake);
    char* camel = (char*)malloc(len + 1);
    if (!camel) return NULL;

    int rc = regcomp(&regex, "(_[a-z])", REG_EXTENDED | REG_NOSUB);
    /* Possible weaknesses found:
     *  Memory leak: camel [memleak]
     */
    if (rc) return NULL;

    char* dest = camel;
    for (const char* src = snake; *src; ) {
        if (regexec(&regex, src, nmatch, pmatch, 0) == 0 && pmatch[0].rm_so == 0) {
            /* Possible weaknesses found:
             *  include the header <ctype.h> or explicitly provide a declaration for 'toupper'
             *  call to undeclared library function 'toupper' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'toupper' [-Wimplicit-function-declaration]
             */
            *dest++ = toupper(src[1]);
            src += 2;
        } else {
            *dest++ = *src++;
        }
    }
    *dest = '\0';

    regfree(&regex);
    return camel;
}

int main() {
    const char* snake = "this_is_a_snake_case_string";
    char* camel = snake_to_camel(snake);
    if (camel) {
        printf("%s\n", camel);
        free(camel);
    }
    return 0;
}