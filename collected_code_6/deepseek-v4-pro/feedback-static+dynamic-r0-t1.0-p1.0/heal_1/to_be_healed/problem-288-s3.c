#include <stdio.h>
#include <stddef.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int count_self_inverse_mod_p(int arr[], size_t n, int p) {
    int count = 0;
    for (size_t i = 0; i < n; i++) {
        int a = arr[i] % p;
        if (a < 0) a += p;
        if (a == 0) continue;
        if ((long long)a * a % p == 1) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 10, 11, 12};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int p = 13;
    int result = count_self_inverse_mod_p(arr, n, p);
    printf("%d\n", result);
    return 0;
}