#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct S{
    int numNums;
    double total;
} item;

void storeData(int numFiles, int fd1[][2], char **argv){
    //BaseCase
    if (numFiles == 0) {
        return;
    }

    int pid = fork();
    if (pid == 0) { //Child Process
        storeData(numFiles - 1, fd1, argv);//recursive function call
        FILE *fptr; //Create a file ptr
        if ((fptr = fopen(argv[numFiles], "r")) == NULL) {
            printf("Error Opening File");
            exit(1);
        }

        //Read each line of the file
        double num, sum;
        int inc = 0;
        while (fscanf(fptr, "%lf", &num)) {
            if (feof(fptr)) { break; }  //check for the end of the file
            //printf("Value of num=%f \n", num);
            sum = sum + num;    //Add to the sum
            inc++;  //increment the counter
        }
        //add to the struct
        item val;
        val.total = sum;
        val.numNums = inc;
        //write to the pipe
        write(fd1[numFiles][1], &val, sizeof(val));
        exit(0);
    } else { //Parent Process
        wait(NULL);
    }
}

int main(int argc, char **argv) {
    double nums=0, sum=0;
    int fd1[argc][2], i;
    int mySize = argc - 1;

    //make lots of pipes
    for(i=1; i<=mySize; i++){
        pipe(fd1[i]);
    }

    //go to function
    storeData(mySize, fd1, argv);

    //Iterate through the stored pipe values to add to the total sum and nums
    for(i=1; i<=mySize; i++){
        item val;
        read(fd1[i][0], &val, sizeof(val));
        sum += val.total;
        nums += val.numNums;
    }

    sum = sum/nums;
    printf("The average is = %.2f \n", sum); //print the avg
    return 0;
}

