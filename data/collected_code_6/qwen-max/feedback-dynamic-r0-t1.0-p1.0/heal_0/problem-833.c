#include <stdio.h>
#include <stdlib.h>

typedef struct dictionary {
    char *key;
    int value;
    struct dictionary *next;
} Dictionary;

Dictionary* create_node(char *key, int value) {
    Dictionary *node = (Dictionary *)malloc(sizeof(Dictionary));
    node->key = key;
    node->value = value;
    node->next = NULL;
    return node;
}

Dictionary* insert(Dictionary *head, char *key, int value) {
    if (head == NULL) {
        return create_node(key, value);
    } else {
        Dictionary *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = create_node(key, value);
    }
    return head;
}

char** get_keys(Dictionary *head, int *keys_count) {
    *keys_count = 0;
    Dictionary *temp = head;
    char **keys = (char **)malloc(100 * sizeof(char *));
    while (temp != NULL) {
        keys[(*keys_count)++] = temp->key;
        temp = temp->next;
    }
    return keys;
}

void free_keys(char **keys, int keys_count) {
    for (int i = 0; i < keys_count; ++i) {
        free(keys[i]);
    }
    free(keys);
}

void free_dictionary(Dictionary *head) {
    Dictionary *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->key);
        free(temp);
    }
}

int main() {
    Dictionary *dict = NULL;
    dict = insert(dict, "one", 1);
    dict = insert(dict, "two", 2);
    dict = insert(dict, "three", 3);

    int keys_count;
    char **keys = get_keys(dict, &keys_count);

    for (int i = 0; i < keys_count; ++i) {
        printf("%s\n", keys[i]);
    }

    free_keys(keys, keys_count);
    free_dictionary(dict);

    return 0;
}