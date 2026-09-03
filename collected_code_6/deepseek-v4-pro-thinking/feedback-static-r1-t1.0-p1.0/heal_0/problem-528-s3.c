#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct List {
    struct Node *head;
    struct List *next;
};

size_t list_length(const struct List *list);
struct List *find_minimum_length(struct List *lists);
struct Node *node_create(int data);
struct List *list_create(void);
int list_append(struct List *list, int data);
void free_all_lists(struct List *lists);

size_t list_length(const struct List *list)
{
    size_t length = 0;
    const struct Node *current;

    if (list == NULL) {
        return 0;
    }

    for (current = list->head; current != NULL; current = current->next) {
        length++;
    }

    return length;
}

struct List *find_minimum_length(struct List *lists)
{
    struct List *min_list = NULL;
    struct List *current;
    size_t min_length = 0;
    int first = 1;

    for (current = lists; current != NULL; current = current->next) {
        size_t length = list_length(current);

        if (first || length < min_length) {
            min_length = length;
            min_list = current;
            first = 0;

            if (length == 0) {
                break;
            }
        }
    }

    return min_list;
}

struct Node *node_create(int data)
{
    struct Node *node = malloc(sizeof *node);

    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

struct List *list_create(void)
{
    struct List *list = malloc(sizeof *list);

    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->next = NULL;

    return list;
}

int list_append(struct List *list, int data)
{
    struct Node *new_node;
    struct Node *current;

    if (list == NULL) {
        return -1;
    }

    new_node = node_create(data);
    if (new_node == NULL) {
        return -1;
    }

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }

    return 0;
}

void free_all_lists(struct List *lists)
{
    struct List *current_list = lists;

    while (current_list != NULL) {
        struct List *next_list = current_list->next;
        struct Node *current_node = current_list->head;

        while (current_node != NULL) {
            struct Node *next_node = current_node->next;
            free(current_node);
            current_node = next_node;
        }

        free(current_list);
        current_list = next_list;
    }
}

int main(void)
{
    struct List *list1;
    struct List *list2;
    struct List *list3;
    struct List *min;

    list1 = list_create();
    if (list1 == NULL) {
        return EXIT_FAILURE;
    }

    list2 = list_create();
    if (list2 == NULL) {
        free_all_lists(list1);
        return EXIT_FAILURE;
    }
    list1->next = list2;

    list3 = list_create();
    if (list3 == NULL) {
        free_all_lists(list1);
        return EXIT_FAILURE;
    }
    list2->next = list3;
    list3->next = NULL;

    if (list_append(list1, 1) != 0) {
        free_all_lists(list1);
        return EXIT_FAILURE;
    }
    if (list_append(list1, 2) != 0) {
        free_all_lists(list1);
        return EXIT_FAILURE;
    }
    if (list_append(list1, 3) != 0) {
        free_all_lists(list1);
        return EXIT_FAILURE;
    }
    if (list_append(list2, 4) != 0) {
        free_all_lists(list1);
        return EXIT_FAILURE;
    }
    if (list_append(list2, 5) != 0) {
        free_all_lists(list1);
        return EXIT_FAILURE;
    }
    if (list_append(list3, 6) != 0) {
        free_all_lists(list1);
        return EXIT_FAILURE;
    }
    if (list_append(list3, 7) != 0) {
        free_all_lists(list1);
        return EXIT_FAILURE;
    }
    if (list_append(list3, 8) != 0) {
        free_all_lists(list1);
        return EXIT_FAILURE;
    }
    if (list_append(list3, 9) != 0) {
        free_all_lists(list1);
        return EXIT_FAILURE;
    }

    min = find_minimum_length(list1);
    if (min != NULL) {
        printf("%zu\n", list_length(min));
    }

    free_all_lists(list1);

    return 0;
}