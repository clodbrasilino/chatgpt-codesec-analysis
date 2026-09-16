#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected [9, 13, 17, 15, 16], got <no output>
  *  test case 0 failed: expected [2, 4, 7, 8, 9, 11, 13], got <no output>
  *  test case 2 failed: expected [3, 5, 7, 9, 11, 13, 15, 17, 19], got <no output>
  */

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int add_consecutive(int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return 0;
    }

    int sum = 0;
    for (int i = 0; i < size - 1; i++) {
        if (arr[i + 1] == arr[i] + 1) {
            sum += arr[i] + arr[i + 1];
        }
    }
    return sum;
}

int main(void) {
    int numbers[] = {1, 2, 3, 5, 6, 8, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    int result = add_consecutive(numbers, size);
    printf("Sum of consecutive pairs: %d\n", result);
    
    return 0;
}