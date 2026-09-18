#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_valid_triangle(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return false;
    }
    
    if (a > b) {
        if (c > a) {
            if (a > INT_MAX - b) return false;
        } else {
            if (c > INT_MAX - b) return false;
        }
    } else {
        if (c > b) {
            if (b > INT_MAX - a) return false;
        } else {
            if (c > INT_MAX - a) return false;
        }
    }
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 388697201 + 1943202929 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:18343,execs:9282,op:havoc,rep:3)
     */
    if (a > b + c || b > a + c || c > a + b) {
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