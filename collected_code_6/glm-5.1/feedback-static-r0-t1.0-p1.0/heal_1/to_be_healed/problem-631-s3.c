#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *replace_whitespace_underscore(const char *src) {
    if (src == NULL) {
        return NULL;
    }

    size_t len = strlen(src);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[ _]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t new_len = len + 1;
    char *dest = malloc(new_len);
    if (dest == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t match;
    size_t src_pos = 0;
    size_t dest_pos = 0;

    while (src_pos < len) {
        ret = regexec(&regex, src + src_pos, 1, &match, 0);
        if (ret == 0) {
            size_t match_start = src_pos + match.rm_so;
            size_t match_len = match_start - src_pos;

            if (dest_pos + match_len + 1 >= new_len) {
                size_t required = dest_pos + match_len + (len - src_pos) + 1;
                char *temp = realloc(dest, required);
                if (temp == NULL) {
                    regfree(&regex);
                    free(dest);
                    return NULL;
                }
                dest = temp;
                new_len = required;
            }

            memcpy(dest + dest_pos, src + src_pos, match_len);
            dest_pos += match_len;

            char original = src[match_start];
            dest[dest_pos++] = (original == ' ') ? '_' : ' ';

            src_pos = match_start + 1;
        } else if (ret == REG_NOMATCH) {
            size_t remaining = len - src_pos;
            if (dest_pos + remaining >= new_len) {
                size_t required = dest_pos + remaining + 1;
                char *temp = realloc(dest, required);
                if (temp == NULL) {
                    regfree(&regex);
                    free(dest);
                    return NULL;
                }
                dest = temp;
                new_len = required;
            }

            memcpy(dest + dest_pos, src + src_pos, remaining);
            dest_pos += remaining;
            break;
        } else {
            regfree(&regex);
            free(dest);
            return NULL;
        }
    }

    if (dest_pos >= new_len) {
        char *temp = realloc(dest, dest_pos + 1);
        if (temp == NULL) {
            regfree(&regex);
            free(dest);
            return NULL;
        }
        dest = temp;
    }

    dest[dest_pos] = '\0';
    regfree(&regex);

    char *final_dest = realloc(dest, dest_pos + 1);
    if (final_dest != NULL) {
        return final_dest;
    }

    return dest;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *result = replace_whitespace_underscore(argv[1]);
    if (result == NULL) {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }

    printf("%s\n", result);
    free(result);

    return 0;
}