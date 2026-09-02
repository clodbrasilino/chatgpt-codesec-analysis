#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isdigit'
  */

int check_decimal(const char *str) {
    if (str == NULL) return 0;
    char *endptr;
    strtod(str, &endptr);
    if (*endptr != '\0') return 0;
    while (*str && *str != '.') str++;
    int decimal_places = 0;
    if (*str == '.') {
        str++;
        while (*str) {
            /* Possible weaknesses found:
             *  implicit declaration of function 'isdigit' [-Wimplicit-function-declaration]
             *  include the header <ctype.h> or explicitly provide a declaration for 'isdigit'
             *  call to undeclared library function 'isdigit' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             */
            if (!isdigit(*str)) return 0;
            decimal_places++;
            str++;
        }
    }
    return decimal_places == 2;
}

int main() {
    const char *test_strings[] = {"12.34", "12.3", "12.345", "abc", "1234", "12.34a"};
    for (size_t i = 0; i < sizeof(test_strings)/sizeof(test_strings[0]); i++) {
        printf("%s: %s\n", test_strings[i], check_decimal(test_strings[i]) ? "Valid" : "Invalid");
    }
    return 0;
}