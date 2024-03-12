#include <stdlib.h>
#include <string.h>
#include "bfs.h"
#include <queue>
#include <iostream>
#include <stack>
using namespace std;



int get_neighbors(const Grid *grid, Point p, Point neighb[])
{
    // TODO: fill the array neighb with the neighbors of the point p and return the number of neighbors
    // the point p will have at most 4 neighbors (up, down, left, right)
    // avoid the neighbors that are outside the grid limits or fall into a wall
    // note: the size of the array neighb is guaranteed to be at least 4
    int dr[8] = {-2,-1,1,2,1,2,-1,-2}; // -2 1, -1 2, 1 2 , 2 1 , 1 -2, 2 -1, -1 -2, -2 -1
    int dc[8] = { 1,2,2,1,-2,-1,-2,-1};
    int j = 0;
    for (int i = 0; i < 8; i++)
    {
        int row = p.row + dr[i];
        int col = p.col + dc[i];
        cout << "row=" << row << " col=" << col << " ";
        if (row < grid->rows && row >= 0 && col < grid->cols && col >= 0 && grid->mat[row][col] != 1)
        {
            neighb[j].row = row;
            neighb[j].col = col;
            j++;
        }
    }
    return j;
}

void grid_to_graph(const Grid *grid, Graph *graph)
{
    //we need to keep the nodes in a matrix, so we can easily refer to a position in the grid
    Node *nodes[MAX_ROWS][MAX_COLS];
    int i, j, k;
    Point neighb[8];

    //compute how many nodes we have and allocate each node
    graph->nrNodes = 0;
    for(i=0; i<grid->rows; ++i){
        for(j=0; j<grid->cols; ++j){
            if(grid->mat[i][j] == 0){
                nodes[i][j] = (Node*)malloc(sizeof(Node));
                memset(nodes[i][j], 0, sizeof(Node)); //initialize all fields with 0/NULL
                nodes[i][j]->position.row = i;
                nodes[i][j]->position.col = j;
                ++graph->nrNodes;
            }else{
                nodes[i][j] = NULL;
            }
        }
    }
    graph->v = (Node**)malloc(graph->nrNodes * sizeof(Node*));
    k = 0;
    for(i=0; i<grid->rows; ++i){
        for(j=0; j<grid->cols; ++j){
            if(nodes[i][j] != NULL){
                graph->v[k++] = nodes[i][j];
            }
        }
    }

    //compute the adjacency list for each node
    for(i=0; i<graph->nrNodes; ++i){
        graph->v[i]->adjSize = get_neighbors(grid, graph->v[i]->position, neighb);
        if(graph->v[i]->adjSize != 0){
            graph->v[i]->adj = (Node**)malloc(graph->v[i]->adjSize * sizeof(Node*));
            k = 0;
            for(j=0; j<graph->v[i]->adjSize; ++j){
                if( neighb[j].row >= 0 && neighb[j].row < grid->rows &&
                    neighb[j].col >= 0 && neighb[j].col < grid->cols &&
                    grid->mat[neighb[j].row][neighb[j].col] == 0){
                        graph->v[i]->adj[k++] = nodes[neighb[j].row][neighb[j].col];
                }
            }
            if(k < graph->v[i]->adjSize){
                //get_neighbors returned some invalid neighbors
                graph->v[i]->adjSize = k;
                graph->v[i]->adj = (Node**)realloc(graph->v[i]->adj, k * sizeof(Node*));
            }
        }
    }
}

void free_graph(Graph *graph)
{
    if(graph->v != NULL){
        for(int i=0; i<graph->nrNodes; ++i){
            if(graph->v[i] != NULL){
                if(graph->v[i]->adj != NULL){
                    free(graph->v[i]->adj);
                    graph->v[i]->adj = NULL;
                }
                graph->v[i]->adjSize = 0;
                free(graph->v[i]);
                graph->v[i] = NULL;
            }
        }
        free(graph->v);
        graph->v = NULL;
    }
    graph->nrNodes = 0;
}
void dezaloca(int r, int** x)
{
    for (int i = 0; i < r; i++)
        free(x[i]); // dezaloca fiecare linie
    free(x); // dezaloca sirul de pointeri la linii
}
void createGraph(Graph* graph, int n, int m) {
    int** a = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        a[i] = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = 0;
    int cnt2 = 0;
    int k = 1;
    while (cnt2 < m - n + 1)
    {
        int min = rand() % (n - 1);
        int other = min + rand() % (n - min);
        if (a[min][other] == 0 && min != other)
        {
            graph->v[min]->adjSize++;
            graph->v[min]->adj[k] = graph->v[other];
            k++;
            a[min][other] =1;
            //cout << " A=" << A[min][other] << endl;
            cnt2++;
        }
    }
    cnt2 = 0;
    dezaloca(n, a);

}
void bfs(Graph *graph, Node *s, Operation *op)
{
    int INF = 999999;
    // TOOD: implement the BFS algorithm on the graph, starting from the node s
    // at the end of the algorithm, every node reachable from s should have the color BLACK
    // for all the visited nodes, the minimum distance from s (dist) and the parent in the BFS tree should be set
    // for counting the number of operations, the optional op parameter is received
    // since op can be NULL (when we are calling the bfs for display purposes), you should check it before counting:
    // if(op != NULL) op->count();
    for (int i = 0; i < graph->nrNodes; i++)
    {
        if (op != NULL)
            op->count(3);
        graph->v[i]->color = 0;
        graph->v[i]->dist = INF;
        graph->v[i]->parent = NULL;
    }
    if (op != NULL)
        op->count(3);
    s->color = 1;
    s->dist = 0;
    s->parent = NULL;
    queue<Node*> q;
    q.push(s);
    cout << q.front();
    int size = 1;
    while (size) {
        Node* u = q.front();
        q.pop();
        size--;
        for (int i = 0; i < u->adjSize; i++)
        {
            if (op != NULL)
                op->count();
            if (u->adj[i]->color == 0)
            {
                if (op != NULL)
                    op->count(4);
                u->adj[i]->color = 1;
                u->adj[i]->dist = u->dist + 1;
                u->adj[i]->parent = u;
                size++;
                q.push(u->adj[i]);
            }
        }
        if (op != NULL)
            op->count();
        u->color = 2;

    }
}
void pp(int a[], int size, int parent, Point repr[], int level)
{
    // cout<<repr[1]->
    for (int i = 0; i < size; i++)
    {
        if (a[i] == parent)
        {
            for (int j = 0; j < level; j++)
                cout << ' ';
            cout <<"("<< repr[i].row << ", " << repr[i].col <<")"<< endl;
            pp(a, size, i,repr, level + 6);
        }

    }
}
void pp2(int a[], int size, int parent, Point repr[], int level)
{
    // cout<<repr[1]->
    for (int i = 0; i < size; i++)
    {
        cout << repr[i].row<<" "<<repr[i].col << " " << repr[a[i]].row<<" "<<repr[a[i]].col<<" "<<a[i] << " ";

    }
}

bool bfs2(Graph* graph, Node* s, Operation* op,Node* d)
{
    int INF = 999999;
    // TOOD: implement the BFS algorithm on the graph, starting from the node s
    // at the end of the algorithm, every node reachable from s should have the color BLACK
    // for all the visited nodes, the minimum distance from s (dist) and the parent in the BFS tree should be set
    // for counting the number of operations, the optional op parameter is received
    // since op can be NULL (when we are calling the bfs for display purposes), you should check it before counting:
    // if(op != NULL) op->count();
    for (int i = 0; i < graph->nrNodes; i++)
    {
        if (op != NULL)
            op->count(3);
        graph->v[i]->color = 0;
        graph->v[i]->dist = INF;
        graph->v[i]->parent = NULL;
    }
    if (op != NULL)
        op->count(3);
    s->color = 1;
    s->dist = 0;
    s->parent = NULL;
    queue<Node*> q;
    q.push(s);
    cout << q.front();
    int size = 1;
    while (size) {
        Node* u = q.front();
        q.pop();
        size--;
        for (int i = 0; i < u->adjSize; i++)
        {
            if (op != NULL)
                op->count();
            if (u->adj[i]->color == 0)
            {
                if (op != NULL)
                    op->count();
                if (op != NULL)
                    op->count(3);
                u->adj[i]->color = 1;
                u->adj[i]->dist = u->dist + 1;
                u->adj[i]->parent = u;
                size++;
                q.push(u->adj[i]);
                if (u->adj[i] == d)
                    return true;
            }
        }
        u->color = 2;

    }
}
void print_bfs_tree(Graph *graph)
{
    //first, we will represent the BFS tree as a parent array
    int n = 0; //the number of nodes
    int *p = NULL; //the parent array
    Point *repr = NULL; //the representation for each element in p

    //some of the nodes in graph->v may not have been reached by BFS
    //p and repr will contain only the reachable nodes
    int *transf = (int*)malloc(graph->nrNodes * sizeof(int));
    for(int i=0; i<graph->nrNodes; ++i){
        if(graph->v[i]->color == COLOR_BLACK){
            transf[i] = n;
            ++n;
        }else{
            transf[i] = -1;
        }
    }
    if(n == 0){
        //no BFS tree
        free(transf);
        return;
    }

    int err = 0;
    int aux;
    p = (int*)malloc(n * sizeof(int));
    repr = (Point*)malloc(n * sizeof(Node));
    for(int i=0; i<graph->nrNodes && !err; ++i){
        if(graph->v[i]->color == COLOR_BLACK){
            if(transf[i] < 0 || transf[i] >= n){
                err = 1;
            }else{
                repr[transf[i]] = graph->v[i]->position;
                if(graph->v[i]->parent == NULL){
                    p[transf[i]] = -1;
                    aux = transf[i];
                }else{
                    err = 1;
                    for(int j=0; j<graph->nrNodes; ++j){
                        if(graph->v[i]->parent == graph->v[j]){
                            if(transf[j] >= 0 && transf[j] < n){
                                p[transf[i]] = transf[j];
                                err = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
    free(transf);
    transf = NULL;

    if(!err){
        // TODO: pretty print the BFS tree
        // the parrent array is p (p[k] is the parent for node k or -1 if k is the root)
        // when printing the node k, print repr[k] (it contains the row and column for that point)
        // you can adapt the code for transforming and printing multi-way trees from the previous labs
        //for (int j = 0; j < graph->nrNodes; j++)
           // cout << j << " " << p[j] << " ";
        //cout << repr[aux].row << " " << repr[aux].col<<endl;
        pp(p, n, -1, repr, 2);

    }

    if(p != NULL){
        free(p);
        p = NULL;
    }
    if(repr != NULL){
        free(repr);
        repr = NULL;
    }
}

int shortest_path(Graph *graph, Node *start, Node *end, Node *path[])
{
    // TODO: compute the shortest path between the nodes start and end in the given graph
    // the nodes from the path, should be filled, in order, in the array path
    // the number of nodes filled in the path array should be returned
    // if end is not reachable from start, return -1
    // note: the size of the array path is guaranteed to be at least 1000
    if (bfs2(graph, start, NULL, end))
    {
        stack<Node*> st;
        int i = 0;
        while (end->parent)
        {
            st.push(end);
            i++;
            end = end->parent;
        }
        for (int j = 0; j < i; j++)
        {
            path[j] = st.top();
            st.pop();
        }
        return i;
    }

    else
    return -1;
}


void performance()
{
    int n, i;
    Profiler p("bfs");

    // vary the number of edges
    for(n=1000; n<=4500; n+=100){
        Operation op = p.createOperation("bfs-edges", n);
        Graph graph;
        graph.nrNodes = 100;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for(i=0; i<graph.nrNodes; ++i){
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }
        // TODO: generate n random edges
        // make sure the generated graph is connected
        for (int i = 0; i < graph.nrNodes - 1; i++)
        {
            graph.v[i]->adjSize = 1;
            graph.v[i]->adj= (Node**)malloc(100 * sizeof(Node*));
            graph.v[i]->adj[0] = graph.v[i + 1];
        }
        srand(time(NULL));
        int** a = (int**)malloc(graph.nrNodes * sizeof(int*));
        for (int i = 0; i < graph.nrNodes; i++)
            a[i] = (int*)malloc(graph.nrNodes * sizeof(int));
        for (int i = 0; i < graph.nrNodes; i++)
            for (int j = 0; j < graph.nrNodes; j++)
                a[i][j] = 0;
        for (int i = 0; i < n - graph.nrNodes + 1; i++)
        {
            int aux1 = rand() % 99;
            int aux2 = rand() % 99;
            if (aux1 != aux2 && a[aux1][aux2]==0)
            {
                graph.v[aux1]->adj[graph.v[aux1]->adjSize] = (Node*)malloc(sizeof(Node));
                graph.v[aux1]->adj[graph.v[aux1]->adjSize] = graph.v[aux2];
                graph.v[aux1]->adjSize++;
                a[aux1][aux2] = 1;
            }
        }
        dezaloca(graph.nrNodes, a);
        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }

    // vary the number of vertices
    for(n=100; n<=200; n+=10){
        Operation op = p.createOperation("bfs-vertices", n);
        Graph graph;
        graph.nrNodes = n;
        //initialize the nodes of the graph
        graph.v = (Node**)malloc(graph.nrNodes * sizeof(Node*));
        for(i=0; i<graph.nrNodes; ++i){
            graph.v[i] = (Node*)malloc(sizeof(Node));
            memset(graph.v[i], 0, sizeof(Node));
        }
        // TODO: generate 4500 random edges
        // make sure the generated graph is connected
        for (int i = 0; i < graph.nrNodes - 1; i++)
        {
            graph.v[i]->adjSize = 1;
            graph.v[i]->adj = (Node**)malloc(100 * sizeof(Node*));
            graph.v[i]->adj[0] = graph.v[i + 1];
        }
        srand(time(NULL));
        int** a = (int**)malloc(graph.nrNodes * sizeof(int*));
        for (int i = 0; i < graph.nrNodes; i++)
            a[i] = (int*)malloc(graph.nrNodes * sizeof(int));
        for (int i = 0; i < graph.nrNodes; i++)
            for (int j = 0; j < graph.nrNodes; j++)
                a[i][j] = 0;
        for (int i = 0; i < 4500 - graph.nrNodes + 1; i++)
        {
            int aux1 = rand() % 99;
            int aux2 = rand() % 99;
            if (aux1 != aux2 && a[aux1][aux2]==0)
            {
                graph.v[aux1]->adj[graph.v[aux1]->adjSize] = (Node*)malloc(sizeof(Node));
                graph.v[aux1]->adj[graph.v[aux1]->adjSize] = graph.v[aux2];
                graph.v[aux1]->adjSize++;
                a[aux1][aux2] = 1;
            }
        }
        dezaloca(graph.nrNodes, a);
        bfs(&graph, graph.v[0], &op);
        free_graph(&graph);
    }

    p.showReport();
}
