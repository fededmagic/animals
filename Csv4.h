#ifndef __CSV4_H__
#define __CSV4_H__

#define DIM 1024

char* readline(FILE*);
char** split(char*, char);
char** duplicatore(char**);

char* readline(FILE* fp){

    char buffer[DIM];
    int i = 0;
    for(; (*(buffer + i) = fgetc(fp)) != EOF && (*(buffer + i) != '\n'); i++);
    if(!i) return NULL;
    *(buffer + i) = '\0';
    return strdup(buffer);
}

char** split(char* str, char sep){

    char* buffer[DIM];
    char separator[] = {sep, '\0'};
    *buffer = strtok(str, separator);
    int i = 1;
    for(; *(buffer + i) = strtok(NULL, separator); i++);
    return duplicatore(buffer);
}

char** duplicatore(char** array){

    int i = 0;
    for(; *(array + i); i++);
    char** ret = (char**) malloc(sizeof(char*) * (i + 1));
    char** tmp = ret;
    for(; *tmp = *array; tmp++, array++);
    return ret;
}

#endif