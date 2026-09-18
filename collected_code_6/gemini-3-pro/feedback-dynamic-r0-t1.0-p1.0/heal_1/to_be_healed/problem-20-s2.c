#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 2 failed: expected False, got <no output>
  */

bool isWoodall(int n) {
    if (n < 1) {
        return false;
    }
    
    int x = 0;
    while (n % 2 == 0) {
        n /= 2;
        x++;
    }
    
    if (x == 0) {
        return false;
    }
    
    if (x == n + 1) {
        return true;
    }
    
    return false;
}

int main() {
    int num;
    int result;

    result = scanf("%d", &num);
    if (result != 1) {
        return EXIT_FAILURE;
    }

    if (isWoodall(num)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return EXIT_SUCCESS;
}