//Id-9115
//Email address- orgoren3146@gmail.

#include "Graph.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace ariel;


Graph::Graph()
{
    this->isDirected = false;
    this->isWeighed = false;
    this->numOfEdges = 0;
    this->numOfVertices = 0;
}

/* The function gets vector and loads it to the graph.
   It also initializes the class fields
 */

void Graph::loadGraph(const vector<vector<int>> &gr)
{
    if (gr.empty() || gr.size() == 0 || gr.size() != gr[0].size())
    {
        throw invalid_argument("Invalid matrix");
    }

    this->graph = gr;
    this->numOfVertices = gr.size();

    size_t isD = 0;
    size_t isW = 0;
    for (size_t i = 0; i < gr.size(); i++)
    {
        for (size_t z = 0; z < gr.size(); z++)
        {
            if (i == z && gr[i][z] != 0)
            {
                throw invalid_argument("Invalid matrix");
            }
            //Checking if the graph is directed
            if (gr[i][z] != gr[z][i])
            {
                isD++;
            }
            //Checking if the graph is weighed
            if (gr[i][z] > 1)
            {
                isW++;
            }
        }
    }
    if (isD != 0)
    {
        this->isDirected = true;
    }
    if (isW != 0)
    {
        this->isWeighed = true;
    }

    this->numOfEdges = countNumOfEdges(gr);
}

// Side function for the print method
int Graph::countNumOfEdges(const vector<vector<int>> &gr)
{

    int countEdges = 0;
    for (size_t i = 0; i < gr.size(); i++)
    {
        for (size_t z = 0; z < gr.size(); z++)
        {
            if (gr[i][z] != 0)
            {
                countEdges++;
            }
        }
    }
    if (this->isDirected == 1)
    {
        return countEdges;
    }
    return countEdges / 2;
}

// The function prints the number of vertices and edgesin the graph
void Graph::printGraph() const
{

    cout << "Graph with " << this->numOfVertices << " vertices and " << this->numOfEdges << " edges" << endl;
}

bool Graph::getIsDirected() const
{
    return this->isDirected;
}
bool Graph::getIsWeighed() const
{
    return this->isWeighed;
}
int Graph::getNumOfVertices() const
{
    return this->numOfVertices;
}
// For testing countNumOfEdges
int Graph::getNumOfEdges() const
{
    return this->numOfEdges;
}
vector<vector<int>> Graph::getGraph() const
{
    return this->graph;
}


// Operators overloading methods

// The computing operators

// Overloading the + operator
Graph Graph:: operator+ (const Graph g1){
    //Checking if the number of vertices in both graphs are equal. If not, throwing an exception
    if(g1.getNumOfVertices()!= this->getNumOfVertices()){
        throw invalid_argument("Matrices dimensions must be equal for addition");
    }

    vector<vector<int>> graph1= this->getGraph();
    vector<vector<int>> graph2= g1.getGraph();
    vector<vector<int>> graph3((size_t)this->getNumOfVertices(),vector<int>((size_t)this->getNumOfVertices(), 0));
    //Adding between the two matrices
    for(size_t i=0;i<g1.getNumOfVertices();i++){
        for(size_t j=0;j<g1.getNumOfVertices();j++){
            graph3[i][j]=graph1[i][j]+graph2[i][j];
        }
    }

    Graph temp;
    temp.loadGraph(graph3);
    return temp;
}


//Overloading the += operator
Graph& Graph:: operator += (const Graph g1){
    //Checking if the number of vertices in both graphs are equal. If not, throwing an exception
    if(g1.getNumOfVertices()!= this->getNumOfVertices()){
        throw invalid_argument("Matrices dimensions must be equal for addition");
    }

    vector<vector<int>> graph1= this->getGraph();
    vector<vector<int>> graph2= g1.getGraph();
    //Adding between the two matrices
    for(size_t i=0;i<g1.getNumOfVertices();i++){
        for(size_t j=0;j<g1.getNumOfVertices();j++){
            graph1[i][j]=graph1[i][j]+graph2[i][j];
        }
    }
    //loading the new matrix to the graph and return a reference of it
    this->loadGraph(graph1);
    return *this;
}


// Overloading the unary + operator
Graph& Graph:: operator + (){
    // return a refernce of the graph
    return *this;
}


//Overloading the - operator
Graph Graph:: operator- (const Graph g1){
    
    //Checking if the number of vertices in both graphs are equal. If not, throwing an exception
    if(g1.getNumOfVertices()!= this->getNumOfVertices()){
        throw invalid_argument("Matrices dimensions must be equal for subtraction");
    }
    vector<vector<int>> graph1= this->getGraph();
    vector<vector<int>> graph2= g1.getGraph();
    vector<vector<int>> graph3((size_t)this->getNumOfVertices(),vector<int>((size_t)this->getNumOfVertices(), 0));
    
    //Subtracting between the two matrices
    for(size_t i=0;i<g1.getNumOfVertices();i++){
        for(size_t j=0;j<g1.getNumOfVertices();j++){
            graph3[i][j]=graph1[i][j]-graph2[i][j];
        }
    }
    Graph temp;
    temp.loadGraph(graph3);
    return temp;
}


//Overloading the -= operator
Graph& Graph:: operator -= (const Graph g1){
    //Checking if the number of vertices in both graphs are the equal. If not, throwing an exception
    if(g1.getNumOfVertices()!= this->getNumOfVertices()){
       throw invalid_argument("Matrices dimensions must be equal for subtraction");
    }

    vector<vector<int>> graph1= this->getGraph();
    vector<vector<int>> graph2= g1.getGraph();
    //Subtracting between the two matrices
    for(size_t i=0;i<g1.getNumOfVertices();i++){
        for(size_t j=0;j<g1.getNumOfVertices();j++){
            graph1[i][j]=graph1[i][j]-graph2[i][j];
        }
    }
    
    this->loadGraph(graph1);
    // return a refernce to the graph after the change
    return *this;
    
}


//Overloading the unary - operator
Graph& Graph:: operator - (){
    
    vector<vector<int>> graph1=this->getGraph();
    
    //Changing each element in the graph from graph[i][j] to -graph[i][j] 
    for(size_t i=0;i<this->getNumOfVertices();i++){
        for(size_t j=0;j<this->getNumOfVertices();j++){
            graph1[i][j]*=-1;
        }
    }

    this->loadGraph(graph1);
    
    // return a refernce to the graph after the change
    return *this;
}


//Overloading the * operator
Graph Graph:: operator * (const Graph g1){
     //Checking if the number of vertices in both graphs are the same. If not, throwing an exception
    if(this->getNumOfVertices()!= g1.getNumOfVertices()){
        throw invalid_argument("The size of the columns in matrix A have to be equal to the size of the rows in matrix B for multiplying");
    }

    vector<vector<int>> graph1= this->getGraph();
    vector<vector<int>> graph2= g1.getGraph();
    vector<vector<int>> graph3((size_t)this->getNumOfVertices(),vector<int>((size_t)g1.getNumOfVertices(), 0));
    
    /*Making the matrix multiplication
    If i==j, setting this element in the matrix to 0. 
    Else, multiply each element in a row of matrix A with the corresponding element in a column of matrix B 
    and then making addition between all the results.
    For each row in matrix A we are repeating it n times (n=num of columns of matrix B) 
    */
    int temp=0;
    // i represents the rows in matrix A
    for(size_t i=0;i<graph1.size();i++){
        // j represents the cols in matrix B
        for(size_t j=0;j<graph2[0].size();j++){
            //If i==j, means it's a diagonal element
            if(i==j){
                continue;
            }
            for(size_t z=0; z<graph2.size(); z++){  
                temp+= graph1[i][z]*graph2[z][j];
            }
            graph3[i][j]=temp;
            temp=0;
        }
    }
    Graph t1;
    t1.loadGraph(graph3);
    return t1;   
}


//Overloading the *= operator
Graph&  Graph:: operator *= ( int num){

    vector<vector<int>> graph1= this->getGraph();
    //multiply each element in the matrix with num
    for(size_t i=0;i<this->getNumOfVertices();i++){
        for(size_t j=0;j<this->getNumOfVertices();j++){
            graph1[i][j]*=num;
        }
    }
    
    this->loadGraph(graph1);
    return *this;
}


//Overloading the /= operator
Graph& Graph:: operator /= (int num){
    //Making sure the scalar!=0
    if(num!=0){
        vector<vector<int>> graph1= this->getGraph();
        //Dividing each element in the matrix with num
        for(size_t i=0;i<this->getNumOfVertices();i++){
            for(size_t j=0;j<this->getNumOfVertices();j++){
                graph1[i][j]/=num;
            }
        }
    
        this->loadGraph(graph1);
    }
    return *this;
    
}


//Overloading the = operator
void Graph:: operator = (const Graph g1){
    this->loadGraph(g1.getGraph()); 
    
}

//Overloading the == operator
bool Graph:: operator == (const Graph g1)const{

    // Check if the graphs has equal num of vertices
    if(g1.getNumOfVertices()!= this->getNumOfVertices()){
        return false;
    }
    vector<vector<int>> graph1= this->getGraph();
    vector<vector<int>> graph2= g1.getGraph();
    // Checking if the graphs has the same edges
    for(size_t i=0;i<g1.getNumOfVertices();i++){
        for(size_t j=0;j<g1.getNumOfVertices();j++){
            if(graph1[i][j]!=graph2[i][j] ){
                return false;
            }
        }
    }
    return true;
}

//Overloading the != operator
bool Graph:: operator != (const Graph g1)const{
    //checking if the graphs are equal by calling to the == overloaded method    
    if(*this==g1){
        return false;
    }
    return true;
}

//Overloading the > operator
bool Graph::operator >(const Graph& g1) const {
    
    vector<vector<int>> graph1= this->getGraph();
    vector<vector<int>> graph2= g1.getGraph();
    
    /* checking whether g1 graph contained in the other graph.
    Making sure before that the number of vertices in the other graph bigger or equal to the number of vertices in g1 to avoid exceptions.
    */    
        if(this->getNumOfVertices()>=g1.getNumOfVertices()){
        int temp=0;
        for(size_t i=0;i<g1.getNumOfVertices();i++){
            for(size_t j=0;j<g1.getNumOfVertices();j++){
                if(graph1[i][j]==0 && graph2[i][j]!=0) {
                    return false;
                }
            }
        }     
       return true;
        
    }
     
    //checking if the number of edges in g1 greater then g2
    if(this->getNumOfEdges()>g1.getNumOfEdges()){
        return true;
    }
    
    //checking if the number of edges in g1 greater then g2
    if(this->getNumOfVertices()>g1.getNumOfVertices()){
        return true;
    }
    return false;
}

//Overloading the >= operator
bool Graph::operator >= (const Graph& g1) const {
    
    //Checking with the overloaded operator methods > and == if the other graph greater or equal to g1
    if(*this>g1 || *this==g1){
        return true;
    }
    return false;
}

//Overloading the < operator
bool Graph::operator <(const Graph& g1) const {
//Checking with the overloaded operator method > if the other graph smaller than g1
    if(*this> g1){
        return false;
    }
    return true;

}

//Overloading the <= operator
bool Graph::operator <= (const Graph& g1) const {
    //Checking with the overloaded operator methods < and == if the other graph smaller or equal to g1
    if(*this<g1 || *this==g1){
        return true;
    }
    return false;
}

//Overloading the << operator
ostream &ariel::operator<<(ostream &os, const Graph &gr)
{
     vector<vector<int>> graph1 = gr.getGraph();
    // using ostream os to print the graph
    for (size_t i = 0; i < graph1.size(); i++) {
        os << "[";
        for (size_t j = 0; j < gr.getNumOfVertices(); j++) {
            os << graph1[i][j];
            if (j < gr.getNumOfVertices() - 1) {
                os << ", ";
            }
        }
        os << "]";
        if (i < graph1.size() - 1) {
            os << ", ";
        }
    }
    os<<endl;
    return os;
}


//Overloading the ++x operator
Graph& Graph::operator++ () {

    vector<vector<int>> graph1 = this->getGraph();
    //incrementing each element of the graph by 1 
    for (size_t i = 0; i < graph1.size(); i++) {
        for (size_t j = 0; j < graph1[i].size(); j++) {
            if(i!=j){
            graph1[i][j]=graph1[i][j]+1 ;
            }
        }
    }
    this->loadGraph(graph1);
    //return a copy of the graph when all the edges incremented by 1
    return *this;
}

//Overloading the x++ operator
Graph Graph::operator++ (int num) {
    //creating another graph with the current parameters of the graph
    Graph temp;
    temp.loadGraph(this->getGraph());

    vector<vector<int>> graph1 = this->getGraph();
      //incrementing each element of the graph by 1 
    for (size_t i = 0; i < graph1.size(); i++) {
        for (size_t j = 0; j < graph1[i].size(); j++) {
            if(i!=j){
            graph1[i][j]=graph1[i][j]+1 ;
            }
        }
    }
    this->loadGraph(graph1);
    //return the same graph 
    return temp;
}


// Overloading the --x operator
Graph& Graph::operator-- () {
    
    vector<vector<int>> graph1 = this->getGraph();
    // Decrementing each element of the graph by 1 
    for (size_t i = 0; i < graph1.size(); i++) {
        for (size_t j = 0; j < graph1[i].size(); j++) {
            if(i!=j){
            graph1[i][j]=graph1[i][j]-1 ;
            }
        }
    }
    //return a copy of the graph when all the edges decremented by 1
    this->loadGraph(graph1);
    return *this;
}

// Overloading the x-- operator
Graph Graph::operator-- (int num) {
    
    Graph temp;
    temp.loadGraph(this->getGraph());
    vector<vector<int>> graph1 = this->getGraph();

    // Decrementing each element of the graph by 1 
    for (size_t i = 0; i < graph1.size(); i++) {
        for (size_t j = 0; j < graph1[i].size(); j++) {
            if(i!=j){
            graph1[i][j]=graph1[i][j]-1 ;
            }
        }
    }
    this->loadGraph(graph1);
    //return the same graph we got, the operator first return the value and then decrementing
    return temp;
}
