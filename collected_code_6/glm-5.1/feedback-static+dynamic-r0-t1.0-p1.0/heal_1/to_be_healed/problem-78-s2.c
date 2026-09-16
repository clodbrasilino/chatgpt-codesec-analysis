#include <stdio.h>
#include <stdlib.h>

int count_odd_set_bits(int n) {
    int count = 0;
    int i;
    for (i = 1; i <= n; ++i) {
        int val = i;
        int bits = 0;
        while (val) {
            val &= val - 1;
            bits++;
        }
        if (bits % 2 != 0) {
            count++;
        }
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }
    
    char *endptr;
    long ln = strtol(argv[1], &endptr, 10);
    
    if (*endptr != '\0' || ln < 1 || ln > 2147483647) {
        fprintf(stderr, "Invalid input. Please provide a positive integer.\n");
        return 1;
    }
    
    n = (int)ln;
    int result = count_odd_set_bits(n);
    printf("%d\n", result);
    
    return 0;
}