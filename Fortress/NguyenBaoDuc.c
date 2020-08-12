// gcc -w -o test test.c jrb.c dllist.c jval.c
// ./test

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "jrb.h"
#include "dllist.h"
#include "jval.h"

#define INFINITIVE_VALUE 10000000
// Do thi bieu dien boi cau truc JRB
typedef struct {
    JRB edges;
} Graph;

Graph createGraph();

void addEdge(Graph graph, int v1, int v2, double weight, int direct);
double getEdgeValue(Graph graph, int v1, int v2);

int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);

double shortestPath(Graph graph, int s, int t, int *path, int *length);
void dropGraph(Graph graph);
//-------------------------------------------------------
int main(){
  Graph g = createGraph();

  int c,count;
  do {
    printf("----------------------------------------\n");
    printf("1- Ma tran thanh tri\n");
    printf("2- Cac thanh tri gan nhau\n");
    printf("3- Cac thanh tri di bo duoc & thanh co nhieu thanh gan nhat\n");
    printf("4- Duong di giua 2 thanh tri\n");
    printf("5- 2 Thanh tri gan nhau nhat\n");
    printf("6- Thoat\n");
    printf("Nhap lua chon: ");
    scanf("%d",&c);
    printf("----------------------------------------\n");
    switch(c) {
    case 1: {
      FILE* file= fopen("dothi.txt","r");
      if (file == NULL)
	{
	  printf("Khong mo duoc dothi.txt\n");
	  return 0;
	}
      int edges;
      fscanf(file,"%d",&count);
      fscanf(file,"%d",&edges);
      while(fgetc(file)!='\n');
      
      for(int i=0;i<edges;i++) {
	int ID1,ID2;
	double value;
	fscanf(file,"%d",&ID1);
	fscanf(file,"%d",&ID2);
	fscanf(file,"%lf",&value);
	//printf("|%2d| - |%2d|\t |%.0lf|\n",ID1,ID2,value);
	addEdge(g, ID1, ID2, value, 2);
      }
      fclose(file);
      printf("\t");
      for(int i=1;i<=count;i++) {
	printf("(%d)  ",i);
      }
      printf("\n");
      for(int i=1;i<=count;i++) {
	printf("->%2d   ",i);
	for(int j=1;j<=count;j++) {
	  if(getEdgeValue(g, i, j) != INFINITIVE_VALUE)
	    printf("|%3.0lf|",getEdgeValue(g, i, j));
	  else
	    printf("| 0 |");
	}
	printf("\n");
      }
    } break;
    case 2: {
      for(int i=1;i<=count;i++) {
	printf("Thanh tri %d :  ",i);
	int out[100];
	int n = outdegree(g, i, &out);
	for(int j=0;j<n;j++) {
	  printf("%2d  ",out[j]);
	}
	printf("\n");
      }
    } break;
    case 3: {
      printf("I  - Cac thanh co the di bo\n---------------------\n");
      for(int i=1;i<=count;i++) {
	for(int j=1;j<=count;j++) {
	  if((getEdgeValue(g, i, j) >= 50) && (getEdgeValue(g, i, j) < INFINITIVE_VALUE))
	    printf("\t Castle %2d| -> Castle %2d|\n",i,j);
	  
	}
      }
      printf("------------------------------\n");
      printf("II - Thanh quan he rong nhat\n--------------------\n");
      int MAX = 0;
      
      for(int i=1;i<=count;i++) {
	int out[100];
	int n = outdegree(g, i, &out);
        if(n >= MAX) {
	  MAX = n;
	}
      }
      for(int i=1;i<=count;i++) {
	int out[100];
	int n = outdegree(g, i, &out);
        if(n >= MAX) {
	  printf("Castle %2d|\n");
	}
      }
    } break;
    case 4: {
      int s,t;
      printf("Nhap thanh suat phat: ");
      scanf("%d",&s);
      printf("Nhap thanh ket thuc : ");
      scanf("%d",&t);
      int path[100], length;
      double distance_s_t = shortestPath(g, s, t, path, &length);
      if (distance_s_t != INFINITIVE_VALUE){
        printf("Duong di tu thanh (%2d) den thanh (%2d) ton mat %.2lf time\n",s ,t, distance_s_t);
        printf("Cac thanh di qua: ");
        for (int i=length-1; i>=0; i--){
	  printf("%d ", path[i]);
        }
        printf("\n");
      }else{
        printf("No Path from s --> t\n");
      }
    } break;
    case 5: {
      printf("\n");
      printf("Chua lam duoc y nay\n");
      
    } break;
    case 6: {
      printf("Ket thuc su dung\n");
    } break;
    default : {
      printf("Lua chon sai\n");
    } break;
    }
  } while(c!=6);
  return 0;
}
//--------------------------------------------------------

void addEdge(Graph graph, int v1, int v2,double weight, int direct){
  JRB node, tree;
  if (getEdgeValue(graph, v1, v2) == INFINITIVE_VALUE)
    {
      node = jrb_find_int(graph.edges, v1);
      if (node == NULL)
        {
	  tree = make_jrb();
	  jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        }
      else
        {
	  tree = (JRB)jval_v(node->val);
        }
      jrb_insert_int(tree, v2, new_jval_d(weight));
      //------------------------------------
      if(direct == 2) {
	node = jrb_find_int(graph.edges, v2);
	if (node == NULL)
	  {
	    tree = make_jrb();
	    jrb_insert_int(graph.edges, v2, new_jval_v(tree));
	  }
	else
	  {
	    tree = (JRB)jval_v(node->val);
	  }
	jrb_insert_int(tree, v1, new_jval_d(weight));
      }
    }
}

double getEdgeValue(Graph graph, int v1, int v2){
  JRB node = jrb_find_int(graph.edges, v1);
  if (node == NULL)
    {
      return INFINITIVE_VALUE;
    }
  JRB tree = (JRB)jval_v(node->val);
  JRB node1 = jrb_find_int(tree, v2);
  if (node1 == NULL) {
    return INFINITIVE_VALUE;
  }
  return jval_d(node1->val);
}

int indegree(Graph graph, int v, int* output){
  JRB tree, node;
  int total = 0;
  jrb_traverse(node, graph.edges){
    tree = (JRB) jval_v(node->val);
    if (jrb_find_int(tree, v))
      {
	output[total] = jval_i(node->key);
	total++;
      }
  }
  return total;
}

int outdegree(Graph graph, int v, int* output){
  JRB tree, node;
  int total;
  node = jrb_find_int(graph.edges, v);
  if (node==NULL)
    return 0;
  tree = (JRB) jval_v(node->val);
  total = 0;
  jrb_traverse(node, tree){
    output[total] = jval_i(node->key);
    total++;
  }
    return total;
}

double shortestPath(Graph graph, int s, int t, int *path, int *length){
  double distance[1000], min;
  int previous[1000], u, visit[1000];
    
  for (int i=0; i<1000; i++){
    distance[i] = INFINITIVE_VALUE;
    visit[i] = 0;
    previous[i] = 0;
  }
  distance[s] = 0;
  previous[s] = s;
  visit[s] = 1;
    
  Dllist ptr, queue, node;
  queue = new_dllist();
  dll_append(queue, new_jval_i(s));
  
  while (!dll_empty(queue)){
    min = INFINITIVE_VALUE;
    dll_traverse(ptr, queue){
      // Lay ra min{distance}
      u = jval_i(ptr->val);
      if (min > distance[u]){
	min = distance[u];
	node = ptr;
      }
    }
    u = jval_i(node->val);
    visit[u] = 1;
    dll_delete_node(node);
    if (u == t) break;
    
    int output[100];
    int n = outdegree(graph, u, output);

    for (int i=0; i<n; i++){
      int v = output[i];
      double w = getEdgeValue(graph, u, v);
      if (distance[v] > distance[u] + w){
	distance[v] = distance[u] + w;
	previous[v] = u;
      }
      if (visit[v] == 0){
	dll_append(queue, new_jval_i(v));
      }
    }
  }

  double distance_s_t = distance[t];
  int count=0;
  if (distance[t] != INFINITIVE_VALUE){
    path[count++] = t;
    while (t != s){
      t = previous[t];
      path[count++] = t;
      *length = count;
    }
  }
  return distance_s_t;
}

Graph createGraph(){
  Graph g;
  g.edges = make_jrb();
    return g;
}

void dropGraph(Graph graph){
  jrb_free_tree(graph.edges);
}
