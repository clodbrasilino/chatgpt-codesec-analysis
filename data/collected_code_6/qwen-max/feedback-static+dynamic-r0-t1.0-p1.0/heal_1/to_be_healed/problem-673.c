#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int convert_to_single_integer(int *list, int n) {
    int result = 0;
    for (int i = 0; i < n; ++i) {
        result = result * 10 + list[i];
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 4};
    int len = sizeof(arr) / sizeof(arr[0]);
    int result = convert_to_single_integer(arr, len);
    printf("%d\n", result);
    return 0;
}