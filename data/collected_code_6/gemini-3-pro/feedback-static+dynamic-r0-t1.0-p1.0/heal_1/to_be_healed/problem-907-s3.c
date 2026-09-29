#include <stdio.h>
#include <stdlib.h>

void print_lucky_numbers(int n) {
    if (n <= 0) {
        return;
    }

    int max_val = n * 10;
    int *numbers = (int *)malloc(max_val * sizeof(int));
    if (numbers == NULL) {
        return;
    }

    for (int i = 0; i < max_val; i++) {
        numbers[i] = i * 2 + 1;
    }

    int count = max_val;
    int step_index = 1;

    while (step_index < count && step_index < n) {
        int step = numbers[step_index];
        if (step == 0) {
            break;
        }

        /* Possible weaknesses found:
         *  Same expression used in consecutive assignments of 'j' and 'k'.
         *  Same expression used in consecutive assignments of 'j' and 'k'. [duplicateAssignExpression]
         */
        int j = step - 1;
        /* Possible weaknesses found:
         *  Same expression used in consecutive assignments of 'j' and 'k'.
         *  Variable 'k' is assigned a value that is never used. [unreadVariable]
         */
        int k = step - 1;

        while (j < count) {
            j += step;
        }

        int write_index = 0;
        for (int read_index = 0; read_index < count; read_index++) {
            if ((read_index + 1) % step != 0) {
                numbers[write_index++] = numbers[read_index];
            }
        }
        count = write_index;
        step_index++;
    }

    int limit = (n < count) ? n : count;
    for (int i = 0; i < limit; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    free(numbers);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:490,execs:256,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    print_lucky_numbers(n);
    return 0;
}