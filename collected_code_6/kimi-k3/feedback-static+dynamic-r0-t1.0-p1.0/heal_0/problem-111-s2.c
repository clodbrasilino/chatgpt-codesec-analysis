#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} IntList;

typedef struct {
    IntList *lists;
    size_t count;
    size_t capacity;
} NestedList;

int init_list(IntList *list, size_t capacity) {
    if (list == NULL || capacity == 0) {
        return -1;
    }
    list->data = malloc(capacity * sizeof(int));
    if (list->data == NULL) {
        return -1;
    }
    list->size = 0;
    list->capacity = capacity;
    return 0;
}

int init_nested_list(NestedList *nested, size_t capacity) {
    if (nested == NULL || capacity == 0) {
        return -1;
    }
    nested->lists = malloc(capacity * sizeof(IntList));
    if (nested->lists == NULL) {
        return -1;
    }
    nested->count = 0;
    nested->capacity = capacity;
    return 0;
}

int add_element(IntList *list, int value) {
    if (list == NULL) {
        return -1;
    }
    if (list->size >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        int *new_data = realloc(list->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            return -1;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->size] = value;
    list->size++;
    return 0;
}

int add_list(NestedList *nested, const IntList *list) {
    if (nested == NULL || list == NULL) {
        return -1;
    }
    if (nested->count >= nested->capacity) {
        size_t new_capacity = nested->capacity * 2;
        IntList *new_lists = realloc(nested->lists, new_capacity * sizeof(IntList));
        if (new_lists == NULL) {
            return -1;
        }
        nested->lists = new_lists;
        nested->capacity = new_capacity;
    }
    nested->lists[nested->count] = *list;
    nested->count++;
    return 0;
}

int contains(const IntList *list, int value) {
    if (list == NULL || list->data == NULL) {
        return 0;
    }
    for (size_t i = 0; i < list->size; i++) {
        if (list->data[i] == value) {
            return 1;
        }
    }
    return 0;
}

int find_common_elements(const NestedList *nested, IntList *result) {
    if (nested == NULL || result == NULL || nested->count == 0) {
        return -1;
    }
    
    result->size = 0;
    
    for (size_t i = 0; i < nested->lists[0].size; i++) {
        int candidate = nested->lists[0].data[i];
        int is_common = 1;
        
        if (contains(result, candidate)) {
            continue;
        }
        
        for (size_t j = 1; j < nested->count; j++) {
            if (!contains(&nested->lists[j], candidate)) {
                is_common = 0;
                break;
            }
        }
        
        if (is_common) {
            if (add_element(result, candidate) != 0) {
                return -1;
            }
        }
    }
    
    return 0;
}

void free_list(IntList *list) {
    if (list != NULL && list->data != NULL) {
        free(list->data);
        list->data = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}

void free_nested_list(NestedList *nested) {
    if (nested != NULL && nested->lists != NULL) {
        for (size_t i = 0; i < nested->count; i++) {
            free_list(&nested->lists[i]);
        }
        free(nested->lists);
        nested->lists = NULL;
        nested->count = 0;
        nested->capacity = 0;
    }
}

int main(void) {
    NestedList nested;
    IntList list1, list2, list3, result;
    
    if (init_nested_list(&nested, 4) != 0) {
        fprintf(stderr, "Failed to initialize nested list\n");
        return EXIT_FAILURE;
    }
    
    if (init_list(&list1, 4) != 0) {
        fprintf(stderr, "Failed to initialize list1\n");
        free_nested_list(&nested);
        return EXIT_FAILURE;
    }
    
    if (init_list(&list2, 4) != 0) {
        fprintf(stderr, "Failed to initialize list2\n");
        free_list(&list1);
        free_nested_list(&nested);
        return EXIT_FAILURE;
    }
    
    if (init_list(&list3, 4) != 0) {
        fprintf(stderr, "Failed to initialize list3\n");
        free_list(&list1);
        free_list(&list2);
        free_nested_list(&nested);
        return EXIT_FAILURE;
    }
    
    if (init_list(&result, 4) != 0) {
        fprintf(stderr, "Failed to initialize result\n");
        free_list(&list1);
        free_list(&list2);
        free_list(&list3);
        free_nested_list(&nested);
        return EXIT_FAILURE;
    }
    
    add_element(&list1, 1);
    add_element(&list1, 2);
    add_element(&list1, 3);
    add_element(&list1, 4);
    add_element(&list1, 5);
    
    add_element(&list2, 2);
    add_element(&list2, 3);
    add_element(&list2, 5);
    add_element(&list2, 7);
    
    add_element(&list3, 1);
    add_element(&list3, 3);
    add_element(&list3, 5);
    add_element(&list3, 8);
    
    add_list(&nested, &list1);
    add_list(&nested, &list2);
    add_list(&nested, &list3);
    
    if (find_common_elements(&nested, &result) != 0) {
        fprintf(stderr, "Failed to find common elements\n");
        free_nested_list(&nested);
        free_list(&result);
        return EXIT_FAILURE;
    }
    
    printf("Common elements: ");
    for (size_t i = 0; i < result.size; i++) {
        printf("%d ", result.data[i]);
    }
    printf("\n");
    
    free_nested_list(&nested);
    free_list(&result);
    
    return EXIT_SUCCESS;
}