#include<stdio.h>
#include<string.h> 
#include<stdlib.h>

#define d 51
int flag = 0;

void search(char *pat, char *txt, int q, int line_no, int offset)
{
    int M = strlen(pat);
    char txt2[M];
    int N = strlen(txt);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
  
    for (i = 0; i < M-1; i++)
        h = (h*d)%q;
    
    i=0; j=0;
    while(i<N)
    {
	
	if(txt[i]>='A' && txt[i]<='Z') {
       		txt2[j] = txt[i] + 32;
		j++; }
 
	if(txt[i]>='a' && txt[i]<='z') {
       		txt2[j] = txt[i];
		j++; }
	if(txt[i]>='0' && txt[i]<='9') {
	      	txt2[j] = txt[i];
		j++; }

		i++;
    }

    for (i = 0; i < M; i++)
    {
        p = (d*p + pat[i])%q;
        t = (d*t + txt2[i])%q;
    }
  
    for (i = 0; i <= N - M; i++)
    {      
        if ( p == t )
        {      
            for (j = 0; j < M; j++)
            {
                if (txt2[i+j] != pat[j])
                    break;
            }
            if (j == M)  
            {
                printf("Pattern found at line:%d offset: %d\n", line_no, i+offset);
		flag++;
            }
        }                  
        if ( i < N-M )
        {
            t = (d*(t - txt2[i]*h) + txt2[i+M])%q;           
            if(t < 0) 
              t = (t + q); 
        }
    }
}


int main()
{
    
    int sz = 500;
    char *txt = malloc(sz*sizeof(char));
    char ch = 'a';
    int i = 0,j = 0;
    int q = 101;
    int line_no = 1, offset = 0;
  
    char str[50],pat[50];

    printf("\nEnter string to compare:");
    gets(str);

	for(i=0;str[i]!='\0';i++){
		
      		if(str[i]>='A' && str[i]<='Z') {
       			pat[j] = str[i] + 32;
			j++; 
		}
		if(str[i]>='a' && str[i]<='z') {
			pat[j] = str[i];
			j++;
		}
		if(str[i]>='0' && str[i]<='9') {
			pat[j] = str[i];
			j++;
		}
  	}
	pat[j] = '\0';
	

    int M = strlen(pat);

    FILE *f;
    f = fopen("American-english.txt","r");
//    f = fopen("dictionary.txt","r");

	while(!feof(f)) 
	{
		fgets(txt, sz, f);
		search(pat,txt,q,line_no,offset);
		if ( strlen(txt) < sz-1 )
		{
			line_no++;
			offset = 0;
		}
		else
		{
			offset += sz-M-1;
			fseek(f,-M,SEEK_CUR);
		}
	}

	if(flag == 0)
		printf("\nPattern not found.\n");
	else
		printf("\nTotal number of matches:%d\n",flag);

    return 0;
}
