#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} RLEElement;

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* decodeRLE(RLEElement* rleList, size_t size) {
    if (rleList == NULL || size == 0) {
        return NULL;
    }

    Node* head = NULL;
    Node* tail = NULL;

    for (size_t i = 0; i < size; ++i) {
        if (rleList[i].count < 0) {
            continue;
        }

        int count = rleList[i].count == 0 ? 1 : rleList[i].count;

        for (int j = 0; j < count; ++j) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            if (newNode == NULL) {
                Node* current = head;
                while (current != NULL) {
                    Node* temp = current;
                    current = current->next;
                    free(temp);
                }
                return NULL;
            }

            newNode->value = rleList[i].value;
            newNode->next = NULL;

            if (head == NULL) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }

    return head;
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    RLEElement encoded[] = {
        {1, 3},
        {5, 0},
        {7, 2}
    };
    size_t size = sizeof(encoded) / sizeof(encoded[0]);

    Node* decodedInfo = decodeRLE(encoded, size);

    if (decodedInfo != NULL) {
        printList(decodedInfo);
        freeList(decodedInfo);
    } else {
        printf("Failed to decode or empty list.\n");
    }

    return 0;
}