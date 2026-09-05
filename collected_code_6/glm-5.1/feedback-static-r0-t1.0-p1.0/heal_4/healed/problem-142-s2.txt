#include <stdio.h>
#include <stdlib.h>

int count_same_triples(const int *a, const int *b, const int *c, size_t size_a, size_t size_b, size_t size_c) {
    int count = 0;
    for (size_t i = 0; i < size_a; i++) {
        for (size_t j = 0; j < size_b; j++) {
            if (a[i] == b[j]) {
                for (size_t k = 0; k < size_c; k++) {
                    if (a[i] == c[k]) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

int main(void) {
    const size_t size_a = 3;
    const size_t size_b = 3;
    const size_t size_c = 3;
    
    if (size_a == 0 || size_b == 0 || size_c == 0) {
        return EXIT_FAILURE;
    }

    const int a[] = {1, 2, 3};
    const int b[] = {1, 2, 4};
    const int c[] = {1, 5, 2};

    int result = count_same_triples(a, b, c, size_a, size_b, size_c);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}