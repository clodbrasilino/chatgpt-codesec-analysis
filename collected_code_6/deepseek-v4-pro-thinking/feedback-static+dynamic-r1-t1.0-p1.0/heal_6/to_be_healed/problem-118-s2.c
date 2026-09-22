#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

typedef struct WordNode {
    Node *word;
    struct WordNode *next;
} WordNode;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['write', 'a', 'program'], got <no output>
  *  test case 1 failed: expected ['lists', 'tuples', 'strings'], got <no output>
  *  test case 0 failed: expected ['python', 'programming'], got ["
  */

Node *string_to_list(const char *str) {
    Node *head = NULL;
    Node *tail = NULL;

    if (str == NULL) return NULL;

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
        if (tail == NULL)
            head = new_node;
        else
            tail->next = new_node;
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
    for (const Node *cur = head; cur != NULL; cur = cur->next)
        putchar(cur->data);
}

WordNode *string_to_word_list(const char *str) {
    WordNode *head = NULL;
    WordNode *tail = NULL;

    if (str == NULL) return NULL;

    const char *p = str;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;

        const char *start = p;
        while (*p != '\0' && *p != ' ' && *p != '\t') ++p;

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
        for (size_t i = 0; i < len; ++i)
            word_str[i] = start[i];
        word_str[len] = '\0';

        Node *word = string_to_list(word_str);
        free(word_str);
        if (word == NULL) {
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
            free_list(word);
            while (head != NULL) {
                WordNode *temp = head;
                head = head->next;
                free_list(temp->word);
                free(temp);
            }
            return NULL;
        }

        new_word->word = word;
        new_word->next = NULL;
        if (tail == NULL)
            head = new_word;
        else
            tail->next = new_word;
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
    for (const WordNode *cur = head; cur != NULL; cur = cur->next) {
        putchar('\'');
        print_list(cur->word);
        putchar('\'');
        if (cur->next != NULL)
            fputs(", ", stdout);
    }
    puts("]");
}

char *read_line(FILE *fp) {
    size_t size = 128;
    size_t len = 0;
    char *buf = malloc(size);
    if (buf == NULL) return NULL;

    int c;
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(fp)) != EOF && c != '\n') {
        if (len + 1 >= size) {
            size_t new_size = size * 2;
            char *tmp = realloc(buf, new_size);
            if (tmp == NULL) {
                free(buf);
                return NULL;
            }
            buf = tmp;
            size = new_size;
        }
        buf[len++] = (char)c;
    }

    if (c == EOF && len == 0) {
        free(buf);
        return NULL;
    }

    buf[len] = '\0';

    if (len > 0 && buf[len - 1] == '\r') {
        buf[len - 1] = '\0';
    }

    return buf;
}

int main(void) {
    char *line = read_line(stdin);
    if (line == NULL)
        return 1;
    if (line[0] == '\0') {
        free(line);
        return 0;
    }

    WordNode *words = string_to_word_list(line);
    free(line);

    if (words != NULL) {
        print_word_list(words);
        free_word_list(words);
    }
    return 0;
}