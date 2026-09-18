#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected False, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

bool is_woodall(int n) {
    if (n < 1) {
        return false;
    }

    int i = 1;
    int power_of_two = 2;
    int woodall = 1;

    while (woodall < n) {
        woodall = i * power_of_two - 1;
        if (woodall == n) {
            return true;
        }
        i++;
        power_of_two *= 2;
    }

    return false;
}

int main(void) {
    int num;

    if (scanf("%d", &num) != 1) {
        return EXIT_FAILURE;
    }

    if (is_woodall(num)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return EXIT_SUCCESS;
}