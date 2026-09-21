#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 256
#define HASH_SIZE 10007

typedef struct WordNode {
    char *word;
    int count;
    struct WordNode *next;
} WordNode;

typedef struct {
    WordNode *buckets[HASH_SIZE];
} HashTable;

unsigned int hash(const char *word) {
    unsigned int hashValue = 0;
    while (*word) {
        hashValue = (hashValue << 5) + *word++;
    }
    return hashValue % HASH_SIZE;
}

HashTable* createTable(void) {
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) return NULL;
    for (int i = 0; i < HASH_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

int insertWord(HashTable *table, const char *word) {
    if (!table || !word) return 0;
    unsigned int index = hash(word);
    WordNode *node = table->buckets[index];

    while (node) {
        if (strcmp(node->word, word) == 0) {
            node->count++;
            return 1;
        }
        node = node->next;
    }

    WordNode *newNode = (WordNode*)malloc(sizeof(WordNode));
    if (!newNode) return 0;
    
    size_t len = 0;
    const char *temp = word;
    while (*temp++) {
        len++;
    }
    
    newNode->word = (char*)malloc(len + 1);
    if (!newNode->word) {
        free(newNode);
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(newNode->word, word, len + 1);
    
    newNode->count = 1;
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
    return 1;
}

void freeTable(HashTable *table) {
    if (!table) return;
    for (int i = 0; i < HASH_SIZE; i++) {
        WordNode *node = table->buckets[i];
        while (node) {
            WordNode *temp = node;
            node = node->next;
            free(temp->word);
            free(temp);
        }
    }
    free(table);
}

void strToLower(char *str) {
    if (!str) return;
    for (; *str; ++str) {
        *str = tolower((unsigned char)*str);
    }
}

int compareNodes(const void *a, const void *b) {
    const WordNode *nodeA = *(const WordNode **)a;
    const WordNode *nodeB = *(const WordNode **)b;
    return nodeB->count - nodeA->count;
}

void findMostCommonWords(HashTable *table, int limit) {
    if (!table || limit <= 0) return;

    WordNode **allNodes = NULL;
    int nodeCount = 0;
    int capacity = 1024;

    allNodes = (WordNode**)malloc(capacity * sizeof(WordNode*));
    if (!allNodes) return;

    for (int i = 0; i < HASH_SIZE; i++) {
        WordNode *node = table->buckets[i];
        while (node) {
            if (nodeCount >= capacity) {
                capacity *= 2;
                WordNode **newNodes = (WordNode**)realloc(allNodes, capacity * sizeof(WordNode*));
                if (!newNodes) {
                    free(allNodes);
                    return;
                }
                allNodes = newNodes;
            }
            allNodes[nodeCount++] = node;
            node = node->next;
        }
    }

    qsort(allNodes, nodeCount, sizeof(WordNode*), compareNodes);

    int printCount = (limit < nodeCount) ? limit : nodeCount;
    for (int i = 0; i < printCount; i++) {
        printf("%s: %d\n", allNodes[i]->word, allNodes[i]->count);
    }

    free(allNodes);
}

int processWord(HashTable *table, char *word, int len) {
    while (len > 0 && ispunct((unsigned char)word[len - 1])) {
        word[len - 1] = '\0';
        len--;
    }
    if (len > 0) {
        strToLower(word);
        if (!insertWord(table, word)) {
            return 0;
        }
    }
    return 1;
}