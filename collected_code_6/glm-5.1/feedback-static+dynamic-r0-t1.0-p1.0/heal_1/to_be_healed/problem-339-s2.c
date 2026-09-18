#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_max_occurring_divisor(int l, int r) {
    int span = r - l + 1;
    int *counts = (int *)calloc(span, sizeof(int));
    if (counts == NULL) {
        return -1;
    }

    for (int i = l; i <= r; i++) {
        if (i == 0) {
            continue;
        }
        int abs_i = i < 0 ? -i : i;
        for (int d = 1; d * d <= abs_i; d++) {
            if (abs_i % d == 0) {
                counts[d - l]++;
                if (d * d != abs_i) {
                    int other = abs_i / d;
                    if (other >= l && other <= r) {
                        counts[other - l]++;
                    }
                }
            }
        }
    }

    int max_count = 0;
    int result = l;

    for (int i = 0; i < span; i++) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            result = i + l;
        }
    }

    free(counts);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:679,execs:554,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int l = 0;
    int r = 0;

    if (scanf("%d %d", &l, &r) != 2) {
        return 1;
    }

    if (l > r) {
        return 1;
    }

    long long span = (long long)r - l + 1;
    if (span > 1000000) {
        return 1;
    }

    int res = find_max_occurring_divisor(l, r);
    printf("%d\n", res);

    return 0;
}