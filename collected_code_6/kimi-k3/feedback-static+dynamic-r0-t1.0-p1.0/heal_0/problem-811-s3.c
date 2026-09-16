#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} Tuple;

typedef struct {
    Tuple *data;
    size_t size;
    size_t capacity;
} TupleList;

int tuple_list_init(TupleList *list, size_t capacity) {
    if (list == NULL || capacity == 0) {
        return -1;
    }
    list->data = (Tuple *)malloc(capacity * sizeof(Tuple));
    if (list->data == NULL) {
        return -1;
    }
    list->size = 0;
    list->capacity = capacity;
    return 0;
}

void tuple_list_free(TupleList *list) {
    if (list != NULL && list->data != NULL) {
        free(list->data);
        list->data = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}

int tuple_list_add(TupleList *list, int x, int y) {
    if (list == NULL || list->data == NULL) {
        return -1;
    }
    if (list->size >= list->capacity) {
        return -1;
    }
    list->data[list->size].x = x;
    list->data[list->size].y = y;
    list->size++;
    return 0;
}

int tuple_lists_identical(const TupleList *list1, const TupleList *list2) {
    if (list1 == NULL || list2 == NULL) {
        return 0;
    }
    if (list1->data == NULL && list2->data == NULL) {
        return 1;
    }
    if (list1->data == NULL || list2->data == NULL) {
        return 0;
    }
    if (list1->size != list2->size) {
        return 0;
    }
    if (list1->size == 0) {
        return 1;
    }
    if (memcmp(list1->data, list2->data, list1->size * sizeof(Tuple)) == 0) {
        return 1;
    }
    return 0;
}

int main(void) {
    TupleList list1;
    TupleList list2;
    TupleList list3;
    int result;

    result = tuple_list_init(&list1, 10);
    if (result != 0) {
        fprintf(stderr, "Failed to initialize list1\n");
        return EXIT_FAILURE;
    }

    result = tuple_list_init(&list2, 10);
    if (result != 0) {
        fprintf(stderr, "Failed to initialize list2\n");
        tuple_list_free(&list1);
        return EXIT_FAILURE;
    }

    result = tuple_list_init(&list3, 10);
    if (result != 0) {
        fprintf(stderr, "Failed to initialize list3\n");
        tuple_list_free(&list1);
        tuple_list_free(&list2);
        return EXIT_FAILURE;
    }

    result = tuple_list_add(&list1, 1, 2);
    if (result != 0) {
        fprintf(stderr, "Failed to add to list1\n");
        tuple_list_free(&list1);
        tuple_list_free(&list2);
        tuple_list_free(&list3);
        return EXIT_FAILURE;
    }

    result = tuple_list_add(&list1, 3, 4);
    if (result != 0) {
        fprintf(stderr, "Failed to add to list1\n");
        tuple_list_free(&list1);
        tuple_list_free(&list2);
        tuple_list_free(&list3);
        return EXIT_FAILURE;
    }

    result = tuple_list_add(&list2, 1, 2);
    if (result != 0) {
        fprintf(stderr, "Failed to add to list2\n");
        tuple_list_free(&list1);
        tuple_list_free(&list2);
        tuple_list_free(&list3);
        return EXIT_FAILURE;
    }

    result = tuple_list_add(&list2, 3, 4);
    if (result != 0) {
        fprintf(stderr, "Failed to add to list2\n");
        tuple_list_free(&list1);
        tuple_list_free(&list2);
        tuple_list_free(&list3);
        return EXIT_FAILURE;
    }

    result = tuple_list_add(&list3, 1, 2);
    if (result != 0) {
        fprintf(stderr, "Failed to add to list3\n");
        tuple_list_free(&list1);
        tuple_list_free(&list2);
        tuple_list_free(&list3);
        return EXIT_FAILURE;
    }

    result = tuple_list_add(&list3, 5, 6);
    if (result != 0) {
        fprintf(stderr, "Failed to add to list3\n");
        tuple_list_free(&list1);
        tuple_list_free(&list2);
        tuple_list_free(&list3);
        return EXIT_FAILURE;
    }

    if (tuple_lists_identical(&list1, &list2)) {
        printf("list1 and list2 are identical\n");
    } else {
        printf("list1 and list2 are not identical\n");
    }

    if (tuple_lists_identical(&list1, &list3)) {
        printf("list1 and list3 are identical\n");
    } else {
        printf("list1 and list3 are not identical\n");
    }

    tuple_list_free(&list1);
    tuple_list_free(&list2);
    tuple_list_free(&list3);

    return EXIT_SUCCESS;
}