#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

typedef struct Dictionary {
    Node* head;
} Dictionary;

Dictionary* createDictionary() {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    dict->head = NULL;
    return dict;
}

int insert(Dictionary* dict, int key, int value) {
    if (!dict) {
        return 0;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        return 0;
    }
    newNode->key = key;
    newNode->value = value;
    newNode->next = dict->head;
    dict->head = newNode;
    return 1;
}

long long sumDictionaryValues(const Dictionary* dict) {
    long long sum = 0;
    if (!dict) {
        return sum;
    }
    Node* current = dict->head;
    while (current != NULL) {
        sum += current->value;
        current = current->next;
    }
    return sum;
}

void freeDictionary(Dictionary* dict) {
    if (!dict) {
        return;
    }
    Node* current = dict->head;
    Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    free(dict);
}

int main() {
    Dictionary* dict = createDictionary();
    if (!dict) {
        fprintf(stderr, "Failed to create dictionary\n");
        return EXIT_FAILURE;
    }

    if (!insert(dict, 1, 10) || !insert(dict, 2, 20) || !insert(dict, 3, 30)) {
        fprintf(stderr, "Failed to insert items\n");
        freeDictionary(dict);
        return EXIT_FAILURE;
    }

    long long totalSum = sumDictionaryValues(dict);
    printf("%lld\n", totalSum);

    freeDictionary(dict);
    return EXIT_SUCCESS;
}