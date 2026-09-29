#include <stdio.h>
#include <stdlib.h>

void print_combination(const int* combination, int size) {
    printf("{ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", combination[i]);
    }
    printf("}\n");
}

void find_combinations(const int* list, int n, int r, int index, int* data, int i) {
    if (index == r) {
        print_combination(data, r);
        return;
    }

    if (i >= n) {
        return;
    }

    data[index] = list[i];
    find_combinations(list, n, r, index + 1, data, i + 1);
    find_combinations(list, n, r, index, data, i + 1);
}

void print_all_combinations(const int* list, int n) {
    int* data = (int*)malloc(n * sizeof(int));
    if (data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int r = 1; r <= n; r++) {
        find_combinations(list, n, r, 0, data, 0);
    }

    free(data);
}

int main(void) {
    int list[] = {1, 2, 3};
    int n = sizeof(list) / sizeof(list[0]);
    
    printf("{ }\n");
    print_all_combinations(list, n);

    return 0;
}