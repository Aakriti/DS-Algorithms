#include<stdio.h>
#include<stdlib.h>

struct node {
	int val;
	struct node * next;
	};

struct node * top[3],* temp[3], * ptr;
int count=0,n,t1,t2,t3;

void display() {
	temp[0]=top[0];
	temp[1]=top[1];
	temp[2]=top[2];
	printf("\nTowers of Hanoi. Disk Shifting Operation:%d\n",count);
	while(temp[0]!=NULL)
	{
		printf("%d  %d  %d\n",temp[0]->val,temp[1]->val,temp[2]->val);
		temp[0]=temp[0]->next;
		temp[1]=temp[1]->next;
		temp[2]=temp[2]->next;
	}
}

void push(int x,int d) {
	temp[d] = top[d];	
	while (temp[d]->val==0) {
		ptr=temp[d];
		if(temp[d]->next!=NULL)
			temp[d]=temp[d]->next;
		else{
			ptr->val=x; break; }
		}
	ptr->val=x;
}

int pop(int d) {
	int popped;
	temp[d]=top[d];
	while(temp[d]->val==0 && temp[d]!=NULL)
		temp[d]=temp[d]->next; 

	popped = temp[d]->val;
	temp[d]->val=0;
	return popped;
}

void inits() {
	int i;	
	top[0] = malloc(sizeof(struct node));
	top[1] = malloc(sizeof(struct node));
	top[2] = malloc(sizeof(struct node));

	top[0]->next=NULL;
	top[1]->next=NULL;
	top[2]->next=NULL;

	top[t1]->val=n;
	top[t2]->val=0;
	top[t3]->val=0;


	for(i=n-1;i>=1;i--) {
		temp[t1] = malloc(sizeof(struct node));
		temp[t1]->val = i;
		temp[t1]->next=top[t1];
		top[t1]= temp[t1];

		temp[t2] = malloc(sizeof(struct node));
		temp[t2]->val = 0;
		temp[t2]->next=top[t2];
		top[t2] = temp[t2];

		temp[t3] = malloc(sizeof(struct node));
		temp[t3]->val = 0;
		temp[t3]->next=top[t3];
		top[t3] = temp[t3];	
	}}

void Hanoi(int numb, int from, int using, int to) {
	int temp;
	if(numb == 1) {
		temp = pop(from);
		push(temp,to);
		count++; 
		display();}
	else {
		Hanoi(numb-1,from,to,using);
		Hanoi(1,from,using,to);
		Hanoi(numb-1,using,from,to); }
	}


main() {
	int p;

	printf("Enter Value of N:");
	scanf("%d",&n);
		if(n<1) { printf("Wrong Input. (N>0).\n"); return; }
	printf("Enter Initial Tower(1,2,3):");
	scanf("%d",&t1);
		if(t1!=1 && t1!=2 && t1!=3) { printf("Wrong Input\n"); return; }
	t1=t1-1;
	printf("Enter Final Tower(1,2,3):");
	scanf("%d",&t2);
		if(t2!=1 && t2!=2 && t2!=3) { printf("Wrong Input\n"); return; }
	t2=t2-1;


	if(t1==0) {
		if(t2==1)
			t3=2;
		else
			t3=1;}
	else if(t1==1) {
		if(t2==0)
			t3=2;
		else
			t3=0;} 
	else {
		if(t2==1)
			t3=0;
		else
			t3=1;}

	
	inits(n,t1);
	display();
	Hanoi(n,t1,t3,t2);

	printf("For N = %d Complexity = %d\n",n,count);

	}
