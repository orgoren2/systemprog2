//Id-9115
//Email address- orgoren3146@gmail.

#include "Graph.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace ariel;


/** The function gets vector and loads it to the graph.
 * It also initalizes the class fields
 */
void Graph::loadGraph(vector<vector<int>> gr)
{
    this->graph = gr; 
    this->numOfVertices = gr.size(); 

    size_t isD = 0;
    size_t isW = 0; 
    for (size_t i = 0; i < gr.size(); i++)
    {
        for (size_t z = 0; z < gr.size(); z++)
        {
            if (gr[i][z] != gr[z][i])
            {
                isD++;
            }
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
int Graph::countNumOfEdges(vector<vector<int>> gr) 
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
    if (this->isDirected)
    {
        return countEdges;
    }
    return countEdges / 2;
}

// The function prints the graph's number of vertices and edges
void Graph::printGraph() const
{
    cout << "Graph with " << this->numOfVertices << " vertices and " << this->numOfEdges << " edges" << endl;
}


// Operators overloading methods

// The computing operators

// Overloading the + operator
Graph Graph:: operator+ (const Graph g1)const{
    //Checking if the number of vertices in both graphs are the same. If not, throwing an exception
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
    //Checking if the number of vertices in both graphs are the same. If not, throwing an exception
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
    //loading the new matrix to the graph and return a copy of it
    this->loadGraph(graph1);
    return *this;
}


// Overloading the unary + operator
Graph& Graph:: operator + (){
    // return a copy of the graph
    return *this;
}


//Overloading the - operator
Graph Graph:: operator- (const Graph g1)const{
    
    //Checking if the number of vertices in both graphs are the same. If not, throwing an exception
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
    //Checking if the number of vertices in both graphs are the same. If not, throwing an exception
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
Graph Graph:: operator * (const Graph g1)const{
     //Checking if the number of vertices in both graphs are the same. If not, throwing an exception
    if(this->getNumOfVertices()!= g1.getNumOfVertices()){
        throw invalid_argument("The size of the columns in matrix A have to be equal to the size of the rows in matrix B for duplicating");
    }

    vector<vector<int>> graph1= this->getGraph();
    vector<vector<int>> graph2= g1.getGraph();
    vector<vector<int>> graph3((size_t)this->getNumOfVertices(),vector<int>((size_t)g1.getNumOfVertices(), 0));
    
    /*Making the matrix multiplication
    If i==j, setting this element in the matrix to 0. 
    Else, multiply each element in a row of matrix A with the corresponding element in a column of matrix B 
    and then making addition between all the results.
    For each row in matrix A we are repeating it n times (n=num of columns of B matrix) 
    */
    int temp=0;
    for(size_t i=0;i<graph1.size();i++){
        for(size_t j=0;j<graph2[0].size();j++){
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
Graph&  Graph:: operator *= ( const int num){

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

    vector<vector<int>> graph1= this->getGraph();
    //Dividing each element in the matrix with num
    for(size_t i=0;i<this->getNumOfVertices();i++){
        for(size_t j=0;j<this->getNumOfVertices();j++){
            graph1[i][j]/=num;
        }
    }
    
    this->loadGraph(graph1);
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
    Making sure before that the numer of vertices in the two matrices equal to avoid exceptions.
    */    if(this->getNumOfVertices()>=g1.getNumOfVertices()){
        int temp=0;
        for(size_t i=0;i<g1.getNumOfVertices();i++){
            for(size_t j=0;j<g1.getNumOfVertices();j++){
                if(graph1[i][j]!=0 && graph2[i][j]!=0) {
                    temp++;
                }
            }
        }
               
        if(temp== g1.getNumOfEdges() &&temp!= this->getNumOfEdges()){
            return true;
        }
        
    }
    /* checking whether the other graph contained g1.
    Making sure before that the numer of vertices in the two matrices equal to avoid exceptions.
    */
    if(this->getNumOfVertices()<=g1.getNumOfVertices()){
        int temp=0;
        for(size_t i=0;i<this->getNumOfVertices();i++){
            for(size_t j=0;j<this->getNumOfVertices();j++){
                if(graph1[i][j]!=0 && graph2[i][j]!=0){
                    temp++;
                }
            }
        }

        if(temp== this->getNumOfEdges() && temp!= g1.getNumOfEdges() ){
            return false;     
        }
    }
    
    //checking if the number of edges in g1 greater then g2
    if(this->getNumOfEdges()>g1.getNumOfEdges()){
        return true;
    }
    if(this->getNumOfEdges()<g1.getNumOfEdges()){
        return false;
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

//Overloading the >= operator
bool Graph::operator <(const Graph& g1) const {
//Checking with the overloaded operator method > if the other graph smaller than g1
    if(*this> g1){
        return false;
    }
    return true;

}

//Overloading the >= operator
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
    //return a copy of the graph when all the edges increment by 1
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
    //return a copy of the graph when all the edges decrement by 1
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