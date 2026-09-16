#include <stdio.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int count_positive(int arr[], int size) {
    int count = 0;
    int i;
    for (i = 0; i < size; i++) {
        if (arr[i] > 0) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int numbers[] = {1, -2, 3, 0, -5, 7};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int result = count_positive(numbers, size);
    printf("%d\n", result);
    return 0;
}