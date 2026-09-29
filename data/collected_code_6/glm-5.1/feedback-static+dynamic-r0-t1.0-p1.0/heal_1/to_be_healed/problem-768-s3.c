#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected True, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 2 failed: expected False, got <no output>
  */

bool check_odd_parity(unsigned int num) {
    bool parity = false;
    while (num) {
        parity = !parity;
        num = num & (num - 1);
    }
    return parity;
}

int main(void) {
    unsigned int val;
    if (scanf("%u", &val) == 1) {
        if (check_odd_parity(val)) {
            printf("Odd Parity\n");
        } else {
            printf("Even Parity\n");
        }
    } else {
        return 1;
    }
    return 0;
}