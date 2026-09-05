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

/* Possible weaknesses found:
 *  Parameter 'user_data' can be declared as pointer to const
 *  Parameter 'user_data' can be declared as pointer to const. However it seems that 'print_n_times' is a callback function, if 'user_data' is declared with const you might also need to cast function pointer(s). [constParameterCallback]
 */
void print_n_times(int value, void *user_data) {
    const PrintData *data = (const PrintData *)user_data;
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

    /* Possible weaknesses found:
     *  You might need to cast the function pointer here
     */
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