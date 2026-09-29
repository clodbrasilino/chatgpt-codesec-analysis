#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#ifndef O_NOFOLLOW
#define O_NOFOLLOW 0
#endif

#ifndef O_CLOEXEC
#define O_CLOEXEC 0
#endif

#ifndef O_NONBLOCK
#define O_NONBLOCK 0
#endif

#define MAX_WORD_LEN 256
#define HASH_SIZE 10007
#define CHUNK_SIZE 4096

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
    const WordNode *nodeA = *(const WordNode * const *)a;
    const WordNode *nodeB = *(const WordNode * const *)b;
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

void processWord(HashTable *table, char *word, int *len) {
    if (*len > 0) {
        word[*len] = '\0';
        strToLower(word);
        while (*len > 0 && ispunct((unsigned char)word[*len - 1])) {
            word[*len - 1] = '\0';
            (*len)--;
        }
        if (*len > 0) {
            if (!insertWord(table, word)) {
                fprintf(stderr, "Memory allocation failed during insert\n");
                exit(EXIT_FAILURE);
            }
        }
        *len = 0;
    }
}

int main(int argc, const char *const argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int fd = open(argv[1], O_RDONLY | O_NOFOLLOW | O_CLOEXEC | O_NONBLOCK);
    if (fd == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    struct stat st;
    if (fstat(fd, &st) == -1 || !S_ISREG(st.st_mode)) {
        fprintf(stderr, "Invalid file type\n");
        close(fd);
        return EXIT_FAILURE;
    }

    int flags = fcntl(fd, F_GETFL, 0);
    if (flags != -1) {
        fcntl(fd, F_SETFL, flags & ~O_NONBLOCK);
    }

    FILE *file = fdopen(fd, "r");
    if (!file) {
        perror("Error creating file stream");
        close(fd);
        return EXIT_FAILURE;
    }

    HashTable *table = createTable();
    if (!table) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    char *word = (char *)malloc(MAX_WORD_LEN);
    if (!word) {
        fclose(file);
        freeTable(table);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    size_t buffer_size = CHUNK_SIZE;
    char *buffer = (char *)malloc(buffer_size);
    if (!buffer) {
        free(word);
        fclose(file);
        freeTable(table);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    size_t bytesRead;
    int len = 0;

    while ((bytesRead = fread(buffer, 1, buffer_size, file)) > 0) {
        for (size_t i = 0; i < bytesRead; i++) {
            unsigned char ch = (unsigned char)buffer[i];
            if (isspace(ch)) {
                processWord(table, word, &len);
            } else {
                if (len < MAX_WORD_LEN - 1) {
                    word[len++] = (char)ch;
                }
            }
        }
    }

    processWord(table, word, &len);

    free(buffer);
    free(word);
    fclose(file);

    findMostCommonWords(table, 10);

    freeTable(table);
    return EXIT_SUCCESS;
}