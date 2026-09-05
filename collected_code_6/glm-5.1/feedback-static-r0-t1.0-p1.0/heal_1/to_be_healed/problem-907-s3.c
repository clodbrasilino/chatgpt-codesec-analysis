#include <stdio.h>
#include <stdlib.h>

void print_lucky_numbers(int n) {
    if (n <= 0) {
        return;
    }

    int max_size = 10;
    if (n > 10) {
        max_size = n * 15;
    }
    
    int *lucky = (int *)malloc(max_size * sizeof(int));
    if (lucky == NULL) {
        return;
    }

    for (int i = 0; i < max_size; i++) {
        lucky[i] = (i * 2) + 1;
    }

    int current_step = 1;
    int size = max_size;

    while (current_step < size && current_step < n) {
        int step_val = lucky[current_step];
        if (step_val <= 0) {
            break; 
        }
        
        int new_size = 0;
        for (int i = 0; i < size; i++) {
            if ((i + 1) % step_val != 0) {
                lucky[new_size] = lucky[i];
                new_size++;
            }
        }
        size = new_size;
        current_step++;
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", lucky[i]);
    }
    printf("\n");

    free(lucky);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("n must be a positive integer.\n");
        return 1;
    }

    print_lucky_numbers(n);
    return 0;
}