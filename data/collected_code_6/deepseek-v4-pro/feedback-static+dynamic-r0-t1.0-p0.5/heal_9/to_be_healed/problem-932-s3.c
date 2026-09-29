#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 100

static int is_duplicate(const char words[][MAX_WORD_LEN], int count, const char *word) {
    if (word == NULL) {
        return 1;
    }
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

static size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int remove_duplicates(const char *input[], int input_count, char output[][MAX_WORD_LEN]) {
    int output_count = 0;
    
    if (input == NULL || output == NULL || input_count <= 0) {
        return 0;
    }
    
    for (int i = 0; i < input_count; i++) {
        if (input[i] == NULL) {
            continue;
        }
        
        if (output_count >= MAX_WORDS) {
            break;
        }
        
        if (!is_duplicate(output, output_count, input[i])) {
            size_t len = safe_strlen(input[i], MAX_WORD_LEN - 1);
            if (len > (size_t)(MAX_WORD_LEN - 1)) {
                len = (size_t)(MAX_WORD_LEN - 1);
            }
            /* Possible weaknesses found:
             * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
             */
            strncpy(output[output_count], input[i], len);
            output[output_count][len] = '\0';
            output_count++;
        }
    }
    
    return output_count;
}

int main(void) {
    const char *words[] = {
        "apple", "banana", "apple", "cherry", "banana", "date", "apple"
    };
    int input_count = (int)(sizeof(words) / sizeof(words[0]));
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char (*unique_words)[MAX_WORD_LEN] = calloc((size_t)MAX_WORDS, sizeof(char[MAX_WORD_LEN]));
    
    if (unique_words == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    if (input_count > MAX_WORDS) {
        input_count = MAX_WORDS;
    }
    
    int unique_count = remove_duplicates(words, input_count, unique_words);
    
    printf("Unique words:\n");
    for (int i = 0; i < unique_count; i++) {
        printf("%s\n", unique_words[i]);
    }
    
    free(unique_words);
    return 0;
}