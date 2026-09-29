#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 3
  *  test case 2 failed: expected 3, got 2
  *  test case 0 failed: expected 1, got 3
  */

int min_operations(int a, int b) {
    int diff = abs(a - b);
    if (diff == 0) return 0;
    
    int k = 1;
    long long sum = 1;
    while (sum < diff || (sum - diff) % 2 != 0) {
        k++;
        sum += k;
    }
    return k;
}

int main(void) {
    int t;
    if (scanf("%d", &t) == 1) {
        while (t-- > 0) {
            int a, b;
            if (scanf("%d %d", &a, &b) == 2) {
                printf("%d\n", min_operations(a, b));
            }
        }
    }
    return 0;
}