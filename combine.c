#include "definations.c"

void combineChunk(FILE *outputFile){
    
    FILE *inputFile = getNextChunk();
    char buffer;

    while(inputFile != NULL){

        fread(&buffer,1,1,inputFile);

        while(!feof(inputFile)){

            fwrite(&buffer,1,1,outputFile);
            fread(&buffer,1,1,inputFile);
        }

        fclose(inputFile);
        inputFile = getNextChunk();

    }

    fclose(outputFile);
    

}