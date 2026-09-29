#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_WORD_LEN 100
#define MAX_WORDS 10000

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
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
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
    char buffer[MAX_WORD_LEN];
    int numWords = 0;
    int i;
    struct stat st;
    int fd;

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

    file = fdopen(fd, "r");
    if (file == NULL) {
        close(fd);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fscanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    while (fscanf(file, "%99s", buffer) == 1) {
        int j = 0;
        
        toLowerCase(buffer);
        
        for (i = 0; buffer[i] != '\0' && j < MAX_WORD_LEN - 1; i++) {
            if (isalpha((unsigned char)buffer[i])) {
                buffer[j++] = buffer[i];
            }
        }
        buffer[j] = '\0';

        if (j == 0) {
            continue;
        }

        int index = findWordIndex(words, numWords, buffer);
        if (index >= 0) {
            words[index].count++;
        } else if (numWords < maxWords) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(buffer);
            if (len < MAX_WORD_LEN) {
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(words[numWords].word, buffer, MAX_WORD_LEN - 1);
                words[numWords].word[MAX_WORD_LEN - 1] = '\0';
                words[numWords].count = 1;
                numWords++;
            }
        }
    }

    if (fclose(file) != 0) {
        return -1;
    }

    qsort(words, numWords, sizeof(WordCount), compareWordCounts);

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