#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    char *key;
    struct Node *value;
    struct Node *next;
} Node;

typedef struct Dictionary {
    Node *head;
} Dictionary;

Dictionary *createDictionary() {
    Dictionary *dict = (Dictionary *)malloc(sizeof(Dictionary));
    if (dict) dict->head = NULL;
    return dict;
}

Node *createNode(char *key, Node *value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node) {
        node->key = key ? strdup(key) : NULL;
        node->value = value;
        node->next = NULL;
    }
    return node;
}

void addEntry(Dictionary *dict, const char *key, Node *value) {
    Node *newNode = createNode(strdup(key), value);
    if (newNode) {
        newNode->next = dict->head;
        dict->head = newNode;
    }
}

Node *findEntry(Dictionary *dict, const char *key) {
    for (Node *curr = dict->head; curr; curr = curr->next) {
        if (strcmp(curr->key, key) == 0) return curr;
    }
    return NULL;
}

void freeDictionary(Dictionary *dict) {
    while (dict->head) {
        Node *temp = dict->head;
        dict->head = dict->head->next;
        if (temp->key) free(temp->key);
        /* Possible weaknesses found:
         *  implicit declaration of function 'isList' [-Wimplicit-function-declaration]
         *  previous implicit declaration of 'isList' with type 'int()'
         *  call to undeclared function 'isList'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  previous implicit declaration is here
         */
        if (temp->value && isList(temp)) {
            freeDictionary((Dictionary *)temp->value);
        } else if (temp->value) {
            free(temp->value);
        }
        free(temp);
    }
    free(dict);
}

/* Possible weaknesses found:
 *  conflicting types for 'isList'; have '_Bool(const Node *)'
 *  conflicting types for 'isList'
 */
bool isList(const Node *node) {
    return node && node->key == NULL;
}

void printDictionary(Dictionary *dict, int level) {
    for (int i = 0; i < level; i++) printf("  ");
    for (Node *curr = dict->head; curr; curr = curr->next) {
        if (isList(curr)) {
            printf("[\n");
            printDictionary((Dictionary *)curr->value, level + 1);
            for (int i = 0; i < level; i++) printf("  ");
            printf("]\n");
        } else {
            printf("%s: ", curr->key);
            if (isList(curr->value)) {
                printf("[\n");
                printDictionary((Dictionary *)curr->value, level + 1);
                for (int i = 0; i < level; i++) printf("  ");
                printf("]\n");
            } else {
                printf("{\n");
                printDictionary((Dictionary *)curr->value, level + 1);
                for (int i = 0; i < level; i++) printf("  ");
                printf("}\n");
            }
        }
    }
}

void convertListsToNestedDictionary(const char ***lists, const int *sizes, int listCount, Dictionary *dict) {
    for (int i = 0; i < listCount; ++i) {
        if (sizes[i] % 2 != 0) continue;
        Dictionary *subDict = createDictionary();
        for (int j = 0; j < sizes[i]; j += 2) {
            const char *key = lists[i][j];
            Node *value = (j + 1 < sizes[i]) ? createNode(NULL, NULL) : NULL;
            if (key && value) addEntry(subDict, key, value);
        }
        if (subDict) addEntry(dict, "list", (Node *)subDict);
    }
}

int main() {
    const char *list1[] = {"a", "b", "c", "d"};
    const char *list2[] = {"e", "f", "g", "h"};
    const char *list3[] = {"i", "j", "k", "l"};

    /* Possible weaknesses found:
     *  The scope of the variable 'lists' can be reduced. [variableScope]
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char **lists[3] = {list1, list2, list3};
    const int sizes[3] = {4, 4, 4};

    Dictionary *rootDict = createDictionary();
    if (rootDict) {
        convertListsToNestedDictionary(lists, sizes, 3, rootDict);
        printDictionary(rootDict, 0);
        freeDictionary(rootDict);
    }
    return 0;
}