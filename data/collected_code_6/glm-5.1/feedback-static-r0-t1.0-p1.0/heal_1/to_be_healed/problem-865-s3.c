#include <stdio.h>
#include <stdlib.h>

typedef void (*MapFunc)(int, void *);

int *map(const int *list, size_t size, MapFunc func, void *user_data) {
    if (list == NULL || func == NULL) {
        return NULL;
    }

    int *result = malloc(size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        result[i] = list[i];
        func(list[i], user_data);
    }

    return result;
}

typedef struct {
    int n;
} PrintData;

void print_n_times(int value, void *user_data) {
    /* Possible weaknesses found:
     *  Variable 'data' can be declared as pointer to const [constVariablePointer]
     */
    PrintData *data = (PrintData *)user_data;
    if (data == NULL || data->n <= 0) {
        return;
    }

    for (int i = 0; i < data->n; i++) {
        printf("%d ", value);
    }
}

int main(void) {
    int list[] = {1, 2, 3};
    size_t size = sizeof(list) / sizeof(list[0]);
    PrintData data = {3};

    int *result = map(list, size, print_n_times, &data);
    
    if (result != NULL) {
        printf("\n");
        free(result);
    } else {
        fprintf(stderr, "Allocation failed\n");
        return 1;
    }

    return 0;
}