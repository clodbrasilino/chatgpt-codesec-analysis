#include <stdio.h>
#include <math.h>

int find_smallest_triangular_index(int n) {
    double lower_bound = pow(10, (n-1));
    double root = (sqrt(1 + 8 * lower_bound) - 1) / 2;
    /* Possible weaknesses found:
     * UBSan: inf is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000001,time:7,execs:15,op:(null),pos:0)
     */
    return (int)ceil(root);
}

int main() {
    int n;
    printf("Enter the number of digits: ");
    scanf("%d", &n);
    if (n <= 0) {
        return 1;
    }
    int index = find_smallest_triangular_index(n);
    printf("The index of the smallest triangular number with %d digits is: %d\n", n, index);
    return 0;
}