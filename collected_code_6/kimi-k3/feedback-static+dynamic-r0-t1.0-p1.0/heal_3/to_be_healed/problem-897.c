#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  *  test case 2 failed: expected False, got <no output>
  */

bool is_word_present(const char *sentence, const char *word) {
    if (sentence == NULL || word == NULL) {
        return false;
    }

    size_t word_len = strnlen(word, 64);
    if (word_len == 0) {
        return false;
    }

    const char *current = sentence;
    while ((current = strstr(current, word)) != NULL) {
        bool start_ok = (current == sentence) || !isalnum((unsigned char)current[-1]);
        bool end_ok = !isalnum((unsigned char)current[word_len]);
        
        if (start_ok && end_ok) {
            return true;
        }
        current++;
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
    
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strnlen(sentence, sizeof(sentence));
    if (len > 0 && sentence[len - 1] == '\n') {
        sentence[len - 1] = '\0';
    }
    
    if (fgets(word, sizeof(word), stdin) == NULL) {
        return 1;
    }
    
    len = strnlen(word, sizeof(word));
    if (len > 0 && word[len - 1] == '\n') {
        word[len - 1] = '\0';
    }
    
    if (is_word_present(sentence, word)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return 0;
}