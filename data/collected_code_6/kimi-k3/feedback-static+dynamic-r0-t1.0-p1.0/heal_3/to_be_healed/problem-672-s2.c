#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 49, got <no output>
  *  test case 0 failed: expected 30, got <no output>
  *  test case 1 failed: expected 55, got <no output>
  */

int max_of_three(int a, int b, int c) {
    int max = a;
    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    return max;
}

int main(void) {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        return 1;
    }
    printf("%d\n", max_of_three(a, b, c));
    return 0;
}