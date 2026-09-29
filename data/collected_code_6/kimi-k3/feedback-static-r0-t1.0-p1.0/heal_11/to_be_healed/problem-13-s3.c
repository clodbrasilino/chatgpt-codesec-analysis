#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef _WIN32
#include <unistd.h>
#endif

#define MAX_WORD_LEN 100
#define MAX_WORDS 10000
#define MAX_LINE_LEN 4096

typedef struct {
    char *word;
    int count;
} WordCount;

int findWordIndex(WordCount words[], int numWords, const char *word) {
    int i;
    for (i = 0; i < numWords; i++) {
        if (strcmp(words[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

int compareWordCounts(const void *a, const void *b) {
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    if (wb->count > wa->count) return 1;
    if (wb->count < wa->count) return -1;
    return 0;
}

void freeWords(WordCount words[], int numWords) {
    int i;
    for (i = 0; i < numWords; i++) {
        free(words[i].word);
        words[i].word = NULL;
    }
}

int countMostCommonWords(const char *filename, WordCount words[], int maxWords, int topN) {
    FILE *file = NULL;
    char *buffer = NULL;
    char *word = NULL;
    int numWords = 0;
    int i;
    int ret = -1;

    if (filename == NULL || words == NULL || maxWords <= 0 || topN <= 0 || maxWords > MAX_WORDS) {
        return -1;
    }

    buffer = (char *)malloc(MAX_LINE_LEN);
    if (buffer == NULL) {
        return -1;
    }

    word = (char *)malloc(MAX_WORD_LEN + 1);
    if (word == NULL) {
        free(buffer);
        return -1;
    }

#ifdef _WIN32
    /* Possible weaknesses found:
     * Flawfinder fopen: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    file = fopen(filename, "rb");
    if (file == NULL) {
        free(word);
        free(buffer);
        return -1;
    }
#else
    /* Possible weaknesses found:
     * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    int fd = open(filename, O_RDONLY | O_NOFOLLOW);
    if (fd < 0) {
        free(word);
        free(buffer);
        return -1;
    }

    struct stat st;
    if (fstat(fd, &st) != 0 || !S_ISREG(st.st_mode)) {
        close(fd);
        free(word);
        free(buffer);
        return -1;
    }

    file = fdopen(fd, "r");
    if (file == NULL) {
        close(fd);
        free(word);
        free(buffer);
        return -1;
    }
#endif

    while (fgets(buffer, MAX_LINE_LEN, file) != NULL) {
        size_t bufLen = strnlen(buffer, MAX_LINE_LEN);
        size_t j = 0;

        for (i = 0; i < (int)bufLen; i++) {
            if (isalpha((unsigned char)buffer[i])) {
                if (j < MAX_WORD_LEN) {
                    word[j++] = (char)tolower((unsigned char)buffer[i]);
                }
            } else {
                if (j > 0) {
                    word[j] = '\0';

                    int index = findWordIndex(words, numWords, word);
                    if (index >= 0) {
                        if (words[index].count < INT_MAX) {
                            words[index].count++;
                        }
                    } else if (numWords < maxWords) {
                        size_t wordLen = strnlen(word, MAX_WORD_LEN + 1);
                        if (wordLen > 0 && wordLen <= MAX_WORD_LEN) {
                            words[numWords].word = (char *)malloc(wordLen + 1);
                            if (words[numWords].word == NULL) {
                                freeWords(words, numWords);
                                free(word);
                                free(buffer);
                                fclose(file);
                                return -1;
                            }
                            /* Possible weaknesses found:
                             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                             */
                            strncpy(words[numWords].word, word, wordLen);
                            words[numWords].word[wordLen] = '\0';
                            words[numWords].count = 1;
                            numWords++;
                        }
                    }
                    j = 0;
                }
            }
        }

        if (j > 0) {
            word[j] = '\0';

            int index = findWordIndex(words, numWords, word);
            if (index >= 0) {
                if (words[index].count < INT_MAX) {
                    words[index].count++;
                }
            } else if (numWords < maxWords) {
                size_t wordLen = strnlen(word, MAX_WORD_LEN + 1);
                if (wordLen > 0 && wordLen <= MAX_WORD_LEN) {
                    words[numWords].word = (char *)malloc(wordLen + 1);
                    if (words[numWords].word == NULL) {
                        freeWords(words, numWords);
                        free(word);
                        free(buffer);
                        fclose(file);
                        return -1;
                    }
                    /* Possible weaknesses found:
                     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                     */
                    strncpy(words[numWords].word, word, wordLen);
                    words[numWords].word[wordLen] = '\0';
                    words[numWords].count = 1;
                    numWords++;
                }
            }
        }
    }

    if (ferror(file)) {
        freeWords(words, numWords);
        free(word);
        free(buffer);
        fclose(file);
        return -1;
    }

    if (fclose(file) != 0) {
        freeWords(words, numWords);
        free(word);
        free(buffer);
        return -1;
    }

    free(word);
    free(buffer);

    qsort(words, numWords, sizeof(WordCount), compareWordCounts);

    ret = numWords < topN ? numWords : topN;
    return ret;
}

int main(void) {
    WordCount words[MAX_WORDS];
    const char *filename = "dictionary.txt";
    int topN = 10;
    int result;
    int i;

    memset(words, 0, sizeof(words));

    result = countMostCommonWords(filename, words, MAX_WORDS, topN);

    if (result < 0) {
        fprintf(stderr, "Error: Could not process file %s\n", filename);
        return EXIT_FAILURE;
    }

    printf("Top %d most common words:\n", result);
    for (i = 0; i < result; i++) {
        printf("%d. %s: %d\n", i + 1, words[i].word, words[i].count);
    }

    freeWords(words, result);

    return EXIT_SUCCESS;
}