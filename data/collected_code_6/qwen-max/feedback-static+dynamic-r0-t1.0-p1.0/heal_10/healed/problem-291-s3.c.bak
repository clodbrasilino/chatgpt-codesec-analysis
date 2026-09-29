#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

int64_t numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;
    int64_t same = 0, diff = k;
    for (int i = 2; i <= n; ++i) {
        int64_t temp = diff;
        int64_t new_diff = (k - 1) * (same + diff);
        if (k == 1 || (new_diff / (k - 1) != same + temp) || new_diff > INT64_MAX || new_diff < INT64_MIN) break;
        diff = new_diff;
        int64_t new_same = (k - 1) * temp;
        if (new_same > INT64_MAX || new_same < INT64_MIN) break;
        same = new_same;
    }
    int64_t result = same + diff;
    if (result > INT64_MAX || result < INT64_MIN) {
        return 0;
    }
    return result;
}

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) {
        printf("Invalid input\n");
        return 1;
    }
    printf("%" PRId64 "\n", numWays(n, k));
    return 0;
}