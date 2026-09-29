#include <stdio.h>
#include <stdlib.h>

int* get_elements_at_indices(const int* list, size_t list_size, const size_t* indices, size_t indices_count, int* error_flag)
{
    if (list == NULL || indices == NULL || error_flag == NULL)
    {
        return NULL;
    }
    
    *error_flag = 0;
    
    if (indices_count == 0)
    {
        return NULL;
    }
    
    int* result = (int*)malloc(indices_count * sizeof(int));
    if (result == NULL)
    {
        *error_flag = 1;
        return NULL;
    }
    
    for (size_t i = 0; i < indices_count; i++)
    {
        if (indices[i] >= list_size)
        {
            free(result);
            *error_flag = 2;
            return NULL;
        }
        result[i] = list[indices[i]];
    }
    
    return result;
}

int main(void)
{
    int list[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    
    size_t indices[] = {0, 3, 5, 8};
    size_t indices_count = sizeof(indices) / sizeof(indices[0]);
    
    int error_flag = 0;
    int* result = get_elements_at_indices(list, list_size, indices, indices_count, &error_flag);
    
    if (error_flag == 1)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    else if (error_flag == 2)
    {
        fprintf(stderr, "Index out of bounds\n");
        return EXIT_FAILURE;
    }
    else if (result == NULL)
    {
        fprintf(stderr, "Invalid input parameters\n");
        return EXIT_FAILURE;
    }
    
    printf("Selected elements: ");
    for (size_t i = 0; i < indices_count; i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    free(result);
    
    return EXIT_SUCCESS;
}