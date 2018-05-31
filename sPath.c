#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

typedef struct Edge{
	int vertex[2];
	int weight;
	int visited;
}Edge;

int d[30];
int parent[30];
int visited[30];
int vNum=0;
Edge edge[200];
char order[30][100]; //index for vertex name since we'll consider all vertex as integer in the program.


void relax(u, v, weight){
	if(d[v] > d[u]+weight){
		d[v] = d[u] + weight;
		parent[v] = u;	
	}
}	

void dijkstra(int matrix[][30], int source){
	
	int i;
	int j;
	int s = source;
	int u;
	int sum = 0;	

	for(i=0;i<vNum;i++){
		d[i] = 10000;
	}
	d[s] = 0;
	
	for(i=0;i<vNum;i++)
		visited[i] = 0;

	int idx;
	while(sum != vNum){
	
		for(i=0;i<vNum;i++){
			if(visited[i]==0){
				int min = d[i];
				for(j=0;j<vNum;j++){
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
		
		for(i=0;i<vNum;i++){
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
	
	for(i=0;i<vNum;i++){
		d[i] = 10000;
	}
	d[s] = 0;

	for(i=0;i<200;i++){
		edge[i].visited = 0;
	}
	
	for(i=0;i<vNum-1;i++){
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

void Floyd(int matrix[][30]){

	int i,j,k;
	int D[30][30];

	for(i=0;i<vNum;i++){
		for(j=0;j<vNum;j++){
			D[i][j] = matrix[i+1][j+1];
		}
	}


	for(i=0;i<vNum;i++){
		for(j=0;j<vNum;j++){
			for(k=0;k<vNum;k++){	
				if(D[j][i] + D[i][k] < D[j][k]){
					D[j][k] = D[j][i] + D[i][k];
				}		
			}
		}
	}

	printf("\t");
	for(i=0;i<vNum;i++){
		printf("%-10s",order[i]);
	}
	printf("\n");


	for(i=0;i<vNum+1;i++){
		if(i==0) continue;
		else{
			for(j=0;j<vNum+1;j++){
				if(j==0){
					printf("%-10s",order[i-1]);
				}
				else{
					printf("%-10d",D[i-1][j-1]);
				}
			}
			printf("\n");
		}
	}
	
}

int main() {

	FILE *fp ; //파일 포인터
        fp = fopen("hw5.data","r");

        char storage[30][30][100];
	char * token;
	char string[100];
	int i;
	int j;

	if( fp != NULL )
	{
		i=0;
		while(!feof(fp))
		{
			fgets(string,100,fp );
			
			token = strtok(string," \t\n\v\f\r");
			j=0;
			while( token != NULL ){
				strcpy(storage[i][j], token);
				if(i==0){
					strcpy(order[j],token);
					vNum++;
				}
				token = strtok(NULL, " \t\n\v\f\r");
				j++;
				
			}
			i++;		
		}
		fclose(fp);
	}

//	for(i=0;i<11;i++) printf("%s\n",index[i]);

/*	for(i=0;i<11;i++){
		for(j=0;j<11;j++){
			 printf("%s ",storage[i][j]); 			
		}
		printf("\n");
	}*/

	int matrix[30][30];
	for(i=1;i<vNum+1;i++){
		for(j=1;j<vNum+1;j++){
			if(strcmp(storage[i][j],"INF")==0)
				matrix[i][j] = 10000;
			else 
				matrix[i][j] = atoi(storage[i][j]);
		}
	}

	for(i=1;i<vNum+1;i++)
		matrix[0][i] = i-1;
	for(i=1;i<vNum+1;i++)
		matrix[i][0] = i-1;

/*	for(i=0;i<11;i++){
		for(j=0;j<11;j++){
			if(i==0 && j==0) continue;
				printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}*/

	printf("Dijkstra Algorithm Applied |V| times: \n\n");	
	/* Apply dijkstra |V| times */

	printf("\t");	
	for(i=0;i<vNum;i++){
		printf("%-10s",order[i]);
	}
	printf("\n");

	
	clock_t begin = clock();
	for(i=0;i<vNum+1;i++){

		if(i==0)
			continue;
		else{
	
			dijkstra(matrix,i-1);
			for(j=0;j<vNum+1;j++){
				if(j==0){
					printf("%-10s", order[i-1]);
				}
				else{
					printf("%-10d",d[j-1]);
				}
			}
			printf("\n");
		}
	}

	clock_t end = clock();

	printf("------------------------------------------------\n");
	printf("Dijkstra time spent : %fseconds \n",(double)(end-begin)/1000);
	printf("------------------------------------------------\n");
	/* Calculate Edges and its weight from Adj.Matrix */
	int size = 0;
	int k=2;
	for(i=1;i<vNum+1;i++){
		for(j=k;j<vNum+1;j++){
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
	
	printf("Bellman-Ford Alogirhtm Applied |V| times: \n\n");
	/* Apply Bellman-Ford |V| times */

	printf("\t");	
	for(i=0;i<vNum;i++){
		printf("%-10s",order[i]);
	}
	printf("\n");

	begin = clock();
	for(i=0;i<vNum+1;i++){

		if(i==0)
			continue;
		else{
			if(Bellman_Ford(i-1,size)){
				for(j=0;j<vNum+1;j++){
					if(j==0){
						printf("%-10s", order[i-1]);
					}
					else{
						printf("%-10d",d[j-1]);	
					}
				}	
				printf("\n");
			}
			else{
				printf("negative cycle exists when source is %d!\n",i);
			}
		}
	}
	end = clock();
	printf("------------------------------------------------\n");
	printf("Bellman-Ford time spent : %fseconds \n",(double)(end-begin)/1000);
	printf("------------------------------------------------\n");

	printf("Floyd Algorithm Applied :\n\n");	
	/* Applly Floyd Algirhtm*/
	begin = clock();
	Floyd(matrix);
	end = clock();
	printf("------------------------------------------------\n");
	printf("Floyd time spent : %fseconds \n",(double)(end-begin)/1000);
	printf("------------------------------------------------\n");
	
	return 0;
}
