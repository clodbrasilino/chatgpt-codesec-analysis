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
    return l;
}

ListOfLists *create_list_of_lists(List *l) {
    ListOfLists *lol = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (lol == NULL) {
        return NULL;
    }
    lol->list = l;
    lol->next = NULL;
    return lol;
}

void free_list_of_lists(ListOfLists *lol) {
    ListOfLists *curr = lol;
    while (curr != NULL) {
        ListOfLists *next = curr->next;
        free(curr);
        curr = next;
    }
}

void free_list(List *l) {
    if (l != NULL) {
        Node *curr = l->head;
        while (curr != NULL) {
            Node *next = curr->next;
            free(curr->data);
            free(curr);
            curr = next;
        }
        free(l);
    }
}

int main(void) {
    List *l1 = create_list(5);
    List *l2 = create_list(2);
    List *l3 = create_list(5);
    List *l4 = create_list(2);

    if (l1 == NULL || l2 == NULL || l3 == NULL || l4 == NULL) {
        free_list(l1);
        free_list(l2);
        free_list(l3);
        free_list(l4);
        return 1;
    }

    ListOfLists *lol1 = create_list_of_lists(l1);
    ListOfLists *lol2 = create_list_of_lists(l2);
    ListOfLists *lol3 = create_list_of_lists(l3);
    ListOfLists *lol4 = create_list_of_lists(l4);

    if (lol1 == NULL || lol2 == NULL || lol3 == NULL || lol4 == NULL) {
        free_list_of_lists(lol1);
        free_list_of_lists(lol2);
        free_list_of_lists(lol3);
        free_list_of_lists(lol4);
        free_list(l1);
        free_list(l2);
        free_list(l3);
        free_list(l4);
        return 1;
    }

    lol1->next = lol2;
    lol2->next = lol3;
    lol3->next = lol4;

    ListOfLists *min_lists = find_min_length_lists(lol1);

    ListOfLists *curr = min_lists;
    while (curr != NULL) {
        printf("List with length: %zu\n", curr->list->length);
        curr = curr->next;
    }

    free_list_of_lists(min_lists);
    free_list_of_lists(lol1);
    free_list(l1);
    free_list(l2);
    free_list(l3);
    free_list(l4);

    return 0;
}