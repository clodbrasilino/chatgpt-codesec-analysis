#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t countTriangles(int n) {
    if (n <= 0) {
        return 0;
    }

    int64_t up = 0;
    for (int i = 1; i <= n; i++) {
        up += (int64_t)i * (i + 1) / 2;
    }

    int64_t down = 0;
    for (int i = n - 1; i > 0; i -= 2) {
        down += (int64_t)i * (i + 1) / 2;
    }

    int64_t both = 0;
    if (n >= 4) {
        for (int i = n - 3; i > 0; i -= 2) {
            both += (int64_t)i * (i + 1) / 2;
        }
        both = both * 2;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9093413570623717336 + 6062262906049940590 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000013,time:27679,execs:14549,op:havoc,rep:2)
     * UBSan: signed integer overflow: 6172843209876728395 + 3086420216048919753 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000003,time:1488,execs:786,op:havoc,rep:8)
     */
    return up + down + both;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:229,execs:143,op:havoc,rep:6; likely memory-safety defect
  */

int main(void) {
    int n;

    printf("Enter side length: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Side length must be non-negative\n");
        return EXIT_FAILURE;
    }

    printf("Maximum equilateral triangles: %" PRId64 "\n", countTriangles(n));

    return EXIT_SUCCESS;
}