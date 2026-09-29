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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len1 = strlen(prefix);
    List *current = head;
    while (current != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len2 = current->data ? strlen(current->data) : 0;
        char *new_data = (char *)malloc(len1 + len2 + 1);
        if (new_data == NULL) {
            return NULL;
        }
        snprintf(new_data, len1 + len2 + 1, "%s%s", prefix, current->data);
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