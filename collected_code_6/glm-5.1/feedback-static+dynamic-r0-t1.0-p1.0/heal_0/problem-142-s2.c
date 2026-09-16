#include <stdio.h>
#include <stdlib.h>

int count_same_triples(int *a, int *b, int *c, int size_a, int size_b, int size_c) {
    int count = 0;
    for (int i = 0; i < size_a; i++) {
        for (int j = 0; j < size_b; j++) {
            if (a[i] == b[j]) {
                for (int k = 0; k < size_c; k++) {
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
    int a[] = {1, 2, 3};
    int b[] = {1, 2, 4};
    int c[] = {1, 5, 2};

    int size_a = sizeof(a) / sizeof(a[0]);
    int size_b = sizeof(b) / sizeof(b[0]);
    int size_c = sizeof(c) / sizeof(c[0]);

    if (size_a == 0 || size_b == 0 || size_c == 0) {
        return EXIT_FAILURE;
    }

    int result = count_same_triples(a, b, c, size_a, size_b, size_c);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}