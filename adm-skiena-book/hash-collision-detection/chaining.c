#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX_KEY_LEN 25
#define MAP_SIZE 1000

long hashing_algo(char str[]){
    int size = strlen(str);
    printf("size of key:    %d\n",size);

    long hash[size];
    long hash_key = 0;

    for(int i = 0; i < size; i++){
        hash[i] = toupper(str[i]) - 64;
        printf("%ld\n",hash[i]);
        printf("-----\n");
        hash_key = ((hash_key + (hash[i] * 25)) % 1000);
    }
    
    printf("final hashkey: %ld \n",hash_key);

    return hash_key;
}

struct Node{
    char* str;
    struct Node* next;
};

struct Node* create_node(char* content){
    struct Node* newNode = malloc(sizeof(struct Node));
    
    if(newNode == NULL){
        printf("could not allocate for node\n");
        return NULL;
    }

    newNode->next = NULL;
    newNode->str = malloc(sizeof(char*) * strlen(content));
    strncpy(newNode->str,content,MAX_KEY_LEN);

    return newNode;
}
    
struct Node** create_map(){
    struct Node** hashmap = calloc(MAP_SIZE,sizeof(struct Node*));
    if (hashmap == NULL){
        printf("could no allocate for hashmap\n");
        return NULL;
    } 

    return hashmap;
}

void add_to_map(struct Node* tail, char* value){
    struct Node* new_tail = create_node(value);
    tail->next = new_tail;
}

void print_chain(struct Node* head, int row){
    if(head == NULL){
        printf("===================================\n");
        printf("this row is empty.\n");
        printf("===================================\n");
        return;
    }
    struct Node* temp = head;
    printf("===================================\n");
    printf("%d | ",row);
    while(temp != NULL){
        printf(" %s ->",temp->str);
        temp = temp->next;
    }
    printf(" NULL |\n");
    printf("===================================\n");
}


int main(void){
    
    struct Node** Hashmap = create_map();
    if(Hashmap == NULL){
        return 0;
    }

    int loop_check = 1;
    int choice = 0;
    char value[MAX_KEY_LEN];
    int row = 0;

    while(loop_check){
        printf("Enter choice:\n");
        printf("Add value to hashmap(1)\nPrint hashmap chain(2)\nQuit(0)\n");
        printf("Choice: ");
        scanf(" %d",&choice);
        switch (choice)
        {
        case 0:
            loop_check = 0;
            break;
        case 1:
            printf("Enter key:  ");
            scanf(" %s",value);
            long key = hashing_algo(value);

            if(Hashmap[key] == NULL){
                struct Node* head = create_node(value);
                Hashmap[key] = head;
            }else{
                struct Node* temp = Hashmap[key];
                while(temp->next != NULL){
                    temp = temp->next;
                }
                add_to_map(temp,value);
            }
            break;
        case 2:
            printf("Enter row to print: ");
            scanf("%d",&row);
            print_chain(Hashmap[row],row);
            break;
        default:
            break;
        }
        
    }
    return 0;
}
