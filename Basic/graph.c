#include<stdio.h>
#include<stdlib.h>

#define n 11 //Number of vertices. Vertex IDs are from 1 to n.
#define k 20 //Number of Edges.
int i;

int input[k][3] = {{9,10,2},{8,9,20},{8,7,3},{9,4,5},{1,2,1},{2,4,5},{1,0,12},{2,3,45},{3,4,80},{3,0,9},{4,0,2},{1,3,11},{7,2,10},{6,4,10},{5,6,7},{5,3,17},{7,4,16},{1,5,14},{0,7,2},{6,0,3} };

struct node {
	int vertex;
	struct node * next;
	};

struct node *  V[n], * Temp,* ptr;

void Add(int a,int b) //Add a new edge in the graph. Since graph is undirected, add it to the list of both vetrices.
{

	Temp = malloc(sizeof(struct node));
	Temp->vertex = b;
	Temp->next = NULL;
	ptr = V[a];
	while(ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = Temp;

	Temp = malloc(sizeof(struct node)); 
        Temp->vertex = a;
        Temp->next = NULL;
        ptr = V[b];
        while(ptr->next != NULL)
                ptr = ptr->next;
        ptr->next = Temp;
}

void BFS(int start)
{
	int color[n],que[n],top=0,index=top;
	for(i=0;i<n;i++)
		color[i] = 0;

	printf("\nBFS:\n");
	
	que[top] = start;
	color[start] = 1;
	
	while(index != n)
	{
		int a = que[index];
		color[a] = 2;
		index++;

		ptr = V[a]->next;
		while(ptr != NULL)
		{
			if(color[ptr->vertex] == 0)
			{
				top++;
				que[top] = ptr->vertex;
				color[ptr->vertex] = 1;
			}
		ptr = ptr->next;
		}
		
	}

	for(i=0;i<n;i++)
		printf("V%d  ",que[i]);
	printf("\n");
}

void DFS(int start)
{
	printf("\nDFS:\n");
	int color[n],que[n],index=0,top=index;
	int stack[n],stack_top=0;
	for(i=0;i<n;i++)
		color[i] = 0;	
	
	que[top] = start;
	color[start] = 1;
	ptr = V[start];
	stack[stack_top] = start;
	while(index != n)
	{
		int a = que[index];
		color[a] = 2;
		index++;
		while(ptr != NULL)
		{
			if(color[ptr->vertex] == 0)
			{
				top++;
				que[top] = ptr->vertex;
				color[ptr->vertex] = 1;
				ptr = V[ptr->vertex];
				stack_top++;
				stack[stack_top] = que[top];
				
			}
			else
			{
				ptr = ptr -> next;
			}
		}
		stack_top--;
		ptr = V[stack[stack_top]]->next;
	}
	for(i=0;i<n;i++)
		printf("V%d  ",que[i]);
	printf("\n");
}

void Dijkstra(int s, int t)
{
	printf("\nDijkstra:\nVertex1:V%d\tVertex2:V%d\t",s,t);
	int dist[n],temp,d,v,relaxed[n],count=1,parent[n];
	for(i=0;i<n;i++)
	{
		relaxed[i] = 0;
		dist[i] = 9000; //Initialize
		parent[i] = -1;
	}
	relaxed[s] = 1;
	dist[s] = 0;
	i = 0;

	while(i<k)
	{
		if(input[i][0] == s)
			{
				dist[input[i][1]] = input[i][2];
				parent[input[i][1]] = s;
			}
		if(input[i][1] == s)
			{
				dist[input[i][0]] = input[i][2];
				parent[input[i][0]] = s;
			}
		i++;
	}

	while(count<n)
	{
		temp = dist[t];
		d = 9050;
		for(i=0;i<n;i++)
		{
			if(d>dist[i] && relaxed[i] == 0)
			{
				d = dist[i];
				v = i;
			}
		}
		count++;
		relaxed[v] = count;
		i=0;
		while(i<k)
		{
			if(input[i][0] == v)
			{
				if (dist[input[i][1]] > d+input[i][2])
				{
					dist[input[i][1]] = d + input[i][2];
					parent[input[i][1]] = v;
				}
			}
			if(input[i][1] == v)
			{
				if (dist[input[i][0]] > d+input[i][2])
				{
					dist[input[i][0]] = d + input[i][2];
					parent[input[i][0]] = v;
				}
			}
			i++;
		}
	}
	
	printf("\tDistance:%d\t",dist[t]);
	printf("\tPath:");
	i = t;
	printf("V%d",i);
	while(i != s)
	{
		i = parent[i];
		printf("-V%d",i);
	}
	printf("\n");
}

main()
{
	int w,v1,v2,S=10; //S is the starting vertex
	
	printf("\nVertices: ");
	for(i=0;i<n;i++) //Initialize all the vertices.
	{
		V[i] =  malloc(sizeof(struct node));
		V[i]->vertex = i;
		V[i]->next = NULL;
		printf("V%d  ",i);
	}
	printf("\n\n");
	for(i=0;i<k;i++) //Add all the edges.
	{
		v1=input[i][0];
		v2=input[i][1];
		w=input[i][2];
		printf("V%d <-> V%d\t%d\n",v1,v2,w);
		Add(v1,v2);
	}
	BFS(S);
	DFS(S);
	Dijkstra(10,3);
//	Dijkstra(4,8);
//	Dijkstra(0,9);
//	Dijkstra(9,2);
}
