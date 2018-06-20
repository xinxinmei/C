#include<stdio.h>
#include<stdlib.h>
#define max 40
#include<string.h>
#define INF 32767//�����
int visited[max];//ȫ�ֱ���  
int path[max][max];path1[max][max];path2[max][max];//��������  
int min[max][max];min1[max][max];min2[max][max];//���·�� 
typedef struct{
	int data[max];
	int top;
}stack;
typedef struct//����Ը����ص���Ϣ�洢�Ľṹ������  
{  
    int top;//�ص����  
    char info[max];//�ص�����  
    char introduce[max];//�ص���� 
} data;//���嶥������  
typedef struct node  
{  
    int adj;//���ڽӵĵص��ľ���  
	int i;//��־
	int j;//��·����
} node;//����ߵ�����  
typedef struct  
{  
    data vertex[max];//�ص㡢����  
    node arcs[max][max];//�ص��·��  
    int vexnum,arcnum;//�ص���������  
} graph;//����ͼ������ 
void creatgraph(graph *g)//¼��ص��·����Ϣ
{
	printf("������ص�����·������");
	scanf("%d,%d",&(g->vexnum),&(g->arcnum));
}
void creat2(graph *g)//��ʼ��
{
	int i,j;
	for(i=1; i<=g->vexnum; i++)  
        for(j=1; j<=g->vexnum; j++)  
            g->arcs[i][j].adj=0; 
	for(i=0;i<=g->vexnum;i++)
		for(j=0;j<=g->vexnum;j++)
		{	if(i==j)	g->arcs[i][j].i=0;
			else 	g->arcs[i][j].i=INF;
		}
}
void graphfile(graph *g)//¼��ص�����·����
{
	FILE *fp;  
    fp=fopen("c.txt","wt");  
	fprintf(fp,"%d %d\n",g->vexnum,g->arcnum);  
    fclose(fp);  
}
void readgraph(graph *g)//����ص�����·����
{
	FILE *fp;  
    fp=fopen("c.txt","rt");  
    fscanf(fp,"%d %d",&g->vexnum,&g->arcnum);
    fclose(fp);  
}
void creat1(graph *g)
{
	int k=1,i,j,a,h;
	for(k=1;k<=g->arcnum;k++)
	{
		printf("���������ص�����:\n");
		scanf("%d,%d",&i,&j);
		g->arcs[i][j].i=1;
		printf("���������ص�ľ���:\n");
		scanf("%d",&a);
		printf("���������ص�ĵ�·���ࣨ���У�0�����г���1��������2��:\n");
		scanf("%d",&h);
		g->arcs[i][j].j=h;
		g->arcs[i][j].adj=a;
	}

}
void creat(graph *g)//¼��ص������Ϣ
{
	char d[20],e[100];
	int b,c;
	for(b=1;b<=g->vexnum;b++)
	{
		printf("������%d�ص����\n",b);
		scanf("%d",&c);
		printf("������%d�ص�����\n",b);
		scanf("%s",&d);
		printf("������%d�ص����\n",b);
		scanf("%s",&e);
		g->vertex[b].top=c;
		memcpy(g->vertex[b].info,d,strlen(d)+1);
		memcpy(g->vertex[b].introduce,e,strlen(e)+1);
	}
}
void vernumfile(graph *g) //����ص���Ϣ 
{  
    FILE *fp;  
    int i;  
    fp=fopen("a.txt","wt");  
    for(i=1; i<=g->vexnum; i++)  
        fprintf(fp,"%d %s %s\n",g->vertex[i].top,g->vertex[i].info,g->vertex[i].introduce);  
    fclose(fp);  
}  
void arcnumfile(graph *g)  /*����ص��·����Ϣ*/
{  
    FILE *fp;  
    int i,j;
    fp=fopen("b.txt","wt");  
    for(i=1; i<=g->vexnum; i++)  
        for(j=1; j<=g->vexnum; j++)
                fprintf(fp,"%d %d %d\n",g->arcs[i][j].adj,g->arcs[i][j].i,g->arcs[i][j].j);          
    fclose(fp);  
}  
void readvernum(graph *g)  //��ȡ�ص���Ϣ
{  
    FILE *fp;  
    int i=1;  
    fp=fopen("a.txt","rt");  
    while(fscanf(fp,"%d %s %s",&g->vertex[i].top,g->vertex[i].info,g->vertex[i].introduce)!=EOF)  
    {  
      // printf("�ص����:%d ����:%s\n",g->vertex[i].top,g->vertex[i].info);  (������Ϣ��ȡ����ȷ��)
     // printf("�ص���Ϣ:%s\n",g->vertex[i].introduce);  
      //  printf("\n");  
        i++;  
    }   
    fclose(fp);  
}  
void readarcnum(graph *g)  /*��ȡ·����Ϣ*/ 
{  
    FILE *fp;  
    int i=1,j=1;  
    fp=fopen("b.txt","rt");
	while(fscanf(fp,"%d %d %d\n",&g->arcs[i][j].adj,&g->arcs[i][j].i,&g->arcs[i][j].j)!=EOF)  
	{
		if(j>g->vexnum) {i++;j=1;} 
	//	printf("%d    %d\n",i,j);	��������Ϣ��ȡ����ȷ�ԣ�
	//	printf("%d %d %d\n",g->arcs[i][j].adj,g->arcs[i][j].i,g->arcs[i][j].j);	
		j++;
	 }  
    fclose(fp);  
}  
void findvernum(graph *g)  /*  ��ѯ�ص���Ϣ*/  
{  
    int i,n;  
    char choice=0;  
    for(i=1; i<=g->vexnum; i++)  
        printf("%d\t%s\n",g->vertex[i].top,g->vertex[i].info);  
    do  
    {  
        printf("������Ҫ��ѯ�ĵص����(1-%d):\n",g->vexnum);  
        scanf("%d",&n);  
        printf("�ص�����:%s\n",g->vertex[n].info);  
        printf("�ص���Ϣ:%s\n",g->vertex[n].introduce);  
        printf("\n");  
        printf("�Ƿ������ѯ:(y/n):\n");  
        _flushall();  
        scanf("%c",&choice);  
    }  
    while(choice=='Y'||choice=='y');  
}  
void findarcnum(graph *g)//��ѯ·����Ϣ
{
	int a,b,i,j;
	printf("·���У�\n");
	for(i=1; i<=g->vexnum; i++)  
        for(j=1; j<=g->vexnum; j++)
			if(g->arcs[i][j].i==1)
				printf("%5d<-->%d\n",i,j);
	printf("����������ص㣺\n");
	scanf("%d",&a);
    printf("������Ŀ�ĵأ�\n");
	scanf("%d",&b);
		if(g->arcs[a][b].i==1)
		{if(g->arcs[a][b].j==0)
				printf("��·��%s--->%s\n��·����-----����\n",g->vertex[a].info,g->vertex[b].info);
			else if(g->arcs[a][b].j==1)
				printf("��·��%s--->%s\n��·����-----���С����г�\n",g->vertex[a].info,g->vertex[b].info);
			else if(g->arcs[a][b].j==2)
				printf("��·��%s--->%s\n��·����-----���С����г�������\n",g->vertex[a].info,g->vertex[b].info);}
		else
			printf("û����ص�·\n");
}
void floyd(graph *g) /*���������㷨*/ 
{  
    int i,j,k;  
    for(i=1; i<=g->vexnum; i++)  //���е����·������
        for(j=1; j<=g->vexnum; j++)  
            min[i][j]=0;  
    for(i=1; i<=g->vexnum; i++)  
        for(j=1; j<=g->vexnum; j++)  
        {  
            min[i][j]=g->arcs[i][j].adj;  
            path[i][j]=0;  
        } 
	for(k=1; k<=g->vexnum; k++) 
		for(i=1; i<=g->vexnum; i++)  
			for(j=1; j<=g->vexnum; j++)   
                if( min[i][j]>min[i][k]+min[k][j])  
                {   
                    min[i][j]=min[i][k]+min[k][j];  
                    path[i][j]=k;
                }  
	for(i=1; i<=g->vexnum; i++)  //���г����·������
        for(j=1; j<=g->vexnum; j++)  
            min1[i][j]=0;  
    for(i=1; i<=g->vexnum; i++)  
        for(j=1; j<=g->vexnum; j++)  
        {  
			if(g->arcs[i][j].j==0)
				min1[i][j]=INF;
			else
				min1[i][j]=g->arcs[i][j].adj;  
            path1[i][j]=0;  
        } 
	for(k=1; k<=g->vexnum; k++) 
		for(i=1; i<=g->vexnum; i++)  
			for(j=1; j<=g->vexnum; j++)   
                if( min1[i][j]>min1[i][k]+min1[k][j])  
                {  
                    min1[i][j]=min1[i][k]+min1[k][j];  
                    path1[i][j]=k;   
                }  
	for(i=1; i<=g->vexnum; i++)  //���������·������
        for(j=1; j<=g->vexnum; j++)  
            min2[i][j]=0;  
    for(i=1; i<=g->vexnum; i++)  
        for(j=1; j<=g->vexnum; j++)  
        {  
			if(min2[i][j]==1||min2[i][j]==0)
				min2[i][j]=INF;
			else
				 min2[i][j]=g->arcs[i][j].adj;  
            path2[i][j]=0;  
        } 
	for(k=1; k<=g->vexnum; k++) 
		for(i=1; i<=g->vexnum; i++)  
			for(j=1; j<=g->vexnum; j++)   
                if( min2[i][j]>min2[i][k]+min2[k][j])  
                {  
                    min2[i][j]=min2[i][k]+min2[k][j];  
                    path2[i][j]=k;   
                }  
}
void findmin(graph *g)//�������·��
{
	int a,b,c,d ,e=0;
	printf("����������ص㣺\n");
	scanf("%d",&a);
    printf("������Ŀ�ĵأ�\n");
	scanf("%d",&b);
	printf("��ѡ��ͨ��ʽ�����У�0�����г���1��������2������\n");
	scanf("%d",&d);
	printf("·��:  %d",b);
	switch(d)
	{
	case 0:
			c=path[a][b];
			while(c!=0)
			{
				printf(" <---%d",c);
				c=path[a][c];
				e++;
	
			}
			printf(" <---%d\n",a);
			if((g->arcs[a][b].adj==INF)&&(e==0))
				printf("��·�߲��Ϸ��������ڣ�\n");
			else
				printf("����Ϊ��%d\n",min[a][b]);
			break;
	case 1:
			c=path1[a][b];
			while(c!=0)
			{
				printf(" <---%d",c);
				c=path1[a][c];
				e++;
	
			}
			printf(" <---%d\n",a);
			if((g->arcs[a][b].adj==INF)&&(e==0))
				printf("��·�߲��Ϸ��������ڣ�\n");
			else
				printf("����Ϊ��%d\n",min1[a][b]);
			break;
	case 2:
			c=path2[a][b];
			while(c!=0)
			{
				printf(" <---%d",c);
				c=path2[a][c];
				e++;
	
			}
			printf(" <---%d\n",a);
			if((g->arcs[a][b].adj==INF)&&(e==0))
				printf("��·�߲��Ϸ��������ڣ�\n");
			else
				printf("����Ϊ��%d\n",min2[a][b]);
			break;
	default:break;
	}

}
void dfs(graph *g)  //�ǵݹ����
{   	

	int i=1,a,j;
	int visit[21]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	stack *q;
	q=(stack*)malloc(sizeof(stack));
	q->top=-1;
	i=1;
	printf("·��Ϊ��%d",i);
	visit[i]=1;
	q->top++;
	q->data[q->top]=i;
	while(q->top!=-1)
	{ 
		a=q->data[q->top];
		for (j=1;j<=g->vexnum;j++)
		{ 
			if ((g->arcs[a][j].i==1)&&(visit[j]!=1))
			{  
				 visit[j]=1;  
				 printf("--->%3d",j);
				 q->top++;
				 q->data[q->top]=j;
			     break;
			 } 
			if(j==g->vexnum)
				q->top--;
		}
	
	}
}
int meun(graph *g)  //�˵�
{  
    char choice;  
    while(1)  
    {  
        printf("\n");  
        printf("\t\t************************************************\n");  
        printf("\t\t***************У԰���㵼��ϵͳ*****************\n");  
        printf("\t\t*****************��ӭ����ʹ��*******************\n");  
        printf("\t\t************************************************\n");    
        printf("\t\t**\t 1: �����ص�                          **\n");  
        printf("\t\t**\t 2: ��ѯ�ص���Ϣ                      **\n");  
        printf("\t\t**\t 3: ��ѯ���·��                      **\n");
	    printf("\t\t**\t 4: ��ѯ·����Ϣ                      **\n"); 
        printf("\t\t**\t 0: �˳���ѯϵͳ                      **\n");  
        printf("\t\t************************************************\n");  
        printf("\t\t************************************************\n");  
        printf("\n");  
        printf("��ѡ����Ҫʹ�õĹ������:");  
        choice=getchar();  
        switch(choice)  
        {  
        case '1':  
        {  
            dfs(g);
            break;  
        }  
        case '2':  
        {
			findvernum(g) ;
            break;  
        }  
        case '3':  
        {  	
			findmin(g);
            break;  
        }  
		 case '4':  
        {  	
			findarcnum(g);
            break;  
        }  
      
        case '0':  
        {  
            printf("ллʹ��,�ټ�!\n");  
            exit(0);  
        }  
        }  
        printf("�밴���������.....");  
        getch();  
        _flushall();//������л�����  
        system("cls");  
    }  
} 
void main()//������
{
	graph *g;  
    g=(graph *)malloc(sizeof(graph));
	readgraph(g);
	creat2(g);
	readvernum(g);
	readarcnum(g);
	floyd(g);
	meun(g);
}