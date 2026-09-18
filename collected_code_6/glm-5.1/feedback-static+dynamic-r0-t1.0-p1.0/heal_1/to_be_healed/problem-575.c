#include <stdio.h>
#include <stdlib.h>

int find_nth_non_multiple(int n, int k) {
    if (n <= 0 || k == 0) {
        exit(EXIT_FAILURE);
    }
    if (k == 1) {
        exit(EXIT_FAILURE);
    }
    int full_cycles = (n - 1) / (k - 1);
    int remainder = (n - 1) % (k - 1);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 862065094 * 3 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:5943,execs:3638,op:havoc,rep:1)
     */
    return full_cycles * k + remainder + 1;
}

int main(void) {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) {
        return EXIT_FAILURE;
    }
    int result = find_nth_non_multiple(n, k);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}