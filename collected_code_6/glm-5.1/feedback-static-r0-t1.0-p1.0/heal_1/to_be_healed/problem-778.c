#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

List *create_list() {
    List *list = malloc(sizeof(List));
    if (!list) return NULL;
    list->head = NULL;
    return list;
}

void list_append(List *list, void *data) {
    if (!list) return;
    Node *node = malloc(sizeof(Node));
    if (!node) return;
    node->data = data;
    node->next = NULL;
    if (!list->head) {
        list->head = node;
    } else {
        Node *current = list->head;
        while (current->next) current = current->next;
        current->next = node;
    }
}

int *create_int(int value) {
    int *ptr = malloc(sizeof(int));
    if (!ptr) return NULL;
    *ptr = value;
    return ptr;
}

List *create_sublist(int value, int count) {
    List *sublist = create_list();
    if (!sublist) return NULL;
    for (int i = 0; i < count; i++) {
        int *item = create_int(value);
        if (!item) {
            Node *curr = sublist->head;
            while (curr) {
                Node *tmp = curr;
                curr = curr->next;
                free(tmp->data);
                free(tmp);
            }
            free(sublist);
            return NULL;
        }
        list_append(sublist, item);
    }
    return sublist;
}

List *pack(List *input) {
    if (!input) return NULL;
    List *output = create_list();
    if (!output) return NULL;
    
    Node *current = input->head;
    while (current) {
        int value = *(int *)current->data;
        int count = 1;
        while (current->next && *(int *)current->next->data == value) {
            count++;
            current = current->next;
        }
        List *sublist = create_sublist(value, count);
        if (!sublist) {
            Node *out_curr = output->head;
            while (out_curr) {
                Node *tmp = out_curr;
                out_curr = out_curr->next;
                List *sub = (List *)tmp->data;
                Node *sub_curr = sub->head;
                while (sub_curr) {
                    Node *sub_tmp = sub_curr;
                    sub_curr = sub_curr->next;
                    free(sub_tmp->data);
                    free(sub_tmp);
                }
                free(sub);
                free(tmp);
            }
            free(output);
            return NULL;
        }
        list_append(output, sublist);
        current = current->next;
    }
    return output;
}

void free_packed(List *list) {
    if (!list) return;
    Node *curr = list->head;
    while (curr) {
        Node *tmp = curr;
        curr = curr->next;
        List *sublist = (List *)tmp->data;
        Node *sub_curr = sublist->head;
        while (sub_curr) {
            Node *sub_tmp = sub_curr;
            sub_curr = sub_curr->next;
            free(sub_tmp->data);
            free(sub_tmp);
        }
        free(sublist);
        free(tmp);
    }
    free(list);
}

void free_flat(List *list) {
    if (!list) return;
    Node *curr = list->head;
    while (curr) {
        Node *tmp = curr;
        curr = curr->next;
        free(tmp->data);
        free(tmp);
    }
    free(list);
}

void print_packed(List *list) {
    if (!list) return;
    printf("[");
    Node *curr = list->head;
    while (curr) {
        List *sublist = (List *)curr->data;
        printf("[");
        Node *sub_curr = sublist->head;
        while (sub_curr) {
            printf("%d", *(int *)sub_curr->data);
            if (sub_curr->next) printf(", ");
            sub_curr = sub_curr->next;
        }
        printf("]");
        if (curr->next) printf(", ");
        curr = curr->next;
    }
    printf("]\n");
}

int main(void) {
    List *input = create_list();
    if (!input) return 1;

    /* Possible weaknesses found:
     *  Variable 'vals' can be declared as const array [constVariable]
     */
    int vals[] = {1, 1, 1, 2, 3, 3, 4, 4, 4, 4, 5};
    for (int i = 0; i < 11; i++) {
        int *item = create_int(vals[i]);
        if (!item) {
            free_flat(input);
            return 1;
        }
        list_append(input, item);
    }

    List *output = pack(input);
    if (output) {
        print_packed(output);
        free_packed(output);
    }

    free_flat(input);
    return 0;
}