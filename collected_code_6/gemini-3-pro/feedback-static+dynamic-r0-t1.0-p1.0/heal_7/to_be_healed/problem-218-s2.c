#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got 2
  */

int min_operations(int a, int b) {
    int diff = abs(a - b);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1116077174 * 2 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:55666,execs:6683,op:havoc,rep:1)
     * UBSan: signed integer overflow: 1303176074 * 2 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000004,time:40069,execs:4687,op:havoc,rep:1)
     */
    return (diff * 2 + 1) / 3; 
}

int main(void) {
    int a, b;
    
    if (scanf("%d %d", &a, &b) == 2) {
        int result = min_operations(a, b);
        printf("%d\n", result);
    }
    
    return EXIT_SUCCESS;
}