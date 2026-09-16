#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct List {
    char *item;
    struct List *next;
};

struct List* string_to_list(const char *str) {
    if (str == NULL || *str == '\0') {
        return NULL;
    }

    struct List *head = NULL, *current = NULL;

    for (const char *token = strtok((char *)str, " "); token; token = strtok(NULL, " ")) {
        struct List *new_item = (struct List *)malloc(sizeof(struct List));
        if (new_item == NULL) {
            while (head != NULL) {
                current = head;
                head = head->next;
                free(current->item);
                free(current);
            }
            return NULL;
        }

        new_item->item = strdup(token);
        new_item->next = NULL;

        if (head == NULL) {
            head = new_item;
        } else {
            current->next = new_item;
        }

        current = new_item;
    }

    return head;
}

void free_list(struct List *list) {
    if (list != NULL) {
        struct List *current = list;
        while (current != NULL) {
            struct List *temp = current;
            current = current->next;
            free(temp->item);
            free(temp);
        }
    }
}

int main() {
    const char *input_string = "This is a sample string";
    struct List *list = string_to_list(input_string);

    for (struct List *current = list; current != NULL; current = current->next) {
        printf("%s\n", current->item);
    }

    free_list(list);
    return 0;
}