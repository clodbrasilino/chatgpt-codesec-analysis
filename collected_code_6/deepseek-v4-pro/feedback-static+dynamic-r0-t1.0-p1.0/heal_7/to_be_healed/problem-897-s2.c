#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

static void clear_input_buffer(void) {
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    if (c == EOF) {
        clearerr(stdin);
    }
}

static bool read_line(char *buffer, size_t size) {
    if (size == 0 || buffer == NULL) {
        return false;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return false;
    }
    
    size_t len = strnlen(buffer, size);
    if (len == 0) {
        return true;
    }

    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == size - 1) {
        clear_input_buffer();
    }
    
    return true;
}

bool is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL || *word == '\0') {
        return false;
    }

    size_t word_len = strnlen(word, 256);
    if (word_len == 0 || word_len > 255) {
        return false;
    }

    size_t sentence_len = strnlen(sentence, 1024);
    if (sentence_len == 0) {
        return false;
    }

    for (size_t i = 0; i < sentence_len; ) {
        while (i < sentence_len && !isalpha((unsigned char)sentence[i])) {
            i++;
        }

        if (i >= sentence_len) {
            break;
        }

        size_t start = i;
        while (i < sentence_len && isalpha((unsigned char)sentence[i])) {
            i++;
        }

        size_t token_len = i - start;
        if (token_len == word_len) {
            bool match = true;
            for (size_t j = 0; j < word_len; j++) {
                if (tolower((unsigned char)sentence[start + j]) != tolower((unsigned char)word[j])) {
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

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[1024];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[256];

    printf("Enter a sentence: ");
    if (!read_line(sentence, sizeof(sentence))) {
        fprintf(stderr, "Error reading sentence.\n");
        return 1;
    }

    printf("Enter a word to search: ");
    if (!read_line(word, sizeof(word))) {
        fprintf(stderr, "Error reading word.\n");
        return 1;
    }

    if (is_word_present(sentence, word)) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }

    return 0;
}