#include <stdio.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

char* snake_to_camel(char *snake_str) {
    char *p = snake_str;
    int capitalize_next = 1;
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    char *output = (char *)malloc(strlen(snake_str) + 1);
    int index = 0;

    while (*p) {
        if (*p == '_') {
            p++;
            capitalize_next = 1;
            continue;
        }
        if (capitalize_next && isalpha(*p)) {
            output[index] = toupper(*p);
            capitalize_next = 0;
        } else {
            output[index] = *p;
        }
        index++;
        p++;
    }
    output[index] = '\0';
    return output;
}

int main() {
    char snake_case[] = "this_is_a_snake_case_string";
    char *camel_case = snake_to_camel(snake_case);

    printf("%s\n", camel_case);
    /* Possible weaknesses found:
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     */
    free(camel_case);

    return 0;
}