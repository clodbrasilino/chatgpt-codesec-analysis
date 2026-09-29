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
    for (Node *current = head; current != NULL; current = current->next) {
        if (strcmp(current->word, word) == 0) {
            return 1;
        }
    }
    return 0;
}

void add_to_list(Node **head, char *word) {
    if (!is_word_in_list(*head, word)) {
        Node *new_node = create_node(word);
        new_node->next = *head;
        *head = new_node;
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

char** remove_duplicates(char **words, int count, int *new_count) {
    Node *unique_words = NULL;
    for (int i = 0; i < count; ++i) {
        add_to_list(&unique_words, words[i]);
    }

    *new_count = 0;
    char **result = NULL;
    for (Node *current = unique_words; current != NULL; current = current->next) {
        /* Possible weaknesses found:
         *  Common realloc mistake: 'result' nulled but not freed upon failure [memleakOnRealloc]
         */
        result = (char **)realloc(result, ((*new_count + 1) * sizeof(char *)));
        if (result == NULL) {
            free_list(unique_words);
            return NULL;
        }
        result[*new_count] = strdup(current->word);
        (*new_count)++;
    }

    free_list(unique_words);
    return result;
}

int main() {
    char *words[] = {"apple", "banana", "apple", "orange", "banana", "grape"};
    int count = 6;
    int new_count;

    char **result = remove_duplicates(words, count, &new_count);

    for (int i = 0; i < new_count; ++i) {
        printf("%s\n", result[i]);
    }

    for (int i = 0; i < new_count; ++i) {
        free(result[i]);
    }
    free(result);

    return 0;
}