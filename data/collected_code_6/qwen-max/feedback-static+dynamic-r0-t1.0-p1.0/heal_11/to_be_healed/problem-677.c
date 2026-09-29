#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected False, got 1
  *  test case 2 failed: expected True, got 0
  */

bool is_valid_triangle(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) return false;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2075430227 + 605545555 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000005,time:1014,execs:1012,op:havoc,rep:1)
     * UBSan: signed integer overflow: 1743798099 + 755545555 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:17179,execs:15423,op:havoc,rep:14)
     */
    if (a + b > c && a + c > b && b + c > a) return true;
    return false;
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