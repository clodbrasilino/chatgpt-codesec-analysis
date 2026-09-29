#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    int size;
} List;

typedef struct Pair {
    List* first;
    List* second;
} Pair;

typedef struct ZipResult {
    Pair* pairs;
    int size;
} ZipResult;

Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

List* create_list(const int* arr, int size) {
    List* list = (List*)malloc(sizeof(List));
    if (!list) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    
    if (size == 0) {
        return list;
    }
    
    Node* current = NULL;
    for (int i = 0; i < size; i++) {
        Node* node = create_node(arr[i]);
        if (!node) {
            Node* temp = list->head;
            while (temp) {
                Node* next = temp->next;
                free(temp);
                temp = next;
            }
            free(list);
            return NULL;
        }
        if (!list->head) {
            list->head = node;
            current = node;
        } else {
            current->next = node;
            current = node;
        }
        list->size++;
    }
    return list;
}

void free_list(List* list) {
    if (!list) {
        return;
    }
    Node* current = list->head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

List* copy_list(const List* source) {
    if (!source) {
        return NULL;
    }
    List* copy = (List*)malloc(sizeof(List));
    if (!copy) {
        return NULL;
    }
    copy->head = NULL;
    copy->size = 0;
    
    Node* current = source->head;
    Node* copy_current = NULL;
    while (current) {
        Node* node = create_node(current->data);
        if (!node) {
            free_list(copy);
            return NULL;
        }
        if (!copy->head) {
            copy->head = node;
            copy_current = node;
        } else {
            copy_current->next = node;
            copy_current = node;
        }
        copy->size++;
        current = current->next;
    }
    return copy;
}

ZipResult* zip_lists(List** lists1, int size1, List** lists2, int size2) {
    if (!lists1 || !lists2 || size1 <= 0 || size2 <= 0) {
        return NULL;
    }
    
    int min_size = size1 < size2 ? size1 : size2;
    
    ZipResult* result = (ZipResult*)malloc(sizeof(ZipResult));
    if (!result) {
        return NULL;
    }
    
    result->pairs = (Pair*)malloc(sizeof(Pair) * min_size);
    if (!result->pairs) {
        free(result);
        return NULL;
    }
    result->size = min_size;
    
    for (int i = 0; i < min_size; i++) {
        result->pairs[i].first = copy_list(lists1[i]);
        result->pairs[i].second = copy_list(lists2[i]);
        
        if (!result->pairs[i].first || !result->pairs[i].second) {
            for (int j = 0; j <= i; j++) {
                free_list(result->pairs[j].first);
                free_list(result->pairs[j].second);
            }
            free(result->pairs);
            free(result);
            return NULL;
        }
    }
    
    return result;
}

void free_zip_result(ZipResult* result) {
    if (!result) {
        return;
    }
    for (int i = 0; i < result->size; i++) {
        free_list(result->pairs[i].first);
        free_list(result->pairs[i].second);
    }
    free(result->pairs);
    free(result);
}

void print_list(const List* list) {
    if (!list) {
        printf("NULL");
        return;
    }
    Node* current = list->head;
    printf("[");
    while (current) {
        printf("%d", current->data);
        if (current->next) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]");
}

void print_zip_result(const ZipResult* result) {
    if (!result) {
        printf("NULL\n");
        return;
    }
    printf("[\n");
    for (int i = 0; i < result->size; i++) {
        printf("  (");
        print_list(result->pairs[i].first);
        printf(", ");
        print_list(result->pairs[i].second);
        printf(")");
        if (i < result->size - 1) {
            printf(",");
        }
        printf("\n");
    }
    printf("]\n");
}

int main() {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5};
    int arr3[] = {6, 7, 8, 9};
    int arr4[] = {10, 11};
    int arr5[] = {12, 13, 14};
    int arr6[] = {15, 16, 17, 18, 19};
    
    List* list1 = create_list(arr1, 3);
    List* list2 = create_list(arr2, 2);
    List* list3 = create_list(arr3, 4);
    List* list4 = create_list(arr4, 2);
    List* list5 = create_list(arr5, 3);
    List* list6 = create_list(arr6, 5);
    
    if (!list1 || !list2 || !list3 || !list4 || !list5 || !list6) {
        free_list(list1);
        free_list(list2);
        free_list(list3);
        free_list(list4);
        free_list(list5);
        free_list(list6);
        return 1;
    }
    
    List* lists1[] = {list1, list2, list3};
    List* lists2[] = {list4, list5, list6};
    
    ZipResult* result = zip_lists(lists1, 3, lists2, 3);
    
    printf("Zipped result:\n");
    print_zip_result(result);
    
    free_zip_result(result);
    free_list(list1);
    free_list(list2);
    free_list(list3);
    free_list(list4);
    free_list(list5);
    free_list(list6);
    
    return 0;
}