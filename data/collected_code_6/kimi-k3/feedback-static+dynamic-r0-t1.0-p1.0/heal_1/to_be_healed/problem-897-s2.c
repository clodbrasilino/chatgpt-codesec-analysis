#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t word_len = strlen(word);
    if (word_len == 0) {
        return false;
    }
    
    const char *pos = sentence;
    while ((pos = strstr(pos, word)) != NULL) {
        bool start_ok = (pos == sentence) || !isalnum((unsigned char)pos[-1]);
        bool end_ok = (pos[word_len] == '\0') || !isalnum((unsigned char)pos[word_len]);
        
        if (start_ok && end_ok) {
            return true;
        }
        pos++;
    }
    
    return false;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char sentence[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[64];
    
    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading sentence\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(sentence);
    if (len > 0 && sentence[len - 1] == '\n') {
        sentence[len - 1] = '\0';
    }
    
    printf("Enter a word to search: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        fprintf(stderr, "Error reading word\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(word);
    if (len > 0 && word[len - 1] == '\n') {
        word[len - 1] = '\0';
    }
    
    if (is_word_present(sentence, word)) {
        printf("The word \"%s\" is present in the sentence.\n", word);
    } else {
        printf("The word \"%s\" is not present in the sentence.\n", word);
    }
    
    return 0;
}