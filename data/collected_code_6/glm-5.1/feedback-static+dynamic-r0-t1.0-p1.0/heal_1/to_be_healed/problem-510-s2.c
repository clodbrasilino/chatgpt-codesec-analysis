#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
unsigned long long count_subsequences(int *arr, int n, unsigned long long k) {
    unsigned long long count = 0;
    unsigned long long product = 1;
    int left = 0;

    for (int right = 0; right < n; right++) {
        product *= arr[right];

        while (left <= right && product >= k) {
            product /= arr[left];
            left++;
        }

        if (left <= right) {
            count += (right - left + 1);
        }
    }

    return count;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000018,time:50523,execs:31365,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int n;
    unsigned long long k;

    if (scanf("%d", &n) != 1) {
        return 1;
    }

    if (n < 0) {
        return 1;
    }

    if (scanf("%llu", &k) != 1) {
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return 1;
        }
        if (arr[i] < 0) {
            free(arr);
            return 1;
        }
    }

    unsigned long long result = count_subsequences(arr, n, k);
    printf("%llu\n", result);

    free(arr);
    return 0;
}