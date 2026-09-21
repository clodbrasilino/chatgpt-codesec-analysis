#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[16];
    fgets(input, sizeof(input), stdin);
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'n'
     *  'n' undeclared (first use in this function)
     */
    if (sscanf(input, "%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    /* Possible weaknesses found:
     *  use of undeclared identifier 'n'
     */
    int lucid_number = get_lucid_number(n);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'n'
     */
    printf("The lucid number less than or equal to %d is: %d\n", n, lucid_number);
    return 0;
}