#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stack>
using namespace std;
#define MAX_VERTEX 50
#define UNDIRECTEDGRAPH 0
#define DIRECTEDGRAPH 1
#define DISPLAYGRAPH 0
#define DEPTHFIRSTTRAVERSAL 1
#define INCREASINGORDER 0
#define DECREASINGORDER 1
struct VertexType
{
    char strName[10];
    float weight;
    bool isMarked;
    VertexType *next;
    VertexType()
    {
        strcpy(strName, "");
        weight = 0;
        isMarked = false;
        next = NULL;
    }
};
struct GraphNode
{
    VertexType vertex;
    VertexType *adjVertex;
    int indegree;
    int outdegree;
    bool isMarked;
    GraphNode()
    {
        indegree = 0;
        outdegree = 0;
        isMarked = false;
        adjVertex = NULL;
    }
};
struct Graph
{
    int nGraphType;
    int nOperation;
    int nVertexNum;
    VertexType startVertex;
    int nOrder;
    GraphNode graph[MAX_VERTEX];
};
Graph myGraph;
int readFile(Graph &myGraph, char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL) // File not found or cannot read
        return 0;

    // Read the graph type and operation type from the file
    fscanf(f, "%d", &myGraph.nGraphType);
    fscanf(f, "%d", &myGraph.nOperation);

    // Read the number of vertices in the graph
    fscanf(f, "%d", &myGraph.nVertexNum);
    // Read the names of the vertices and populate the graph structure
    char strName[MAX_VERTEX];
    for (int i = 0; i < myGraph.nVertexNum; i++)
    {
        fscanf(f, "%s", strName);
        strcpy(myGraph.graph[i].vertex.strName, strName);
    }
    // Read the starting vertex for depth-first traversal
    char startVertexName[MAX_VERTEX];
    fscanf(f, "%s", startVertexName);
    for (int i = 0; i < myGraph.nVertexNum; i++)
    {
        if (strcmp(myGraph.graph[i].vertex.strName, startVertexName) == 0)
        {
            myGraph.startVertex = myGraph.graph[i].vertex;
            break;
        }
    }
    fscanf(f, "%d", &myGraph.nOrder);
    // Read the adjacency matrix and update the graph structure
    for (int i = 0; i < myGraph.nVertexNum; i++)
    {
        VertexType *temp = myGraph.graph[i].adjVertex;

        for (int j = 0; j < myGraph.nVertexNum; j++)
        {
            int edgeWeight;
            fscanf(f, "%d", &edgeWeight);
            if (edgeWeight != 0)
            {
                VertexType *tempHea = NULL;
                VertexType *newAdjVertex = new VertexType;
                strcpy(newAdjVertex->strName, myGraph.graph[j].vertex.strName);
                newAdjVertex->weight = edgeWeight;
                if (temp == NULL)
                {
                    myGraph.graph[i].adjVertex = newAdjVertex;
                    temp = newAdjVertex;
                }
                else
                {
                    temp->next = newAdjVertex;
                    temp = temp->next;
                }
                myGraph.graph[i].outdegree++;
                myGraph.graph[j].indegree++;

                // Check if the edge is undirected, then add the reverse edge for directed graph
                if (myGraph.nGraphType == UNDIRECTEDGRAPH)
                {
                    cout << "UNDIRECTEDGRAPh" << endl;
                    VertexType *reverseAdjVertex = new VertexType;
                    reverseAdjVertex->weight = edgeWeight;
                    reverseAdjVertex->next = myGraph.graph[i].adjVertex;
                    myGraph.graph[j].outdegree++;
                    myGraph.graph[i].indegree++;
                    myGraph.graph[i].adjVertex = reverseAdjVertex;
                }
            }
        }
    }
    fclose(f);
    // Todo
    return 1;
}
void DisplayGraph(Graph &myGraph)
{
    // Todo
    for (int i = 0; i < myGraph.nVertexNum; i++)
    {
        cout << myGraph.graph[i].vertex.strName << ": ";

        VertexType *adjVertex = myGraph.graph[i].adjVertex;
        while (adjVertex != NULL)
        {
            cout << adjVertex->strName << " ";
            adjVertex = adjVertex->next;
        }
        cout << endl;
    }
}
// Custom stack implementation
template <typename T>
class MyStack
{
private:
    T *arr;
    int top;
    int capacity;

public:
    MyStack(int size)
    {
        capacity = size;
        arr = new T[capacity];
        top = -1;
    }

    ~MyStack()
    {
        delete[] arr;
    }

    void push(T item)
    {
        if (top == capacity - 1)
        {
            cout << "Stack Overflow" << endl;
            return;
        }
        arr[++top] = item;
    }

    T pop()
    {
        if (top == -1)
        {
            cout << "Stack Underflow" << endl;
            return T();
        }
        return arr[top--];
    }

    bool empty()
    {
        return top == -1;
    }
};

string depthFirstTraversal(Graph &myGraph, VertexType startVertex) {
    string result = "";
    MyStack<int> vertexStack(myGraph.nVertexNum);

    int startIndex = -1;
    for (int i = 0; i < myGraph.nVertexNum; i++) {
        if (strcmp(myGraph.graph[i].vertex.strName, startVertex.strName) == 0) {
            startIndex = i;
            break;
        }
    }

    if (startIndex == -1) {
        cout << "Start vertex not found." << endl;
        return result;
    }

    bool visited[MAX_VERTEX] = { false };
    visited[startIndex] = true;

    vertexStack.push(startIndex);

    while (!vertexStack.empty()) {
        int currentIndex = vertexStack.pop();
        result += myGraph.graph[currentIndex].vertex.strName;
        result += " ";

        // Collect adjacent vertices
        int adjIndices[MAX_VERTEX];
        int adjCount = 0;
        VertexType *adjVertex = myGraph.graph[currentIndex].adjVertex;

        while (adjVertex != NULL) {
            int adjIndex = -1;
            for (int i = 0; i < myGraph.nVertexNum; i++) {
                if (strcmp(myGraph.graph[i].vertex.strName, adjVertex->strName) == 0) {
                    adjIndex = i;
                    break;
                }
            }

            if (adjIndex != -1 && !visited[adjIndex]) {
                adjIndices[adjCount++] = adjIndex;
                visited[adjIndex] = true;
            }
            adjVertex = adjVertex->next;
        }

        // Sort adjacent vertices based on nOrder
        for (int i = 0; i < adjCount - 1; i++) {
            for (int j = i + 1; j < adjCount; j++) {
                if ((myGraph.nOrder == INCREASINGORDER && strcmp(myGraph.graph[adjIndices[i]].vertex.strName, myGraph.graph[adjIndices[j]].vertex.strName) > 0) ||
                    (myGraph.nOrder == DECREASINGORDER && strcmp(myGraph.graph[adjIndices[i]].vertex.strName, myGraph.graph[adjIndices[j]].vertex.strName) < 0)) {
                    int temp = adjIndices[i];
                    adjIndices[i] = adjIndices[j];
                    adjIndices[j] = temp;
                }
            }
        }

        // Push sorted adjacent vertices onto the stack
        for (int i = 0; i < adjCount; i++) {
            vertexStack.push(adjIndices[i]);
        }
    }

    return result;
}

int main()
{
    for (int i = 0; i < MAX_VERTEX; i++)
        strcpy(myGraph.graph[i].vertex.strName, "-1");
    readFile(myGraph, "input.txt");
    switch (myGraph.nOperation)
    {
    case DISPLAYGRAPH:
        cout << "Display Graph" << endl;
        DisplayGraph(myGraph);
        cout << "-----------------------------" << endl;
        break;
    case DEPTHFIRSTTRAVERSAL:
        cout << "Depth First Traversal" << endl;
        cout << depthFirstTraversal(myGraph, myGraph.startVertex) << endl;
        cout << "-----------------------------" << endl;
        break;
    }
    return 0;
}