#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool match_word_with_z(const char *text, int *start_pos, int *end_pos) {
    int i = 0;
    bool in_word = false;
    int word_start = 0;
    
    while (text[i] != '\0') {
        if (isalnum((unsigned char)text[i]) || text[i] == '_') {
            if (!in_word) {
                in_word = true;
                word_start = i;
            }
        } else {
            if (in_word) {
                int word_end = i - 1;
                int word_len = word_end - word_start + 1;
                
                if (word_len >= 3) {
                    for (int j = word_start + 1; j < word_end; j++) {
                        if (text[j] == 'z' || text[j] == 'Z') {
                            *start_pos = word_start;
                            *end_pos = word_end;
                            return true;
                        }
                    }
                }
                in_word = false;
            }
        }
        i++;
    }
    
    if (in_word) {
        int word_end = i - 1;
        int word_len = word_end - word_start + 1;
        
        if (word_len >= 3) {
            for (int j = word_start + 1; j < word_end; j++) {
                if (text[j] == 'z' || text[j] == 'Z') {
                    *start_pos = word_start;
                    *end_pos = word_end;
                    return true;
                }
            }
        }
    }
    
    return false;
}

int main(void) {
    const char *test_strings[] = {
        "amazing",
        "zebra",
        "buzz",
        "pizza pie",
        "no z here",
        "az",
        "za",
        "a z b",
        "middlezposition",
        "Zoo",
        "fooZbar"
    };
    
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    for (int i = 0; i < num_tests; i++) {
        int start_pos = -1;
        int end_pos = -1;
        
        printf("Testing: '%s' -> ", test_strings[i]);
        
        if (match_word_with_z(test_strings[i], &start_pos, &end_pos)) {
            printf("MATCH (word from position %d to %d): '", start_pos, end_pos);
            for (int j = start_pos; j <= end_pos; j++) {
                putchar(test_strings[i][j]);
            }
            printf("'\n");
        } else {
            printf("NO MATCH\n");
        }
    }
    
    return 0;
}