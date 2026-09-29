#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct KeyValueNode {
    char *key;
    char *value;
    struct KeyValueNode *next;
} KeyValueNode;

KeyValueNode* merge_dicts(KeyValueNode* dict1, KeyValueNode* dict2) {
    if (dict1 == NULL) return dict2;
    if (dict2 == NULL) return dict1;
    
    KeyValueNode *last = dict1;
    
    while (last->next != NULL) {
        last = last->next;
    }

    last->next = dict2;

    return dict1;
}

void print_dict(KeyValueNode *dict) {
    KeyValueNode *node = dict;
    while (node != NULL) {
        printf("%s: %s\n", node->key, node->value);
        node = node->next;
    }
}

KeyValueNode* make_node(char* key, char* value) {
    KeyValueNode* node = (KeyValueNode*)malloc(sizeof(KeyValueNode));

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    node->key = (char *)malloc(strlen(key) + 1);
    strcpy(node->key, key);

    node->value = (char *)malloc(strlen(value) + 1);
    strcpy(node->value, value);

    node->next = NULL;
    return node;
}

int main() {
    KeyValueNode* dict1 = make_node("a", "1");
    dict1->next = make_node("b", "2");
    
    KeyValueNode* dict2 = make_node("c", "3");
    dict2->next = make_node("d", "4");

    KeyValueNode* merged_dict = merge_dicts(dict1, dict2);

    print_dict(merged_dict);

    // Free memory
    KeyValueNode *node = merged_dict;
    KeyValueNode *tmp;
    while (node != NULL)
    {
        tmp = node;
        node = node->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }

    return 0;
}