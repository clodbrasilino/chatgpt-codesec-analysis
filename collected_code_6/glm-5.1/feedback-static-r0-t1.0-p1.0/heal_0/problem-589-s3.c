#include <stdio.h>
#include <math.h>

void find_perfect_squares(long long start, long long end) {
    if (start > end) {
        long long temp = start;
        start = end;
        end = temp;
    }
    
    if (start < 0) {
        start = 0;
    }

    long long root = (long long)ceil(sqrt((double)start));
    long long square = root * root;

    while (square <= end) {
        printf("%lld\n", square);
        root++;
        square = root * root;
    }
}

int main() {
    long long a, b;
    if (scanf("%lld %lld", &a, &b) != 2) {
        return 1;
    }

    find_perfect_squares(a, b);
    return 0;
}