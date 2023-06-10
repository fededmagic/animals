#include "AnimaleNodo.h"
#include "AnimaleLoadSave.h"

#define MAX_STR 1024

char* inputStr();
char* inputStrPrompt(char*);
int askSiNo(char*);
AnimaleNodo* creaNuovoAnimale(AnimaleNodo*);

int main(int argc, char** argv) {	

	FILE* fpopen = fopen("persistance.txt", "r");
	if(!fpopen) {

		printf("Cannot open the persistance file\n");
		return -1;
	}

	AnimaleNodo* albero = NULL;
	albero = loadFile(fpopen, albero);
	AnimaleNodo* curr = albero;	;

	fclose(fpopen);

	int game = 1;

	while(game == 1) {

		if(isLeaf(curr)) {

			if(askSiNo(curr->text)) printf("Ho vinto!");
			else {
				printf("Non ho indovinato!");
				curr = creaNuovoAnimale(curr);
			}
			curr = albero;
			
			printf("\nContinuare a giocare? (s/n) ");
			char* ans = inputStr();
			if(strcmp(ans, "n") == 0) game = 0;
			free(ans);
		}
		else {

			if(askSiNo(curr->text)) curr = curr->yes;
			else curr = curr->no;
		}
	}

	FILE* fpsave = fopen("persistance.txt", "w");
	if(!fpsave) {

		printf("Cannot open the persistance file\n");
		return -1;
	}

	//showAlberoPreOrder(albero);

	saveFile(fpsave, albero);

	fclose(fpsave);

	disposerAnimaleNodo(albero);

	return 0;
}

char* inputStr() {
	
	char buffer[MAX_STR];
	int i= 0;
	for(; (*(buffer + i) = getchar())!= '\n'; i++) { }
	*(buffer + i) = '\0';
	return strdup(buffer);
}

char* inputStrPrompt(char* prompt) {

	printf("%s ", prompt);
	return inputStr();
}

int askSiNo(char* prompt) {

	printf("%s? (s/n): ",prompt);
	char* ans;
	while((strcmp(ans = inputStr(), "s"))!=0 && (strcmp(ans, "n") != 0));
	return (strcmp(ans, "s") == 0);
}

AnimaleNodo* creaNuovoAnimale(AnimaleNodo* curr) { 

	char* text = inputStrPrompt("Che animale era?\n");
	printf("Inserisci una domanda per distinguere un %s da un %s (in caso di risposta positiva sara' un %s): ", 
		curr->text, text, text);
	char* question = inputStr();
	
	AnimaleNodo* nuovo = createAnimaleNodo(text, 0, NULL, NULL);
	AnimaleNodo* vecchio = createAnimaleNodo(curr->text, 0, NULL, NULL);	
	setAnimal(curr, question, nuovo, vecchio);

	free(text);
	free(question);
	
	return curr;	
}
