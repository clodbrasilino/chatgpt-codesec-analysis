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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int n = atoi(argv[1]);
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
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