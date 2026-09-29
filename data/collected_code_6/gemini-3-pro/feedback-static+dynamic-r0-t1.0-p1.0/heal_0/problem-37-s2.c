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
} MixedElement;

int compare_mixed(const void *a, const void *b) {
    const MixedElement *elem1 = (const MixedElement *)a;
    const MixedElement *elem2 = (const MixedElement *)b;

    if (elem1->type != elem2->type) {
        return elem1->type - elem2->type;
    }

    if (elem1->type == TYPE_INT) {
        return (elem1->data.int_val > elem2->data.int_val) - (elem1->data.int_val < elem2->data.int_val);
    } else {
        return strcmp(elem1->data.str_val, elem2->data.str_val);
    }
}

void sort_mixed_list(MixedElement *list, size_t length) {
    if (list != NULL && length > 0) {
        qsort(list, length, sizeof(MixedElement), compare_mixed);
    }
}

void free_mixed_list(MixedElement *list, size_t length) {
    if (list == NULL) return;
    for (size_t i = 0; i < length; ++i) {
        if (list[i].type == TYPE_STRING && list[i].data.str_val != NULL) {
            free(list[i].data.str_val);
            list[i].data.str_val = NULL;
        }
    }
}

MixedElement* create_string_element(const char *str) {
    MixedElement *elem = malloc(sizeof(MixedElement));
    if (elem == NULL) return NULL;
    
    elem->type = TYPE_STRING;
    elem->data.str_val = strdup(str);
    
    if (elem->data.str_val == NULL) {
        free(elem);
        return NULL;
    }
    
    return elem;
}

int main(void) {
    size_t length = 5;
    MixedElement *list = calloc(length, sizeof(MixedElement));
    if (list == NULL) {
        return 1;
    }

    list[0].type = TYPE_INT;
    list[0].data.int_val = 42;

    list[1].type = TYPE_STRING;
    list[1].data.str_val = strdup("hello");
    if (list[1].data.str_val == NULL) goto cleanup;

    list[2].type = TYPE_INT;
    list[2].data.int_val = 7;

    list[3].type = TYPE_STRING;
    list[3].data.str_val = strdup("apple");
    if (list[3].data.str_val == NULL) goto cleanup;

    list[4].type = TYPE_INT;
    list[4].data.int_val = -5;

    sort_mixed_list(list, length);

    for (size_t i = 0; i < length; ++i) {
        if (list[i].type == TYPE_INT) {
            printf("%d\n", list[i].data.int_val);
        } else {
            printf("%s\n", list[i].data.str_val);
        }
    }

cleanup:
    free_mixed_list(list, length);
    free(list);

    return 0;
}