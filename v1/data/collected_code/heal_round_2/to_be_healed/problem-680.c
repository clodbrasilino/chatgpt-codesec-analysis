#include <stdbool.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

bool isIncreasing(const int numbers[], int length) {
    for (int i = 1; i < length; i++) {
        if (numbers[i] <= numbers[i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int length = sizeof(numbers) / sizeof(numbers[0]);

    if (isIncreasing(numbers, length)) {
        /* Possible weaknesses found:
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
         */
        printf("The array is increasing.\n");
    } else {
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         */
        printf("The array is not increasing.\n");
    }

    return 0;
}