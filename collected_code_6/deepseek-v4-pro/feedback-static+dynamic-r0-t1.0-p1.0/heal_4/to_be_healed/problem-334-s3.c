#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_valid_triangle(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return false;
    }
    
    if (a > INT_MAX - b || a > INT_MAX - c ||
        b > INT_MAX - a || b > INT_MAX - c ||
        c > INT_MAX - a || c > INT_MAX - b) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1848304525 + 1848304525 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000006,time:26599,execs:16316,op:havoc,rep:2)
         * UBSan: signed integer overflow: 1858374526 + 757385741 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000006,time:20396,execs:12193,op:havoc,rep:4)
         */
        if (a + b > c && b + c > a && a + c > b) {
            return true;
        }
        return false;
    }
    
    if (a + b <= c || b + c <= a || a + c <= b) {
        return false;
    }
    
    return true;
}

int main(void) {
    int a, b, c;
    
    printf("Enter three sides of a triangle: ");
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (is_valid_triangle(a, b, c)) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }
    
    return 0;
}