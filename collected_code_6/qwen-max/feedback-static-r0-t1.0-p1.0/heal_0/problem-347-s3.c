#include <stdio.h>

long long count_squares(long width, long height) {
    if (width < 0 || height < 0) return 0;
    long smaller = width < height ? width : height;
    long larger = width > height ? width : height;
    long long total = 0;
    for (long i = 1; i <= smaller; ++i)
        total += (larger - i + 1) * (smaller - i + 1);
    return total;
}

int main() {
    long width, height;
    scanf("%ld %ld", &width, &height);
    long long result = count_squares(width, height);
    printf("%lld\n", result);
    return 0;
}