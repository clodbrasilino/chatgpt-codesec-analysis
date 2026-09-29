#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

bool isEven(int num) {
    return num % 2 == 0;
}

int main() {
    int num;
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
     *  include '<stdio.h>' or provide a declaration of 'printf'
     *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
     */
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  implicit declaration of function 'scanf' [-Wimplicit-function-declaration]
     *  include '<stdio.h>' or provide a declaration of 'scanf'
     *  incompatible implicit declaration of built-in function 'scanf' [-Wbuiltin-declaration-mismatch]
     */
    scanf("%d", &num);

    if(isEven(num)) {
        printf("The number is even.\n");
    } else {
        printf("The number is odd.\n");
    }

    return 0;
}