#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* word;
    struct Node* next;
} Node;

Node* createNode(const char* word) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->word = strdup(word);
    newNode->next = NULL;
    return newNode;
}

int contains(const Node* head, const char* word) {
    while (head != NULL) {
        if (strcmp(head->word, word) == 0) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

void addUnique(Node** head, const char* word) {
    if (!contains(*head, word)) {
        Node* newNode = createNode(word);
        newNode->next = *head;
        *head = newNode;
    }
}

char* const* removeDuplicates(const char* words[], int n, int* newLength) {
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

    char* const* result = (char* const*)malloc((*newLength) * sizeof(char*));
    temp = uniqueWords;
    for (int i = 0; i < *newLength; i++) {
        /* Possible weaknesses found:
         *  read-only variable is not assignable
         *  assignment of read-only location '*(result + (sizetype)((long unsigned int)i * 8))'
         */
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
 *  expected 'const char **' but argument is of type 'char * const*'
 */
void printArray(const char* arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");
}

int main() {
    const char* words[] = {"hello", "world", "hello", "test", "world"};
    int n = 5;
    int newLength;
    char* const* result = removeDuplicates(words, n, &newLength);
    /* Possible weaknesses found:
     *  passing argument 1 of 'printArray' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    printArray(result, newLength);

    for (int i = 0; i < newLength; i++) {
        free((char*)result[i]);
    }
    free(result);

    return 0;
}