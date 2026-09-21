#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 4096

typedef struct Node {
    char *str;
    struct Node *next;
} Node;

static size_t safe_str_len(const char *str, size_t maxlen)
{
    const char *end;
    if (str == NULL) {
        return 0;
    }
    end = memchr(str, '\0', maxlen);
    if (end == NULL) {
        return maxlen;
    }
    return (size_t)(end - str);
}

Node *new_node(const char *str)
{
    Node *node;
    size_t len;

    if (str == NULL) {
        return NULL;
    }

    len = safe_str_len(str, MAX_STRING_LENGTH);
    if (len == MAX_STRING_LENGTH) {
        return NULL;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }

    node->str = malloc(len + 1);
    if (node->str == NULL) {
        free(node);
        return NULL;
    }

    strncpy(node->str, str, len + 1);
    node->str[len] = '\0';
    node->next = NULL;
    return node;
}

void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head->str);
        free(head);
        head = next;
    }
}

int convert_to_floats(Node *head, float **out, size_t *count)
{
    size_t capacity = 0;
    size_t used = 0;
    float *result = NULL;
    Node *current;

    if (out == NULL || count == NULL) {
        return -1;
    }

    *out = NULL;
    *count = 0;

    current = head;
    while (current != NULL) {
        if (current->str != NULL) {
            char *end = NULL;
            float value;

            errno = 0;
            value = strtof(current->str, &end);

            if (end != current->str) {
                while (*end != '\0' && isspace((unsigned char)*end)) {
                    end++;
                }

                if (*end == '\0' &&
                    (errno != ERANGE ||
                     (value != HUGE_VALF && value != -HUGE_VALF))) {
                    if (used == capacity) {
                        size_t new_capacity = capacity == 0 ? 8 : capacity * 2;
                        float *temp = realloc(result, new_capacity * sizeof(*temp));

                        if (temp == NULL) {
                            free(result);
                            return -1;
                        }

                        result = temp;
                        capacity = new_capacity;
                    }

                    result[used] = value;
                    used++;
                }
            }
        }

        current = current->next;
    }

    *out = result;
    *count = used;
    return 0;
}

int main(void)
{
    const char *items[] = {
        "3.14", "abc", " 2.5 ", "1e3", "", "17",
        "foo", "0.001", "1e-50", "1e1000"
    };
    size_t item_count = sizeof(items) / sizeof(items[0]);
    Node *head = NULL;
    Node *tail = NULL;
    float *floats = NULL;
    size_t count = 0;
    size_t i;

    for (i = 0; i < item_count; i++) {
        Node *node = new_node(items[i]);

        if (node == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(head);
            return EXIT_FAILURE;
        }

        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    if (convert_to_floats(head, &floats, &count) != 0) {
        fprintf(stderr, "Conversion failed\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        printf("%.6f\n", floats[i]);
    }

    free(floats);
    free_list(head);
    return EXIT_SUCCESS;
}