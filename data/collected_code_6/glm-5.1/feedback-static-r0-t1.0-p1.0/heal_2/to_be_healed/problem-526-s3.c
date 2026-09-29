#include <stdio.h>
#include <ctype.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

char *capitalize_first_last(char *str) {
    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  'SIZE_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'SIZE_MAX'
     */
    size_t len = strnlen(str, SIZE_MAX);
    if (len == 0) {
        return str;
    }

    size_t i = 0;
    while (i < len) {
        if (isalpha((unsigned char)str[i])) {
            size_t start = i;
            while (i < len && isalpha((unsigned char)str[i])) {
                i++;
            }
            size_t end = i - 1;

            if (islower((unsigned char)str[start])) {
                str[start] = (char)toupper((unsigned char)str[start]);
            }

            if (start != end) {
                if (islower((unsigned char)str[end])) {
                    str[end] = (char)toupper((unsigned char)str[end]);
                }
            }
        } else {
            i++;
        }
    }

    return str;
}

int main(void) {
    char str1[] = "hello world";
    char str2[] = "c programming is fun";
    char str3[] = "a";
    char str4[] = "  multiple   spaces  ";

    printf("%s\n", capitalize_first_last(str1));
    printf("%s\n", capitalize_first_last(str2));
    printf("%s\n", capitalize_first_last(str3));
    printf("%s\n", capitalize_first_last(str4));

    return 0;
}