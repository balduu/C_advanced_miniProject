#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jrb.h"
#include"jrb.c"
#include"jval.h"
#include"jval.c"
#define INFINITIVE_VALUE 1000

typedef struct
{
  JRB edges;
  JRB vertices;
  JRB bus;
}Graph;

typedef struct
{
  int id_canh;
  int bus[150];
}queue;

Graph createGraph();
int getVertexID(Graph graph, char*name);
char* getVertexName(Graph graph, int id_canh);
char* getBusName(Graph graph, int b_id);
void addVertex(Graph graph, char*name,int *vertex_id);
int getBusID(Graph graph, char*name);
void addEdge(Graph graph, int v1, int v2, int bus_id);
JRB getEdgeValue(Graph graph,  int v1, int v2);
void addBus(Graph graph, char*name,int *bus_id);
int in_degree   (Graph graph, int id_canh, int* output);
int out_degree(Graph graph, int id_canh, int* output);
void bus_pass(Graph graph, int id_canh, int * bus_flag);
typedef struct
{
  int visit;
  double cur_distance;
  int id_dinh_truoc[100];
  int dem_dinh_truoc;
}DIJKSTRA;
void shortestPath(Graph graph, double *distance_s_f,  int v1, int v2,DIJKSTRA*dijikstra,int vertex_id);
void dropGraph(Graph graph);
void read(Graph graph, int * vertex_id, int *bus_id);
void menu();
int luachon();
int check_exist();


int main()
{
  Graph graph = createGraph();
  int vertex_id=-1;
  int bus_id=-1;

  read(graph,&vertex_id,&bus_id);

  int v1,v2;
  int output[vertex_id+1];
  int bus_flag[bus_id+1];
  DIJKSTRA dijikstra[vertex_id+1];
  int min_change=INFINITIVE_VALUE;

  queue min_change_trace[100];
  for(int i=0;i<100;i++)
    for(int j=0;j<150;j++) min_change_trace[i].bus[j]=0;

  queue truy_vet_tam_thoi[100];
  for(int i=0;i<100;i++)
    for(int j=0;j<150	;j++) truy_vet_tam_thoi[i].bus[j]=0;

  int choice;
  do
    {
      menu();
      choice = luachon();
      switch(choice)
        {
        case 1:
          printf("Nhập vào tên địa điểm muốn kiểm tra: ");
          char ben_find[100];

          while(getchar()!='\n');
          scanf("%[^\n]s",ben_find);
          while(getchar()!='\n');

          if(check_exist(graph,ben_find)==0) printf("\nCo dia dien nay tai Ha Noi.\n");
          else printf("\nKhong co dia diem nay tai Ha Noi.\n");
          printf("\n******************************\n\n");
          break;

        case 2:
          while(getchar()!='\n');

          printf("Bạn nhập vào địa điểm 1: ");
          char s1[100];
          scanf("%[^\n]s",s1);
          while(getchar()!='\n');

          if(check_exist(graph,s1)==1)
            {
              printf("\nDia diem khong ton tai.\n");
              break;
            }

          printf("Bạn nhập vào địa điểm 2: ");
          char s2[100];
          scanf("%[^\n]s",s2);
          while(getchar()!='\n');

          if(check_exist(graph,s2)==1)
            {
              printf("\nDia diem nay khong ton tai.\n");
              break;
            }

           if((getEdgeValue(graph, getVertexID(graph, s1), getVertexID(graph, s2))!=NULL)||(getEdgeValue(graph,  getVertexID(graph, s2), getVertexID(graph, s1))!=NULL))
              printf("\nHai dia diem noi truc tiep voi nhau.\n");
            else printf("\nHai dia diem khong noi truc tiep voi nhau.\n");

            printf("\n******************************\n\n");
          break;

        case 3:
          printf("Bạn nhập vào địa điểm: ");
          char place[100];
          while(getchar()!='\n');
          scanf("%[^\n]s",place);
          while(getchar()!='\n');

          if(check_exist(graph,place)==1)
            {
              printf("\Dia diem khong ton tai.\n");
              break;
            }

          int total;
          total=out_degree(graph, getVertexID(graph,place), output);
          printf("Nhung dia diem noi voi dia diem nay :\n");
          for(int i=0;i<=total;i++)
            printf("%s\n",getVertexName(graph,output[i]));

          printf("\n");

          total=in_degree(graph, getVertexID(graph,place), output);
          printf("Nhung dia diem noi voi dia diem nay :\n");
          for(int i=0;i<=total;i++)
            printf("%s\n",getVertexName(graph,output[i]));

          printf("\n******************************\n\n");
          break;

        case 4:
          printf("Bạn nhập vào địa điểm: ");
          char place3[100];
          while(getchar()!='\n');
          scanf("%[^\n]s",place3);
          while(getchar()!='\n');

          if(check_exist(graph,place3)==1)
            {
              printf("\nDia diem khong ton tai.\n");
              break;
            }

          for(int i=0;i<=bus_id;i++) bus_flag[i]=-1;

          bus_pass(graph,getVertexID(graph,place3) , bus_flag);

          for(int i=0;i<=bus_id;i++)
            if(bus_flag[i]==1) printf("Tuyen: %s\n",getBusName(graph,i));

          printf("\n******************************\n\n");
          break;

        case 5:
          printf("Bạn nhập vào địa điểm bắt đầu: ");
          char diembd[100];
          while(getchar()!='\n');
          scanf("%[^\n]s",diembd);
          while(getchar()!='\n');

          if(check_exist(graph,diembd)==1)
            {
              printf("\nDia diem khong ton tai.\n");
              break;
            }

          printf("Bạn nhập vào địa điểm kết thúc: ");
          char diemkt[100];
          scanf("%[^\n]s",diemkt);
          while(getchar()!='\n');

          if(check_exist(graph,diemkt)==1)
            {
              printf("\nDia diem nay khong ton tai.\n");
              break;
            }

          v1 = getVertexID(graph,diembd);
          v2= getVertexID(graph,diemkt);

          if(v1==v2)
            {
              printf("Ban dang giam chan tai cho roi.\n");
              break;
            }

          double distance_s_f;
          shortestPath(graph,&distance_s_f, v1,v2, dijikstra,vertex_id);

          if(distance_s_f!=-1)
            {
              int count=1;
             truy_vet_tam_thoi[0].id_canh=v2;
              for(int i=1;i<=dijikstra[v2].dem_dinh_truoc;i++)
              /**/  find_min_change(graph,dijikstra,v2, dijikstra[v2].id_dinh_truoc[i-1], 0, &min_change, min_change_trace, truy_vet_tam_thoi, 0);
printf("\n");
printf("Duong di ngan nhat (Su dung cho cac loai phuong tien ngoai tru xe BUS):\n");
              for(int i=(int)distance_s_f;i>0;i--)
                {
                  printf(" %s ", getVertexName(graph, min_change_trace[i].id_canh));
                  printf(" -->");
                }
              printf(" %s",getVertexName(graph, min_change_trace[0].id_canh));
              printf("\n");

            }

          else printf("Khong co tuyen duong di nay .\n");

          printf("\n******************************\n");
          break;

        default:
          printf("CAM ON BAN DA SU DUNG CHUON TRINH.\n");
          break;
        }
    } while(choice != 0);

  dropGraph(graph);

  return 0;
}

void path_num(int *count,DIJKSTRA*dijikstra, int id_v)//dem so dg di
{
  if(dijikstra[id_v].dem_dinh_truoc==0) return;
  *count=*count+dijikstra[id_v].dem_dinh_truoc-1;
  for(int i=1;i<=dijikstra[id_v].dem_dinh_truoc;i++)
    path_num(count, dijikstra, dijikstra[id_v].id_dinh_truoc[i-1]);
}
void find_min_change(Graph graph, DIJKSTRA*dijikstra, int pre_vid, int vid, int change, int*min_change, queue * min_change_trace, queue *truy_vet_tam_thoi, int dem_tamthoi)
{
  dem_tamthoi=dem_tamthoi+1;
  truy_vet_tam_thoi[dem_tamthoi].id_canh=vid;

  JRB vertex_treeEdge= (JRB) jval_v(jrb_find_int(graph.edges, vid) ->val);

  JRB bus_tree=(JRB)jval_v(jrb_find_int(vertex_treeEdge, pre_vid)->val);
  JRB bus_Node;  int flag=0;
  jrb_traverse(bus_Node, bus_tree)
    {
      int id_bus=jval_i(bus_Node->key);
     truy_vet_tam_thoi[dem_tamthoi].bus[id_bus]=1;
      if(truy_vet_tam_thoi[dem_tamthoi-1].bus[id_bus]==1) flag=1;
    }

  if(flag==0)
    {
      change=change+1;
      if(change>*min_change) return;
    }
  else
    {
      for(int i=0;i<150;i++)
        if((truy_vet_tam_thoi[dem_tamthoi-1].bus[i]==1)&&(truy_vet_tam_thoi[dem_tamthoi].bus[i]==1));
        else
          {
            truy_vet_tam_thoi[dem_tamthoi-1].bus[i]=0;
            truy_vet_tam_thoi[dem_tamthoi].bus[i]=0;
          }
    }

  if(dijikstra[vid].dem_dinh_truoc==0)
    {
      if(change<*min_change)
        {
          *min_change=change;
          for(int i=0;i<100;i++)
            {
              min_change_trace[i].id_canh=truy_vet_tam_thoi[i].id_canh;
              for(int j=0;j<150;j++) min_change_trace[i].bus[j]=truy_vet_tam_thoi[i].bus[j];
            }
        }
      return;
    }

  else for(int i=1;i<=dijikstra[vid].dem_dinh_truoc;i++)
         find_min_change(graph,dijikstra,vid,dijikstra[vid].id_dinh_truoc[i-1], change, min_change, min_change_trace,truy_vet_tam_thoi, dem_tamthoi);
  return;
}


Graph createGraph()
{
Graph graph;
graph.edges=make_jrb();
graph.vertices=make_jrb();
 graph.bus=make_jrb();
  return graph;
}

void addVertex(Graph graph, char*name,int *vertex_id)
{
  if(jrb_find_str(graph.vertices,name)==NULL)
    {
      *vertex_id=*vertex_id+1;
      jrb_insert_str(graph.vertices,strdup(name),new_jval_i(*vertex_id));
      JRB newEdgesTree=make_jrb();
      jrb_insert_int(graph.edges,*vertex_id, new_jval_v(newEdgesTree));
    }
  return;
}

int getVertexID(Graph graph, char*name)
{
 JRB vertex=jrb_find_str(graph.vertices,name);
 if(vertex==NULL) return INFINITIVE_VALUE;
 else return jval_i(vertex->val);
}

char* getVertexName(Graph graph, int id_canh)
{
  JRB ptr;
  jrb_traverse(ptr,graph.vertices)
    {
      if(jval_i(ptr->val)==id_canh)
        return jval_s(ptr->key);
    }
}

void addBus(Graph graph, char*name,int *bus_id)
{
  if(jrb_find_str(graph.bus,name)==NULL)
    {
      *bus_id=*bus_id+1;
      jrb_insert_str(graph.bus,strdup(name),new_jval_i(*bus_id));
    }
  return;
}

int getBusID(Graph graph, char*name)
{
 JRB bus=jrb_find_str(graph.bus,name);
 if(bus==NULL) return INFINITIVE_VALUE;
 else return jval_i(bus->val);
}

char* getBusName(Graph graph, int b_id)
{
  JRB Node;
  jrb_traverse(Node,graph.bus)
    {
      if(jval_i(Node->val)==b_id)
        return jval_s(Node->key);
    }
}

void addEdge(Graph graph, int v1, int v2, int bus_id)
{
  JRB startVertex=jrb_find_int(graph.edges,v1);
  if(startVertex==NULL)
    {
      printf("Khong co diem bat dau.\n");
      return;
    }

  JRB finishVertex=jrb_find_int(graph.edges,v2);
  if(finishVertex==NULL)
    {
      printf("Khong co diem ket thuc.\n");
      return;
    }

  JRB rootEdgeTreeStartVertex=(JRB)jval_v(startVertex->val);
  JRB vfinishNode=jrb_find_int(rootEdgeTreeStartVertex,v2);

  if(vfinishNode==NULL)
    {
      JRB bus=make_jrb();
      jrb_insert_int(bus,bus_id,new_jval_i(1));
      jrb_insert_int(rootEdgeTreeStartVertex,v2,new_jval_v(bus));
    }
  else
    {
      JRB bus=(JRB)jval_v(vfinishNode->val);
      if(jrb_find_int(bus,bus_id)==NULL)
        jrb_insert_int(bus,bus_id,new_jval_i(1));
    }

  return;
}

JRB getEdgeValue(Graph graph,  int v1, int v2)
{
  JRB node=jrb_find_int(graph.edges,v1);
  if(node==NULL) return NULL;

  JRB Tree=(JRB)jval_v(node->val);

  JRB node1=jrb_find_int(Tree,v2);
  if(node1==NULL)
    { return NULL;}

  return (JRB) jval_v(node1->val);
}

int in_degree(Graph graph, int id_canh, int* output)
{
  JRB Node,tree;
  int total = 0;

  jrb_traverse(Node, graph.edges)
    {
    tree = (JRB) jval_v(Node->val);
      if (jrb_find_int(tree, id_canh)!=NULL)
        {
          total++;
          output[total] = jval_i(Node->key);
        }
    }
  return total;
}

int out_degree(Graph graph, int id_canh, int* output)
{
  JRB Node;
  JRB vertex=jrb_find_int(graph.edges,id_canh);
  JRB vertex_treeEdge= (JRB) jval_v(vertex->val);
  int total = 0;

  jrb_traverse(Node, vertex_treeEdge)
    {
      total++;
     output[total] = jval_i(Node->key);
    }
  return total;
}

void bus_pass(Graph graph, int id_canh, int * xet)//danh dau da di qua
{
  JRB Node;
  JRB vertex_treeEdge;
  jrb_traverse(Node, graph.edges)
    {
      vertex_treeEdge= (JRB) jval_v(Node->val);

      if (jrb_find_int(vertex_treeEdge, id_canh)!=NULL)
        {
          JRB bus_tree=(JRB)jval_v(jrb_find_int(vertex_treeEdge,id_canh)->val);
          JRB bus_Node;
          jrb_traverse(bus_Node, bus_tree)
              xet[jval_i(bus_Node->key)] =1 ;
        }
    }

  JRB vertex=jrb_find_int(graph.edges,id_canh);
  vertex_treeEdge= (JRB) jval_v(vertex->val);
  jrb_traverse(Node, vertex_treeEdge)
    {
      JRB bus_tree=(JRB)jval_v(Node->val);
      JRB bus_Node;
      jrb_traverse(bus_Node, bus_tree)
        {xet[jval_i(bus_Node->key)] =1 ;}
    }
  return;
}

void shortestPath(Graph graph, double *distance_s_f,  int v1, int v2,DIJKSTRA *dijikstra,int  vertex_id)
{
  int  new_choice_vid;
  int new_choice_vid_tmp;

  double min;

  dijikstra[v1].cur_distance = 0;
  dijikstra[v1].dem_dinh_truoc=0;
  new_choice_vid=v1;
  dijikstra[v1].visit=1;

  min= INFINITIVE_VALUE;

  for (int i=0; i<=vertex_id; i++)
    if(i!=v1)
      {
        if(getEdgeValue(graph,v1,i)==NULL)
          {
            dijikstra[i].cur_distance = INFINITIVE_VALUE;
            dijikstra[i].dem_dinh_truoc=0;
          }
        else
          {
            dijikstra[i].cur_distance=1;
            dijikstra[i].dem_dinh_truoc=1;
            dijikstra[i].id_dinh_truoc[dijikstra[i].dem_dinh_truoc-1]= v1;
          }

        if(dijikstra[i].cur_distance<min)
          {
            min=dijikstra[i].cur_distance;
            new_choice_vid_tmp=i;
          }

        dijikstra[i].visit=0;
      }

  if(min==INFINITIVE_VALUE)
    {printf("xay ra loi.\n");*distance_s_f=  -1; return;}

  new_choice_vid=new_choice_vid_tmp;
  dijikstra[new_choice_vid].visit=1;

  do
    {
      min= INFINITIVE_VALUE;

      for (int i=0; i<=vertex_id; i++)
        {
          if(dijikstra[i].visit==0)
            {
              if(getEdgeValue(graph,new_choice_vid,i)!=NULL)
                {

                  double new_distance = dijikstra[new_choice_vid].cur_distance+1;

                  if(dijikstra[i].cur_distance==new_distance)
                    {
                      int check_bansao=0;
                      for(int check=1;check<=dijikstra[i].dem_dinh_truoc;check++)
                        {if(dijikstra[i].id_dinh_truoc[check-1]==new_choice_vid) check_bansao=1;}

                      if(check_bansao==0)
                        {
                          dijikstra[i].dem_dinh_truoc=dijikstra[i].dem_dinh_truoc+1;
                          dijikstra[i].id_dinh_truoc[dijikstra[i].dem_dinh_truoc-1]=new_choice_vid;
                        }
                    }
                  if(dijikstra[i].cur_distance>new_distance)
                    {
                      dijikstra[i].dem_dinh_truoc=1;
                      dijikstra[i].cur_distance=new_distance;
                      dijikstra[i].id_dinh_truoc[dijikstra[i].dem_dinh_truoc-1]=new_choice_vid;
                    }
                }

              if(dijikstra[i].cur_distance<min)
                {
                  min=dijikstra[i].cur_distance;
                  new_choice_vid_tmp=i;
                }
            }
        }
      if(min==INFINITIVE_VALUE)
        {printf("Xay ra loi.\n");*distance_s_f=  -1; return;}

      new_choice_vid=new_choice_vid_tmp;
      dijikstra[new_choice_vid].visit=1;
    }while(dijikstra[v2].cur_distance!=min);
  *distance_s_f=min;
  return ;
}

void dropGraph(Graph graph)
{
  jrb_free_tree(graph.edges);
  jrb_free_tree(graph.vertices);
  jrb_free_tree(graph.bus);
  return;
}

void read(Graph graph, int * vertex_id, int *bus_id)
{
  FILE* file= fopen("bus.txt","r");
  if (file == NULL)
    {
      printf("File input could not open\n");
      return;
	}

  char* ben_chieu_di[50];
  for (int i = 0;i<50;i++)
    ben_chieu_di[i] = (char*)malloc(100*sizeof(char));

  char* ben_chieu_ve[50];
  for (int i = 0;i<50;i++)
    ben_chieu_ve[i] = (char*)malloc(100*sizeof(char));

  fseek(file,0,SEEK_SET);
  char checkEOF=' ';
  while (!feof(file))
	{
      char bus_name[10];
      fscanf(file,"%[^\n]s",bus_name);
      addBus(graph,bus_name,bus_id);

      while (fgetc(file)=='\n');
      fseek(file,-1,SEEK_CUR);

      int ben_count_di=-1;
      char check='\0';
      do{
        ben_count_di=ben_count_di+1;
        fscanf(file,"%[^-.]s",ben_chieu_di[ben_count_di]);
        addVertex(graph, ben_chieu_di[ben_count_di],vertex_id);
        check=fgetc(file);
      }while(check!='.');

      while (fgetc(file)=='\n');
      fseek(file,-1,SEEK_CUR);

      for(int i=0;i<ben_count_di;i++)
        addEdge(graph, getVertexID(graph,ben_chieu_di[i] ), getVertexID(graph,ben_chieu_di[i+1] ),*bus_id);

      int ben_count_ve=-1;
      check='\0';
      do{
        ben_count_ve=ben_count_ve+1;
        fscanf(file,"%[^-.]s",ben_chieu_ve[ben_count_ve]);
        addVertex(graph, ben_chieu_ve[ben_count_ve],vertex_id);
        check=fgetc(file);
      }while(check!='.');

      for(int i=0;i<ben_count_ve;i++)
        addEdge(graph, getVertexID(graph,ben_chieu_ve[i] ), getVertexID(graph,ben_chieu_ve[i+1] ), *bus_id);

      while(fgetc(file)!='\n');
      while((checkEOF=fgetc(file))=='\n');

      if(checkEOF!=EOF)
        fseek(file,-1,SEEK_CUR);
    }

  for (int i = 0;i<50;i++) free(ben_chieu_di[i]);
  for (int i = 0;i<50;i++) free(ben_chieu_ve[i]);
  fclose(file);
}

int check_exist(Graph graph, char*name)
{if(getVertexID(graph, name)!=INFINITIVE_VALUE)
    return 0; else return 1;}
void menu()
{
  printf("\nMENU\n\n");
  printf("******************************\n");
    printf("Lua Chon 0: Thoat chuong trinh.\n");
  printf("Lua chon 1: Kiem tra ten mot dia diem trong Ha Noi.\n");
  printf("Lua chon 2: Kiem tra 2 dia diem co noi truc tiep voi nhau hay khong.\n");
  printf("Lua chon 3: Nhung dia diem noi voi dia diem cho truoc.\n");
  printf("Lua chon 4: Cac tuyen bus di qua 1 dia diem.\n");
  printf("Lua chon 5: Quang duong ngan nhat di chuyen.\n");
  printf("******************************\n\n");
  return;
}
int luachon()
{
  float choice;
  printf("Moi ban nhap vao lua chon cua minh: ");
  scanf("%f",&choice);
  while((choice!=1)&(choice!=2)&(choice!=3)&(choice!=4)&(choice!=5)&(choice!=0))
    {
      printf("Ban da nhap sai!\n");
      printf("Moi ban nhap lai: ");
      scanf("%f",&choice);
    }
  printf("\n******************************\n\n");
  return choice;
}

