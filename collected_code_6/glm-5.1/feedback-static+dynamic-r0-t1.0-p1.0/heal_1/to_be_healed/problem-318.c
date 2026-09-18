#include <stdio.h>

long long find_max_cuboid_volume(long long s) {
    if (s <= 0) {
        return -1;
    }
    if (s % 3 == 0) {
        long long side = s / 3;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 8779149715665296016 * 2962962996 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:595,execs:378,op:havoc,rep:4)
         * UBSan: signed integer overflow: 3440151943267179072 * 296296296296 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:1252,execs:796,op:havoc,rep:3)
         * UBSan: signed integer overflow: 296296296296 * 296296296296 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000001,time:1252,execs:796,op:havoc,rep:3)
         */
        return side * side * side;
    }
    if (s % 3 == 1) {
        long long side1 = (s - 4) / 3;
        long long side2 = side1 + 1;
        if (side1 < 1) {
            return -1;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -2049638230412172399 * 3074457345618258602 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:818,execs:519,op:havoc,rep:6)
         * UBSan: signed integer overflow: 3074457345618258601 * 3074457345618258601 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:818,execs:519,op:havoc,rep:6)
         * UBSan: signed integer overflow: 6721528093281 * 2592592 cannot be represented in type 'long long' (AFL crash: id:000005,sig:06,src:000001,time:1710,execs:1083,op:havoc,rep:3)
         */
        return side1 * side1 * side2;
    }
    if (s % 3 == 2) {
        long long side = (s - 2) / 3;
        if (side < 1) {
            return -1;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2962962962962962962 * 2962962962962962962 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:628,execs:399,op:havoc,rep:4)
         * UBSan: signed integer overflow: 8779143813444 * 2962963 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000001,time:1373,execs:870,op:havoc,rep:8)
         * UBSan: signed integer overflow: -8935642192445265596 * 2962962962962962963 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:628,execs:399,op:havoc,rep:4)
         */
        return side * side * (side + 1);
    }
    return -1;
}

int main(void) {
    long long s;
    if (scanf("%lld", &s) != 1) {
        return 1;
    }
    long long volume = find_max_cuboid_volume(s);
    printf("%lld\n", volume);
    return 0;
}