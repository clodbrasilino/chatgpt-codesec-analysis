#include <stddef.h>
#include <stdlib.h>

typedef struct Dictionary {
    void **keys;
    void **values;
    size_t length;
    size_t capacity;
} Dictionary;

Dictionary **create_list_of_empty_dicts(size_t count);
void free_list_of_empty_dicts(Dictionary **list, size_t count);

Dictionary **create_list_of_empty_dicts(size_t count)
{
    Dictionary **list;
    size_t i;

    if (count == 0 || count > (size_t)-1 / sizeof(*list)) {
        return NULL;
    }

    list = malloc(count * sizeof(*list));
    if (list == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        list[i] = malloc(sizeof(*list[i]));
        if (list[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        list[i]->keys = NULL;
        list[i]->values = NULL;
        list[i]->length = 0;
        list[i]->capacity = 0;
    }

    return list;
}

void free_list_of_empty_dicts(Dictionary **list, size_t count)
{
    size_t i;

    if (list == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void)
{
    Dictionary **list;
    size_t count = 5;
    size_t i;

    list = create_list_of_empty_dicts(count);
    if (list == NULL) {
        return 1;
    }

    for (i = 0; i < count; i++) {
        if (list[i]->keys != NULL || list[i]->values != NULL ||
            list[i]->length != 0 || list[i]->capacity != 0) {
            free_list_of_empty_dicts(list, count);
            return 1;
        }
    }

    free_list_of_empty_dicts(list, count);
    return 0;
}