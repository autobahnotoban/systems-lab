#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 25
#define MAX_VALUE_LEN 100
#define MAP_SIZE 1000

struct Pair {
    char *key;
    char *value;
};

static char *copy_string(const char *src, size_t limit) {
    char *dst = malloc(limit);
    if (dst == NULL) {
        return NULL;
    }

    strncpy(dst, src, limit - 1);
    dst[limit - 1] = '\0';
    return dst;
}

struct Pair *create_pair(const char *key, const char *value) {
    struct Pair *new_pair = malloc(sizeof(struct Pair));
    if (new_pair == NULL) {
        printf("could not allocate memory for pair struct.\n");
        return NULL;
    }

    new_pair->key = copy_string(key, MAX_KEY_LEN);
    if (new_pair->key == NULL) {
        printf("could not allocate memory for pair key.\n");
        free(new_pair);
        return NULL;
    }

    new_pair->value = copy_string(value, MAX_VALUE_LEN);
    if (new_pair->value == NULL) {
        printf("could not allocate memory for pair value.\n");
        free(new_pair->key);
        free(new_pair);
        return NULL;
    }

    return new_pair;
}

long hashing_algo(const char str[]) {
    long hash_key = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        int letter = toupper((unsigned char)str[i]) - 64;
        hash_key = (hash_key + (letter * 25)) % MAP_SIZE;
    }

    return hash_key;
}

void free_pair(struct Pair *pair) {
    if (pair == NULL) {
        return;
    }

    free(pair->key);
    free(pair->value);
    free(pair);
}

void free_table(struct Pair **array) {
    if (array == NULL) {
        return;
    }

    for (int i = 0; i < MAP_SIZE; i++) {
        free_pair(array[i]);
    }

    free(array);
}

void add_to_table(const char *key, const char *value, struct Pair **array) {
    long start = hashing_algo(key);
    long index = start;

    for (int step = 0; step < MAP_SIZE; step++) {
        if (array[index] == NULL) {
            array[index] = create_pair(key, value);
            if (array[index] == NULL) {
                return;
            }

            printf("stored key '%s' at slot %ld\n", key, index);
            return;
        }

        if (strcmp(array[index]->key, key) == 0) {
            char *new_value = copy_string(value, MAX_VALUE_LEN);
            if (new_value == NULL) {
                printf("could not update value.\n");
                return;
            }

            free(array[index]->value);
            array[index]->value = new_value;
            printf("updated key '%s' at slot %ld\n", key, index);
            return;
        }

        index = (index + 1) % MAP_SIZE;
    }

    printf("table is full, could not insert '%s'\n", key);
}

const char *get_value(const char *key, struct Pair **array) {
    long start = hashing_algo(key);
    long index = start;

    for (int step = 0; step < MAP_SIZE; step++) {
        if (array[index] == NULL) {
            return NULL;
        }

        if (strcmp(array[index]->key, key) == 0) {
            return array[index]->value;
        }

        index = (index + 1) % MAP_SIZE;
    }

    return NULL;
}

int main(void) {
    struct Pair **string_array = calloc(MAP_SIZE, sizeof(struct Pair *));
    if (string_array == NULL) {
        return 0;
    }

    int loop_check = 1;
    int choice = 0;
    char key[MAX_KEY_LEN];
    char value[MAX_VALUE_LEN];

    while (loop_check) {
        printf("Enter choice:\n");
        printf("Add key/value to hashmap(1)\nGet value from map(2)\nQuit(0)\n");
        printf("Choice: ");

        if (scanf(" %d", &choice) != 1) {
            break;
        }

        switch (choice) {
        case 0:
            loop_check = 0;
            break;
        case 1:
            printf("Enter key:  ");
            if (scanf(" %24s", key) != 1) {
                loop_check = 0;
                break;
            }

            printf("Enter value:  ");
            if (scanf(" %99s", value) != 1) {
                loop_check = 0;
                break;
            }

            add_to_table(key, value, string_array);
            break;
        case 2: {
            printf("Enter key to get value:    ");
            if (scanf(" %24s", key) != 1) {
                loop_check = 0;
                break;
            }

            const char *found = get_value(key, string_array);
            if (found == NULL) {
                printf("key '%s' was not found\n", key);
            } else {
                printf("Value: %s\n", found);
            }
            break;
        }
        default:
            break;
        }
    }

    free_table(string_array);
    return 0;
}
