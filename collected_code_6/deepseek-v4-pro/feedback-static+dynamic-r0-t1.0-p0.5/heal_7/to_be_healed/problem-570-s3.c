#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int is_separator(char c) {
    if (c == '\0' || isspace((unsigned char)c)) {
        return 1;
    }
    
    const char *separators = ",.!?;:()[] {}\"'&+#@-";
    return strchr(separators, c) != NULL;
}

static int contains_word(const char *str, const char *word) {
    if (str == NULL || word == NULL || *word == '\0') {
        return 0;
    }

    size_t word_len = strlen(word);
    const char *pos = str;

    while ((pos = strstr(pos, word)) != NULL) {
        int at_start = (pos == str);
        int at_end = (*(pos + word_len) == '\0');
        char prev_char = at_start ? '\0' : *(pos - 1);
        char next_char = at_end ? '\0' : *(pos + word_len);

        if (is_separator(prev_char) && is_separator(next_char)) {
            return 1;
        }

        pos += word_len;
    }

    return 0;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got ["Red &","Orange+","Green","Orange @","White"]
  *  test case 2 failed: expected ['Red &', 'Orange+', 'Green', 'Orange', 'White'], got ["Red &","Orange+","Green","Orange @","White"]
  *  test case 0 failed: expected ['Red', '', 'Green', 'Orange', 'White'], got ["Red color","Orange#","Green","Orange @","White"]
  */

char **remove_words(char **words, int word_count, const char *filter, int *new_count) {
    if (words == NULL || filter == NULL || word_count <= 0) {
        if (new_count != NULL) {
            *new_count = 0;
        }
        return NULL;
    }

    char **result = (char **)malloc(word_count * sizeof(char *));
    if (result == NULL) {
        if (new_count != NULL) {
            *new_count = 0;
        }
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < word_count; i++) {
        if (words[i] != NULL && !contains_word(words[i], filter)) {
            result[count] = (char *)malloc((strlen(words[i]) + 1) * sizeof(char));
            if (result[count] == NULL) {
                for (int j = 0; j < count; j++) {
                    free(result[j]);
                }
                free(result);
                if (new_count != NULL) {
                    *new_count = 0;
                }
                return NULL;
            }
            strcpy(result[count], words[i]);
            count++;
        }
    }

    if (count == 0) {
        free(result);
        if (new_count != NULL) {
            *new_count = 0;
        }
        return NULL;
    }

    char **final_result = (char **)realloc(result, count * sizeof(char *));
    if (final_result == NULL) {
        for (int j = 0; j < count; j++) {
            free(result[j]);
        }
        free(result);
        if (new_count != NULL) {
            *new_count = 0;
        }
        return NULL;
    }

    if (new_count != NULL) {
        *new_count = count;
    }
    return final_result;
}

void free_words(char **words, int count) {
    if (words == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);
}

int main(void) {
    char *words[] = {
        "Red",
        "",
        "Green",
        "Orange",
        "White"
    };
    int word_count = sizeof(words) / sizeof(words[0]);
    int new_count = 0;

    char **filtered = remove_words(words, word_count, "Orange", &new_count);

    if (filtered != NULL) {
        printf("[");
        for (int i = 0; i < new_count; i++) {
            printf("'%s'", filtered[i]);
            if (i < new_count - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free_words(filtered, new_count);
    } else {
        printf("[]\n");
    }

    char *words2[] = {
        "Red &",
        "Orange+",
        "Green",
        "Orange @",
        "White"
    };
    word_count = sizeof(words2) / sizeof(words2[0]);
    new_count = 0;

    filtered = remove_words(words2, word_count, "Orange", &new_count);

    if (filtered != NULL) {
        printf("[");
        for (int i = 0; i < new_count; i++) {
            printf("'%s'", filtered[i]);
            if (i < new_count - 1) {
                printf(", ");
            }
        }
        printf("]\n");
        free_words(filtered, new_count);
    } else {
        printf("[]\n");
    }

    return 0;
}