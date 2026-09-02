#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    struct List *sublist;
} List;

Node* create_node(int value) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

List* create_list() {
    List *new_list = (List*) malloc(sizeof(List));
    if (new_list == NULL) {
        exit(EXIT_FAILURE);
    }
    new_list->head = NULL;
    new_list->sublist = NULL;
    return new_list;
}

void append_node(List *list, int value) {
    Node *new_node = create_node(value);
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

List* extract_column(List *source, int column) {
    if (source == NULL) {
        return NULL;
    }

    List *result = create_list();
    for (List *current = source; current != NULL; current = current->sublist) {
        int col_count = 0;
        for (Node *node = current->head; node != NULL; node = node->next) {
            if (col_count == column) {
                append_node(result, node->value);
                break;
            }
            col_count++;
        }
    }
    return result;
}

void print_list(List *list) {
    for (Node *node = list->head; node != NULL; node = node->next) {
        printf("%d ", node->value);
    }
    printf("\n");
}

int main() {
    List *main_list = create_list();
    for (int i = 0; i < 3; i++) {
        List *nest_list = create_list();
        for (int j = 0; j < 3; j++) {
            append_node(nest_list, j + i * 3 + 1);
        }
        if (i == 0) {
            main_list->sublist = nest_list;
        } else {
            List *last = main_list->sublist;
            while (last->sublist != NULL) {
                last = last->sublist;
            }
            last->sublist = nest_list;
        }
    }

    List *column = extract_column(main_list, 1);
    print_list(column);

    // Free memory
    for (List *current = main_list; current != NULL;) {
        List *temp = current->sublist;
        Node *node = current->head;
        while (node != NULL) {
            Node *next = node->next;
            free(node);
            node = next;
        }
        free(current);
        current = temp;
    }

    for (List *current = column; current != NULL;) {
        List *temp = current->sublist;
        Node *node = current->head;
        while (node != NULL) {
            Node *next = node->next;
            free(node);
            node = next;
        }
        free(current);
        current = temp;
    }

    return 0;
}