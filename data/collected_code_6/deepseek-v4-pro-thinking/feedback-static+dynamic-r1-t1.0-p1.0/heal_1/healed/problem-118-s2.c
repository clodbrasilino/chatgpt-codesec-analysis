#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

typedef struct WordNode {
    Node *word;
    struct WordNode *next;
} WordNode;

Node *string_to_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;

    for (const char *p = str; *p != '\0'; ++p) {
        Node *new_node = malloc(sizeof(*new_node));
        if (new_node == NULL) {
            while (head != NULL) {
                Node *temp = head;
                head = head->next;
                free(temp);
            }
            return NULL;
        }

        new_node->data = *p;
        new_node->next = NULL;

        if (tail == NULL) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
    }

    return head;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

void print_list(const Node *head) {
    for (const Node *current = head; current != NULL; current = current->next) {
        putchar(current->data);
    }
}

WordNode *string_to_word_list(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    WordNode *head = NULL;
    WordNode *tail = NULL;
    const char *p = str;

    while (*p != '\0') {
        while (*p == ' ' || *p == '\t') {
            ++p;
        }
        if (*p == '\0') {
            break;
        }

        const char *start = p;
        while (*p != '\0' && *p != ' ' && *p != '\t') {
            ++p;
        }

        size_t len = p - start;
        char *word_str = malloc(len + 1);
        if (word_str == NULL) {
            while (head != NULL) {
                WordNode *temp = head;
                head = head->next;
                free_list(temp->word);
                free(temp);
            }
            return NULL;
        }
        memcpy(word_str, start, len);
        word_str[len] = '\0';

        Node *word_list = string_to_list(word_str);
        free(word_str);
        if (word_list == NULL) {
            while (head != NULL) {
                WordNode *temp = head;
                head = head->next;
                free_list(temp->word);
                free(temp);
            }
            return NULL;
        }

        WordNode *new_word = malloc(sizeof(*new_word));
        if (new_word == NULL) {
            free_list(word_list);
            while (head != NULL) {
                WordNode *temp = head;
                head = head->next;
                free_list(temp->word);
                free(temp);
            }
            return NULL;
        }

        new_word->word = word_list;
        new_word->next = NULL;

        if (tail == NULL) {
            head = new_word;
        } else {
            tail->next = new_word;
        }
        tail = new_word;
    }

    return head;
}

void free_word_list(WordNode *head) {
    while (head != NULL) {
        WordNode *temp = head;
        head = head->next;
        free_list(temp->word);
        free(temp);
    }
}

void print_word_list(const WordNode *head) {
    putchar('[');
    for (const WordNode *current = head; current != NULL; current = current->next) {
        putchar('\'');
        print_list(current->word);
        putchar('\'');
        if (current->next != NULL) {
            fputs(", ", stdout);
        }
    }
    puts("]");
}

int main(void) {
    char line[1024];

    if (fgets(line, sizeof(line), stdin) == NULL) {
        return 1;
    }

    line[strcspn(line, "\n")] = '\0';

    if (line[0] == '\0') {
        return 0;
    }

    WordNode *word_list = string_to_word_list(line);
    if (word_list != NULL) {
        print_word_list(word_list);
        free_word_list(word_list);
    }

    return 0;
}