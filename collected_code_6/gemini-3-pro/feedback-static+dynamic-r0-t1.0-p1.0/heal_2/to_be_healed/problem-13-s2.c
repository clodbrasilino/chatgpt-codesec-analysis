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
    newNode->word = strdup(word);
    if (!newNode->word) {
        free(newNode);
        return 0;
    }
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
    /* Possible weaknesses found:
     *  Variable 'nodeA' can be declared as pointer to const [constVariablePointer]
     */
    WordNode *nodeA = *(WordNode **)a;
    /* Possible weaknesses found:
     *  Variable 'nodeB' can be declared as pointer to const [constVariablePointer]
     */
    WordNode *nodeB = *(WordNode **)b;
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

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    HashTable *table = createTable();
    if (!table) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    char word[MAX_WORD_LEN];
    while (fscanf(file, "%255s", word) == 1) {
        strToLower(word);
        int len = strlen(word);
        while (len > 0 && ispunct((unsigned char)word[len - 1])) {
            word[len - 1] = '\0';
            len--;
        }
        if (len > 0) {
            if (!insertWord(table, word)) {
                fprintf(stderr, "Memory allocation failed during insert\n");
                fclose(file);
                freeTable(table);
                return EXIT_FAILURE;
            }
        }
    }

    fclose(file);

    findMostCommonWords(table, 10);

    freeTable(table);
    return EXIT_SUCCESS;
}