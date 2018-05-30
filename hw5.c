#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#define numOfVertex 10

typedef struct Edge{
	int vertex[2];
	int weight;
	int visited;
}Edge;

int d[10];
int parent[10];
int visited[10];
Edge edge[200];

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

	int idx;
	while(sum != 10){
	
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
}

int Bellman_Ford(int source, int size){

	int i;
	int j;
	int s = source;
	int sum = 0;	
	
	for(i=0;i<10;i++){
		d[i] = 10000;
	}
	d[s] = 0;

	for(i=0;i<50;i++){
		edge[i].visited = 0;
	}
	
	for(i=0;i<9;i++){
		for(j=0;j<size;j++){
			relax(edge[j].vertex[0],edge[j].vertex[1],edge[j].weight);
		}	
	}
	sum=0;
	size=0;

	for(i=0;i<size;i++){
		edge[i].visited = 0;
	}

	for(i=0;i<size;i++){
		if( d[ edge[i].vertex[1] ] > (d[ edge[i].vertex[0] ] + edge[i].weight) )
			return 0;
		edge[i].visited = 1;
		sum += edge[i].visited;
	}	

	return 1;
}

void Floyd(int matrix[][11]){

	int i,j,k;
	int D[10][10];

	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			D[i][j] = matrix[i+1][j+1];
		}
	}


	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			for(k=0;k<10;k++){	
				if(D[j][i] + D[i][k] < D[j][k]){
					D[j][k] = D[j][i] + D[i][k];
				}		
			}
		}
	}

	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			printf("%d ",D[i][j]);
		}
		printf("\n");
	}
	
}

int main() {

	FILE *fp ; //파일 포인터
        fp = fopen("hw5.data","r");

        char storage[11][11][100];
	char * token;
	char string[100];
	char index[10][100]; //index for vertex name since we'll consider all vertex as integer in the program.
	int i;
	int j;
	int cnt=0;

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
				if(i==0){
					strcpy(index[j],token);
					cnt++;
				}
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

	clock_t begin = clock();
	printf("Dijkstra Algorithm Applied |V| times: \n\n");	
	/* Apply dijkstra |V| times */
	for(i=0;i<10;i++){
		dijkstra(matrix,i);
		for(j=0;j<10;j++){
			printf("%d ",d[j]);
		}
		printf("\n");
	}

	clock_t end = clock();

	printf("------------------------------------------------\n");
	printf("Dijkstra time spent : %fseconds \n",(double)(end-begin)/1000);
	printf("------------------------------------------------\n");
	/* Calculate Edges and its weight from Adj.Matrix */
	int size = 0;
	int k=2;
	for(i=1;i<11;i++){
		for(j=k;j<11;j++){
			if(matrix[i][j]>0 && matrix[i][j]<10000){
				edge[size].vertex[0] = i-1;
				edge[size].vertex[1] = j-1;
				edge[size].weight = matrix[i][j];
				size++;
				edge[size].vertex[1] = i-1;
				edge[size].vertex[0] = j-1;
				edge[size].weight = matrix[i][j];
				size++;
			}
		}
		k++;
	}	
	// Check if edges are calculated well 
/*	for(i=0;i<size;i++){
		printf("edge: (%d,%d) ",edge[i].vertex[0], edge[i].vertex[1]);
		printf("weight: %d\n",edge[i].weight);	
	}*/
	
	begin = clock();
	printf("Bellman-Ford Alogirhtm Applied |V| times: \n\n");
	/* Apply Bellman-Ford |V| times */
	for(i=0;i<10;i++){
		if(Bellman_Ford(i,size)){
			for(j=0;j<10;j++){
				printf("%d ",d[j]);	
			}	
			printf("\n");
		}
		else{
			printf("negative cycle exists when source is %d!\n",i);
		}
	}
	end = clock();
	printf("------------------------------------------------\n");
	printf("Bellman-Ford time spent : %fseconds \n",(double)(end-begin)/1000);
	printf("------------------------------------------------\n");

	begin = clock();
	printf("Floyd Algorithm Applied :\n\n");	
	/* Applly Floyd Algirhtm*/
	Floyd(matrix);
	end = clock();
	printf("------------------------------------------------\n");
	printf("Floyd time spent : %fseconds \n",(double)(end-begin)/1000);
	printf("------------------------------------------------\n");
	
	return 0;
}
