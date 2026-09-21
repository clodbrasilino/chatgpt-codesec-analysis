#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    char *data;
    struct list *next;
} List;

List* create_list_item(const char *str) {
    List *new_item = (List *)malloc(sizeof(List));
    if (new_item == NULL) return NULL;
    new_item->data = strdup(str);
    if (new_item->data == NULL) {
        free(new_item);
        return NULL;
    }
    new_item->next = NULL;
    return new_item;
}

void free_list(List *head) {
    while (head != NULL) {
        List *temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

List* prepend_string_to_list_items(const char *prefix, List *head) {
    if (prefix == NULL) return head;
    List *current = head;
    while (current != NULL) {
        size_t prefix_len = strlen(prefix);
        size_t data_len = 0;
        if (current->data != NULL) data_len = strlen(current->data);
        size_t len = prefix_len + data_len + 1;
        char *new_data = (char *)malloc(len);
        if (new_data == NULL) {
            return NULL;
        }
        snprintf(new_data, len, "%s%s", prefix, current->data ? current->data : "");
        free(current->data);
        current->data = new_data;
        current = current->next;
    }
    return head;
}

int main() {
    List *head = create_list_item("item1");
    if (head == NULL) return 1;
    head->next = create_list_item("item2");
    if (head->next == NULL) {
        free_list(head);
        return 1;
    }
    head->next->next = create_list_item("item3");
    if (head->next->next == NULL) {
        free_list(head);
        return 1;
    }

    const char *prefix = "pre-";
    head = prepend_string_to_list_items(prefix, head);

    for (List *current = head; current != NULL; current = current->next) {
        printf("%s\n", current->data);
    }

    free_list(head);
    return 0;
}