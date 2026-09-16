#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int is_delim(char c, const char *delim) {
    size_t i;
    if (delim == NULL) {
        return isspace((unsigned char)c);
    }
    for (i = 0; delim[i] != '\0'; i++) {
        if (c == delim[i]) {
            return 1;
        }
    }
    return 0;
}

char **string_to_list(const char *str, const char *delim) {
    char **list = NULL;
    size_t capacity = 0;
    size_t count = 0;
    size_t i = 0;
    size_t start;
    size_t token_len;
    size_t new_capacity;
    char **new_list;
    size_t j;

    if (str == NULL) {
        return NULL;
    }

    while (str[i] != '\0') {
        if (is_delim(str[i], delim)) {
            i++;
            continue;
        }

        start = i;
        while (str[i] != '\0' && !is_delim(str[i], delim)) {
            i++;
        }

        token_len = i - start;
        if (count >= capacity) {
            new_capacity = capacity == 0 ? 8 : capacity * 2;
            if (new_capacity <= capacity) {
                for (j = 0; j < count; j++) {
                    free(list[j]);
                }
                free(list);
                return NULL;
            }
            new_list = realloc(list, (new_capacity + 1) * sizeof(char *));
            if (new_list == NULL) {
                for (j = 0; j < count; j++) {
                    free(list[j]);
                }
                free(list);
                return NULL;
            }
            list = new_list;
            capacity = new_capacity;
        }

        list[count] = malloc(token_len + 1);
        if (list[count] == NULL) {
            for (j = 0; j < count; j++) {
                free(list[j]);
            }
            free(list);
            return NULL;
        }
        memcpy(list[count], str + start, token_len);
        list[count][token_len] = '\0';

        count++;
    }

    if (count == 0) {
        list = malloc(sizeof(char *));
        if (list == NULL) {
            return NULL;
        }
        list[0] = NULL;
        return list;
    }

    new_list = realloc(list, (count + 1) * sizeof(char *));
    if (new_list != NULL) {
        list = new_list;
    }

    list[count] = NULL;

    return list;
}

void free_list(char **list) {
    size_t i;
    if (list == NULL) {
        return;
    }
    for (i = 0; list[i] != NULL; i++) {
        free(list[i]);
    }
    free(list);
}

int main(int argc, const char * const argv[]) {
    size_t total_len;
    char *str;
    char *ptr;
    int i;
    size_t arg_len;
    char **list;
    size_t j;
    size_t len;
    char buf[4096];

    if (argc > 1) {
        total_len = 0;
        for (i = 1; i < argc; i++) {
            total_len += strlen(argv[i]);
            if (i < argc - 1) {
                total_len++;
            }
        }
        
        str = malloc(total_len + 1);
        if (str != NULL) {
            ptr = str;
            for (i = 1; i < argc; i++) {
                arg_len = strlen(argv[i]);
                memcpy(ptr, argv[i], arg_len);
                ptr += arg_len;
                if (i < argc - 1) {
                    *ptr++ = ' ';
                }
            }
            *ptr = '\0';
            
            list = string_to_list(str, NULL);
            if (list != NULL) {
                printf("[");
                for (j = 0; list[j] != NULL; j++) {
                    printf("'%s'", list[j]);
                    if (list[j + 1] != NULL) {
                        printf(", ");
                    }
                }
                printf("]\n");
                free_list(list);
            } else {
                printf("[]\n");
            }
            fflush(stdout);
            free(str);
        } else {
            printf("[]\n");
            fflush(stdout);
        }
    } else {
        while (fgets(buf, sizeof(buf), stdin)) {
            len = strlen(buf);
            while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
                buf[len - 1] = '\0';
                len--;
            }
            list = string_to_list(buf, NULL);
            if (list != NULL) {
                printf("[");
                for (j = 0; list[j] != NULL; j++) {
                    printf("'%s'", list[j]);
                    if (list[j + 1] != NULL) {
                        printf(", ");
                    }
                }
                printf("]\n");
                free_list(list);
            } else {
                printf("[]\n");
            }
            fflush(stdout);
        }
    }
    return 0;
}