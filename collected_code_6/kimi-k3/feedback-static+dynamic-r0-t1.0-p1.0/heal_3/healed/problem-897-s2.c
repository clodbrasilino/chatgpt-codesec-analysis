#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool is_word_present(const char *sentence, size_t sentence_len, const char *word, size_t word_len) {
    if (sentence == NULL || word == NULL || word_len == 0) {
        return false;
    }
    
    if (word_len > sentence_len) {
        return false;
    }
    
    size_t pos = 0;
    while (pos <= sentence_len - word_len) {
        if (memcmp(sentence + pos, word, word_len) == 0) {
            bool start_ok = (pos == 0) || !isalnum((unsigned char)sentence[pos - 1]);
            bool end_ok = (pos + word_len >= sentence_len) || !isalnum((unsigned char)sentence[pos + word_len]);
            
            if (start_ok && end_ok) {
                return true;
            }
        }
        pos++;
    }
    
    return false;
}

int main(void) {
    char sentence[257];
    char word[65];
    
    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading sentence\n");
        return 1;
    }
    
    size_t sentence_len = strnlen(sentence, sizeof(sentence));
    if (sentence_len > 0 && sentence[sentence_len - 1] == '\n') {
        sentence[sentence_len - 1] = '\0';
        sentence_len--;
    }
    
    printf("Enter a word to search: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        fprintf(stderr, "Error reading word\n");
        return 1;
    }
    
    size_t word_len = strnlen(word, sizeof(word));
    if (word_len > 0 && word[word_len - 1] == '\n') {
        word[word_len - 1] = '\0';
        word_len--;
    }
    
    if (is_word_present(sentence, sentence_len, word, word_len)) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }
    
    return 0;
}