#include<stdio.h>
#include<stdlib.h>
#define max 40
#include<string.h>
#define INF 32767//无穷大
int visited[max];//全局变量  
int path[max][max];path1[max][max];path2[max][max];//经过景点  
int min[max][max];min1[max][max];min2[max][max];//最短路径 
typedef struct{
	int data[max];
	int top;
}stack;
typedef struct//定义对各个地点信息存储的结构体类型  
{  
    int top;//地点序号  
    char info[max];//地点名称  
    char introduce[max];//地点介绍 
} data;//定义顶点类型  
typedef struct node  
{  
    int adj;//相邻接的地点间的距离  
	int i;//标志
	int j;//道路种类
} node;//定义边的类型  
typedef struct  
{  
    data vertex[max];//地点、顶点  
    node arcs[max][max];//地点间路径  
    int vexnum,arcnum;//地点数、边数  
} graph;//定义图的类型 
void creatgraph(graph *g)//录入地点间路径信息
{
	printf("请输入地点数和路径数：");
	scanf("%d,%d",&(g->vexnum),&(g->arcnum));
}
void creat2(graph *g)//初始化
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
void graphfile(graph *g)//录入地点数和路径数
{
	FILE *fp;  
    fp=fopen("c.txt","wt");  
	fprintf(fp,"%d %d\n",g->vexnum,g->arcnum);  
    fclose(fp);  
}
void readgraph(graph *g)//存入地点数和路径数
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
void creat(graph *g)//录入地点相关信息
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
	}
}
void vernumfile(graph *g) //存入地点信息 
{  
    FILE *fp;  
    int i;  
    fp=fopen("a.txt","wt");  
    for(i=1; i<=g->vexnum; i++)  
        fprintf(fp,"%d %s %s\n",g->vertex[i].top,g->vertex[i].info,g->vertex[i].introduce);  
    fclose(fp);  
}  
void arcnumfile(graph *g)  /*存入地点间路径信息*/
{  
    FILE *fp;  
    int i,j;
    fp=fopen("b.txt","wt");  
    for(i=1; i<=g->vexnum; i++)  
        for(j=1; j<=g->vexnum; j++)
                fprintf(fp,"%d %d %d\n",g->arcs[i][j].adj,g->arcs[i][j].i,g->arcs[i][j].j);          
    fclose(fp);  
}  
void readvernum(graph *g)  //读取地点信息
{  
    FILE *fp;  
    int i=1;  
    fp=fopen("a.txt","rt");  
    while(fscanf(fp,"%d %s %s",&g->vertex[i].top,g->vertex[i].info,g->vertex[i].introduce)!=EOF)  
    {  
      // printf("地点序号:%d 名称:%s\n",g->vertex[i].top,g->vertex[i].info);  (测试信息读取的正确性)
     // printf("地点信息:%s\n",g->vertex[i].introduce);  
      //  printf("\n");  
        i++;  
    }   
    fclose(fp);  
}  
void readarcnum(graph *g)  /*读取路径信息*/ 
{  
    FILE *fp;  
    int i=1,j=1;  
    fp=fopen("b.txt","rt");
	while(fscanf(fp,"%d %d %d\n",&g->arcs[i][j].adj,&g->arcs[i][j].i,&g->arcs[i][j].j)!=EOF)  
	{
		if(j>g->vexnum) {i++;j=1;} 
	//	printf("%d    %d\n",i,j);	（测试信息读取的正确性）
	//	printf("%d %d %d\n",g->arcs[i][j].adj,g->arcs[i][j].i,g->arcs[i][j].j);	
		j++;
	 }  
    fclose(fp);  
}  
void findvernum(graph *g)  /*  查询地点信息*/  
{  
    int i,n;  
    char choice=0;  
    for(i=1; i<=g->vexnum; i++)  
        printf("%d\t%s\n",g->vertex[i].top,g->vertex[i].info);  
    do  
    {  
        printf("请输入要查询的地点序号(1-%d):\n",g->vexnum);  
        scanf("%d",&n);  
        printf("地点名称:%s\n",g->vertex[n].info);  
        printf("地点信息:%s\n",g->vertex[n].introduce);  
        printf("\n");  
        printf("是否继续查询:(y/n):\n");  
        _flushall();  
        scanf("%c",&choice);  
    }  
    while(choice=='Y'||choice=='y');  
}  
void findarcnum(graph *g)//查询路径信息
{
	int a,b,i,j;
	printf("路径有：\n");
	for(i=1; i<=g->vexnum; i++)  
        for(j=1; j<=g->vexnum; j++)
			if(g->arcs[i][j].i==1)
				printf("%5d<-->%d\n",i,j);
	printf("请输入出发地点：\n");
	scanf("%d",&a);
    printf("请输入目的地：\n");
	scanf("%d",&b);
		if(g->arcs[a][b].i==1)
		{if(g->arcs[a][b].j==0)
				printf("道路：%s--->%s\n道路类型-----步行\n",g->vertex[a].info,g->vertex[b].info);
			else if(g->arcs[a][b].j==1)
				printf("道路：%s--->%s\n道路类型-----步行、自行车\n",g->vertex[a].info,g->vertex[b].info);
			else if(g->arcs[a][b].j==2)
				printf("道路：%s--->%s\n道路类型-----步行、自行车、汽车\n",g->vertex[a].info,g->vertex[b].info);}
		else
			printf("没有相关道路\n");
}
void floyd(graph *g) /*弗洛伊德算法*/ 
{  
    int i,j,k;  
    for(i=1; i<=g->vexnum; i++)  //步行的最短路径数组
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
	for(i=1; i<=g->vexnum; i++)  //自行车最短路径数组
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
	for(i=1; i<=g->vexnum; i++)  //汽车的最短路径数组
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
void findmin(graph *g)//查找最短路径
{
	int a,b,c,d ,e=0;
	printf("请输入出发地点：\n");
	scanf("%d",&a);
    printf("请输入目的地：\n");
	scanf("%d",&b);
	printf("请选择交通方式（步行（0）自行车（1）汽车（2））：\n");
	scanf("%d",&d);
	printf("路线:  %d",b);
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
				printf("该路线不合法（不存在）\n");
			else
				printf("距离为：%d\n",min[a][b]);
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
				printf("该路线不合法（不存在）\n");
			else
				printf("距离为：%d\n",min1[a][b]);
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
				printf("该路线不合法（不存在）\n");
			else
				printf("距离为：%d\n",min2[a][b]);
			break;
	default:break;
	}

}
void dfs(graph *g)  //非递归遍历
{   	

	int i=1,a,j;
	int visit[21]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	stack *q;
	q=(stack*)malloc(sizeof(stack));
	q->top=-1;
	i=1;
	printf("路线为：%d",i);
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
int meun(graph *g)  //菜单
{  
    char choice;  
    while(1)  
    {  
        printf("\n");  
        printf("\t\t************************************************\n");  
        printf("\t\t***************校园景点导航系统*****************\n");  
        printf("\t\t*****************欢迎您的使用*******************\n");  
        printf("\t\t************************************************\n");    
        printf("\t\t**\t 1: 遍历地点                          **\n");  
        printf("\t\t**\t 2: 查询地点信息                      **\n");  
        printf("\t\t**\t 3: 查询最短路径                      **\n");
	    printf("\t\t**\t 4: 查询路径信息                      **\n"); 
        printf("\t\t**\t 0: 退出查询系统                      **\n");  
        printf("\t\t************************************************\n");  
        printf("\t\t************************************************\n");  
        printf("\n");  
        printf("请选择需要使用的功能序号:");  
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
            printf("谢谢使用,再见!\n");  
            exit(0);  
        }  
        }  
        printf("请按任意键继续.....");  
        getch();  
        _flushall();//清除所有缓冲区  
        system("cls");  
    }  
} 
void main()//主函数
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