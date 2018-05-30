#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define numOfVertex 10

int main() {

	char * token = NULL;
	char delimiter[] = " \n\r\b\t";
	char *pStr;
	char string[100];	
	char* storage[100];
	pStr = "		Busan	Daegu	Daejeon	Gangeung	Gwangju	Jeonju	Jinju	Pohang	Seoul Wonju";		
	strcpy(string,pStr);
	token = strtok(string,delimiter);
	int j=0;
	while( token != NULL){	
//	printf("token = %s\n",token);
	//	strcpy(storage[j],token);
		storage[j] = token;
		token = strtok(NULL, delimiter);
		j++;
	}

	int i;
	for(i=0;i<j;i++){
		printf("result: %s\n",storage[i]);
	}
	return 0;
}
