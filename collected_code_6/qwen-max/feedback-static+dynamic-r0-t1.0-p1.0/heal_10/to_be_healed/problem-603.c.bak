#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcspn'
  */

int get_next_power_of_2(int n) {
    if (n <= 0) return 1;
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

int is_lucid_number(int n) {
    int next_power = get_next_power_of_2(n);
    return (next_power == 2 * n);
}

int get_lucid_number(int n) {
    if (n <= 0) return 0;
    while (n >= 1 && !is_lucid_number(n)) {
        n--;
    }
    return n;
}

int main() {
    char input[16];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Input error.\n");
        return 1;
    }
    /* Possible weaknesses found:
     *  call to undeclared library function 'strcspn' with type 'unsigned long (const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'strcspn' [-Wimplicit-function-declaration]
     *  include the header <string.h> or explicitly provide a declaration for 'strcspn'
     */
    input[strcspn(input, "\n")] = 0; // Remove newline character
    int n;
    if (sscanf(input, "%d", &n) != 1 || n < 0) {
        printf("Invalid input.\n");
        return 1;
    }
    int lucid_number = get_lucid_number(n);
    printf("The lucid number less than or equal to %d is: %d\n", n, lucid_number);
    return 0;
}