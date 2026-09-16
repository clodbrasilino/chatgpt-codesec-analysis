#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TYPE_INT,
    TYPE_STRING
} ElementType;

typedef struct {
    ElementType type;
    union {
        int int_val;
        char *str_val;
    } data;
} Element;

static int compare_elements(const void *a, const void *b)
{
    const Element *elem_a = (const Element *)a;
    const Element *elem_b = (const Element *)b;
    
    if (elem_a->type != elem_b->type) {
        return (elem_a->type == TYPE_INT) ? -1 : 1;
    }
    
    if (elem_a->type == TYPE_INT) {
        if (elem_a->data.int_val < elem_b->data.int_val) {
            return -1;
        }
        if (elem_a->data.int_val > elem_b->data.int_val) {
            return 1;
        }
        return 0;
    }
    
    return strcmp(elem_a->data.str_val, elem_b->data.str_val);
}

static void free_element(Element *elem)
{
    if (elem != NULL && elem->type == TYPE_STRING && elem->data.str_val != NULL) {
        free(elem->data.str_val);
        elem->data.str_val = NULL;
    }
}

static int init_element_int(Element *elem, int value)
{
    if (elem == NULL) {
        return -1;
    }
    elem->type = TYPE_INT;
    elem->data.int_val = value;
    return 0;
}

static int init_element_string(Element *elem, const char *value)
{
    char *dup_str;
    
    if (elem == NULL || value == NULL) {
        return -1;
    }
    
    dup_str = malloc(strlen(value) + 1);
    if (dup_str == NULL) {
        return -1;
    }
    
    strcpy(dup_str, value);
    elem->type = TYPE_STRING;
    elem->data.str_val = dup_str;
    return 0;
}

static void print_element(const Element *elem)
{
    if (elem == NULL) {
        return;
    }
    
    if (elem->type == TYPE_INT) {
        printf("%d", elem->data.int_val);
    } else {
        printf("\"%s\"", elem->data.str_val);
    }
}

static void print_list(const Element *arr, size_t size)
{
    size_t i;
    
    printf("[");
    for (i = 0; i < size; i++) {
        print_element(&arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

static void free_list(Element *arr, size_t size)
{
    size_t i;
    
    if (arr == NULL) {
        return;
    }
    
    for (i = 0; i < size; i++) {
        free_element(&arr[i]);
    }
    free(arr);
}

static Element *create_mixed_list(size_t *size)
{
    Element *arr;
    size_t count = 7;
    size_t i;
    int init_success;
    
    arr = calloc(count, sizeof(Element));
    if (arr == NULL) {
        return NULL;
    }
    
    init_success = 1;
    init_success &= (init_element_int(&arr[0], 42) == 0);
    init_success &= (init_element_string(&arr[1], "banana") == 0);
    init_success &= (init_element_int(&arr[2], 7) == 0);
    init_success &= (init_element_string(&arr[3], "apple") == 0);
    init_success &= (init_element_int(&arr[4], 100) == 0);
    init_success &= (init_element_string(&arr[5], "cherry") == 0);
    init_success &= (init_element_int(&arr[6], 3) == 0);
    
    if (!init_success) {
        for (i = 0; i < count; i++) {
            free_element(&arr[i]);
        }
        free(arr);
        return NULL;
    }
    
    *size = count;
    return arr;
}

int main(void)
{
    Element *list;
    size_t size = 0;
    
    list = create_mixed_list(&size);
    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return EXIT_FAILURE;
    }
    
    printf("Original list: ");
    print_list(list, size);
    
    qsort(list, size, sizeof(Element), compare_elements);
    
    printf("Sorted list:   ");
    print_list(list, size);
    
    free_list(list, size);
    
    return EXIT_SUCCESS;
}