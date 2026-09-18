#include<stdio.h>
#include<stdlib.h>

size_t getMaxSegments(size_t n, size_t a, size_t b, size_t c) {
    if (a == 0 || b == 0 || c == 0) {
        return 0;
    }

    size_t divisor = (n > a) ? a : (n > b) ? b : c;
    size_t remainder = n;

    while (remainder > 0) {
        if (remainder % divisor == 0) {
            return remainder / divisor;
        }
        remainder -= divisor;
        divisor = (remainder > a) ? a : (remainder > b) ? b : c;
    }

    return 0;
}

int main() {
    size_t n, a, b, c;
    printf("Enter total length: ");
    scanf("%zu", &n);
    printf("Enter segment length a: ");
    scanf("%zu", &a);
    printf("Enter segment length b: ");
    scanf("%zu", &b);
    printf("Enter segment length c: ");
    scanf("%zu", &c);

    size_t maxSegments = getMaxSegments(n, a, b, c);
    printf("Maximum number of segments: %zu\n", maxSegments);

    return 0;
}