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

typedef struct ZipResult {
    List **lists;
    size_t count;
} ZipResult;

List *list_create(void) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->length = 0;
    return list;
}

int list_append(List *list, void *data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->data = data;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->length++;
    return 0;
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

void list_destroy_deep(List *list) {
    if (list == NULL) {
        return;
    }
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        list_destroy((List *)current->data);
        free(current);
        current = next;
    }
    free(list);
}

ZipResult *zip_lists(List *list1, List *list2) {
    if (list1 == NULL || list2 == NULL) {
        return NULL;
    }
    
    size_t min_length = list1->length < list2->length ? list1->length : list2->length;
    
    ZipResult *result = (ZipResult *)malloc(sizeof(ZipResult));
    if (result == NULL) {
        return NULL;
    }
    
    result->lists = (List **)malloc(min_length * sizeof(List *));
    if (result->lists == NULL) {
        free(result);
        return NULL;
    }
    result->count = min_length;
    
    Node *node1 = list1->head;
    Node *node2 = list2->head;
    
    for (size_t i = 0; i < min_length; i++) {
        List *pair = list_create();
        if (pair == NULL) {
            for (size_t j = 0; j < i; j++) {
                list_destroy(result->lists[j]);
            }
            free(result->lists);
            free(result);
            return NULL;
        }
        
        if (list_append(pair, node1->data) != 0) {
            list_destroy(pair);
            for (size_t j = 0; j < i; j++) {
                list_destroy(result->lists[j]);
            }
            free(result->lists);
            free(result);
            return NULL;
        }
        
        if (list_append(pair, node2->data) != 0) {
            list_destroy(pair);
            for (size_t j = 0; j < i; j++) {
                list_destroy(result->lists[j]);
            }
            free(result->lists);
            free(result);
            return NULL;
        }
        
        result->lists[i] = pair;
        node1 = node1->next;
        node2 = node2->next;
    }
    
    return result;
}

void zip_result_destroy(ZipResult *result) {
    if (result == NULL) {
        return;
    }
    for (size_t i = 0; i < result->count; i++) {
        list_destroy(result->lists[i]);
    }
    free(result->lists);
    free(result);
}

int main(void) {
    List *list1 = list_create();
    List *list2 = list_create();
    
    if (list1 == NULL || list2 == NULL) {
        list_destroy(list1);
        list_destroy(list2);
        return 1;
    }
    
    int data1[] = {1, 2, 3};
    int data2[] = {10, 20, 30, 40};
    
    for (int i = 0; i < 3; i++) {
        if (list_append(list1, &data1[i]) != 0) {
            list_destroy(list1);
            list_destroy(list2);
            return 1;
        }
    }
    
    for (int i = 0; i < 4; i++) {
        if (list_append(list2, &data2[i]) != 0) {
            list_destroy(list1);
            list_destroy(list2);
            return 1;
        }
    }
    
    ZipResult *zipped = zip_lists(list1, list2);
    if (zipped == NULL) {
        list_destroy(list1);
        list_destroy(list2);
        return 1;
    }
    
    for (size_t i = 0; i < zipped->count; i++) {
        Node *node = zipped->lists[i]->head;
        printf("[");
        while (node != NULL) {
            printf("%d", *(int *)node->data);
            if (node->next != NULL) {
                printf(", ");
            }
            node = node->next;
        }
        printf("]\n");
    }
    
    zip_result_destroy(zipped);
    list_destroy(list1);
    list_destroy(list2);
    
    return 0;
}