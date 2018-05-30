#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define numOfVertex 10

int main() {

	FILE *fp ; //파일 포인터
        fp = fopen("hw5.data","r");

        char storage[11][11][100];
	char * token;
	char string[100];
	int cnt = 0;
	int i;
	int j;
	
	if( fp != NULL )
	{
		i=0;
		while(i<11)
		{
			fgets(string,100,fp );
			
			token = strtok(string," \t\n\v\f\r");
			j=0;
			while( token != NULL ){
				strcpy(storage[i][j], token);
				token = strtok(NULL, " \t\n\v\f\r");
				j++;
				
			}
			i++;		
		}

	}

	for(i=0;i<11;i++){
		for(j=0;j<11;j++){
			 printf("%s ",storage[i][j]); 			
		}
		printf("\n");
	}
	return 0;
}
