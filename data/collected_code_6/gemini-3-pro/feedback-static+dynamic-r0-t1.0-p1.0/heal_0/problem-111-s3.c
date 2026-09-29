#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(List* list, int data) {
    if (!list) return;
    Node* newNode = createNode(data);
    if (!list->head) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void freeList(List* list) {
    if (!list) return;
    Node* current = list->head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

int contains(List* list, int value) {
    if (!list) return 0;
    Node* current = list->head;
    while (current) {
        if (current->data == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

List* findCommonElements(List** lists, int numLists) {
    if (!lists || numLists <= 0) return NULL;
    
    List* commonList = (List*)malloc(sizeof(List));
    if (!commonList) {
        exit(EXIT_FAILURE);
    }
    commonList->head = NULL;
    
    if (numLists == 1) {
        Node* current = lists[0]->head;
        while (current) {
            if (!contains(commonList, current->data)) {
                appendNode(commonList, current->data);
            }
            current = current->next;
        }
        return commonList;
    }

    Node* current = lists[0]->head;
    while (current) {
        int value = current->data;
        if (!contains(commonList, value)) {
            int isCommon = 1;
            for (int i = 1; i < numLists; i++) {
                if (!contains(lists[i], value)) {
                    isCommon = 0;
                    break;
                }
            }
            if (isCommon) {
                appendNode(commonList, value);
            }
        }
        current = current->next;
    }
    
    return commonList;
}

void printList(List* list) {
    if (!list) return;
    Node* current = list->head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    int numLists = 3;
    List** lists = (List**)malloc(numLists * sizeof(List*));
    if (!lists) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < numLists; i++) {
        lists[i] = (List*)malloc(sizeof(List));
        if (!lists[i]) {
            for (int j = 0; j < i; j++) {
                freeList(lists[j]);
                free(lists[j]);
            }
            free(lists);
            return EXIT_FAILURE;
        }
        lists[i]->head = NULL;
    }

    appendNode(lists[0], 1);
    appendNode(lists[0], 2);
    appendNode(lists[0], 3);
    appendNode(lists[0], 4);

    appendNode(lists[1], 2);
    appendNode(lists[1], 3);
    appendNode(lists[1], 5);

    appendNode(lists[2], 3);
    appendNode(lists[2], 2);
    appendNode(lists[2], 6);

    List* common = findCommonElements(lists, numLists);

    printList(common);

    for (int i = 0; i < numLists; i++) {
        freeList(lists[i]);
        free(lists[i]);
    }
    free(lists);

    if (common) {
        freeList(common);
        free(common);
    }

    return EXIT_SUCCESS;
}