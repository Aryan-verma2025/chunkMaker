#include "definations.c"

void fixedChunks(size_file chunk_size,FILE *src_file,char file_name[]){
    size_file count = 1;
    char *buffer = malloc(sizeof(char));
    if(buffer == NULL){
        Error("Cant allocate memory for buffer");
    }
    size_file chunkCounter =0;

    initializeRecord(file_name);

    FILE *output_file = getFileToWrite(file_name,count);



    fread(buffer,1,1,src_file);

    while(!feof(src_file)){

        fwrite(buffer,1,1,output_file);
        fread(buffer,1,1,src_file);

        chunkCounter++;

        if(chunkCounter == chunk_size){
            count++;
            fclose(output_file);

            chunkCounter = 0;

            if(!feof(src_file))
            output_file = getFileToWrite(file_name,count);
            else
            output_file = NULL;
        }

    }

    if(output_file!=NULL){
        fclose(output_file);
    }
    free(buffer);

}

