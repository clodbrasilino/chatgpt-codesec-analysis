#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct Node {
    char *data;
    struct Node *next;
} Node;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  */

Node *string_to_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    if (str[0] == '\0') {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;
    size_t start = 0;
    size_t end = 0;

    while (1) {
        if (str[end] == ' ' || str[end] == '\0') {
            if (end > start) {
                size_t word_len = end - start;
                char *word = (char *)malloc(word_len + 1);
                if (word == NULL) {
                    Node *current = head;
                    while (current != NULL) {
                        Node *next = current->next;
                        free(current->data);
                        free(current);
                        current = next;
                    }
                    return NULL;
                }

                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(word, str + start, word_len);
                word[word_len] = '\0';

                Node *new_node = (Node *)malloc(sizeof(Node));
                if (new_node == NULL) {
                    free(word);
                    Node *current = head;
                    while (current != NULL) {
                        Node *next = current->next;
                        free(current->data);
                        free(current);
                        current = next;
                    }
                    return NULL;
                }

                new_node->data = word;
                new_node->next = NULL;

                if (head == NULL) {
                    head = new_node;
                    tail = new_node;
                } else {
                    tail->next = new_node;
                    tail = new_node;
                }
            }
            start = end + 1;
            if (str[end] == '\0') {
                break;
            }
        }
        end++;
    }

    return head;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int main(void) {
    const char *test_str = "Hello world from C";
    Node *list = string_to_list(test_str);

    if (list != NULL) {
        print_list(list);
        free_list(list);
    }

    return 0;
}