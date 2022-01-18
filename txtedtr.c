#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 256

struct node 
{
	int statno;	
	char statement[40]; 
	int next;
};

struct node textbuffer[30]; 
int head;

struct dfs 
{
	int code;		
	int	statno;	
	char statement[40];  
};

struct dfs diffs[20]; 
int version;	

void edit(char *filename);
void insert(int statno, char *stat);
void delete(int statno);
void print();
void save();
void update(int num,char *name);
void menu();

void save()
{	
	FILE *wrt;
	
	wrt = fopen("writeFile.txt","a+");
	
	int checkVersion;
	fscanf(wrt,"%d",&checkVersion);
	fclose(wrt);
	if(checkVersion==0)
	{
		wrt = fopen("writeFile.txt","w");
	}
	else
	{
		wrt = fopen("writeFile.txt","a");
	}
	
	version++;
	fprintf(wrt,"%d\n",version);
	
	int k=0;
	while(diffs[k].code!=0)
	{
		fprintf(wrt,"%d %d %s\n",diffs[k].code,diffs[k].statno,diffs[k].statement);
		k++;
	}
	fprintf(wrt,"%d\n",-1);
	
	fclose(wrt);
	
	int l=0;
	while(l<k)
	{
		diffs[l].code=0;
		strcpy(diffs[l].statement,"");
		diffs[l].statno=0;
		l++;
	}
	
	int i=0;                                 
	while(i<30)
	{
		textbuffer[i].next=0;
		strcpy(textbuffer[i].statement,"");          
		textbuffer[i].statno=0;
		head=0;
		i++;
	}                                        
	
}

void edit(char *name)
{
	
	char v[100];
		
	gets(v);
	
	FILE *tmp;
	
	tmp = fopen(name, "r");
	
	int number;
	char str[40];
	int index=0;
	
	while(fscanf(tmp,"%d",&number) == 1)
	{
		textbuffer[index].statno = number;
		fscanf(tmp,"%s",&str);
		strcpy(textbuffer[index].statement,str);
		textbuffer[index].next = index+1;
		index++;
	}
	
	textbuffer[index-1].next = -1;
	
	//printf("Index value : %d\n",index);
	
	//int counter=0;
	
	//printf("Head Value : %d\n",head);
	
	/*while(counter<index)
	{
		printf("Index : %d, State no: %d, Statement: %s, Next Value: %d\n",counter,textbuffer[counter].statno,textbuffer[counter].statement,textbuffer[counter].next);
		counter++;
	}*/
	
   	fclose(tmp);
   	
   	FILE *f;
   	
   	f = fopen("writeFile.txt","r");
   	
   	int versionArray[20];
   	versionArray[0]=0;
   	int vA=0;
   	int vIndex=1;
   	
   	int vCheck;
   	fscanf(f,"%d",&vCheck);
   	if(vCheck!=0)
   	{
   		int op;
   		while(fscanf(f,"%d",&op) == 1)
   		{
   			//printf("op value : %d\n",op);
   			if(op==1)
   			{
   				int No;
				char st[40];
				
				fscanf(f,"%d",&No);
				fscanf(f,"%s",st);
				
				vA = vA + 2;
				
				//printf("Insert %d %s\n",No,st);
				
				insert(No,st);	
			}
			else if(op==2)
			{
				int No;
				
				fscanf(f,"%d",&No);
				
				vA++;
				
				//printf("Delete %d\n",No);
				
				delete(No);
			}
			else if(op==-1)
			{
				versionArray[vIndex] = versionArray[vIndex-1] + vA;
				vA=1;
				vIndex++;
				
				vCheck++;
				int empty;
				fscanf(f,"%d",&empty);
			}
		}
		
		fclose(f);
		
		int i=0;
		while(i!=vIndex)
		{
			printf("Index : %d , Value : %d\n",i,versionArray[i]);
			i++;
		}
		
		int j=0;
		while(j<20)
		{
			diffs[j].code=0;
			strcpy(diffs[j].statement,"");
			diffs[j].statno=0;
			version=0;
			j++;
		}
		
		//printf("Last Version Value : %d\n",vCheck);
			
		if(v[0]!='\0')
		{
			int x = v[1] - '0';
			int y = v[2] - '0';
			if(v[2]=='\0')
			{
				version = x;
			}
			else
			{
				x = x*10;
				int z = x+y;
				version = z;
			}
			
			int go = versionArray[version-1];
			update(go,name);
			
			version--;
			
			FILE *design;
			design = fopen("writeFile.txt","a");
			fprintf(design,"%d\n",-1);
			fclose(design);
				
		}
		else
		{
			version = vCheck-1;
		}
		
		
	}

   
}

void update(int num,char *name)
{
	FILE *fptr1, *fptr2;
    int lno, linectr = 0;
    char str[MAX],fname[MAX];        
    char newln[MAX], temp[] = "temp.txt";
		
	//printf(" Input the file name to be opened : ");
    //fgets(fname, MAX, stdin);
    strcpy(fname,"writeFile.txt");
    
    //fname[strlen(fname) - 1] = '\0';
    
    fptr1 = fopen(fname, "r");
        
    fptr2 = fopen(temp, "w");
        
    strcpy(newln,"");
        
    //printf(" Input the line no you want to replace : ");
    //scanf("%d", &lno);
    lno=num;
    lno++;
        
    while (!feof(fptr1)) 
    {
        strcpy(str, "\0");
        fgets(str, MAX, fptr1);
        if (!feof(fptr1)) 
        {
            linectr++;
            if (linectr < lno)
            {
            	fprintf(fptr2, "%s", str);
            }
            else 
            {
                fprintf(fptr2, "%s", newln);
            }
        }
    }
        
    fclose(fptr1);
    fclose(fptr2);
    remove(fname);
    rename(temp, fname);
    printf("Version updated successfully..!! \n");
    
    int i=0;                                 
	while(i<30)
	{
		textbuffer[i].next=0;
		strcpy(textbuffer[i].statement,"");          
		textbuffer[i].statno=0;
		head=0;
		i++;
	}
	
	FILE *reDesign;
	
	reDesign = fopen(name, "r");
	
	int number;
	char strr[40];
	int index=0;
	
	while(fscanf(reDesign,"%d",&number) == 1)
	{
		textbuffer[index].statno = number;
		fscanf(reDesign,"%s",&strr);
		strcpy(textbuffer[index].statement,strr);
		textbuffer[index].next = index+1;
		index++;
	}
	
	textbuffer[index-1].next = -1;
	
	fclose(reDesign);
    
    FILE *df;
   	
   	df = fopen("writeFile.txt","r");
    
    int opPrev;
   	fscanf(df,"%d",&opPrev);
   	
   	int op;
   	while(fscanf(df,"%d",&op) == 1)
   	{
   		//printf("op value : %d\n",op);
   		if(op==1)
   		{
   			int No;
			char st[40];
				
			fscanf(df,"%d",&No);
			fscanf(df,"%s",st);
				
			//printf("Insert %d %s\n",No,st);
				
			insert(No,st);	
		}
		else if(op==2)
		{
			int No;
				
			fscanf(df,"%d",&No);
				
			//printf("Delete %d\n",No);
				
			delete(No);
		}
		else if(op==-1)
		{
			int empty;
			fscanf(df,"%d",&empty);
		}
	}
	
	fclose(df);
}

void delete(int statno)
{
	int temp = head;
	
	int d=0;
	while(1)
	{
		if(diffs[d].code==0)
		{
			break;
		}
		d++;
	}
	
	diffs[d].code = 2;
	diffs[d].statno = statno;
	
	while(1)
	{
		int tempN = textbuffer[temp].next;
		
		if(textbuffer[head].statno==statno)
		{
			head = textbuffer[head].next;
			break;
		}
		else if(textbuffer[tempN].statno==statno)
		{
			if(textbuffer[tempN].next==-1)
			{
				textbuffer[temp].next = -1;
				break;
			}
			textbuffer[temp].next = textbuffer[tempN].next;
			break;
		}
		else if(tempN==-1)
		{
			break;
		}
		
		temp = textbuffer[temp].next;
		
	}
	
	/*int counter = head;
	
	printf("Head Value : %d\n",head);
	
	while(1)
	{
		if(textbuffer[counter].next==-1)
		{
			printf("Index: %d, State no: %d, Statement: %s, Next Value: %d\n",counter,textbuffer[counter].statno,textbuffer[counter].statement,textbuffer[counter].next);
			break;
		}
		printf("Index: %d, State no: %d, Statement: %s, Next Value: %d\n",counter,textbuffer[counter].statno,textbuffer[counter].statement,textbuffer[counter].next);
		counter=textbuffer[counter].next;
	}*/
}

void print()
{
	int q = head;
	while(1)
	{
		if(textbuffer[q].next==-1)
		{
			printf("%d %s\n",textbuffer[q].statno,textbuffer[q].statement);
			break;
		}
		printf("%d %s\n",textbuffer[q].statno,textbuffer[q].statement);
		q = textbuffer[q].next;
	}
	
}

void insert(int statno, char *stat)
{
	int i=0;
	while(1)                            
	{
		if(textbuffer[i].next==0)      
		{
			break;
		}                               
		i++;
	}
	
	textbuffer[i].statno = statno;
	strcpy(textbuffer[i].statement,stat);
	
	int d=0;
	while(1)
	{
		if(diffs[d].code==0)
		{
			break;
		}
		d++;
	}
	
	diffs[d].code = 1;
	diffs[d].statno = statno;
	strcpy(diffs[d].statement,stat);
	
	int p = head;
	
	while(1)
	{
		int pN = textbuffer[p].next;
		
		if(textbuffer[head].statno>textbuffer[i].statno)
		{
			textbuffer[i].next = head;
			head = i;
			break;
		}
		else if(textbuffer[pN].statno>textbuffer[i].statno)
		{
			textbuffer[p].next = i;
			textbuffer[i].next = pN;
			break;
		}
		else if(pN==-1)
		{
			textbuffer[p].next = i;
			textbuffer[i].next = -1;
			break;
		}
	
		p = textbuffer[p].next;
	}
	
	/*int counter = head;
	
	printf("Head Value : %d and i : %d\n",head,i);
	
	while(1)
	{
		if(textbuffer[counter].next==-1)
		{
			printf("Index: %d, State no: %d, Statement: %s, Next Value: %d\n",counter,textbuffer[counter].statno,textbuffer[counter].statement,textbuffer[counter].next);
			break;
		}
		printf("Index: %d, State no: %d, Statement: %s, Next Value: %d\n",counter,textbuffer[counter].statno,textbuffer[counter].statement,textbuffer[counter].next);
		counter=textbuffer[counter].next;
	}*/
}

void commit()
{
	FILE *file;
	
	file = fopen("deneme.txt","w");
	
	int q = head;
	while(1)
	{
		if(textbuffer[q].next==-1)
		{
			fprintf(file,"%d %s\n",textbuffer[q].statno,textbuffer[q].statement);
			break;
		}
		fprintf(file,"%d %s\n",textbuffer[q].statno,textbuffer[q].statement);
		q = textbuffer[q].next;
	}
	
	fclose(file);
	
	FILE *reset;
	
	reset = fopen("writeFile.txt","w");
	
	fprintf(reset,"%d\n",0);
	
	fclose(reset);
	
	int i=0;
	while(i<30)
	{
		textbuffer[i].next=0;
		strcpy(textbuffer[i].statement,"");
		textbuffer[i].statno=0;
		head=0;
		i++;
	}
	
	int j=0;
	while(j<20)
	{
		diffs[j].code=0;
		strcpy(diffs[j].statement,"");
		diffs[j].statno=0;
		version=0;
		j++;
	}
	
}

void menu()
{
	char select;
	
	while(1)
	{
		printf("I : insert\n");
		printf("D : delete\n");
		printf("P : print\n");
		printf("S : save\n");
		printf("E : edit\n");
		printf("C : commit\n");
		printf("X : exit\n");
		printf("Enter your choice : ");
		
		scanf(" %c",&select);
		
		
		if(select=='I')
		{
			char name2[100];
			int num;
	
			printf("Enter the values : ");
			scanf("%d %s",&num,name2);
			
			insert(num,name2);
		}
		else if(select=='D')
		{
			int deleteNumber;
	
			printf("Enter the statNo that will be deleted : ");
			scanf("%d",&deleteNumber);
	
			delete(deleteNumber);
		}
		else if(select=='P')
		{
			print();	
		}
		else if(select=='S')
		{
			save();	
		}
		else if(select=='E')
		{
			char name[100];
			
			//printf("Enter the name of txt : ");
			scanf("%s",name);
			
			edit(name);
			
		}
		else if(select=='C')
		{
			commit();
		}
		else if(select=='X')
		{
			break;
		}
		else
		{
			printf("\nYou entered invalid input !!!\n");	
		}
		
	}
}

int main()
{
	/*char name[100];
	
	printf("Enter the name of txt : ");
	scanf("%s",name);
	
	printf("File name : %s\n",name);
	
	edit(name);
	
	print();*/
	
	menu();
	
	/*char name2[100];
	int num;
	
	printf("Enter the value of statement : ");
	scanf("%s",name2);
	printf("Enter the statNo : ");
	scanf("%d",&num);
	
	insert(num,name2);
	
	print();
	
	int deleteNumber;
	
	printf("Enter the statNo that will be deleted : ");
	scanf("%d",&deleteNumber);
	
	delete(deleteNumber);
	
	print();*/
}











