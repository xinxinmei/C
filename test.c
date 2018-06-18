#include<stdio.h>
#include<stdlib.h>
#define max 40
#include<string.h>

#define INF 32767//无穷大
int visited[max];//全局变量  
int path[max][max];//经过景点  
int min[max][max];//最短路径  
typedef struct//定义对各个景点信息存储的结构体类型  
{  
    int top;//景点序号  
    char info[max];//景点名称  
    char introduce[max];//景点介绍 
} data;//定义顶点类型  
typedef struct node  
{  
    int adj;//相邻接的景点间的距离  
	int i;//方向标志
	int j;//道路种类
} node;//定义边的类型  
typedef struct  
{  
    data vertex[max];//景点、顶点  
    node arcs[max][max];//景点间距离  
    int vexnum,arcnum;//景点数、边数  
} graph;//定义图的类型 
void creatgraph(graph *g)//信息录入
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
		printf("请输入两地点的序号:\n");
		scanf("%d,%d",&i,&j);
		g->arcs[i][j].i=1;
		printf("请输入两地点的距离:\n");
		scanf("%d",&a);
		printf("请输入两地点的道路种类（步行：0，自行车：1，汽车：2）:\n");
		scanf("%d",&h);
		g->arcs[i][j].j=h;
		g->arcs[i][j].adj=a;
	}


}
void creat(graph *g)//地点相关信息
{
	char d[20],e[100];
	int b,c;
	for(b=1;b<=g->vexnum;b++)
	{
		printf("请输入%d地点序号\n",b);
		scanf("%d",&c);
		printf("请输入%d地点名称\n",b);
		scanf("%s",&d);
		printf("请输入%d地点介绍\n",b);
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
  
  
void arcnumfile(graph *g)  /*已存景点间路径文本*/
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
    g=(graph *)malloc(sizeof(graph));//创建头结点
	creatgraph(g);
	printf("%d",g->arcs[1][2].adj);


	arcnumfile(g);
}