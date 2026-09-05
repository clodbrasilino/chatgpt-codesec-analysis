#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    size_t length;
} List;

typedef struct ListOfLists {
    List *list;
    struct ListOfLists *next;
} ListOfLists;

ListOfLists *find_min_length_lists(ListOfLists *lol) {
    if (lol == NULL) {
        return NULL;
    }

    size_t min_len = lol->list->length;
    ListOfLists *curr = lol->next;

    while (curr != NULL) {
        if (curr->list->length < min_len) {
            min_len = curr->list->length;
        }
        curr = curr->next;
    }

    ListOfLists *result = NULL;
    ListOfLists *tail = NULL;
    curr = lol;

    while (curr != NULL) {
        if (curr->list->length == min_len) {
            ListOfLists *new_node = (ListOfLists *)malloc(sizeof(ListOfLists));
            if (new_node == NULL) {
                ListOfLists *temp = result;
                while (temp != NULL) {
                    ListOfLists *next = temp->next;
                    free(temp);
                    temp = next;
                }
                return NULL;
            }
            new_node->list = curr->list;
            new_node->next = NULL;

            if (result == NULL) {
                result = new_node;
                tail = new_node;
            } else {
                tail->next = new_node;
                tail = new_node;
            }
        }
        curr = curr->next;
    }

    return result;
}

List *create_list(size_t length) {
    List *l = (List *)malloc(sizeof(List));
    if (l == NULL) {
        return NULL;
    }
    l->length = length;
    l->head = NULL;
    for (size_t i = 0; i < length; i++) {
        Node *n = (Node *)malloc(sizeof(Node));
        if (n == NULL) {
            Node *curr = l->head;
            while (curr != NULL) {
                Node *next = curr->next;
                free(curr);
                curr = next;
            }
            free(l);
            return NULL;
        }
        n->data = NULL;
        n->next = l->head;
        l->head = n;
    }
    return l;
}

void free_list(List *l) {
    if (l == NULL) {
        return;
    }
    Node *curr = l->head;
    while (curr != NULL) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    free(l);
}

void free_list_of_lists(ListOfLists *lol) {
    ListOfLists *curr = lol;
    while (curr != NULL) {
        ListOfLists *next = curr->next;
        free(curr);
        curr = next;
    }
}

int main(void) {
    List *l1 = create_list(5);
    List *l2 = create_list(2);
    List *l3 = create_list(3);
    List *l4 = create_list(2);

    if (l1 == NULL || l2 == NULL || l3 == NULL || l4 == NULL) {
        free_list(l1);
        free_list(l2);
        free_list(l3);
        free_list(l4);
        return 1;
    }

    ListOfLists *lol = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (lol == NULL) {
        free_list(l1);
        free_list(l2);
        free_list(l3);
        free_list(l4);
        return 1;
    }
    lol->list = l1;

    ListOfLists *lol2 = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (lol2 == NULL) {
        free_list(l1);
        free_list(l2);
        free_list(l3);
        free_list(l4);
        free(lol);
        return 1;
    }
    lol2->list = l2;
    lol->next = lol2;

    ListOfLists *lol3 = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (lol3 == NULL) {
        free_list(l1);
        free_list(l2);
        free_list(l3);
        free_list(l4);
        free(lol);
        free(lol2);
        return 1;
    }
    lol3->list = l3;
    lol2->next = lol3;

    ListOfLists *lol4 = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (lol4 == NULL) {
        free_list(l1);
        free_list(l2);
        free_list(l3);
        free_list(l4);
        free(lol);
        free(lol2);
        free(lol3);
        return 1;
    }
    lol4->list = l4;
    lol4->next = NULL;
    lol3->next = lol4;

    ListOfLists *min_lists = find_min_length_lists(lol);

    ListOfLists *curr = min_lists;
    while (curr != NULL) {
        printf("List with length: %zu\n", curr->list->length);
        curr = curr->next;
    }

    free_list_of_lists(min_lists);
    free_list_of_lists(lol);
    free_list(l1);
    free_list(l2);
    free_list(l3);
    free_list(l4);

    return 0;
}