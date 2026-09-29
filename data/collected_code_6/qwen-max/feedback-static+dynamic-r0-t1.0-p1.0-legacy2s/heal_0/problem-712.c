#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_node {
    int data;
    struct list_node *next;
} list_node_t;

typedef struct list {
    list_node_t *head;
    struct list *next_list;
} list_t;

list_node_t* create_node(int data) {
    list_node_t *new_node = (list_node_t*)malloc(sizeof(list_node_t));
    if (!new_node) return NULL;
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

list_t* create_list() {
    list_t *new_list = (list_t*)malloc(sizeof(list_t));
    if (!new_list) return NULL;
    new_list->head = NULL;
    new_list->next_list = NULL;
    return new_list;
}

void add_to_list(list_t *list, int data) {
    list_node_t *temp = create_node(data);
    temp->next = list->head;
    list->head = temp;
}

void free_list(list_t *list) {
    while (list) {
        list_node_t *current = list->head;
        list_t *next_list = list->next_list;
        while (current) {
            list_node_t *to_free = current;
            current = current->next;
            free(to_free);
        }
        free(list);
        list = next_list;
    }
}

int is_in_list(list_node_t *head, int data) {
    while (head) {
        if (head->data == data) return 1;
        head = head->next;
    }
    return 0;
}

list_t* remove_duplicates(list_t *lists) {
    list_t *result = create_list();
    while (lists) {
        list_node_t *current = lists->head;
        list_t *new_list = create_list();
        while (current) {
            if (!is_in_list(result->head, current->data)) {
                add_to_list(result, current->data);
                add_to_list(new_list, current->data);
            }
            current = current->next;
        }
        new_list->next_list = result->next_list;
        result->next_list = new_list;
        lists = lists->next_list;
    }
    return result;
}

int main() {
    list_t *lists = create_list();
    list_t *lst1 = create_list();
    add_to_list(lst1, 3);
    add_to_list(lst1, 2);
    add_to_list(lst1, 1);

    list_t *lst2 = create_list();
    add_to_list(lst2, 4);
    add_to_list(lst2, 3);
    add_to_list(lst2, 2);

    lst1->next_list = lst2;
    lists->next_list = lst1;

    list_t *deduped_lists = remove_duplicates(lists);

    while (deduped_lists) {
        list_node_t *current = deduped_lists->head;
        while (current) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
        deduped_lists = deduped_lists->next_list;
    }

    free_list(lists);
    return 0;
}