#include <stdio.h>
#include <stdlib.h>

int* find_multiples(int n, int m, int* err) {
    if (n == 0 || m <= 0) {
        *err = 1;
        return NULL;
    }
    
    int* multiples = malloc(m * sizeof(int));
    if (multiples == NULL) {
        *err = 2;
        return NULL;
    }
    
    *err = 0;
    for (int i = 1; i <= m; i++) {
        multiples[i - 1] = n * i;
    }
    
    return multiples;
}

int main(int argc, char const * const * argv) {
    if (argc != 3) {
        return 1;
    }
    
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int err = 0;
    
    int* res = find_multiples(n, m, &err);
    
    if (err != 0) {
        return 1;
    }
    
    for (int i = 0; i < m; i++) {
        printf("%d\n", res[i]);
    }
    
    free(res);
    
    return 0;
}