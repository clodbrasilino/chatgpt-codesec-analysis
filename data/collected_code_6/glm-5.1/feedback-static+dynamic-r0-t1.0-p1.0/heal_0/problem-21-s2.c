#include <stdio.h>
#include <stdlib.h>

int *find_multiples(int n, int m) {
    if (n == 0 || m <= 0) {
        return NULL;
    }

    int *multiples = (int *)malloc(m * sizeof(int));
    if (multiples == NULL) {
        return NULL;
    }

    for (int i = 0; i < m; i++) {
        multiples[i] = n * (i + 1);
    }

    return multiples;
}

int main(void) {
    int n = 3;
    int m = 5;
    
    int *result = find_multiples(n, m);
    
    if (result == NULL) {
        fprintf(stderr, "Invalid input or memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < m; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    result = NULL;
    
    return 0;
}