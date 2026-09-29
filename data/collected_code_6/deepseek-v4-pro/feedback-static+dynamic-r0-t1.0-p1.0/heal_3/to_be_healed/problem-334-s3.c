#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_valid_triangle(int a, int b, int c) {
    /* Possible weaknesses found:
     *  Assuming that condition 'a<=0' is not redundant
     *  Assuming that condition 'c<=0' is not redundant
     */
    if (a <= 0 || b <= 0 || c <= 0) {
        return false;
    }
    
    if (a > b) {
        int max = a;
        int sum_others = b + c;
        /* Possible weaknesses found:
         *  Condition 'c>0' is always true
         *  Condition 'c>0' is always true [knownConditionTrueFalse]
         */
        if (c > 0 && b > INT_MAX - c) return false;
        if (max > sum_others) return false;
    } else {
        int max = b;
        int sum_others = a + c;
        /* Possible weaknesses found:
         *  Condition 'c>0' is always true
         *  Condition 'c>0' is always true [knownConditionTrueFalse]
         */
        if (c > 0 && a > INT_MAX - c) return false;
        if (max > sum_others) return false;
    }
    
    if (c > a && c > b) {
        int sum_others = a + b;
        /* Possible weaknesses found:
         *  Condition 'a>0' is always true [knownConditionTrueFalse]
         *  Condition 'a>0' is always true
         */
        if (a > 0 && b > INT_MAX - a) return false;
        if (c > sum_others) return false;
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