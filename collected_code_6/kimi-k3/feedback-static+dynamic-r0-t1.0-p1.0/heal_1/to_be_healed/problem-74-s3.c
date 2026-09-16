#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'patterns' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int check_sequence(int *arr, int arr_size, int *patterns, int patterns_size) {
    int i;
    int j;
    /* Possible weaknesses found:
     *  Unused variable: k [unusedVariable]
     */
    int k;
    /* Possible weaknesses found:
     *  The scope of the variable 'match' can be reduced. [variableScope]
     */
    int match;
    int count = 0;

    if (arr == NULL || patterns == NULL || arr_size <= 0 || patterns_size <= 0) {
        return 0;
    }

    if (patterns_size > arr_size) {
        return 0;
    }

    for (i = 0; i <= arr_size - patterns_size; i++) {
        match = 1;
        for (j = 0; j < patterns_size; j++) {
            if (arr[i + j] != patterns[j]) {
                match = 0;
                break;
            }
        }
        if (match == 1) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int arr[] = {1, 2, 3, 1, 2, 3, 1, 2};
    int patterns[] = {1, 2, 3};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    int patterns_size = sizeof(patterns) / sizeof(patterns[0]);
    int result;

    result = check_sequence(arr, arr_size, patterns, patterns_size);

    if (result > 0) {
        printf("Pattern found %d time(s)\n", result);
    } else {
        printf("Pattern not found\n");
    }

    return 0;
}