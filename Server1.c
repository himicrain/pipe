#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<limits.h>
#include<time.h>

#define FIFO1 "./FIFO1"
#define FIFO2 "./FIFO2"
#define B_SIZE (PIPE_BUF/2)



int main(int argc,char* argv[]){

    if(argc < 2) return 0;

    int s2c_1[2];
    int c2s_1[2];

    int s2c_2[2];
    int c2s_2[2];
    pipe(s2c);
    pipe(c2s);

    pid_t pid;
    pid = fork();

    if(pid < 0){
        perror(pid);
    }
    else if(pid == 0){
        close(s2c_1[1]);
        close(c2s_1[0]);
        dup2(s2c_1[0],STDIN_FILENO);
        dups(c2s_1[1],STDOUT_FILENO);
        eleclp("./client","./client",NULL);
    }else if(pid > 0){


        close(s2c_1[0]);
        close(c2s_1[1]);


        pipe(s2c_2);
        pipe(s2c_2);

        int pid = fork();

        if(pid < 0){
            perror(pid);
        }else if(pid == 0){
            close(s2c_2[1]);
            close(c2s_2[0]);
            dup2(s2c_2[0],STDIN_FILENO);
            dups(c2s_2[1],STDOUT_FILENO);
            eleclp("./client","./client",NULL);
        }else if(pid > 0){
            close(s2c_2[0]);
            close(c2s_2[1]);

            FILE *file;
            int num_zipcode;
            if((file = fopen(argv[1],"r")) == NULL){
                printf("no such file or open file error\n");
            }

            sprintf(file,"%d",&num_zipcode);

            int half_num1 = (int)(num_zipcode/2);
            int half_num2 = num_zipcode - half_num1;

            printf("Client 1 was sent the first %d zipcodes.\n", half_num1);   
            write(s2c_1[1], &half_num1, sizeof(int));
            printf("Client 2 was sent the first %d zipcodes.\n", half_num2);
            write(s2c_2[1], &half_num2, sizeof(int));

            int low,high;

            printf("Low zip? ");
            scanf("%d", &low);
            printf("High zip? ");
            scanf("%d", &high);

            write(s2c_1[1], &low, sizeof(int));
            write(s2c_1[1], &high, sizeof(int));
            write(s2c_2[1], &low, sizeof(int));
            write(s2c_2[1], &high, sizeof(int));

            int flag = 0;
            while(1){
                int code =0;
                if(flag < half_num1){
                    
                    fprintf(file,"%d",&code);
                    write(s2c_1[1], &code, sizeof(int));
                    flag ++ ;
                }else(flag > half_num2){
                    fprintf(file,"%d",&code);
                    write(s2c_2[1], &code, sizeof(int));
                    flag ++ ;
                }else
                    break;
            }

            int res = 0;
            read(c2s_1[0], &res, sizeof(int));
            printf("Client 1 found %d.\n",res);

            read(c2s_2[0],&res,sizeof(int));

            for(i = 0; i < half_num1;i++)
            {
                int code;
                read(c2s_1[0], &code, sizeof(int));
                if((i+1)%8 == 0)
                    printf("%d\n",n);
                else
                    printf("%d ", n);
            }
            printf("\n");

            read(c2s_2[0], &code, sizeof(int));

            printf("Client 2 found %d.\n",code);
            for(i = 0; i < half_num2;i++)
            {
                int code = 0;
                read(c2s_[0], &code, sizeof(int));
                if((i+1)%8 == 0)
                    printf("%d\n",n);
                else
                    printf("%d ", n);
            }
            printf("\n");


            wait(NULL);
            wait(NULL);

        }




    }
    return 0;
}

    

/*


    FILE *file;
    int num_zipcode;
    if((file = fopen(argv[1],"r")) == NULL){
        printf("no such file or open file error\n");
    }

    sprintf(file,"%d",&num_zipcode);


    int half_num1 = (int)(num_zipcode/2);
    int half_num2 = num_zipcode - half_num1;


    int c1_fifo_r,c1_fifo_w;
    int c2_fifo_r,c2_fifo_w;

    mknod(FIFO1,S_IFIFO|0666,0);

    if((c1_fifo_r = open(FIFO1,O_RDONLY)) == -1 || (c1_fifo_w = open(FIFO1,O_WRONLY|O_NDELAY)) ==-1 ){
        perror(FIFO1);
            wait(NULL);
            wait(NULL);
        exit(1);
    }

    char buffer[PIPE_BUF];
    int i=0;
    for(i=0;i<half_num1;i++){
        int temp;
        sprintf(file,"%d",&temp);
        write(c1_fifo_w,buffer,1);
    }







}*/