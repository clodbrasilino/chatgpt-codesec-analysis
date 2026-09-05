#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef enum {
    TYPE_INT,
    TYPE_STRING
} ElementType;

typedef struct {
    ElementType type;
    union {
        long long int_val;
        char *str_val;
    } data;
} Element;

static int compare_elements(const void *a, const void *b)
{
    const Element *elem_a = (const Element *)a;
    const Element *elem_b = (const Element *)b;
    
    if (elem_a->type == TYPE_INT && elem_b->type == TYPE_INT) {
        if (elem_a->data.int_val < elem_b->data.int_val) return -1;
        if (elem_a->data.int_val > elem_b->data.int_val) return 1;
        return 0;
    }
    
    if (elem_a->type == TYPE_STRING && elem_b->type == TYPE_STRING) {
        return strcmp(elem_a->data.str_val, elem_b->data.str_val);
    }
    
    if (elem_a->type == TYPE_INT) return -1;
    return 1;
}

static bool is_valid_integer(const char *str, long long *result)
{
    if (str == NULL || *str == '\0') return false;
    
    char *endptr;
    long long val = strtoll(str, &endptr, 10);
    
    if (*endptr != '\0') return false;
    if (endptr == str) return false;
    
    *result = val;
    return true;
}

static void free_elements(Element *arr, size_t count)
{
    if (arr == NULL) return;
    
    for (size_t i = 0; i < count; i++) {
        if (arr[i].type == TYPE_STRING && arr[i].data.str_val != NULL) {
            free(arr[i].data.str_val);
        }
    }
    free(arr);
}

static int process_input(Element *arr, size_t *count, size_t capacity)
{
    char buffer[256];
    size_t idx = 0;
    
    while (idx < capacity && fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        
        if (len == 0) continue;
        
        long long int_val;
        if (is_valid_integer(buffer, &int_val)) {
            arr[idx].type = TYPE_INT;
            arr[idx].data.int_val = int_val;
        } else {
            char *str_copy = malloc(len + 1);
            if (str_copy == NULL) {
                free_elements(arr, idx);
                return -1;
            }
            strcpy(str_copy, buffer);
            arr[idx].type = TYPE_STRING;
            arr[idx].data.str_val = str_copy;
        }
        idx++;
    }
    
    *count = idx;
    return 0;
}

int main(void)
{
    const size_t MAX_ELEMENTS = 1000;
    Element *elements = calloc(MAX_ELEMENTS, sizeof(Element));
    
    if (elements == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    size_t count = 0;
    
    if (process_input(elements, &count, MAX_ELEMENTS) != 0) {
        fprintf(stderr, "Error processing input\n");
        return EXIT_FAILURE;
    }
    
    if (count > 0) {
        qsort(elements, count, sizeof(Element), compare_elements);
        
        for (size_t i = 0; i < count; i++) {
            if (elements[i].type == TYPE_INT) {
                printf("%lld\n", elements[i].data.int_val);
            } else {
                printf("%s\n", elements[i].data.str_val);
            }
        }
    }
    
    free_elements(elements, count);
    return EXIT_SUCCESS;
}