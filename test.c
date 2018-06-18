#include<stdio.h>
#include<stdlib.h>
#define max 40
#include<string.h>

#define INF 32767//�����
int visited[max];//ȫ�ֱ���  
int path[max][max];//��������  
int min[max][max];//���·��  
typedef struct//����Ը���������Ϣ�洢�Ľṹ������  
{  
    int top;//�������  
    char info[max];//��������  
    char introduce[max];//������� 
} data;//���嶥������  
typedef struct node  
{  
    int adj;//���ڽӵľ����ľ���  
	int i;//�����־
	int j;//��·����
} node;//����ߵ�����  
typedef struct  
{  
    data vertex[max];//���㡢����  
    node arcs[max][max];//��������  
    int vexnum,arcnum;//������������  
} graph;//����ͼ������ 
void creatgraph(graph *g)//��Ϣ¼��
{
	int i,j,k,a,h;
	scanf("%d,%d",&(g->vexnum),&(g->arcnum));
	for(i=0; i<=g->vexnum; i++)  
        for(j=0; j<=g->vexnum; j++)  
            g->arcs[i][j].adj=INF; 
	for(i=0;i<=g->vexnum;i++)
		for(j=0;j<=g->vexnum;j++)
			g->arcs[i][j].i=0;
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
void creat(graph *g)//�ص������Ϣ
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
			printf("%s",g->vertex[b].info);
	}
}
void vernumfile(graph *g)  
{  
    FILE *fp;  
    int i;  
    fp=fopen("a.txt","wt");  
    for(i=1; i<=g->vexnum; i++)  
        fprintf(fp,"%d %s %s\n",g->vertex[i].top,g->vertex[i].info,g->vertex[i].introduce);  
    fclose(fp);  
}  
  
  
void arcnumfile(graph *g)  /*�Ѵ澰���·���ı�*/
{  
    FILE *fp;  
    int i,j;
    fp=fopen("b.txt","wt");  
    for(i=1; i<=g->vexnum; i++)  
        for(j=1; j<=g->vexnum; j++)
			if(g->arcs[i][j].adj!=INF) 
            {  
                fprintf(fp,"%d %d %d\n",g->arcs[i][j].adj,g->arcs[i][j].i,g->arcs[i][j].j);  
            }  
           
    fclose(fp);  
}  
void main()
{
	graph *g;  
    g=(graph *)malloc(sizeof(graph));//����ͷ���
	creatgraph(g);
	printf("%d",g->arcs[1][2].adj);


	arcnumfile(g);
}