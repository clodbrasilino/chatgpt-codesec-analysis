#include <stdio.h>
#include <stdlib.h>

int numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;
    
    long long same = k;
    long long diff = (long long)k * (k - 1);
    long long total = same + diff;
    
    for (int i = 3; i <= n; i++) {
        same = diff;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 10383997101241 * 3222420 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:1590,execs:747,op:havoc,rep:4)
         */
        diff = total * (k - 1);
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 3559958832009428378 + 5760134388741632240 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1223,execs:580,op:havoc,rep:3)
         * UBSan: signed integer overflow: 4150058567113300544 + 8655542029470735360 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:1590,execs:747,op:havoc,rep:4)
         */
        total = same + diff;
    }
    
    return (int)total;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:496,execs:242,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int n, k;
    
    printf("Enter number of posts (n): ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("Enter number of colors (k): ");
    if (scanf("%d", &k) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n < 0 || k < 0) {
        fprintf(stderr, "Values must be non-negative\n");
        return 1;
    }
    
    if (k == 0 && n > 0) {
        printf("0\n");
        return 0;
    }
    
    if (k == 1 && n > 2) {
        printf("0\n");
        return 0;
    }
    
    printf("%d\n", numWays(n, k));
    
    return 0;
}