#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *next;
};

struct dictionary {
    struct node *node;
};

long depth(struct node *node) {
    long depth = 0;
    while (node != NULL) {
        node = node->next;
        depth++;
    }
    return depth;
}

struct node* addNode(struct node* node) {
    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode -> next = node;
    return newNode;
}

void freeDictionary(struct dictionary* dict) {
    struct node* nextNode;
    while (dict -> node) {
        nextNode = dict -> node -> next;
        free(dict -> node);
        dict -> node = nextNode;
    }
    free(dict);
}

int main() {
    struct dictionary* dict = (struct dictionary*) malloc(sizeof(struct dictionary));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'dict' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    dict -> node = NULL;
    for (int i = 0; i < 10; i++)
        dict -> node = addNode(dict -> node);
    printf("Depth: %ld\n", depth(dict -> node));
    freeDictionary(dict);
    return 0;
}