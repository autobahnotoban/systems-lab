#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LEN 25
#define MAP_SIZE 1000

struct Node {
    char *str;
    struct Node *next;
};

long hashing_algo(const char str[]) {
    long hash_key = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        int letter = toupper((unsigned char)str[i]) - 64;
        hash_key = (hash_key + (letter * 25)) % MAP_SIZE;
    }

    return hash_key;
}

struct Node *create_node(const char *content) {
    struct Node *newNode = malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("could not allocate for node\n");
        return NULL;
    }

    newNode->next = NULL;
    newNode->str = malloc(MAX_KEY_LEN);
    if (newNode->str == NULL) {
        free(newNode);
        printf("could not allocate for key string\n");
        return NULL;
    }

    strncpy(newNode->str, content, MAX_KEY_LEN - 1);
    newNode->str[MAX_KEY_LEN - 1] = '\0';

    return newNode;
}

struct Node **create_map(void) {
    struct Node **hashmap = calloc(MAP_SIZE, sizeof(struct Node *));
    if (hashmap == NULL) {
        printf("could not allocate for hashmap\n");
        return NULL;
    }

    return hashmap;
}

void add_to_map(struct Node *tail, const char *value) {
    tail->next = create_node(value);
}

void print_chain(struct Node *head, int row) {
    if (head == NULL) {
        printf("===================================\n");
        printf("this row is empty.\n");
        printf("===================================\n");
        return;
    }

    struct Node *temp = head;
    printf("===================================\n");
    printf("%d | ", row);
    while (temp != NULL) {
        printf(" %s ->", temp->str);
        temp = temp->next;
    }
    printf(" NULL |\n");
    printf("===================================\n");
}

void free_chain(struct Node *head) {
    while (head != NULL) {
        struct Node *next = head->next;
        free(head->str);
        free(head);
        head = next;
    }
}

void free_map(struct Node **hashmap) {
    if (hashmap == NULL) {
        return;
    }

    for (int i = 0; i < MAP_SIZE; i++) {
        free_chain(hashmap[i]);
    }

    free(hashmap);
}

int main(void) {
    struct Node **Hashmap = create_map();
    if (Hashmap == NULL) {
        return 0;
    }

    int loop_check = 1;
    int choice = 0;
    char value[MAX_KEY_LEN];
    int row = 0;

    while (loop_check) {
        printf("Enter choice:\n");
        printf("Add value to hashmap(1)\nPrint hashmap chain(2)\nQuit(0)\n");
        printf("Choice: ");

        if (scanf(" %d", &choice) != 1) {
            break;
        }

        switch (choice) {
        case 0:
            loop_check = 0;
            break;
        case 1: {
            printf("Enter key:  ");
            if (scanf(" %24s", value) != 1) {
                loop_check = 0;
                break;
            }

            long key = hashing_algo(value);

            if (Hashmap[key] == NULL) {
                Hashmap[key] = create_node(value);
            } else {
                struct Node *temp = Hashmap[key];
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                add_to_map(temp, value);
            }
            break;
        }
        case 2:
            printf("Enter row to print: ");
            if (scanf("%d", &row) != 1) {
                loop_check = 0;
                break;
            }
            if (row >= 0 && row < MAP_SIZE) {
                print_chain(Hashmap[row], row);
            } else {
                printf("row out of range\n");
            }
            break;
        default:
            break;
        }
    }

    free_map(Hashmap);
    return 0;
}
