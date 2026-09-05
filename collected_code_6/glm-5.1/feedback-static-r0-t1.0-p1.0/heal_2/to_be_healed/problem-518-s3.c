#include <stdio.h>
#include <stdlib.h>

unsigned long int find_square_root(unsigned long int number) {
    if (number == 0) {
        return 0;
    }
    unsigned long int low = 1;
    unsigned long int high = number;
    while (low <= high) {
        unsigned long int mid = low + (high - low) / 2;
        if (mid == number / mid && number % mid == 0) {
            return mid;
        } else if (mid > number / mid) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    unsigned long int perfect_number = strtoul(argv[1], NULL, 10);
    if (perfect_number == 0) {
        return EXIT_FAILURE;
    }
    unsigned long int result = find_square_root(perfect_number);
    printf("%lu\n", result);
    return EXIT_SUCCESS;
}