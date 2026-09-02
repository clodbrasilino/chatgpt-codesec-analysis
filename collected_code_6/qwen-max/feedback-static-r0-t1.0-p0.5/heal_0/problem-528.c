#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *data;
    size_t length;
} List;

List* create_list(size_t length) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->data = (int *)malloc(length * sizeof(int));
    if (list->data == NULL) {
        free(list);
        return NULL;
    }
    list->length = length;
    for (size_t i = 0; i < length; ++i) {
        list->data[i] = 0;
    }
    return list;
}

void free_list(List *list) {
    if (list != NULL) {
        free(list->data);
        free(list);
    }
}

List** find_min_length_lists(List **lists, size_t count, size_t *min_count) {
    if (count == 0) {
        *min_count = 0;
        return NULL;
    }

    size_t min_length = lists[0]->length;
    for (size_t i = 1; i < count; ++i) {
        if (lists[i]->length < min_length) {
            min_length = lists[i]->length;
        }
    }

    *min_count = 0;
    for (size_t i = 0; i < count; ++i) {
        if (lists[i]->length == min_length) {
            (*min_count)++;
        }
    }

    List **result = (List **)malloc(*min_count * sizeof(List *));
    if (result == NULL) {
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < count; ++i) {
        if (lists[i]->length == min_length) {
            result[index++] = lists[i];
        }
    }

    return result;
}

int main() {
    size_t num_lists = 4;
    List *lists[4] = {create_list(3), create_list(5), create_list(3), create_list(2)};

    size_t min_count;
    List **min_lists = find_min_length_lists(lists, num_lists, &min_count);

    if (min_lists != NULL) {
        printf("Lists with minimum length:\n");
        for (size_t i = 0; i < min_count; ++i) {
            printf("List %zu: Length = %zu\n", i + 1, min_lists[i]->length);
        }
        free(min_lists);
    } else {
        printf("No lists found.\n");
    }

    for (size_t i = 0; i < num_lists; ++i) {
        free_list(lists[i]);
    }

    return 0;
}