#include <stdio.h>
#include <stdlib.h>

int count_rectangles(int r) {
    if (r <= 0) {
        return 0;
    }

    int count = 0;
    long long limit = 4LL * r * r;

    for (long long w = 1; w <= 2LL * r; w++) {
        for (long long l = 1; l <= 2LL * r; l++) {
            if ((w * w) + (l * l) <= limit) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    int r = 2;
    int rectangles = count_rectangles(r);
    
    if (printf("%d\n", rectangles) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}