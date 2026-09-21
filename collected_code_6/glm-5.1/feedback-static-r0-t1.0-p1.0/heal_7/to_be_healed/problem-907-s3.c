#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

void print_lucky_numbers(int n) {
    if (n <= 0) {
        return;
    }

    int max_size = n * 15;
    if (max_size < 10) {
        max_size = 10;
    }
    
    int *lucky = malloc(max_size * sizeof(int));
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
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || val <= 0 || val > INT_MAX) {
        printf("n must be a positive integer.\n");
        return 1;
    }

    int n = (int)val;
    print_lucky_numbers(n);
    return 0;
}