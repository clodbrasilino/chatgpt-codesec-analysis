#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    int initial;
    char *data;
    struct Tuple *next;
} Tuple;

Tuple *join_tuples(Tuple *head) {
    if (head == NULL) {
        return NULL;
    }
    Tuple *result = NULL;
    Tuple *result_tail = NULL;
    Tuple *current = head;
    while (current != NULL) {
        Tuple *existing = result;
        while (existing != NULL) {
            if (existing->initial == current->initial) {
                size_t existing_len = strlen(existing->data);
                size_t current_len = strlen(current->data);
                size_t len = existing_len + current_len + 1;
                char *new_data = calloc(len, sizeof(char));
                if (new_data == NULL) {
                    return NULL;
                }
                memcpy(new_data, existing->data, existing_len);
                memcpy(new_data + existing_len, current->data, current_len);
                free(existing->data);
                existing->data = new_data;
                break;
            }
            existing = existing->next;
        }
        if (existing == NULL) {
            Tuple *new_tuple = malloc(sizeof(Tuple));
            if (new_tuple == NULL) {
                return NULL;
            }
            new_tuple->initial = current->initial;
            size_t data_len = strlen(current->data);
            new_tuple->data = malloc(data_len + 1);
            if (new_tuple->data == NULL) {
                free(new_tuple);
                return NULL;
            }
            memcpy(new_tuple->data, current->data, data_len + 1);
            new_tuple->next = NULL;
            if (result == NULL) {
                result = new_tuple;
                result_tail = new_tuple;
            } else {
                result_tail->next = new_tuple;
                result_tail = new_tuple;
            }
        }
        current = current->next;
    }
    return result;
}

void free_tuple_list(Tuple *head) {
    Tuple *current = head;
    while (current != NULL) {
        Tuple *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

int main(void) {
    Tuple *head = NULL;
    Tuple *tail = NULL;
    int initials[] = {1, 2, 1, 3, 2};
    const char *datas[] = {"a", "b", "c", "d", "e"};
    size_t count = sizeof(initials) / sizeof(initials[0]);
    for (size_t i = 0; i < count; i++) {
        Tuple *new_tuple = malloc(sizeof(Tuple));
        if (new_tuple == NULL) {
            free_tuple_list(head);
            return 1;
        }
        new_tuple->initial = initials[i];
        size_t data_len = strlen(datas[i]);
        new_tuple->data = malloc(data_len + 1);
        if (new_tuple->data == NULL) {
            free(new_tuple);
            free_tuple_list(head);
            return 1;
        }
        memcpy(new_tuple->data, datas[i], data_len + 1);
        new_tuple->next = NULL;
        if (head == NULL) {
            head = new_tuple;
            tail = new_tuple;
        } else {
            tail->next = new_tuple;
            tail = new_tuple;
        }
    }
    Tuple *joined = join_tuples(head);
    Tuple *current = joined;
    while (current != NULL) {
        printf("%d: %s\n", current->initial, current->data);
        current = current->next;
    }
    free_tuple_list(head);
    free_tuple_list(joined);
    return 0;
}