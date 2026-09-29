#include <stdio.h>
#include <stdlib.h>

unsigned int count_unset_bits(unsigned int number);
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1, got 30
  *  test case 1 failed: expected 2, got 31
  *  test case 0 failed: expected 1, got 31
  */

unsigned int count_unset_bits(unsigned int number) {
    unsigned int unset_count = 0;
    unsigned int total_bits = sizeof(unsigned int) * 8;
    unsigned int i;

    for (i = 0; i < total_bits; i++) {
        if ((number & (1U << i)) == 0) {
            unset_count++;
        }
    }

    return unset_count;
}

int main(void) {
    unsigned int input_number = 0;
    unsigned int unset_bits = 0;
    int scan_result = 0;

    scan_result = scanf("%u", &input_number);
    
    if (scan_result != 1) {
        fprintf(stderr, "Invalid Input\n");
        return EXIT_FAILURE;
    }

    unset_bits = count_unset_bits(input_number);
    printf("%u\n", unset_bits);

    return EXIT_SUCCESS;
}