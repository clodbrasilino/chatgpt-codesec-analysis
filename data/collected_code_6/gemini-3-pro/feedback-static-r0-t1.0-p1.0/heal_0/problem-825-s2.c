#include <stdio.h>
#include <stdlib.h>

int* get_elements(const int* list, size_t list_size, const size_t* indices, size_t num_indices) {
    if (list == NULL || indices == NULL || num_indices == 0) {
        return NULL;
    }

    int* result = malloc(num_indices * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < num_indices; ++i) {
        if (indices[i] >= list_size) {
            free(result);
            return NULL; 
        }
        result[i] = list[indices[i]];
    }

    return result;
}

int main(void) {
    int my_list[] = {10, 20, 30, 40, 50, 60, 70, 80};
    size_t list_size = sizeof(my_list) / sizeof(my_list[0]);
    
    size_t my_indices[] = {1, 3, 5, 7};
    size_t num_indices = sizeof(my_indices) / sizeof(my_indices[0]);

    int* selected_elements = get_elements(my_list, list_size, my_indices, num_indices);

    if (selected_elements != NULL) {
        for (size_t i = 0; i < num_indices; ++i) {
            printf("%d ", selected_elements[i]);
        }
        printf("\n");
        free(selected_elements);
    } else {
        fprintf(stderr, "Failed to get elements.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}