#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define numOfVertex 10

int d[10];
int parent[10];
int visited[10];

void relax(u, v, weight){
	if(d[v] > d[u]+weight){
		d[v] = d[u] + weight;
		parent[v] = u;	
	}
}	

void dijkstra(int matrix[][11], int source){
	
	int i;
	int j;
	int s = source;
	int u;
	int sum = 0;	

	for(i=0;i<10;i++){
		d[i] = 10000;
	}
	d[s] = 0;
	
	for(i=0;i<10;i++)
		visited[i] = 0;

	
	//for(i=0;i<10;i++) Q[i] = i;
	int idx;
	while(sum != 10){
	
//		int min = 0;
		for(i=0;i<10;i++){
			if(visited[i]==0){
				int min = d[i];
				for(j=0;j<10;j++){
					if(visited[j]==0){
						if(min >= d[j]){
							min = d[j];
							idx = j;
						}

					}
				}
			}
		}
		visited[idx] = 1;
		u = idx;
		
//		printf("%d \n",u);
		
		for(i=0;i<10;i++){
			if(matrix[u+1][i+1]>0 && matrix[u+1][i+1]<10000)
				relax(u, i, matrix[u+1][i+1]);
		}

		sum += visited[idx]; 
	
	}
//	for(i=0;i<10;i++) printf("%d ",d[i]);
}

int main() {

	FILE *fp ; //파일 포인터
        fp = fopen("hw5.data","r");

        char storage[11][11][100];
	char * token;
	char string[100];
	char index[10][100];
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
				if(i==0)
					strcpy(index[j],token);
				token = strtok(NULL, " \t\n\v\f\r");
				j++;
				
			}
			i++;		
		}

	}

//	for(i=0;i<10;i++) printf("%s\n",index[i]);

/*	for(i=0;i<11;i++){
		for(j=0;j<11;j++){
			 printf("%s ",storage[i][j]); 			
		}
		printf("\n");
	}*/

	int matrix[11][11];
	int k;
	for(i=1;i<11;i++){
		for(j=1;j<11;j++){
			if(strcmp(storage[i][j],"INF")==0)
				matrix[i][j] = 10000;
			else 
				matrix[i][j] = atoi(storage[i][j]);
		}
	}

	for(i=1;i<11;i++)
		matrix[0][i] = i-1;
	for(i=1;i<11;i++)
		matrix[i][0] = i-1;


/*	for(i=0;i<11;i++){
		for(j=0;j<11;j++){
			if(i==0 && j==0) continue;
				printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}*/


	for(i=0;i<10;i++){
		dijkstra(matrix,i);
		for(j=0;j<10;j++){
			printf("%d ",d[j]);
		}
		printf("\n");
	}

	return 0;
}
