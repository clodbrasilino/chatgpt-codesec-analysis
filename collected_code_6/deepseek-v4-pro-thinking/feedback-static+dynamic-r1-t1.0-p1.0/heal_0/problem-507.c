#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct WordNode {
    char *word;
    struct WordNode *next;
};

static char *duplicate_string(const char *s)
{
    if (s == NULL) {
        return NULL;
    }
    size_t len = strlen(s);
    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, s, len + 1);
    return copy;
}

static struct WordNode *create_node(const char *word)
{
    if (word == NULL) {
        return NULL;
    }
    struct WordNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->word = duplicate_string(word);
    if (node->word == NULL) {
        free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}

static void free_list(struct WordNode *head)
{
    while (head != NULL) {
        struct WordNode *next = head->next;
        free(head->word);
        free(head);
        head = next;
    }
}

static int append_word(struct WordNode **head, const char *word)
{
    struct WordNode *node = create_node(word);
    if (node == NULL) {
        return 0;
    }
    if (*head == NULL) {
        *head = node;
    } else {
        struct WordNode *tail = *head;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = node;
    }
    return 1;
}

static size_t remove_words(struct WordNode **head, const char *const *words_to_remove, size_t remove_count)
{
    if (head == NULL || *head == NULL || words_to_remove == NULL || remove_count == 0) {
        return 0;
    }
    size_t removed = 0;
    struct WordNode *current = *head;
    struct WordNode *previous = NULL;
    while (current != NULL) {
        int should_remove = 0;
        for (size_t i = 0; i < remove_count; ++i) {
            if (current->word != NULL && words_to_remove[i] != NULL &&
                strcmp(current->word, words_to_remove[i]) == 0) {
                should_remove = 1;
                break;
            }
        }
        if (should_remove) {
            struct WordNode *to_delete = current;
            current = current->next;
            if (previous == NULL) {
                *head = current;
            } else {
                previous->next = current;
            }
            free(to_delete->word);
            free(to_delete);
            ++removed;
        } else {
            previous = current;
            current = current->next;
        }
    }
    return removed;
}

int main(void)
{
    struct WordNode *list = NULL;
    const char *initial_words[] = { "apple", "banana", "cherry", "apple", "date" };
    const char *words_to_remove[] = { "apple", "cherry" };
    size_t initial_count = sizeof(initial_words) / sizeof(initial_words[0]);
    size_t remove_count = sizeof(words_to_remove) / sizeof(words_to_remove[0]);

    for (size_t i = 0; i < initial_count; ++i) {
        if (!append_word(&list, initial_words[i])) {
            free_list(list);
            return EXIT_FAILURE;
        }
    }

    size_t removed_count = remove_words(&list, words_to_remove, remove_count);
    printf("Removed: %zu\n", removed_count);
    for (struct WordNode *node = list; node != NULL; node = node->next) {
        printf("%s\n", node->word);
    }

    free_list(list);
    return EXIT_SUCCESS;
}