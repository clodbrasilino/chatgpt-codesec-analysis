#include <stdio.h>

int find_median(int a, int b, int c);

int find_median(int a, int b, int c) {
    if ((a >= b && a <= c) || (a >= c && a <= b)) {
        return a;
    }
    if ((b >= a && b <= c) || (b >= c && b <= a)) {
        return b;
    }
    return c;
}

int main(void) {
    int val1 = 15;
    int val2 = 10;
    int val3 = 20;

    int median = find_median(val1, val2, val3);
    
    printf("%d\n", median);

    return 0;
}