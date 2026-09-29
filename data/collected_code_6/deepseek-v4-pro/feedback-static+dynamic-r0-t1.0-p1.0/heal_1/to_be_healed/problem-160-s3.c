#include <stdio.h>
#include <stdlib.h>

int extended_gcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

int find_solution(int a, int b, int n, int *x, int *y) {
    if (a == 0 && b == 0) {
        return n == 0;
    }
    if (a == 0) {
        if (n % b == 0) {
            *x = 0;
            *y = n / b;
            return 1;
        }
        return 0;
    }
    if (b == 0) {
        if (n % a == 0) {
            *x = n / a;
            *y = 0;
            return 1;
        }
        return 0;
    }
    
    int x0, y0;
    int gcd = extended_gcd(abs(a), abs(b), &x0, &y0);
    
    if (n % gcd != 0) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -115645449 * 22224 cannot be represented in type 'int' (AFL crash: id:000004,sig:06,src:000011,time:26529,execs:13089,op:havoc,rep:1)
     * UBSan: signed integer overflow: -21940433 * 247 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000011,time:21375,execs:10666,op:havoc,rep:1)
     */
    x0 *= n / gcd;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 23026178 * 22224 cannot be represented in type 'int' (AFL crash: id:000004,sig:06,src:000011,time:26529,execs:13089,op:havoc,rep:1)
     * UBSan: signed integer overflow: -203333897 * 222224 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000011,time:21383,execs:10669,op:havoc,rep:6)
     */
    y0 *= n / gcd;
    
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    
    *x = x0;
    *y = y0;
    return 1;
}

int main(void) {
    int a, b, n;
    int x, y;
    
    printf("Enter a, b, n: ");
    if (scanf("%d %d %d", &a, &b, &n) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (find_solution(a, b, n, &x, &y)) {
        printf("Solution: x = %d, y = %d\n", x, y);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 61432719 * -1124319655 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000011,time:21375,execs:10666,op:havoc,rep:1)
         * UBSan: signed integer overflow: 247 * 1678994288 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000011,time:21383,execs:10669,op:havoc,rep:6)
         * UBSan: signed integer overflow: 247 * 203333897 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:5402,execs:2714,op:havoc,rep:6)
         * UBSan: signed integer overflow: 222222247 * -1714015568 cannot be represented in type 'int' (AFL crash: id:000004,sig:06,src:000011,time:26529,execs:13089,op:havoc,rep:1)
         * UBSan: signed integer overflow: 22222247 * -228 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:2120,execs:1094,op:havoc,rep:15)
         * UBSan: signed integer overflow: -1822745074 * -149912146 cannot be represented in type 'int' (AFL crash: id:000005,sig:06,src:000011,time:28872,execs:14149,op:havoc,rep:1)
         * UBSan: signed integer overflow: 2224 * 2278180 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:2120,execs:1094,op:havoc,rep:15)
         * UBSan: signed integer overflow: -1116077168 * -632671648 cannot be represented in type 'int' (AFL crash: id:000004,sig:06,src:000011,time:26529,execs:13089,op:havoc,rep:1)
         * UBSan: signed integer overflow: 614327184 * -444798200 cannot be represented in type 'int' (AFL crash: id:000005,sig:06,src:000011,time:28872,execs:14149,op:havoc,rep:1)
         * UBSan: signed integer overflow: 222222224 * 1498146884 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000011,time:21375,execs:10666,op:havoc,rep:1)
         * UBSan: signed integer overflow: -1116077168 * 45 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:5402,execs:2714,op:havoc,rep:6)
         * UBSan: signed integer overflow: -1116077168 * -10000080 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000011,time:21383,execs:10669,op:havoc,rep:6)
         */
        printf("Verification: %d*%d + %d*%d = %d\n", a, x, b, y, a*x + b*y);
    } else {
        printf("No integer solution exists\n");
    }
    
    return EXIT_SUCCESS;
}