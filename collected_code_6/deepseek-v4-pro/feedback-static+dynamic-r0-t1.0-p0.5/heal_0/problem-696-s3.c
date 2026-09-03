#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
    int size;
} List;

typedef struct ListOfLists {
    List **lists;
    int size;
} ListOfLists;

List *list_create(void) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

int list_append(List *list, void *data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return 0;
    }
    new_node->data = data;
    new_node->next = NULL;
    
    if (list->tail == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
    return 1;
}

void *list_get(List *list, int index) {
    if (list == NULL || index < 0 || index >= list->size) {
        return NULL;
    }
    
    Node *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

void list_destroy(List *list) {
    if (list == NULL) {
        return;
    }
    
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

ListOfLists *list_of_lists_create(void) {
    ListOfLists *lol = (ListOfLists *)malloc(sizeof(ListOfLists));
    if (lol == NULL) {
        return NULL;
    }
    lol->lists = NULL;
    lol->size = 0;
    return lol;
}

int list_of_lists_add(ListOfLists *lol, List *list) {
    List **new_lists = (List **)realloc(lol->lists, (lol->size + 1) * sizeof(List *));
    if (new_lists == NULL) {
        return 0;
    }
    lol->lists = new_lists;
    lol->lists[lol->size] = list;
    lol->size++;
    return 1;
}

void list_of_lists_destroy(ListOfLists *lol) {
    if (lol == NULL) {
        return;
    }
    
    for (int i = 0; i < lol->size; i++) {
        list_destroy(lol->lists[i]);
    }
    free(lol->lists);
    free(lol);
}

ListOfLists *zip_lists(ListOfLists *lol1, ListOfLists *lol2) {
    if (lol1 == NULL || lol2 == NULL) {
        return NULL;
    }
    
    int max_size = (lol1->size > lol2->size) ? lol1->size : lol2->size;
    ListOfLists *result = list_of_lists_create();
    if (result == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < max_size; i++) {
        List *zipped = list_create();
        if (zipped == NULL) {
            list_of_lists_destroy(result);
            return NULL;
        }
        
        if (i < lol1->size) {
            if (!list_append(zipped, lol1->lists[i])) {
                list_destroy(zipped);
                list_of_lists_destroy(result);
                return NULL;
            }
        }
        
        if (i < lol2->size) {
            if (!list_append(zipped, lol2->lists[i])) {
                list_destroy(zipped);
                list_of_lists_destroy(result);
                return NULL;
            }
        }
        
        if (!list_of_lists_add(result, zipped)) {
            list_destroy(zipped);
            list_of_lists_destroy(result);
            return NULL;
        }
    }
    
    return result;
}

void print_list_of_lists(ListOfLists *lol) {
    if (lol == NULL) {
        printf("NULL\n");
        return;
    }
    
    printf("[");
    for (int i = 0; i < lol->size; i++) {
        printf("[");
        List *list = lol->lists[i];
        for (int j = 0; j < list->size; j++) {
            List *inner = (List *)list_get(list, j);
            printf("[");
            for (int k = 0; k < inner->size; k++) {
                int *val = (int *)list_get(inner, k);
                printf("%d", *val);
                if (k < inner->size - 1) {
                    printf(", ");
                }
            }
            printf("]");
            if (j < list->size - 1) {
                printf(", ");
            }
        }
        printf("]");
        if (i < lol->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    ListOfLists *lol1 = list_of_lists_create();
    ListOfLists *lol2 = list_of_lists_create();
    
    List *list1 = list_create();
    int val1 = 1;
    list_append(list1, &val1);
    int val2 = 2;
    list_append(list1, &val2);
    list_of_lists_add(lol1, list1);
    
    List *list2 = list_create();
    int val3 = 3;
    list_append(list2, &val3);
    list_of_lists_add(lol1, list2);
    
    List *list3 = list_create();
    int val4 = 4;
    list_append(list3, &val4);
    int val5 = 5;
    list_append(list3, &val5);
    int val6 = 6;
    list_append(list3, &val6);
    list_of_lists_add(lol2, list3);
    
    List *list4 = list_create();
    int val7 = 7;
    list_append(list4, &val7);
    list_of_lists_add(lol2, list4);
    
    List *list5 = list_create();
    int val8 = 8;
    list_append(list5, &val8);
    int val9 = 9;
    list_append(list5, &val9);
    list_of_lists_add(lol2, list5);
    
    printf("List of lists 1: ");
    print_list_of_lists(lol1);
    printf("List of lists 2: ");
    print_list_of_lists(lol2);
    
    ListOfLists *zipped = zip_lists(lol1, lol2);
    printf("Zipped result: ");
    print_list_of_lists(zipped);
    
    list_of_lists_destroy(zipped);
    list_of_lists_destroy(lol1);
    list_of_lists_destroy(lol2);
    
    return 0;
}