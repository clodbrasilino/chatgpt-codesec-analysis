#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'numbers' can be declared as pointer to const [constParameterPointer]
 */
int sum_between_indices(int *numbers, int start_index, int end_index) {
    if (start_index < 0 || end_index >= 0 && end_index < start_index) {
        return -1;
    }

    int sum = 0;
    for (int i = start_index; i <= end_index; ++i) {
        /* Possible weaknesses found:
         * ASan: stack-overflow (AFL crash: id:000001,sig:11,src:000009,time:14823,execs:4565,op:havoc,rep:6)
         */
        sum += numbers[i];
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:36,execs:26,op:havoc,rep:12; likely memory-safety defect
  */

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    /* Possible weaknesses found:
     *  Variable 'n' is assigned a value that is never used. [unreadVariable]
     */
    int n = sizeof(numbers) / sizeof(numbers[0]);

    int start_index, end_index;
    printf("Enter the start index: ");
    scanf("%d", &start_index);
    printf("Enter the end index: ");
    scanf("%d", &end_index);

    int result = sum_between_indices(numbers, start_index, end_index);
    if (result == -1) {
        printf("Invalid indices.\n");
    } else {
        printf("Sum between indices %d and %d is: %d\n", start_index, end_index, result);
    }

    return 0;
}