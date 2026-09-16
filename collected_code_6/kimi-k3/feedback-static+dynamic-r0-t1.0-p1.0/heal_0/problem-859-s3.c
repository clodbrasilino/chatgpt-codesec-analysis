#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node **items;
    size_t count;
    size_t capacity;
} Sublist;

typedef struct {
    Sublist *items;
    size_t count;
    size_t capacity;
} SublistList;

static Node *create_node(int data)
{
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

static void free_list(Node *head)
{
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

static int append_node(Node **head, Node **tail, int data)
{
    Node *node = create_node(data);
    if (node == NULL) {
        return 0;
    }
    if (*head == NULL) {
        *head = node;
        *tail = node;
    } else {
        (*tail)->next = node;
        *tail = node;
    }
    return 1;
}

static int sublist_init(Sublist *sublist)
{
    sublist->capacity = 4;
    sublist->count = 0;
    sublist->items = malloc(sublist->capacity * sizeof(*sublist->items));
    if (sublist->items == NULL) {
        return 0;
    }
    return 1;
}

static void sublist_free(Sublist *sublist)
{
    free(sublist->items);
    sublist->items = NULL;
    sublist->count = 0;
    sublist->capacity = 0;
}

static int sublist_add(Sublist *sublist, Node *node)
{
    if (sublist->count == sublist->capacity) {
        size_t new_capacity = sublist->capacity * 2;
        Node **new_items = realloc(sublist->items, new_capacity * sizeof(*new_items));
        if (new_items == NULL) {
            return 0;
        }
        sublist->items = new_items;
        sublist->capacity = new_capacity;
    }
    sublist->items[sublist->count] = node;
    sublist->count++;
    return 1;
}

static int sublist_copy(const Sublist *source, Sublist *dest)
{
    dest->capacity = source->count > 0 ? source->count : 1;
    dest->count = source->count;
    dest->items = malloc(dest->capacity * sizeof(*dest->items));
    if (dest->items == NULL) {
        return 0;
    }
    for (size_t i = 0; i < source->count; i++) {
        dest->items[i] = source->items[i];
    }
    return 1;
}

static int sublist_list_init(SublistList *list)
{
    list->capacity = 16;
    list->count = 0;
    list->items = malloc(list->capacity * sizeof(*list->items));
    if (list->items == NULL) {
        return 0;
    }
    return 1;
}

static void sublist_list_free(SublistList *list)
{
    for (size_t i = 0; i < list->count; i++) {
        sublist_free(&list->items[i]);
    }
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

static int sublist_list_add(SublistList *list, const Sublist *sublist)
{
    if (list->count == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Sublist *new_items = realloc(list->items, new_capacity * sizeof(*new_items));
        if (new_items == NULL) {
            return 0;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    if (!sublist_copy(sublist, &list->items[list->count])) {
        return 0;
    }
    list->count++;
    return 1;
}

static int generate_sublists_recursive(Node *current, Sublist *current_sublist, SublistList *result)
{
    if (current == NULL) {
        return sublist_list_add(result, current_sublist);
    }

    if (!generate_sublists_recursive(current->next, current_sublist, result)) {
        return 0;
    }

    if (!sublist_add(current_sublist, current)) {
        return 0;
    }

    if (!generate_sublists_recursive(current->next, current_sublist, result)) {
        return 0;
    }

    current_sublist->count--;
    return 1;
}

static int generate_sublists(Node *head, SublistList *result)
{
    Sublist current_sublist;
    if (!sublist_init(&current_sublist)) {
        return 0;
    }

    int success = generate_sublists_recursive(head, &current_sublist, result);
    sublist_free(&current_sublist);
    return success;
}

static void print_sublists(const SublistList *list)
{
    printf("Total sublists: %zu\n", list->count);
    for (size_t i = 0; i < list->count; i++) {
        printf("[");
        for (size_t j = 0; j < list->items[i].count; j++) {
            printf("%d", list->items[i].items[j]->data);
            if (j + 1 < list->items[i].count) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(void)
{
    Node *head = NULL;
    Node *tail = NULL;
    SublistList result;
    int values[] = {1, 2, 3};
    size_t num_values = sizeof(values) / sizeof(values[0]);

    for (size_t i = 0; i < num_values; i++) {
        if (!append_node(&head, &tail, values[i])) {
            fprintf(stderr, "Failed to allocate memory for list node\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    if (!sublist_list_init(&result)) {
        fprintf(stderr, "Failed to initialize sublist list\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    if (!generate_sublists(head, &result)) {
        fprintf(stderr, "Failed to generate sublists\n");
        sublist_list_free(&result);
        free_list(head);
        return EXIT_FAILURE;
    }

    print_sublists(&result);

    sublist_list_free(&result);
    free_list(head);

    return EXIT_SUCCESS;
}