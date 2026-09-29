#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

bool isValidTriangle(int a, int b, int c) {
    if ((a + b > c) && (a + c > b) && (b + c > a)) {
        return true;
    } else {
        return false;
    }
}

int main() {
    int a = 7, b = 10, c = 5;

    if (isValidTriangle(a, b, c)) {
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
         */
        printf("Valid Triangle\n");
    } else {
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         */
        printf("Invalid Triangle\n");
    }

    return 0;
}