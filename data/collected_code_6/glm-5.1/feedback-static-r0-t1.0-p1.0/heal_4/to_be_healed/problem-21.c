#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char* const argv[const]) {
    if (argc != 3) {
        return 1;
    }
    
    char* endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return 1;
    }
    int n = (int)val;

    errno = 0;
    val = strtol(argv[2], &endptr, 10);
    if (errno != 0 || endptr == argv[2] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return 1;
    }
    int m = (int)val;
    
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