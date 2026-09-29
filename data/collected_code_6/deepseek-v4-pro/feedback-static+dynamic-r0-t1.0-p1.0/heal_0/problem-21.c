#include <stdio.h>
#include <stdlib.h>

int* find_multiples(int n, int m, int* count) {
    if (n <= 0 || m < 0) {
        *count = 0;
        return NULL;
    }
    
    if (m == 0) {
        *count = 0;
        return NULL;
    }
    
    int* multiples = (int*)malloc(m * sizeof(int));
    if (multiples == NULL) {
        *count = 0;
        return NULL;
    }
    
    for (int i = 0; i < m; i++) {
        multiples[i] = n * (i + 1);
    }
    
    *count = m;
    return multiples;
}

int main(void) {
    int n = 5;
    int m = 3;
    int count = 0;
    
    int* result = find_multiples(n, m, &count);
    if (result == NULL) {
        printf("Error: Unable to generate multiples or invalid input\n");
        return 1;
    }
    
    printf("First %d multiples of %d: ", count, n);
    for (int i = 0; i < count; i++) {
        printf("%d", result[i]);
        if (i < count - 1) {
            printf(", ");
        }
    }
    printf("\n");
    
    free(result);
    return 0;
}