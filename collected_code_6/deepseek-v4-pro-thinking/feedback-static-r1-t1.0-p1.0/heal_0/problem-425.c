#include <stdio.h>

long long count_sublists_containing(const int *arr, int len, int element) {
    if (arr == NULL || len <= 0) {
        return 0;
    }

    long long count = 0;
    int prev = -1;

    for (int i = 0; i < len; ++i) {
        if (arr[i] == element) {
            count += (long long)(i - prev) * (len - i);
            prev = i;
        }
    }

    return count;
}

int main(void) {
    int arr[] = {1, 2, 3, 2};
    int len = (int)(sizeof(arr) / sizeof(arr[0]));
    int element = 2;

    printf("%lld\n", count_sublists_containing(arr, len, element));

    return 0;
}