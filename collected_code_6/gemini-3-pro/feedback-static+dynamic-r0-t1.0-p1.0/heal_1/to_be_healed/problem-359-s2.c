#include <stdio.h>
#include <stdbool.h>

bool isOneRootTwiceTheOther(int a, int b, int c) {
    if (a == 0) {
        return false;
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -598358244 * 1848304526 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000002,time:2327,execs:1251,op:havoc,rep:1)
     * UBSan: signed integer overflow: 1842981546 * 921490773 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000001,time:7632,execs:4156,op:havoc,rep:1)
     * UBSan: signed integer overflow: 2 * 1848304526 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000002,time:2327,execs:1251,op:havoc,rep:1)
     */
    int expected_c = (2 * b * b);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1215752191 * 3 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:549,execs:303,op:havoc,rep:1)
     * UBSan: signed integer overflow: 99999999 * 22 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:1993,execs:1079,op:havoc,rep:3)
     * UBSan: signed integer overflow: 9 * -1773790777 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:549,execs:303,op:havoc,rep:1)
     */
    int actual_c = (9 * a * c);
    
    return expected_c == actual_c;
}

int main(void) {
    int a = 0;
    int b = 0;
    int c = 0;
    
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (isOneRootTwiceTheOther(a, b, c)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return 0;
}