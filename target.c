#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int is_word(const char* word) {
    size_t buffer_size = (buffer_size + 1) * sizeof(char);
    size_t word_length = strlen(word);
    char *line_ptr = malloc(buffer_size);
    FILE *words = fopen("/usr/share/dict/words", "r");
    while (1) {
        ssize_t found_length = getline(&line_ptr, &buffer_size, words);
        if (-1 == found_length)
            break;
        if (0 == strncmp(word, line_ptr, word_length)) {
            free(line_ptr);
            return 1;
        }
    }
    free(line_ptr);
    return 0;
}


int strfind(const char* haystack, char needle, size_t length) {
    int i = 0;
    for (i = 0; i < length; ++i) {
        if (needle == haystack[i]) {
            return i;
        }
    }
    return -1;
}

int _anagram_of_substring(const char* target_word, const char* word) {
    size_t target_word_len = strlen(target_word);
    size_t word_len = strlen(word);

    char *duplicate = strdup(target_word);
    assert(NULL != duplicate);
    int fits = 1;
    int i;
    for (i = 0; i < word_len; ++i) {
        int position = strfind(duplicate, word[i], target_word_len);
        if (-1 == position) {
            fits = 0;
            break;
        } else {
            duplicate[position] = '\0';
        }
    }
    free(duplicate);
    return fits;
}

int fits_target(const char* target_word, char central, const char* word) {
    size_t target_word_len = strlen(target_word) * sizeof(char);
    assert(target_word_len == 9);
    int word_len = strlen(word);

    /* Is it more than four letters long? */
    if (word_len < 4) {
        return 0;
    }

    /* Does it have the central character? */
    if (NULL == strchr(word, central)) {
        return 0;
    }

    return _anagram_of_substring(target_word, word);
}


void rstrip(char *word) {
    int len = strlen(word);
    char *last = strchr(word, '\0');
    while (word != (--last)) {
        if ('\n' == *last) {
            *last = '\0';
        }
    }
}


void search_dictionary(const char* target_word, char central) {
    size_t buffer_size = 0;
    char *line_ptr = 0;
    FILE *words = fopen("/usr/share/dict/words", "r");
    int solutions_found = 0;
    while (1) {
        ssize_t found_len = getline(&line_ptr, &buffer_size, words);
        if (-1 == found_len) {
            break;
        }
        rstrip(line_ptr);
        found_len = strlen(line_ptr);
        if (fits_target(target_word, central, line_ptr)) {
            if ('s' == line_ptr[found_len - 1]) {
                char *duplicate = strdup(line_ptr);
                duplicate[found_len - 1] = '\0';
                if (!is_word(duplicate)) {
                    printf("%s\n", line_ptr);
                    ++solutions_found;
                }
                free(duplicate);
            } else {
                printf("--> %s\n", line_ptr);
                ++solutions_found;
            }
        }
    }
    free(line_ptr);
    fclose(words);
    printf("%d solutions found.\n", solutions_found);
}


void usage(char **argv) {
    printf("%s <target_word> <center_character>\n", argv[0]);
    exit(2);
}

int main(int argc, char **argv) {
    if (3 != argc) {
        usage(argv);
    }
    if (9 != strlen(argv[1])) {
        usage(argv);
    }
    if (1 != strlen(argv[2])) {
        usage(argv);
    }
    char central = argv[2][0];
    search_dictionary(argv[1], central);
    return 0;
}
