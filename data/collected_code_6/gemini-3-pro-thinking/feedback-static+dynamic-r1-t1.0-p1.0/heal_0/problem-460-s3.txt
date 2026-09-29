#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} SubList;

typedef struct {
    SubList *sublists;
    size_t count;
} ListOfSubLists;

typedef struct {
    int *data;
    size_t size;
} ResultList;

int get_first_elements(const ListOfSubLists *input, ResultList *output) {
    size_t valid_count = 0;
    size_t index = 0;

    if (!input || !output) {
        return -1;
    }

    output->data = NULL;
    output->size = 0;

    if (input->count == 0 || !input->sublists) {
        return 0;
    }

    for (size_t i = 0; i < input->count; ++i) {
        if (input->sublists[i].data != NULL && input->sublists[i].size > 0) {
            valid_count++;
        }
    }

    if (valid_count == 0) {
        return 0;
    }

    output->data = (int *)malloc(valid_count * sizeof(int));
    if (!output->data) {
        return -1;
    }

    output->size = valid_count;

    for (size_t i = 0; i < input->count; ++i) {
        if (input->sublists[i].data != NULL && input->sublists[i].size > 0) {
            output->data[index++] = input->sublists[i].data[0];
        }
    }

    return 0;
}

int main(void) {
    int arr1[] = {10, 20, 30};
    int arr2[] = {40, 50};
    int arr3[] = {70};

    SubList sublists[4];
    
    sublists[0].data = arr1;
    sublists[0].size = sizeof(arr1) / sizeof(arr1[0]);
    
    sublists[1].data = NULL; 
    sublists[1].size = 0;
    
    sublists[2].data = arr2;
    sublists[2].size = sizeof(arr2) / sizeof(arr2[0]);
    
    sublists[3].data = arr3;
    sublists[3].size = sizeof(arr3) / sizeof(arr3[0]);

    ListOfSubLists input;
    input.sublists = sublists;
    input.count = sizeof(sublists) / sizeof(sublists[0]);

    ResultList result = {NULL, 0};

    if (get_first_elements(&input, &result) == 0) {
        for (size_t i = 0; i < result.size; ++i) {
            printf("%d\n", result.data[i]);
        }
        
        free(result.data);
        result.data = NULL;
        result.size = 0;
    } else {
        fprintf(stderr, "Error processing sublists\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}