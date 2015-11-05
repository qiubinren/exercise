#include <stdio.h>
int map[5][5]={
0,1,0,0,0,
0,1,0,0,0,
0,0,0,0,0,
0,1,1,1,0,
0,0,0,1,0
};
int map1[5][5]={
0,1,0,0,0,
0,1,0,0,0,
0,0,0,0,0,
0,1,1,1,0,
0,0,0,1,0
};
typedef struct pair{
	int x;
	int y;
	int k;
}pair;
struct pair queue[100];
int front=0,rear=-1;
int max=999;
int bfs()
{
	int x=0,y=0,k;
	queue[++rear].x=0;
	queue[rear].y=0;
	queue[rear].k=0;
	while(front<=rear)
	{
		x=queue[front].x;
		y=queue[front].y;
		k=queue[front++].k;
		if(x==4&&y==4)
		{
			printf("%d\n",k);
			return 0;
		}
		if(x>=0&&x<=4&&y+1>=0&&y+1<=4&&!map1[x][y+1])
		{
			map1[x][y+1]=1;
			queue[++rear].x=x;
			queue[rear].y=y+1;
			queue[rear].k=k+1;
		}
		if(x+1>=0&&x+1<=4&&y>=0&&y<=4&&!map1[x+1][y])
		{
			rear++;
			map1[x+1][y]=1;
			queue[++rear].x=x+1;
			queue[rear].y=y;
			queue[rear].k=k+1;
		}
		if(y-1>=0&&y-1<=4&&x>=0&&x<=4&&!map1[x][y-1])
		{
			rear++;
			map1[x][y-1]=1;
			queue[++rear].x=x;
			queue[rear].y=y-1;
			queue[rear].k=k+1;
		}
		if(x-1>=0&&x-1<=4&&y>=0&&y<=4&&!map1[x-1][y])
		{
			rear++;
			map1[x-1][y]=1;
			queue[++rear].x=x-1;
			queue[rear].y=y;
			queue[rear].k=k+1;
		}
	}
	return 0;
}
int dfs(int i,int j,int k)
{
	if(k>max)
		return 0;
	if(i==4&&j==4)
	{
		max=k;
		return 0;
	}
	if(i-1>=0&&map[i-1][j]==0)
	{
		map[i-1][j]=1;
		dfs(i-1,j,k+1);
		map[i-1][j]=0;
	}
	if(i+1<=4&&map[i+1][j]==0)
	{
		map[i+1][j]=1;
		dfs(i+1,j,k+1);
		map[i+1][j]=0;
	}
	if(j-1>=0&&map[i][j-1]==0)
	{
		map[i][j-1]=1;
		dfs(i,j-1,k+1);
		map[i][j-1]=0;
	}
	if(j+1<=4&&map[i][j+1]==0)
	{
		map[i][j+1]=1;
		dfs(i,j+1,k+1);
		map[i][j+1]=0;
	}
	return 0;
}
int main()
{
	dfs(0,0,0);
	printf("%d\n",max);
	bfs();
}
