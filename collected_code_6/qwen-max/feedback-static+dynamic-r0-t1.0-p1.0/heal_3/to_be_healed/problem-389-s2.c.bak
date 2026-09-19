#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

long long lucas_number(int n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    /* Possible weaknesses found:
     *  use of undeclared identifier 'int128_t'
     *  unknown type name 'int128_t'; did you mean 'int32_t'?
     */
    int128_t a = 2, b = 1;
    for (int i = 2; i <= n; ++i) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'int128_t'
         *  unknown type name 'int128_t'; did you mean 'int32_t'?
         */
        int128_t c = a + b;
        /* Possible weaknesses found:
         *  use of undeclared identifier 'a'
         *  use of undeclared identifier 'b'
         */
        a = b;
        /* Possible weaknesses found:
         *  use of undeclared identifier 'c'
         *  use of undeclared identifier 'b'
         */
        b = c;
    }
    /* Possible weaknesses found:
     *  use of undeclared identifier 'b'
     */
    return (long long)b;
}

int main() {
    int n;
    printf("Enter the position of the Lucas number: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter an integer.\n");
        return EXIT_FAILURE;
    }

    long long result = lucas_number(n);
    printf("The %dth Lucas number is: %lld\n", n, result);

    return EXIT_SUCCESS;
}