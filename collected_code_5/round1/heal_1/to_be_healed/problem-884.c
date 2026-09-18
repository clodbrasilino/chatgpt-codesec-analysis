#include <stdbool.h>
#include <limits.h>

bool checkBitsInRange(int n, int low, int high) {
    if (low < 0 || high > (sizeof(int) * CHAR_BIT - 1)) {
        return false;
    }
    
    for (int i = low; i <= high; i++) {
        if ((n & (1 << i)) == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int n = 15;
    int low = 0;
    int high = 3;

    bool result = checkBitsInRange(n, low, high);
    if (result) {
        /* Possible weaknesses found:
         *  include the header <stdio.h> or explicitly provide a declaration for 'printf'
         *  call to undeclared library function 'printf' with type 'int (const char *, ...)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        printf("All bits are set in range\n");
    } else {
        printf("All bits are not set in range\n");
    }
    return 0;
}