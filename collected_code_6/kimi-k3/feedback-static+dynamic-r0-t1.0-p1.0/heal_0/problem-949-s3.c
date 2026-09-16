#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
} TupleList;

int count_total_digits(const Tuple *t) {
    if (t == NULL || t->data == NULL) {
        return 0;
    }
    
    int count = 0;
    for (size_t i = 0; i < t->size; i++) {
        int num = t->data[i];
        if (num == 0) {
            count++;
        } else {
            if (num < 0) {
                num = -num;
            }
            while (num > 0) {
                count++;
                num /= 10;
            }
        }
    }
    return count;
}

int compare_tuples(const void *a, const void *b) {
    const Tuple *ta = (const Tuple *)a;
    const Tuple *tb = (const Tuple *)b;
    int digits_a = count_total_digits(ta);
    int digits_b = count_total_digits(tb);
    
    if (digits_a < digits_b) return -1;
    if (digits_a > digits_b) return 1;
    return 0;
}

int init_tuple(Tuple *t, size_t size) {
    if (t == NULL || size == 0) {
        return -1;
    }
    
    t->data = (int *)malloc(size * sizeof(int));
    if (t->data == NULL) {
        return -1;
    }
    
    t->size = size;
    return 0;
}

void free_tuple(Tuple *t) {
    if (t != NULL && t->data != NULL) {
        free(t->data);
        t->data = NULL;
        t->size = 0;
    }
}

int init_tuple_list(TupleList *list, size_t size) {
    if (list == NULL || size == 0) {
        return -1;
    }
    
    list->tuples = (Tuple *)malloc(size * sizeof(Tuple));
    if (list->tuples == NULL) {
        return -1;
    }
    
    list->size = size;
    return 0;
}

void free_tuple_list(TupleList *list) {
    if (list != NULL && list->tuples != NULL) {
        for (size_t i = 0; i < list->size; i++) {
            free_tuple(&list->tuples[i]);
        }
        free(list->tuples);
        list->tuples = NULL;
        list->size = 0;
    }
}

void sort_tuple_list(TupleList *list) {
    if (list == NULL || list->tuples == NULL || list->size == 0) {
        return;
    }
    
    qsort(list->tuples, list->size, sizeof(Tuple), compare_tuples);
}

void print_tuple_list(const TupleList *list) {
    if (list == NULL || list->tuples == NULL) {
        return;
    }
    
    for (size_t i = 0; i < list->size; i++) {
        printf("(");
        for (size_t j = 0; j < list->tuples[i].size; j++) {
            printf("%d", list->tuples[i].data[j]);
            if (j < list->tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(") [digits: %d]\n", count_total_digits(&list->tuples[i]));
    }
}

int main(void) {
    TupleList list;
    
    if (init_tuple_list(&list, 5) != 0) {
        fprintf(stderr, "Failed to initialize tuple list\n");
        return EXIT_FAILURE;
    }
    
    if (init_tuple(&list.tuples[0], 2) != 0) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }
    list.tuples[0].data[0] = 12;
    list.tuples[0].data[1] = 345;
    
    if (init_tuple(&list.tuples[1], 1) != 0) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }
    list.tuples[1].data[0] = 7;
    
    if (init_tuple(&list.tuples[2], 3) != 0) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }
    list.tuples[2].data[0] = 1;
    list.tuples[2].data[1] = 2;
    list.tuples[2].data[2] = 3;
    
    if (init_tuple(&list.tuples[3], 2) != 0) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }
    list.tuples[3].data[0] = 100;
    list.tuples[3].data[1] = 200;
    
    if (init_tuple(&list.tuples[4], 1) != 0) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }
    list.tuples[4].data[0] = 9999;
    
    printf("Before sorting:\n");
    print_tuple_list(&list);
    
    sort_tuple_list(&list);
    
    printf("\nAfter sorting:\n");
    print_tuple_list(&list);
    
    free_tuple_list(&list);
    
    return EXIT_SUCCESS;
}