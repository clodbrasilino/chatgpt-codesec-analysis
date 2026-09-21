#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define SENTENCE_SIZE 1024
#define WORD_SIZE 256

static void clear_input_buffer(void) {
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static size_t string_length(const char *str, size_t max_size) {
    size_t len = 0;
    if (str != NULL) {
        while (len < max_size && str[len] != '\0') {
            len++;
        }
    }
    return len;
}

static bool is_word_present(const char *sentence, size_t sentence_max, const char *word) {
    if (sentence == NULL || word == NULL || *sentence == '\0' || *word == '\0') {
        return false;
    }

    size_t word_len = string_length(word, WORD_SIZE);
    if (word_len == 0 || word_len >= WORD_SIZE) {
        return false;
    }

    const char *pos = sentence;
    const char *sentence_end = sentence + sentence_max;

    while (pos < sentence_end && *pos != '\0') {
        while (pos < sentence_end && *pos != '\0' && !isalpha((unsigned char)*pos)) {
            pos++;
        }

        if (pos >= sentence_end || *pos == '\0') {
            break;
        }

        const char *start = pos;
        while (pos < sentence_end && *pos != '\0' && isalpha((unsigned char)*pos)) {
            pos++;
        }

        size_t token_len = (size_t)(pos - start);
        if (token_len == word_len && token_len < WORD_SIZE) {
            bool match = true;
            for (size_t i = 0; i < word_len; i++) {
                if (tolower((unsigned char)start[i]) != tolower((unsigned char)word[i])) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
    }

    return false;
}

static bool read_line(char *buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return false;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return false;
    }

    size_t len = string_length(buffer, size);

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        bool newline_found = false;
        for (size_t i = 0; i < len; i++) {
            if (buffer[i] == '\n') {
                buffer[i] = '\0';
                newline_found = true;
                break;
            }
        }
        if (!newline_found && len == size - 1) {
            clear_input_buffer();
        }
    }

    return true;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[SENTENCE_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[WORD_SIZE];

    if (SENTENCE_SIZE <= 1 || WORD_SIZE <= 1) {
        return 1;
    }

    sentence[0] = '\0';
    word[0] = '\0';

    printf("Enter a sentence: ");
    if (!read_line(sentence, SENTENCE_SIZE)) {
        printf("Error reading input.\n");
        return 1;
    }

    printf("Enter a word to search: ");
    if (!read_line(word, WORD_SIZE)) {
        printf("Error reading input.\n");
        return 1;
    }

    if (is_word_present(sentence, SENTENCE_SIZE, word)) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }

    return 0;
}