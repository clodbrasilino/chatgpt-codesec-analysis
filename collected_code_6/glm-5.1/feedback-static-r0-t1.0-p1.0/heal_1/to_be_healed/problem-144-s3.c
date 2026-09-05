#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

long long sum_of_absolute_differences(int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }

    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            /* Possible weaknesses found:
             *  use of undeclared identifier 'INT_MAX'
             *  'INT_MAX' undeclared (first use in this function)
             *  each undeclared identifier is reported only once for each function it appears in
             */
            if ((arr[i] > 0 && arr[j] < 0 && arr[i] > INT_MAX + arr[j]) ||
                /* Possible weaknesses found:
                 *  use of undeclared identifier 'INT_MAX'
                 */
                (arr[i] < 0 && arr[j] > 0 && arr[j] > INT_MAX + arr[i])) {
                continue;
            }
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    long long suffix_sum = 0;
    for (size_t i = 0; i < size; i++) {
        suffix_sum += arr[i];
    }

    long long total = 0;
    long long current_suffix_sum = suffix_sum;
    for (size_t i = 0; i < size; i++) {
        current_suffix_sum -= arr[i];
        total += ((long long)size - 1 - i) * arr[i] - current_suffix_sum;
    }

    return total;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    long long result = sum_of_absolute_differences(arr, size);

    printf("%lld\n", result);

    return 0;
}