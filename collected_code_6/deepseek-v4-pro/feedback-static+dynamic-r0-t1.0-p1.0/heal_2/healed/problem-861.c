#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 256
#define ALPHABET_SIZE 256

static void count_chars(const char *str, int *counts) {
    memset(counts, 0, ALPHABET_SIZE * sizeof(int));
    while (*str) {
        counts[(unsigned char)*str]++;
        str++;
    }
}

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static int is_anagram(const char *str1, const char *str2) {
    int counts1[ALPHABET_SIZE];
    int counts2[ALPHABET_SIZE];
    size_t len1, len2;

    len1 = safe_strlen(str1, MAX_STR_LEN);
    len2 = safe_strlen(str2, MAX_STR_LEN);

    if (len1 != len2 || len1 == MAX_STR_LEN || len2 == MAX_STR_LEN) {
        return 0;
    }

    count_chars(str1, counts1);
    count_chars(str2, counts2);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (counts1[i] != counts2[i]) {
            return 0;
        }
    }

    return 1;
}

char **find_anagrams(const char *target, char *word_list[], int word_count, int *result_count) {
    char **results;
    int count = 0;

    if (target == NULL || word_list == NULL || word_count <= 0 || result_count == NULL) {
        if (result_count != NULL) {
            *result_count = 0;
        }
        return NULL;
    }

    results = (char **)malloc(word_count * sizeof(char *));
    if (results == NULL) {
        *result_count = 0;
        return NULL;
    }

    for (int i = 0; i < word_count; i++) {
        if (word_list[i] != NULL && is_anagram(target, word_list[i])) {
            results[count] = word_list[i];
            count++;
        }
    }

    if (count == 0) {
        free(results);
        results = NULL;
    } else {
        char **temp = (char **)realloc(results, count * sizeof(char *));
        if (temp != NULL) {
            results = temp;
        }
    }

    *result_count = count;
    return results;
}

int main(void) {
    char *words[] = {"listen", "silent", "enlist", "hello", "world", "tinsel", "inlets"};
    int word_count = sizeof(words) / sizeof(words[0]);
    char target[] = "listen";
    char **anagrams;
    int anagram_count;

    anagrams = find_anagrams(target, words, word_count, &anagram_count);

    printf("Anagrams of '%s':\n", target);
    if (anagrams != NULL) {
        for (int i = 0; i < anagram_count; i++) {
            printf("%s\n", anagrams[i]);
        }
        free(anagrams);
    } else {
        printf("None found\n");
    }

    return 0;
}