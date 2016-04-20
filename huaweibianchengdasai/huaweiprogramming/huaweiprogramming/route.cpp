//#include "route.h"
//#include "lib_record.h"
//#include <stdio.h>
#include "route.h"
#include "lib_io.h"
#include "lib_time.h"
#include "lib_record.h"
#include <stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>


eNode netMap[MAXV][MAXV];   //网络图
int start, end;             //起始点
bool visited[MAXV] = {false}; //记录已经经过的点
int min_cost = 0x7fffffff;
unsigned short result[MAXV];   //结果
unsigned int resultnum = 0;
unsigned int possible_result[MAXV];   //结果


unsigned int visitnum = 0;
unsigned int vSearch[MAXS];  //必须经过的点
int numofvS = 0;

void search_route(char *topo[5000], int edge_num, char *demand)
{
	int n1, n2, num, cost;
	char vS[MAXS*2] = {'\0'};
	
   	for(int i=0; i<MAXV; i++){
		for(int j=0; j<MAXV; j++)
			netMap[i][j].num = INVALID;  //edge between i and j
  	}

	printf("init netMap ok\n");
	for(int i=0; i<edge_num; i++){
		sscanf(topo[i], "%d,%d,%d,%d", &num, &n1, &n2, &cost);
		if(INVALID != netMap[n1][n2].num && cost >= netMap[n1][n2].cost) continue;
		netMap[n1][n2].cost = cost;
		netMap[n1][n2].num = num;
	}
	printf("fill netMap ok\n");

	sscanf(demand, "%d,%d,%s", &start, &end, vS);

	char *tmp = vS;
	int index = 0;
	int val = 0;
	while(*tmp != '\0'){
		while(*tmp != '|' && *tmp != '\0'){
			val = val*10 + (*tmp - '0');
			tmp++;
		}
		vSearch[index++] = val;
		numofvS++;
		if( '\0' ==  *tmp) break;
		val = 0;
		tmp++;
	}

	for(index = 0; index < numofvS; index++){
		printf("%d ", vSearch[index]);
	}
	printf("\n");

	
	dfs(start, 0);
	if(0 == resultnum){
	    printf("NA\n"); 
	}
	else{
		for (int i = 0; i < resultnum; i++)
      		record_result(result[i]);
	}
	return;
}


void dfs(int nowv, int cost)
{
	static int w = 0;
	//printf("Dfs: the %d times\n", w++);
	//printf("node: %d cost: %d\n", nowv, cost);

	if(cost > min_cost) return;
	
	visited[nowv] = true;
	visitnum++;

	if(nowv == end){
		//printf("\nFind one sulution!  nowv: %d visited: %d  and cost: %d\n", nowv, visitnum, cost);
		bool flag = checkSolution(cost);
		if(true == flag){
			printf("\nFind one sulution!  nowv: %d visited: %d  and cost: %d\n", nowv, visitnum, cost);
			updateResult(visitnum-1, cost); //  visitnum个点被访问，产生visitnum-1条边
		}
		visited[nowv] = false;
		visitnum--;
		return ; 
	}

	for(int nextv = 0; nextv < MAXV; nextv++){
		if(isValidE(nowv, nextv, cost)){
			possible_result[visitnum-1] = netMap[nowv][nextv].num;
			dfs(nextv, cost + netMap[nowv][nextv].cost);
		}
	}
	
	visitnum--;
	visited[nowv] = false;
}

bool checkSolution(int cost){

	//检查一个方案是否有效
	for(int i=0; i< numofvS; i++){
		if(false == visited[vSearch[i]]) return false;
	}
	return true;
}

void updateResult(int visitnum, int cost){
	for(int i=0; i<visitnum; i++){
		result[i] = possible_result[i];
		printf("%d ", result[i]);
	}
	printf("\n");
	resultnum = visitnum;
	min_cost = cost;
	printf("now Result: \n	min_cost: %d   ", min_cost);
	for (int i = 0; i < resultnum; i++)
      	printf("%d ", result[i]);
	printf("\n");
}

bool isValidE(int now, int next, int cost){
	
	if(INVALID == netMap[now][next].num) return false;
	if(true == visited[next]) return false;
	
	return true;
}
