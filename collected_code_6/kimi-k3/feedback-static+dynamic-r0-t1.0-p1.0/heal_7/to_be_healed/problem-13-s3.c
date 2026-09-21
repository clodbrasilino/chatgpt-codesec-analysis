#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#define MAX_WORD_LEN 100
#define MAX_WORDS 10000
#define SCAN_BUFFER_SIZE 1024

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
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

void toLowerCase(char *str) {
    size_t i;
    if (str == NULL) {
        return;
    }
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

int compareWordCounts(const void *a, const void *b) {
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    if (wb->count > wa->count) return 1;
    if (wb->count < wa->count) return -1;
    return 0;
}

int countMostCommonWords(const char *filename, WordCount words[], int maxWords, int topN) {
    FILE *file = NULL;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[SCAN_BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char wordBuffer[MAX_WORD_LEN];
    int numWords = 0;
    size_t i;
    size_t j;
    struct stat st;
    int fd;
    int index;
    /* Possible weaknesses found:
     *  The scope of the variable 'scanResult' can be reduced. [variableScope]
     */
    int scanResult;

    if (filename == NULL || words == NULL || maxWords <= 0 || topN <= 0) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    fd = open(filename, O_RDONLY | O_NOFOLLOW | O_CLOEXEC);
    if (fd < 0) {
        return -1;
    }

    if (fstat(fd, &st) != 0) {
        close(fd);
        return -1;
    }

    if (!S_ISREG(st.st_mode)) {
        close(fd);
        return -1;
    }

    if (st.st_size < 0 || st.st_size > (off_t)(SIZE_MAX / 2)) {
        close(fd);
        return -1;
    }

    file = fdopen(fd, "r");
    if (file == NULL) {
        close(fd);
        return -1;
    }

    while (1) {
        /* Possible weaknesses found:
         * Flawfinder fscanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
         */
        scanResult = fscanf(file, "%1023s", buffer);
        if (scanResult == EOF) {
            break;
        }
        if (scanResult != 1) {
            continue;
        }

        buffer[SCAN_BUFFER_SIZE - 1] = '\0';
        j = 0;

        toLowerCase(buffer);

        for (i = 0; buffer[i] != '\0' && j < (size_t)(MAX_WORD_LEN - 1); i++) {
            if (isalpha((unsigned char)buffer[i])) {
                wordBuffer[j++] = buffer[i];
            }
        }
        wordBuffer[j] = '\0';

        if (j == 0) {
            continue;
        }

        index = findWordIndex(words, numWords, wordBuffer);
        if (index >= 0) {
            if (words[index].count < INT_MAX) {
                words[index].count++;
            }
        } else if (numWords < maxWords) {
            size_t len = strnlen(wordBuffer, MAX_WORD_LEN - 1);
            if (len > 0 && len < MAX_WORD_LEN) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(words[numWords].word, wordBuffer, len);
                words[numWords].word[len] = '\0';
                words[numWords].count = 1;
                numWords++;
            }
        }
    }

    if (fclose(file) != 0) {
        return -1;
    }

    if (numWords > 0) {
        qsort(words, (size_t)numWords, sizeof(WordCount), compareWordCounts);
    }

    return numWords < topN ? numWords : topN;
}

int main(void) {
    WordCount words[MAX_WORDS];
    const char *filename = "dictionary.txt";
    int topN = 10;
    int result;
    int i;

    result = countMostCommonWords(filename, words, MAX_WORDS, topN);

    if (result < 0) {
        fprintf(stderr, "Error: Could not process file %s\n", filename);
        return EXIT_FAILURE;
    }

    printf("Top %d most common words:\n", result);
    for (i = 0; i < result; i++) {
        printf("%d. %s: %d\n", i + 1, words[i].word, words[i].count);
    }

    return EXIT_SUCCESS;
}