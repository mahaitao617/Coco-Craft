#include "route.h"
#include "lib_io.h"
#include "lib_time.h"
#include "lib_record.h"
#include <stdio.h>
#include<time.h>
#include<Windows.h>

int main(int argc, char *argv[])
{
	long start,end;
	start=clock();
	//print_time(""Begin);
    char *topo[5000];
    int edge_num;
    char *demand;
    int demand_num;

    char *topo_file = argv[1];
    edge_num = read_file(topo, 5000, topo_file);
    if (edge_num == 0)
    {
        printf("Please input valid topo file.\n");
        return -1;
    }
    char *demand_file = argv[2];
    demand_num = read_file(&demand, 1, demand_file);
    if (demand_num != 1)
    {
        printf("Please input valid demand file.\n");
        return -1;
    }
    search_route(topo, edge_num, demand);

    char *result_file = argv[3];
    write_result(result_file);
    release_buff(topo, edge_num);
    release_buff(&demand, 1);
	end=clock();
	printf("%ld\n",end-start);
	//print_time("End");
	system("pause");
	return 0;
}

