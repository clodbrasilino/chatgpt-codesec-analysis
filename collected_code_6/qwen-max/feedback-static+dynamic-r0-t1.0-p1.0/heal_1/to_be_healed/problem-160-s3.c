#include <stdio.h>
#include <stdlib.h>

int find_solution(int a, int b, int n, int *x, int *y) {
    if (a == 0 && b == 0) return 0;
    if (a == 0) {
        if (n % b == 0) {
            *x = 0;
            *y = n / b;
            return 1;
        } else {
            return 0;
        }
    }
    if (b == 0) {
        if (n % a == 0) {
            *x = n / a;
            *y = 0;
            return 1;
        } else {
            return 0;
        }
    }

    int gcd, x1, y1;

    // Extended Euclidean Algorithm
    for (int i = 0; ; i++) {
        /* Possible weaknesses found:
         * UBSan: division by zero (AFL crash: id:000001,sig:06,src:000002,time:619,execs:234,op:havoc,rep:8)
         */
        if (a % b == 0) {
            gcd = b;
            break;
        }
        a = a % b;
        if (a % b == 0) {
            gcd = a;
            break;
        }
        b = b % a;
    }

    if (n % gcd != 0) return 0;

    /* Possible weaknesses found:
     * ASan: FPE (AFL crash: id:000001,sig:06,src:000002,time:619,execs:234,op:havoc,rep:8)
     */
    a = a / gcd;
    n = n / gcd;

    x1 = 1;
    y1 = -(a - 1);

    if (n < 0) {
        n = -n;
        x1 = -x1;
        y1 = -y1;
    }

    while (y1 < 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2146666453 + 4444444 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000002,time:9752,execs:3207,op:havoc,rep:8)
         */
        x1 += a;
        y1 += b / gcd;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 19744693 * 1199547824 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000002,time:10998,execs:3608,op:havoc,rep:6)
     * UBSan: signed integer overflow: -198471 * 1199547824 cannot be represented in type 'int' (AFL crash: id:000004,sig:06,src:000002,time:29337,execs:9599,op:havoc,rep:8)
     */
    *x = x1 * n;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1721 * 1014428410 cannot be represented in type 'int' (AFL crash: id:000005,sig:06,src:000018,time:49273,execs:16073,op:havoc,rep:8)
     */
    *y = y1 * n / (b / gcd);

    return 1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:278,execs:109,op:havoc,rep:4; likely memory-safety defect
  */

int main() {
    int a, b, n, x, y;
    printf("Enter values of a, b, and n: ");
    scanf("%d %d %d", &a, &b, &n);

    if (find_solution(a, b, n, &x, &y)) {
        printf("Solution found: x = %d, y = %d\n", x, y);
    } else {
        printf("No solution found.\n");
    }

    return 0;
}