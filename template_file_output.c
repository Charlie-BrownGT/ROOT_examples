//include any libraries here
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <complex.h>

//initialise main function
int main(){

	//declare variable named fp that is a pointer to FILE structure
	FILE *fp;

	//declare any variables that you need
	int i, j;
	double x, y, x_err, y_err;

	//open fp in write mode
	fp = fopen("template_data_output.txt", "w");

	//exit the programme is file cannot be opened
	if (fp == NULL){
		printf("Error opening file.\n");
		return 1;
	}

	//optional - write headers to data file
	//fprintf(fp, "x\ty\tx_err\ty_err\n");

	j = 1000;

	//write function that produces data
	for(int i = 0; i < j; i++){
		x = i;
		y = sin(x);
		x_err = 0.1;
		y_err = 0.1;

		//write the data to the file
		fprintf(fp, "%f %f %f %f\n", x, y, x_err, y_err);
	}

	//close the file
	fclose(fp);

	//write a confirmation message
	printf("The data has been written to file named template_data_output.txt.\n");

	return 0;
}
