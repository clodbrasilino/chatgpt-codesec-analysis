#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool check_root_is_twice(long long a, long long b, long long c);

bool check_root_is_twice(long long a, long long b, long long c) {
    if (a == 0) {
        return false;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:571,execs:313,op:havoc,rep:1)
     * UBSan: signed integer overflow: -2 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:300,execs:174,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9223372036854775799 * 3 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:571,execs:313,op:havoc,rep:1)
     * UBSan: signed integer overflow: 9 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000002,time:2569,execs:1363,op:havoc,rep:4)
     * UBSan: signed integer overflow: 6666666666666 * 3333333333333 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:2183,execs:1167,op:havoc,rep:1)
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:300,execs:174,op:havoc,rep:1)
     */
    return (2 * b * b) == (9 * a * c);
}

int main(void) {
    long long a = 0;
    long long b = 0;
    long long c = 0;

    if (scanf("%lld %lld %lld", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input format.\n");
        return EXIT_FAILURE;
    }

    if (check_root_is_twice(a, b, c)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return EXIT_SUCCESS;
}