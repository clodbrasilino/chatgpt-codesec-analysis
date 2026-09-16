#include <stdio.h>
#include <stdlib.h>

typedef void (*print_func)(int);

void print_number(int n) {
    printf("%d ", n);
}

void print_n_times(int *list, int size, int n, print_func func) {
    if (list == NULL || func == NULL || size <= 0 || n <= 0) {
        return;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < size; j++) {
            func(list[j]);
        }
        printf("\n");
    }
}

void map_print(int *list, int size, int n, print_func func) {
    print_n_times(list, size, n, func);
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5};
    int size = sizeof(list) / sizeof(list[0]);
    int n = 3;
    
    map_print(list, size, n, print_number);
    
    return 0;
}