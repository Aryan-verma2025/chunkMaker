#define size_file unsigned long long


#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void fixedChunks(size_file, FILE*, char[]);
void Error(char*);
void Log(char*);
void fixedChunkH();
void cutChunkH();
FILE* getFileToWrite(char[],size_file);
void makeRecord(char*);
char* stripPath(char*);
void initializeRecord(char*);
int fileExists(char*);
void combineChunkH();
void combineChunk(FILE*);
FILE* getNextChunk();

extern FILE* records_file;
extern char path[250];