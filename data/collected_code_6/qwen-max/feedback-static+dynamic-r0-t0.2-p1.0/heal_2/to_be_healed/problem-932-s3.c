#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *word;
    struct Node *next;
} Node;

Node* create_node(char *word) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->word = strdup(word);
    new_node->next = NULL;
    return new_node;
}

int is_word_in_list(Node *head, char *word) {
    while (head != NULL) {
        if (strcmp(head->word, word) == 0) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

void add_to_list(Node **head, char *word) {
    if (*head == NULL || strcmp((*head)->word, word) > 0) {
        Node *new_node = create_node(word);
        new_node->next = *head;
        *head = new_node;
    } else {
        Node *current = *head;
        while (current->next != NULL && strcmp(current->next->word, word) < 0) {
            current = current->next;
        }
        if (current->next == NULL || strcmp(current->next->word, word) != 0) {
            Node *new_node = create_node(word);
            new_node->next = current->next;
            current->next = new_node;
        }
    }
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp->word);
        free(temp);
    }
}

void remove_duplicates(char **words, int count) {
    Node *list = NULL;
    for (int i = 0; i < count; i++) {
        if (!is_word_in_list(list, words[i])) {
            add_to_list(&list, words[i]);
        }
    }

    int index = 0;
    Node *current = list;
    while (current != NULL) {
        words[index++] = current->word;
        current = current->next;
    }
    for (int i = index; i < count; i++) {
        /* Possible weaknesses found:
         * ASan: BUS
         */
        free(words[i]);
        words[i] = NULL;
    }
    free_list(list);
}

int main() {
    char *words[] = {"apple", "banana", "apple", "orange", "banana", "grape"};
    int count = sizeof(words) / sizeof(words[0]);

    remove_duplicates(words, count);

    for (int i = 0; i < count; i++) {
        if (words[i] != NULL) {
            printf("%s\n", words[i]);
        }
    }

    for (int i = 0; i < count; i++) {
        if (words[i] != NULL) {
            free(words[i]);
        }
    }

    return 0;
}