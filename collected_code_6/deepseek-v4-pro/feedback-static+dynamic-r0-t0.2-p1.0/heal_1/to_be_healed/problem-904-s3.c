#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

bool is_even(int number) {
    return number % 2 == 0;
}

int main(void) {
    int test_numbers[] = {0, 1, 2, -3, -4, 100, 101};
    int count = sizeof(test_numbers) / sizeof(test_numbers[0]);
    
    for (int i = 0; i < count; i++) {
        if (is_even(test_numbers[i])) {
            /* Possible weaknesses found:
             *  include the header <stdio.h> or explicitly provide a declaration for 'printf'
             *  call to undeclared library function 'printf' with type 'int (const char *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
             */
            printf("%d is even\n", test_numbers[i]);
        } else {
            printf("%d is odd\n", test_numbers[i]);
        }
    }
    
    return 0;
}