#include <stdio.h>
#include <stdlib.h>

void print_lucky_numbers(int n) {
    if (n <= 0) {
        return;
    }

    int *numbers = NULL;
    int count = n * 10;
    if (count < 100) {
        count = 100;
    }

    numbers = (int *)malloc(count * sizeof(int));
    if (numbers == NULL) {
        return;
    }

    for (int i = 0; i < count; i++) {
        numbers[i] = i + 1;
    }

    int step = 2;
    int remaining = count;

    /* Possible weaknesses found:
     *  Assuming that condition 'step>=2' is not redundant
     */
    while (step <= remaining && step >= 2) {
        int new_index = 0;
        for (int i = 0; i < remaining; i++) {
            if ((i + 1) % step != 0) {
                numbers[new_index++] = numbers[i];
            }
        }
        remaining = new_index;

        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (remaining == 0) {
            break;
        }

        /* Possible weaknesses found:
         *  Assignment 'next_step_index=step-1', assigned value is greater than 0
         */
        int next_step_index = step - 1;
        /* Possible weaknesses found:
         *  Condition 'next_step_index<0' is always false
         *  Condition 'next_step_index<0' is always false [knownConditionTrueFalse]
         */
        if (next_step_index < 0 || next_step_index >= remaining) {
            break;
        }
        
        int next_step = numbers[next_step_index];
        if (next_step < 2 || next_step > remaining) {
            break;
        }
        step = next_step;
    }

    if (n > remaining) {
        n = remaining;
    }

    if (n > 0 && remaining > 0) {
        for (int i = 0; i < n; i++) {
            printf("%d", numbers[i]);
            if (i < n - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }

    free(numbers);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:38647,execs:709,op:havoc,rep:5; likely memory-safety defect
  */

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input\n");
        return 1;
    }

    print_lucky_numbers(n);

    return 0;
}