#ifndef __ANIMALE_NODO_H__
#define __ANIMALE_NODO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BT {

	char* text;	
	int id;
	struct BT* yes;
	struct BT* no;

} AnimaleNodo;

AnimaleNodo* createAnimaleNodo(char*, int, AnimaleNodo*, AnimaleNodo*);
int	isLeaf(AnimaleNodo*);
AnimaleNodo* newAlbero();
void setAnimal(AnimaleNodo*, char*, AnimaleNodo*, AnimaleNodo*);
AnimaleNodo* add(char*, int, AnimaleNodo*);

AnimaleNodo* createAnimaleNodo(char* text, int id, AnimaleNodo* yes, AnimaleNodo* no) {

	AnimaleNodo* ret = (AnimaleNodo*) malloc(sizeof(AnimaleNodo));
	ret->text = strdup(text);
	ret->id = id;
	ret->yes = yes;		
	ret->no = no;
	return ret;
}

int	isLeaf(AnimaleNodo* node) {

	return ((node->yes == NULL) && (node->no == NULL));
}

AnimaleNodo* newAlbero() {

	return NULL;
}

void setAnimal(AnimaleNodo* curr, char* text, AnimaleNodo* yes, AnimaleNodo* no) {
	
	free(curr->text);
	curr->text = strdup(text);
	curr->yes = yes;
	curr->no = no;
}

AnimaleNodo* add(char* text, int id, AnimaleNodo* root) {

    AnimaleNodo* current = (AnimaleNodo*) malloc(sizeof(AnimaleNodo));
    current->yes = NULL;
    current->text = strdup(text);
    current->no = NULL;
	current->id = id;

	//printf("current text & id: %s %d\n", current->text, current->id);

    if(!root) return current;

	//printf("root text: %s\n", root->text);
    if(root->id > id) root->yes = add(text, id, root->yes);
    else root->no = add(text, id, root->no);
    return root;
}

#endif // __ANIMALE_NODO_H__