#include <stdbool.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  include '<stdio.h>' or provide a declaration of 'printf'
  */

bool areAllEmpty(int arr[][10], size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < 10; j++) {
            if (arr[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int dictionaries[5][10] = {{0}, {0}, {0}, {0}, {0}};
    if (areAllEmpty(dictionaries, 5)) {
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         *  implicit declaration of function 'printf' [-Wimplicit-function-declaration]
         */
        printf("All dictionaries are empty\n");
    } else {
        /* Possible weaknesses found:
         *  include '<stdio.h>' or provide a declaration of 'printf'
         *  incompatible implicit declaration of built-in function 'printf' [-Wbuiltin-declaration-mismatch]
         */
        printf("All dictionaries are not empty\n");
    }
    return 0;
}