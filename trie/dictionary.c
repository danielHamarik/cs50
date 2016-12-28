/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
#include "dictionary.h"


struct node {
    bool val;
    struct node *arr[ARRAY_SIZE];
};


struct node* root;
int count;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    struct node* n = root;
    int pos;
    for(int i = 0, j = strlen(word); i < j ; i++){
        if(word[i] == '\'')
            pos = ARRAY_SIZE - 1;
        else 
            pos = (tolower(word[i])) - 'a';
        if(n->arr[pos] == NULL) return false;
        n = n->arr[pos];
    }
    if(n->val == true) 
        return true;
    else
        return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* dic = fopen(dictionary, "r");
    if(dic == NULL){
        return false;
    }
    root = calloc(1,sizeof(struct node));
    struct node* n;
    char* word = malloc(sizeof(char) * LENGTH);
    while(fscanf(dic, "%s", word)==1){
        n = root;
        int pos = 0;
        for(int i = 0, j = strlen(word); i < j; i++){
            if(word[i] == '\'')
                pos = ARRAY_SIZE - 1;
            else 
                pos = word[i] - 'a';
            if(n->arr[pos] == NULL){
                n->arr[pos] = calloc(1,sizeof(struct node));
            }
            n = n->arr[pos];
        }
        n->val = true;
        count++;
    }
    free(word);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return count;
}


void unloadRec(struct node* n){
    if(n == NULL) return;
    for(int i = 0; i < ARRAY_SIZE; i++){
        unloadRec(n->arr[i]);
    }
    free(n);
}
/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    unloadRec(root); 
    return true;
}
