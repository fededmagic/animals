#ifndef __ANIMALE_LOAD_SAVE_H__
#define __ANIMALE_LOAD_SAVE_H__

#include "Csv4.h"

static int counter = 1;

AnimaleNodo* loadFile(FILE*, AnimaleNodo*);
void    CurrentLevel(AnimaleNodo*, int);
void    LevelOrder(AnimaleNodo*);
int height(AnimaleNodo*);
void    saveFile(FILE*, AnimaleNodo*);
void    saveFileLevel(FILE*, AnimaleNodo*, int);
void    disposerAnimaleNodo(AnimaleNodo*);
void    rinumera(AnimaleNodo*);
void    showAlberoPreOrder(AnimaleNodo*);

AnimaleNodo* loadFile(FILE* fp, AnimaleNodo* root) {

    char* line = readline(fp);
    if(!line) return NULL;
    char** vetstr = split(line, ';');
    int i = 0;
    for(; *(vetstr + i); i++) {

        char* elem = strdup(*(vetstr + i));
        char** risp = split(elem, '-');
        //if(i > 0) printf("root3 text: %s\n", root->text);
        //printf("\nID: %s; TEXT: %s", *risp, *(risp + 1));
        if(strcmp("zz", *(risp + 1))) 
            root = add(*(risp + 1), atoi(*risp), root);

        //printf("root2 text: %s\n", root->text);
        free(elem);
    } 
    free(line);
    //disposer_vet_str(vetstr);
    //LevelOrder(root);

    return root;
}

void    CurrentLevel(AnimaleNodo* root, int level) {
  
    if(!root) return;
    if(level == 1) printf("%s ", root->text);

    else if(level > 1) {

        CurrentLevel(root->yes, level - 1);
        CurrentLevel(root->no, level - 1);
    }
}

void    LevelOrder(AnimaleNodo* root) {
 
    int h = height(root);
    int i = 1;
    for(; i <= h; i++) CurrentLevel(root, i);
}

int height(AnimaleNodo* node) {
  
    if(!node) return 0;
    else {

        int lheight = height(node->yes);
        int rheight = height(node->no);

        if(lheight > rheight) return (lheight + 1);
        else return (rheight + 1);
    }
}

void    saveFile(FILE* fp, AnimaleNodo* root) {
    
    //int dim = height(root);
    int a = 1; 
    rinumera(root);
    //showAlberoPreOrder(root);
    int h = height(root);
    //printf("HEIGHT: %d\n", h);
    int i = 1;
    for(; i <= h; i++) saveFileLevel(fp, root, i);  
}

void    saveFileLevel(FILE* fp, AnimaleNodo* root, int level) {

    //printf("LEVEL: %d\n", level);
    if(!root) {
        
        //fprintf(fp, "%d-zz;", root->id);
        //printf("%d-zz;\n", root->id);
        return;
    }
    if(level == 1) {
        
        fprintf(fp, "%d-%s;", root->id, root->text);
        //printf("%d-%s;", root->id, root->text);
    }


    else if(level > 1) {

        saveFileLevel(fp, root->yes, level - 1);
        saveFileLevel(fp, root->no, level - 1);
    }
}

void    disposerAnimaleNodo(AnimaleNodo* root) {

    if(root) {

        disposerAnimaleNodo(root->yes);
        disposerAnimaleNodo(root->no);
        free(root);
    }
}

void    showAlberoPreOrder(AnimaleNodo* root) {

    if(root) {

        printf("SHOWING: %d-%s ", root->id, root->text);
        if(!root->yes) printf("-NULL");
        else printf("-collegato");
        if(!root->no) printf("-NULL\n");
        else printf("-collegato\n");
        showAlberoPreOrder(root->yes);
        showAlberoPreOrder(root->no);
    }
}

void rinumera(AnimaleNodo* root) {

    if(root) {

        rinumera(root->yes);
        root->id = counter;
        counter++;
       // printf("root->text = %s, root->id = %d\n", root->text, root->id);
        rinumera(root->no);
    }
}
#endif  