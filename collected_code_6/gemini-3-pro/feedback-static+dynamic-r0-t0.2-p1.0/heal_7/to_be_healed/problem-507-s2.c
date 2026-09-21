#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *word;
    struct Node *next;
} Node;

Node* create_node(const char *word) {
    if (!word) return NULL;
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return NULL;
    
    size_t len = 0;
    while (len < 8192 && word[len] != '\0') {
        len++;
    }
    
    new_node->word = (char*)malloc(len + 1);
    if (!new_node->word) {
        free(new_node);
        return NULL;
    }
    
    snprintf(new_node->word, len + 1, "%s", word);
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current) {
        Node *next = current->next;
        free(current->word);
        free(current);
        current = next;
    }
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['red', 'green', 'blue', 'black'], got <no output>
  *  test case 1 failed: expected ['red', 'green', 'blue', 'white'], got <no output>
  *  test case 2 failed: expected ['red', 'green', 'black', 'orange'], got <no output>
  */

Node* remove_words(Node *head, const char **words_to_remove, int num_words_to_remove) {
    if (!head || !words_to_remove || num_words_to_remove <= 0) return head;

    Node dummy;
    dummy.next = head;
    Node *prev = &dummy;
    Node *current = head;

    while (current) {
        int should_remove = 0;
        if (current->word) {
            for (int i = 0; i < num_words_to_remove; ++i) {
                if (words_to_remove[i] && strcmp(current->word, words_to_remove[i]) == 0) {
                    should_remove = 1;
                    break;
                }
            }
        }

        if (should_remove) {
            prev->next = current->next;
            if (current->word) free(current->word);
            free(current);
            current = prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }

    return dummy.next;
}

void print_list(Node *head) {
    printf("[");
    Node *current = head;
    while (current) {
        if (current->word) {
            printf("'%s'", current->word);
        } else {
            printf("''");
        }
        if (current->next) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
    fflush(stdout);
}

int main(void) {
    Node *head = create_node("red");
    if (!head) return 1;
    
    head->next = create_node("green");
    if (!head->next) { free_list(head); return 1; }
    
    head->next->next = create_node("blue");
    if (!head->next->next) { free_list(head); return 1; }
    
    head->next->next->next = create_node("black");
    if (!head->next->next->next) { free_list(head); return 1; }

    const char *words_to_remove[] = {"yellow"};
    int num_words_to_remove = 1;

    head = remove_words(head, words_to_remove, num_words_to_remove);

    print_list(head);

    free_list(head);

    return 0;
}