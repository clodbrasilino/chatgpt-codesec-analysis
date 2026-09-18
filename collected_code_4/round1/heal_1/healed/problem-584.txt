#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define MAX_MATCHES 100 

typedef struct match_position {
    int start;
    int end;
} match_position;

typedef struct match_result {
    char** matches;
    match_position* positions;
    int match_count;
} match_result;

match_result* match_regex(const char* text, const char* pattern) {
    regex_t regex_comp;
    regmatch_t group_array[MAX_MATCHES];

    if (regcomp(&regex_comp, pattern, REG_EXTENDED)) {
        puts("Compilation of regex failed.");
        return NULL;
    }

    int nomatch = regexec(&regex_comp, text, MAX_MATCHES, group_array, 0);
	
    match_result* result = malloc(sizeof(match_result));
    if (!result) {
        return NULL;
    }

    result->matches = NULL;
    result->positions = NULL;
    result->match_count = 0;

    if (!nomatch) {
        int match_count = 0;
        for (match_count = 0; match_count < MAX_MATCHES && group_array[match_count].rm_so != -1; match_count++);

        result->matches = malloc(sizeof(char*) * match_count);
        if (!result->matches) {
            free(result);
            return NULL;
        }
        
        result->positions = malloc(sizeof(match_position) * match_count);
        if (!result->positions) {
            free(result->matches);
            free(result);
            return NULL;
        }

        result->match_count = match_count;

        for (int i = 0; i < match_count; i++) {
            int start = group_array[i].rm_so;
            int end = group_array[i].rm_eo;
            size_t length = end - start;

            result->positions[i].start = start;
            result->positions[i].end = end;

            result->matches[i] = malloc(sizeof(char) * (length + 1));
            if (!result->matches[i]) {
                for(int j = i - 1; j >= 0; j--){
                    free(result->matches[j]);
                }

                free(result->matches);
                free(result->positions);
                free(result);
                return NULL;
            }

            strncpy(result->matches[i], &text[start], length);
            result->matches[i][length] = '\0';
        }
    }

    regfree(&regex_comp);

    return result;
}

void free_match_result(match_result* result) {
    if (!result) {
        return;
    }

    for (int i = 0; i < result->match_count; i++) {
        free(result->matches[i]);
    }
    free(result->matches);
    free(result->positions);
    free(result);
}

int main() {
    const char* sentence = "They badly need to quickly solve this excellently designed yet unfortunately precise problem, really";
    const char* adverb_pattern = "\\b\\w+(ly)\\b"; 

    match_result* result = match_regex(sentence, adverb_pattern);

    if (!result) {
        printf("No matches found or an error occurred.\n");
        return 1;
    }

    printf("Found %d match(es).\n\n", result->match_count);
    for (int i = 0; i < result->match_count; i++) {
        printf("Match: \"%s\"\n", result->matches[i]);
        printf("At position: %d - %d\n\n", result->positions[i].start, result->positions[i].end);
    }

    free_match_result(result);

    return 0;
}