#include <stdio.h>
#include <stdlib.h>

long long perrin(int n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;
    return perrin(n - 2) + perrin(n - 3);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000001,time:7276,execs:138,op:havoc,rep:3; likely memory-safety defect
  */

int main(void) {
    int n;
    char buffer[256];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (sscanf(buffer, "%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    if (n < 0) {
        return EXIT_FAILURE;
    }

    printf("%lld\n", perrin(n));
    return EXIT_SUCCESS;
}