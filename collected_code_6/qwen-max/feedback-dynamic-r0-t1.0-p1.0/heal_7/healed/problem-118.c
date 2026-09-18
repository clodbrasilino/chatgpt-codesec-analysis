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

    char *str_copy = strdup(str);
    if (str_copy == NULL) {
        return NULL;
    }

    struct List *head = NULL, *current = NULL;

    for (char *token = strtok(str_copy, " "); token; token = strtok(NULL, " ")) {
        struct List *new_item = malloc(sizeof(struct List));
        if (new_item == NULL) {
            free(str_copy);
            while (head != NULL) {
                current = head;
                head = head->next;
                free(current->item);
                free(current);
            }
            return NULL;
        }

        new_item->item = strdup(token);
        if (new_item->item == NULL) {
            free(new_item);
            free(str_copy);
            while (head != NULL) {
                current = head;
                head = head->next;
                free(current->item);
                free(current);
            }
            return NULL;
        }

        new_item->next = NULL;

        if (head == NULL) {
            head = new_item;
        } else {
            current->next = new_item;
        }

        current = new_item;
    }

    free(str_copy);
    return head;
}

void free_list(struct List *list) {
    while (list != NULL) {
        struct List *temp = list;
        list = list->next;
        free(temp->item);
        free(temp);
    }
}

int main() {
    const char *input_strings[] = {"python programming", "lists tuples strings", "write a program"};
    int num_inputs = sizeof(input_strings) / sizeof(input_strings[0]);

    for (int i = 0; i < num_inputs; ++i) {
        struct List *list = string_to_list(input_strings[i]);
        if (list != NULL) {
            for (struct List *current = list; current != NULL; current = current->next) {
                printf("%s ", current->item);
            }
            printf("\n");
            free_list(list);
        } else {
            printf("<no output>\n");
        }
    }

    return 0;
}