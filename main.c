#include "definations.c"

void printLogo(){
    printf(" _____ _                 _     ___  ___      _             \n/  __ | |               | |    |  \\/  |     | |            \n| /  \\| |__  _   _ _ __ | | __ | .  . | __ _| | _____ _ __ \n| |   | \'_ \\| | | | \'_ \\| |/ / | |\\/| |/ _` | |/ / _ | \'__|\n| \\__/| | | | |_| | | | |   <  | |  | | (_| |   |  __| |   \n \\____|_| |_|\\__,_|_| |_|_|\\_\\ \\_|  |_/\\__,_|_|\\_\\___|_|   \n\n");
}


int main(){

    printLogo();

    char choice,tmp;

    do{
        printf("\n");
        printf("[1] Create Chunks\n");
        printf("[2] Combine Chunks\n");
  
        printf("EXIT [0]\n");

        printf("Enter Choice: ");

        scanf("%c",&tmp);

        while(tmp != '\n' && !(feof(stdin))){
            choice = tmp;
            scanf("%c",&tmp);
        }

        tmp = 'a';

        if(feof(stdin)){
            exit(0);
        }

        switch(choice){
            case '0':   exit(0);
                        break;
            case '1':   printf("Creating chunks...\n");
                        fixedChunkH();
                        scanf("%c",&tmp);
                    break;
            case '2':   printf("Combining chunks...\n");
                        combineChunkH();
                        scanf("%c",&tmp);
                    break;
            default:printf("Invalid choice!\n");

        }
    }while(1);

    return 0;
}