#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    int test_values[] = {4, 7, 0, -3, 10, -8};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (int i = 0; i < num_tests; i++) {
        if (is_even(test_values[i])) {
            /* Possible weaknesses found:
             *  include the header <stdio.h> or explicitly provide a declaration for 'printf'
             *  call to undeclared library function 'printf' with type 'int (const char *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
             */
            printf("%d is even\n", test_values[i]);
        } else {
            printf("%d is odd\n", test_values[i]);
        }
    }
    
    return 0;
}