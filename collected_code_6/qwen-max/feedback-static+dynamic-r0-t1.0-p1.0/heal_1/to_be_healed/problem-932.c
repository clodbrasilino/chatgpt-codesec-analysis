#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* word;
    struct Node* next;
} Node;

Node* createNode(char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->word = strdup(word);
    newNode->next = NULL;
    return newNode;
}

int contains(Node* head, char* word) {
    while (head != NULL) {
        if (strcmp(head->word, word) == 0) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

void addUnique(Node** head, char* word) {
    if (!contains(*head, word)) {
        Node* newNode = createNode(word);
        newNode->next = *head;
        *head = newNode;
    }
}

char** removeDuplicates(char* words[], int n, int* newLength) {
    Node* uniqueWords = NULL;
    for (int i = 0; i < n; i++) {
        addUnique(&uniqueWords, words[i]);
    }

    *newLength = 0;
    Node* temp = uniqueWords;
    while (temp != NULL) {
        (*newLength)++;
        temp = temp->next;
    }

    char** result = (char**)malloc((*newLength) * sizeof(char*));
    temp = uniqueWords;
    for (int i = 0; i < *newLength; i++) {
        result[i] = temp->word;
        temp = temp->next;
    }

    temp = uniqueWords;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
void printArray(char* arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");
}

int main() {
    char* words[] = {"hello", "world", "hello", "test", "world"};
    int n = 5;
    int newLength;
    char** result = removeDuplicates(words, n, &newLength);
    printArray(result, newLength);

    for (int i = 0; i < newLength; i++) {
        free(result[i]);
    }
    free(result);

    return 0;
}