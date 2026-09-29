#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strlen'
  */

int is_number_at_end(const char *str) {
    if (str == NULL) return 0;
    /* Possible weaknesses found:
     *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strlen'
     *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
     */
    const char *end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) --end;
    while (end > str && isdigit(*end)) --end;
    return end + 1 != str && !isdigit(*(end + 1));
}

int main(void) {
    const char *test_strings[] = {"hello123", "123hello", "hello 123", "hello", ""};
    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        printf("'%s': %d\n", test_strings[i], is_number_at_end(test_strings[i]));
    }
    return 0;
}