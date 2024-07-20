#include "definations.c"

char* stripPath(char str[]){
    char *ret = malloc(300*sizeof(char));

    int index =0;
    int find = 0;

    while(str[index] != '\0'){

        if(str[index]=='/' || str[index] == '\\'){
            find = index+1; 
        }
        index++;

    }

    index = 0;

    while(str[find]!='\0'){
        ret[index++]=str[find++];
    }
    ret[index] = '\0';

    return ret;
}

size_file convertSize(size_file size,char id){

    int mul = 1;

    switch(id){

        case 'g':   mul *= 1024;
        case 'm':   mul *= 1024;
        case 'k':   mul *= 1024;
        case 'b':   mul *= 1; break;
        default: Error("Invalid size identifier");
    }

    return mul * size;
}


void fixedChunkH(){
    char fileName[300],sid;
    size_file chunkSize,fileSize;

    FILE *source_file;

    printf("Enter file name/path:");
    scanf("%s",fileName);
    printf("Enter chunk size with b(byte) k(kilo-byte) m g :");
    scanf("%llu",&chunkSize);
    scanf("%c",&sid);

    chunkSize = convertSize(chunkSize,sid);

    source_file = fopen(fileName,"rb");

    if(source_file == NULL){
        Error("Faild to open source file");
    }

    fseek(source_file,0,SEEK_END);

    fileSize = ftell(source_file);
    
    fseek(source_file,0,SEEK_SET);

    if(fileSize < chunkSize){
        Error("Invalid Chunk size");
    }

    fixedChunks(chunkSize,source_file,fileName);

    fclose(source_file);
    fclose(records_file);

    records_file = NULL;

}

void cutChunkH(){

   

}

size_file reverseInt(size_file n){
    
    size_file rev = 0;
    
    while(n){
        rev = rev*10 + n%10;
        n = n/10;
    }

    return rev;
}

FILE* getFileToWrite(char name[],size_file count){

    FILE *fptr;

    char fname[300];
    char sn[30];

    sprintf(sn,"%llu",count);

    strcpy(fname,name);
    strcat(fname,sn);
    strcat(fname,".chk");

   
    fptr = fopen(fname,"wb");
    
    if(fptr==NULL){
        Error("Failed to create file in function getFileToWrite");
    }

    char *stripPathFilePtr = stripPath(fname);

    makeRecord(stripPathFilePtr);
    free(stripPathFilePtr);

    return fptr;

}

void initializeRecord(char *fileName){
    if(records_file ==NULL){
        char str[300];
        strcpy(str,fileName);
        strcat(str,"rec.txt");   

        if(fileExists(str)){
            Error("Records file already exists");
        }

        records_file = fopen(str,"w");

        if(records_file == NULL){
            Error("Failed to create records file");
        }

        char *stripPathFilePtr = stripPath(fileName);

        fprintf(records_file,"%s\n",stripPathFilePtr);
        free(stripPathFilePtr);

        return;
    }

    Error("Records file is already initialized");
}

int fileExists(char *str){

    FILE *ptr = fopen(str,"r");

    if(ptr == NULL)
    return 0;

    fclose(ptr);

    return 1;

}

void makeRecord(char *str){

    if(records_file == NULL){
        Error("Records file not initialized");
    }

    fprintf(records_file,"%s\n",str);

}

void combineChunkH(){
    
    char outputFileName[300];
    char tempStr[300];
    FILE *outputFile = NULL;
    char recFileName[300];
    

    printf("Enter record file name/path: ");
    scanf("%s",recFileName);

    if(records_file != NULL){
        Error("Records file pointer is not NULL");
    }

    records_file = fopen(recFileName,"r");

    if(records_file == NULL){
        Error("Cannot open records file");
    }

    strcpy(path,recFileName);

    char *stripPathFilePtr = stripPath(recFileName);

    int i  = strlen(stripPathFilePtr);
    free(stripPathFilePtr);

    int j = strlen(recFileName);

    if(j-i < 0){
        Error("Failed to find path");
    }
   
    path[j-i]='\0';

    strcpy(outputFileName,path);

    fscanf(records_file,"%s[^\n]",tempStr);
    
    strcat(outputFileName,tempStr);

    outputFile = fopen(outputFileName,"r");
    if(outputFile != NULL){
        fclose(outputFile);
        Error("Output file named file already exists");
    }
    outputFile = fopen(outputFileName,"wb");

    combineChunk(outputFile);

    
    fclose(records_file);
    records_file =  NULL;

}

FILE* getNextChunk(){

    char buffer[300];
    char fileName[300];
    FILE *ret = NULL;

    if(fscanf(records_file,"%s[^\n]",buffer)!=EOF){

        strcpy(fileName,path);
        strcat(fileName,buffer);

        ret = fopen(fileName,"rb");

        if(ret == NULL){
            Error("Faild to open chunk file");
        }

        return ret;
    }
    

    return NULL;

}
