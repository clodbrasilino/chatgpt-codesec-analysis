#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define INITIAL_CAPACITY 64

int* generate_lucky_numbers(int n) {
    if (n <= 0) {
        return NULL;
    }

    size_t capacity = (size_t)n * 2;
    if (capacity < INITIAL_CAPACITY) {
        capacity = INITIAL_CAPACITY;
    }

    int* numbers = (int*)malloc(sizeof(int) * capacity);
    if (numbers == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < capacity; i++) {
        numbers[i] = (int)(i + 1);
    }

    size_t count = capacity;
    int step = 2;

    while (step > 0 && (size_t)step <= count) {
        size_t write_index = 0;
        for (size_t i = 0; i < count; i++) {
            if ((i + 1) % (size_t)step != 0) {
                numbers[write_index] = numbers[i];
                write_index++;
            }
        }
        count = write_index;

        if (count == 0) {
            break;
        }

        size_t next_step_index = (size_t)(step - 1);
        if (next_step_index >= count) {
            break;
        }

        int next_step = numbers[next_step_index];
        if (next_step <= step || next_step <= 0) {
            break;
        }

        step = next_step;
    }

    if (count == 0 || (size_t)n > count) {
        free(numbers);
        return NULL;
    }

    int* result = (int*)malloc(sizeof(int) * (size_t)n);
    if (result == NULL) {
        free(numbers);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
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
        printf("Not enough lucky numbers found or memory allocation failed\n");
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