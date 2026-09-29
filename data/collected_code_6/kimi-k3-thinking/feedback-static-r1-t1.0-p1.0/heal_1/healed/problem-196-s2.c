#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_ELEMENT_LEN 4096

typedef struct {
    char **elements;
    size_t length;
} Tuple;

typedef struct {
    Tuple *data;
    size_t count;
    size_t capacity;
} TupleList;

void remove_tuples_of_length(TupleList *list, size_t k);

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len;

    if (s == NULL) {
        return 0;
    }

    len = 0;
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

static Tuple create_tuple(const char *const *elements, size_t length)
{
    Tuple t;
    size_t i;

    t.elements = NULL;
    t.length = 0;

    if (length == 0) {
        return t;
    }

    if (elements == NULL) {
        return t;
    }

    if (length > SIZE_MAX / sizeof(char *)) {
        return t;
    }

    t.elements = (char **)malloc(length * sizeof(char *));
    if (t.elements == NULL) {
        return t;
    }

    for (i = 0; i < length; i++) {
        size_t elem_len;

        if (elements[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(t.elements[j]);
            }
            free(t.elements);
            t.elements = NULL;
            return t;
        }

        elem_len = bounded_strlen(elements[i], MAX_ELEMENT_LEN);
        t.elements[i] = (char *)malloc(elem_len + 1);
        if (t.elements[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(t.elements[j]);
            }
            free(t.elements);
            t.elements = NULL;
            return t;
        }
        memcpy(t.elements[i], elements[i], elem_len);
        t.elements[i][elem_len] = '\0';
    }

    t.length = length;
    return t;
}

static void free_tuple(Tuple *t)
{
    size_t i;

    if (t == NULL) {
        return;
    }

    for (i = 0; i < t->length; i++) {
        free(t->elements[i]);
        t->elements[i] = NULL;
    }
    free(t->elements);
    t->elements = NULL;
    t->length = 0;
}

static int append_tuple(TupleList *list, const char *const *elements, size_t length)
{
    Tuple t;

    if (list == NULL) {
        return -1;
    }

    if (list->count == list->capacity) {
        size_t new_capacity;
        Tuple *new_data;

        new_capacity = (list->capacity == 0) ? 4 : list->capacity * 2;
        if (new_capacity < list->capacity) {
            return -1;
        }
        if (new_capacity > SIZE_MAX / sizeof(Tuple)) {
            return -1;
        }

        new_data = (Tuple *)realloc(list->data, new_capacity * sizeof(Tuple));
        if (new_data == NULL) {
            return -1;
        }

        list->data = new_data;
        list->capacity = new_capacity;
    }

    t = create_tuple(elements, length);
    if (length > 0 && t.elements == NULL) {
        return -1;
    }

    list->data[list->count] = t;
    list->count++;
    return 0;
}

static void free_list(TupleList *list)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < list->count; i++) {
        free_tuple(&list->data[i]);
    }
    free(list->data);
    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
}

static void print_list(const TupleList *list)
{
    size_t i;
    size_t j;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < list->count; i++) {
        printf("(");
        for (j = 0; j < list->data[i].length; j++) {
            printf("%s%s", list->data[i].elements[j],
                   (j + 1 < list->data[i].length) ? ", " : "");
        }
        printf(")\n");
    }
}

void remove_tuples_of_length(TupleList *list, size_t k)
{
    size_t read_idx;
    size_t write_idx;

    if (list == NULL || list->data == NULL) {
        return;
    }

    write_idx = 0;
    for (read_idx = 0; read_idx < list->count; read_idx++) {
        if (list->data[read_idx].length == k) {
            free_tuple(&list->data[read_idx]);
        } else {
            if (write_idx != read_idx) {
                list->data[write_idx] = list->data[read_idx];
                list->data[read_idx].elements = NULL;
                list->data[read_idx].length = 0;
            }
            write_idx++;
        }
    }

    list->count = write_idx;
}

int main(void)
{
    TupleList list;
    const char *t1[] = {"apple", "banana"};
    const char *t2[] = {"red", "green", "blue"};
    const char *t3[] = {"cat", "dog"};
    const char *t4[] = {"solo"};
    const char *t5[] = {"one", "two"};
    const size_t k = 2;

    list.data = NULL;
    list.count = 0;
    list.capacity = 0;

    if (append_tuple(&list, t1, 2) != 0 ||
        append_tuple(&list, t2, 3) != 0 ||
        append_tuple(&list, t3, 2) != 0 ||
        append_tuple(&list, t4, 1) != 0 ||
        append_tuple(&list, t5, 2) != 0) {
        fprintf(stderr, "Error: failed to build tuple list\n");
        free_list(&list);
        return EXIT_FAILURE;
    }

    printf("Before removal:\n");
    print_list(&list);

    remove_tuples_of_length(&list, k);

    printf("After removing tuples of length %zu:\n", k);
    print_list(&list);

    free_list(&list);
    return EXIT_SUCCESS;
}