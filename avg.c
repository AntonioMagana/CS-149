#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    double num = 0; //Variables
    int inc = 0;    //Variables
    double sum = 0; //Variables

    FILE *fptr; //Create a file ptr
    //Open the file or exit the program if there is an error
    if ((fptr = fopen(argv[1], "r")) == NULL) {
        printf("Error Opening File");

        exit(1);
    }

    //Read each line of the file
    while(fscanf(fptr, "%lf", &num)) {
        if(feof(fptr)){break;}  //check for the end of the file
        //printf("Value of num=%f \n", num);
        sum = sum + num;    //Add to the sum
        inc++;  //increment the counter
    }

    if(inc != 0) {
        sum = sum / inc;  //compute the average
    }
    printf("Value of sum=%f \n", sum); //print the avg
    fclose(fptr);   //close the file

    return 0;
}