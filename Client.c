#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<limits.h>
#include<time.h>


#define B_SIZE (PIPE_BUF/2)

int main(int argc,char* argv[]){


    int n=0;
    int code =0;
    

    int num =0;

    read(STDIN_FILENO, &num, sizeof(int));

    int low =0,high=0;
    read(STDIN_FILENO, &low, sizeof(int));
    read(STDIN_FILENO, &high, sizeof(int));

    int* num_array = (int *)malloc(num * sizeof(int));

    int* temp_array = (int *)malloc(num * sizeof(int));

    while(n = read(STDIN_FILENO, temp_array, sizeof(int))){

        for(int i=0;i<n;i++){
            num_array[n] = temp_array[i];
            n ++ ;
        }

    }


    for(int i=0;i<num;i++){
        if(num_array[i] >= low && num_array[i] <= high){
            write(STDOUT_FILENO, &num_array[i], sizeof(int));
        }
    }


    return 0;
}
/*

    int num_zipcode = atoi(argv[1]);
    int low = atoi(argv[2]);
    int high = atoi(argv[3]);
    char* fifo;
    char buffer[B_SIZE];
    int fifo_r,fifo_w;
    int n;

    char* data;
    data = (char*)malloc(sizeof(char)*num_zipcode);
    if((fifo_r = open(fifo,O_RDONLY))==-1 || (fifo_w=open(fifo,O_WRONLY)) ==-1){
        perror(fifo);
        exit(1); 
    }
    int i = 0;
    while((n = read(fifo_r,buffer,PIPE_BUF))>0){
        for(int j=0;j<n;j++){
            data[i] = buffer[j];
            i++;
        }
    }

    for(int k=0;k<num_zipcode;k++){
        printf("%d");
    }



}
*/