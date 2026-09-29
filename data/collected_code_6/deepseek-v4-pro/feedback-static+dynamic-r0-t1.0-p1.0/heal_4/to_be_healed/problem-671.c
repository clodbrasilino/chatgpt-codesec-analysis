#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 15, got <no output>
  *  test case 0 failed: expected 23, got <no output>
  *  test case 1 failed: expected 15, got <no output>
  */

unsigned int setRightmostUnsetBit(unsigned int n) {
    return n | (n + 1);
}

int main(void) {
    unsigned int test_values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 15, 16, 255, 1024};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        unsigned int input = test_values[i];
        unsigned int result = setRightmostUnsetBit(input);
        printf("setRightmostUnsetBit(%u) = %u\n", input, result);
    }
    
    return 0;
}