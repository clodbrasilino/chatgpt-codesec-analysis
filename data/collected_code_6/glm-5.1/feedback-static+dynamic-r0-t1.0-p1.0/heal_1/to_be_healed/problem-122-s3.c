#include <stdio.h>
#include <stdlib.h>

int find_nth_smart_number(int n) {
    if (n <= 0) {
        return -1;
    }

    int max_limit = n * 20;
    int *count = (int *)calloc(max_limit + 1, sizeof(int));
    if (count == NULL) {
        return -1;
    }

    for (int i = 2; i <= max_limit; i++) {
        if (count[i] == 0) {
            for (int j = i; j <= max_limit; j += i) {
                count[j]++;
            }
        }
    }

    int result = 0;
    int found = 0;
    for (int i = 2; i <= max_limit; i++) {
        if (count[i] >= 3) {
            found++;
            if (found == n) {
                result = i;
                break;
            }
        }
    }

    free(count);

    if (result == 0) {
        return -1;
    }

    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:6207,execs:748,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (n <= 0) {
        return 1;
    }

    int res = find_nth_smart_number(n);
    if (res == -1) {
        return 1;
    }

    printf("%d\n", res);

    return 0;
}