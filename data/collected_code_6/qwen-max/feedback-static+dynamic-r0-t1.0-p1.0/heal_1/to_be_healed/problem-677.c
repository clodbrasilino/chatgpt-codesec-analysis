#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got 0
  *  test case 0 failed: expected False, got 1
  */

bool is_valid_triangle(int a, int b, int c) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2107649024 + 1316134912 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:10142,execs:4283,op:havoc,rep:8)
     */
    return (a + b > c) && (a + c > b) && (b + c > a);
}

int main() {
    int a, b, c;
    if (scanf("%d %d %d", &a, &b, &c) == 3) {
        if (is_valid_triangle(a, b, c)) {
            printf("Valid triangle\n");
        } else {
            printf("Invalid triangle\n");
        }
    } else {
        printf("Error: Invalid input\n");
    }
    return 0;
}