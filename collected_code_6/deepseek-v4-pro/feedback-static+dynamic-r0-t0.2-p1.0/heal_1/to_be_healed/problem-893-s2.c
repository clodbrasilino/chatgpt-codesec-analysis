#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Sublist {
    Node* head;
    struct Sublist* next;
} Sublist;

int* get_last_elements(Sublist* sublists, int* count) {
    /* Possible weaknesses found:
     *  Assuming that condition 'count==NULL' is not redundant
     */
    if (sublists == NULL || count == NULL) {
        /* Possible weaknesses found:
         *  Null pointer dereference
         *  Either the condition 'count==NULL' is redundant or there is possible null pointer dereference: count. [nullPointerRedundantCheck]
         */
        *count = 0;
        return NULL;
    }

    int num_sublists = 0;
    Sublist* current_sublist = sublists;
    while (current_sublist != NULL) {
        num_sublists++;
        current_sublist = current_sublist->next;
    }

    int* result = (int*)malloc(num_sublists * sizeof(int));
    if (result == NULL) {
        *count = 0;
        return NULL;
    }

    current_sublist = sublists;
    int index = 0;
    while (current_sublist != NULL) {
        if (current_sublist->head == NULL) {
            free(result);
            *count = 0;
            return NULL;
        }

        Node* current_node = current_sublist->head;
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        result[index++] = current_node->data;
        current_sublist = current_sublist->next;
    }

    *count = num_sublists;
    return result;
}

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

/* Possible weaknesses found:
 *  Parameter 'values' can be declared as pointer to const [constParameterPointer]
 */
Sublist* create_sublist(int* values, int size) {
    if (values == NULL || size <= 0) {
        return NULL;
    }

    Sublist* sublist = (Sublist*)malloc(sizeof(Sublist));
    if (sublist == NULL) {
        return NULL;
    }

    sublist->head = NULL;
    sublist->next = NULL;

    Node* current = NULL;
    for (int i = 0; i < size; i++) {
        Node* new_node = create_node(values[i]);
        if (new_node == NULL) {
            Node* temp = sublist->head;
            while (temp != NULL) {
                Node* next = temp->next;
                free(temp);
                temp = next;
            }
            free(sublist);
            return NULL;
        }

        if (sublist->head == NULL) {
            sublist->head = new_node;
            current = new_node;
        } else {
            current->next = new_node;
            current = new_node;
        }
    }

    return sublist;
}

void free_sublists(Sublist* sublists) {
    while (sublists != NULL) {
        Sublist* next_sublist = sublists->next;
        Node* current = sublists->head;
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
        free(sublists);
        sublists = next_sublist;
    }
}

int main() {
    int values1[] = {1, 2, 3};
    int values2[] = {4, 5};
    int values3[] = {6, 7, 8, 9};

    Sublist* sublist1 = create_sublist(values1, 3);
    Sublist* sublist2 = create_sublist(values2, 2);
    Sublist* sublist3 = create_sublist(values3, 4);

    if (sublist1 == NULL || sublist2 == NULL || sublist3 == NULL) {
        free_sublists(sublist1);
        free_sublists(sublist2);
        free_sublists(sublist3);
        return 1;
    }

    sublist1->next = sublist2;
    sublist2->next = sublist3;

    int count = 0;
    int* last_elements = get_last_elements(sublist1, &count);

    if (last_elements != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%d ", last_elements[i]);
        }
        printf("\n");
        free(last_elements);
    }

    free_sublists(sublist1);
    return 0;
}