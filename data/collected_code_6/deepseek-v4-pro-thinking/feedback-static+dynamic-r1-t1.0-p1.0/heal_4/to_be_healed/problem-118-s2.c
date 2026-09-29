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
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['python', 'programming'], got <no output>
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  */

Node *string_to_list(const char *str) {
    Node *head = NULL;
    Node *tail = NULL;
    const char *p;

    if (str == NULL) {
        return NULL;
    }

    for (p = str; *p != '\0'; ++p) {
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
    const Node *current;
    for (current = head; current != NULL; current = current->next) {
        putchar(current->data);
    }
}

WordNode *string_to_word_list(const char *str) {
    WordNode *head = NULL;
    WordNode *tail = NULL;
    const char *p;

    if (str == NULL) {
        return NULL;
    }

    p = str;
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

        for (size_t i = 0; i < len; ++i) {
            word_str[i] = start[i];
        }
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
    const WordNode *current;

    putchar('[');
    for (current = head; current != NULL; current = current->next) {
        putchar('\'');
        print_list(current->word);
        putchar('\'');
        if (current->next != NULL) {
            fputs(", ", stdout);
        }
    }
    puts("]");
}

char *read_line(FILE *fp) {
    size_t size = 128;
    size_t len = 0;
    char *buffer = malloc(size);
    if (buffer == NULL) {
        return NULL;
    }

    while (1) {
        if (fgets(buffer + len, size - len, fp) == NULL) {
            if (len == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t new_len = len + strlen(buffer + len);
        if (new_len > 0 && buffer[new_len - 1] == '\n') {
            buffer[new_len - 1] = '\0';
            if (new_len > 1 && buffer[new_len - 2] == '\r') {
                buffer[new_len - 2] = '\0';
            }
            return buffer;
        }

        len = new_len;
        size_t new_size = size * 2;
        char *tmp = realloc(buffer, new_size);
        if (tmp == NULL) {
            free(buffer);
            return NULL;
        }
        buffer = tmp;
        size = new_size;
    }

    return buffer;
}

int main(void) {
    char *line;
    WordNode *word_list;

    line = read_line(stdin);
    if (line == NULL) {
        return 1;
    }

    if (line[0] == '\0') {
        free(line);
        return 0;
    }

    word_list = string_to_word_list(line);
    free(line);

    if (word_list != NULL) {
        print_word_list(word_list);
        free_word_list(word_list);
    }

    return 0;
}