#ifndef __ROUTE_H__
#define __ROUTE_H__

typedef struct {
	int num;
	int cost;
}eNode;

#define MAXV 600
#define MAXS 60
#define INVALID -1


void search_route(char *graph[5000], int edge_num, char *condition);
void dfs(int nowv, int n);
bool checkSolution(int cost);
void updateResult(int visitnum, int cost);
bool isValidE(int now, int next, int cost);

#endif