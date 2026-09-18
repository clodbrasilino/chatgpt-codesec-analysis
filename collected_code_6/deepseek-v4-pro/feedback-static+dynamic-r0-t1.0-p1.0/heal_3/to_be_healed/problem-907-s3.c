#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 64

int* generate_lucky_numbers(int n) {
    if (n <= 0) {
        return NULL;
    }

    int capacity = n * 2;
    if (capacity < INITIAL_CAPACITY) {
        capacity = INITIAL_CAPACITY;
    }

    int* numbers = (int*)malloc(sizeof(int) * capacity);
    if (numbers == NULL) {
        return NULL;
    }

    for (int i = 0; i < capacity; i++) {
        numbers[i] = i + 1;
    }

    int count = capacity;
    int step = 2;

    while (step <= count) {
        int write_index = 0;
        for (int i = 0; i < count; i++) {
            if ((i + 1) % step != 0) {
                numbers[write_index] = numbers[i];
                write_index++;
            }
        }
        count = write_index;

        if (count == 0) {
            break;
        }

        if (step > count) {
            break;
        }

        int next_step_index = step - 1;
        if (next_step_index >= count) {
            break;
        }

        step = numbers[next_step_index];
        if (step > count) {
            break;
        }
    }

    int result_size = (n < count) ? n : count;
    if (result_size <= 0) {
        free(numbers);
        return NULL;
    }

    int* result = (int*)malloc(sizeof(int) * result_size);
    if (result == NULL) {
        free(numbers);
        return NULL;
    }

    for (int i = 0; i < result_size; i++) {
        result[i] = numbers[i];
    }

    free(numbers);
    return result;
}

void print_lucky_numbers(int n) {
    if (n <= 0) {
        printf("Invalid input: n must be positive\n");
        return;
    }

    int* lucky = generate_lucky_numbers(n);
    if (lucky == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    printf("First %d lucky numbers: ", n);
    for (int i = 0; i < n; i++) {
        printf("%d", lucky[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("\n");

    free(lucky);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:14985,execs:500,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int n;

    printf("Enter the number of lucky numbers to print: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (n <= 0) {
        printf("Invalid input: n must be positive\n");
        return 1;
    }

    print_lucky_numbers(n);

    return 0;
}