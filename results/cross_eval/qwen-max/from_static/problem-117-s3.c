#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

List* create_list() {
    return (List*)calloc(1, sizeof(List));
}

void add_node(List *list, const char *value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->value = strdup(value);
    new_node->next = list->head;
    list->head = new_node;
}

bool is_float(const char *str) {
    if (*str == '\0') return false;
    bool has_decimal = false;
    while (*str) {
        if (isspace(*str)) {
            str++;
            continue;
        }
        if (*str == '.' && !has_decimal) {
            has_decimal = true;
        } else if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

void convert_to_float(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        if (is_float(current->value)) {
            float value = strtof(current->value, NULL);
            free(current->value);
            asprintf(&(current->value), "%.2f", value);
        }
        current = current->next;
    }
}

void print_list(const List *list) {
    const Node *current = list->head;
    while (current != NULL) {
        printf("%s -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    List *list = create_list();
    add_node(list, "3.14");
    add_node(list, "7.0");
    add_node(list, "hello");
    add_node(list, "2.718");

    printf("Original list:\n");
    print_list(list);

    convert_to_float(list);

    printf("Converted list:\n");
    print_list(list);

    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->value);
        free(temp);
    }
    free(list);

    return 0;
}