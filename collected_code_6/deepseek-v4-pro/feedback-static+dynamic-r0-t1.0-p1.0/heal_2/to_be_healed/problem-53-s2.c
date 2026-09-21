#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

bool first_last_equal(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return false;
    }
    
    size_t len = 0;
    while (str[len] != '\0') {
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'SIZE_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'SIZE_MAX'
         */
        if (len >= SIZE_MAX) {
            return false;
        }
        len++;
    }
    
    return str[0] == str[len - 1];
}

int main(void) {
    const char *test1 = "hello";
    const char *test2 = "world";
    const char *test3 = "a";
    const char *test4 = "";
    const char *test5 = NULL;
    const char *test6 = "racecar";

    printf("%d\n", first_last_equal(test1));
    printf("%d\n", first_last_equal(test2));
    printf("%d\n", first_last_equal(test3));
    printf("%d\n", first_last_equal(test4));
    printf("%d\n", first_last_equal(test5));
    printf("%d\n", first_last_equal(test6));

    return 0;
}