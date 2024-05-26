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
    this->getNumOfVertices= gr.size();
    this->getNumOfVertices=gr[0].size();

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

// The function prints 
void Graph::printGraph() const
{
    cout << "Graph with " << this->numOfVertices << " vertices and " << this->numOfEdges << " edges" << endl;
}



Graph Graph:: operator+ (const Graph g1)const{
    if(g1.getNumOfVertices()!= this->getNumOfVertices()){
        cout<< "Matrices dimensions must be equal for addition"<<endl;
        exit(1);
    }

    vector<vector<int>> graph1= this->getGraph();
    vector<vector<int>> graph2= g1.getGraph();
    vector<vector<int>> graph3((size_t)this->getNumOfVertices(),vector<int>((size_t)this->getNumOfVertices(), 0));

    for(size_t i=0;i<g1.getNumOfVertices();i++){
        for(size_t j=0;j<g1.getNumOfVertices();j++){
            graph3[i][j]=graph1[i][j]+graph2[i][j];
        }
    }
    Graph temp;
    temp.loadGraph(graph3);
    return temp;
}


Graph& Graph:: operator + (){
    
    return *this;
}

Graph& Graph:: operator += (const Graph g1){
    if(g1.getNumOfVertices()!= this->getNumOfVertices()){
        cout<< "Matrices dimensions must be equal for addition"<<endl;
        exit(1);
    }

    vector<vector<int>> graph1= this->getGraph();
    vector<vector<int>> graph2= g1.getGraph();

    for(size_t i=0;i<g1.getNumOfVertices();i++){
        for(size_t j=0;j<g1.getNumOfVertices();j++){
            graph1[i][j]=graph1[i][j]+graph2[i][j];
        }
    }
    
    this->loadGraph(graph1);
    return *this;
}



Graph& Graph::operator++ () {

    vector<vector<int>> graph1 = this->getGraph();
    for (size_t i = 0; i < graph1.size(); i++) {
        for (size_t j = 0; j < graph1[i].size(); j++) {
            graph1[i][j]=graph1[i][j]+1;
        }
    }
    
    this->loadGraph(graph1);
    
    return *this;
}

Graph Graph::operator++ (int num) {
    Graph temp;
    temp.loadGraph(this->getGraph());

    vector<vector<int>> graph1 = this->getGraph();

    for (size_t i = 0; i < graph1.size(); i++) {
        for (size_t j = 0; j < graph1[i].size(); j++) {
            graph1[i][j]=graph1[i][j]+1 ;
        }
    }
    this->loadGraph(graph1);

    return temp;
}

Graph Graph:: operator- (const Graph g1)const{
    if(g1.getNumOfVertices()!= this->getNumOfVertices()){
        cout<< "Matrices dimensions must be equal for subtraction"<<endl;
        exit(1);
    }
    vector<vector<int>> graph1= this->getGraph();
    vector<vector<int>> graph2= g1.getGraph();
    vector<vector<int>> graph3((size_t)this->getNumOfVertices(),vector<int>((size_t)this->getNumOfVertices(), 0));

    for(size_t i=0;i<g1.getNumOfVertices();i++){
        for(size_t j=0;j<g1.getNumOfVertices();j++){
            graph3[i][j]=graph1[i][j]-graph2[i][j];
        }
    }
    Graph temp;
    temp.loadGraph(graph3);
    return temp;
}

Graph& Graph:: operator - (){
    
    vector<vector<int>> graph1=this->getGraph();

    for(size_t i=0;i<this->getNumOfVertices();i++){
        for(size_t j=0;j<this->getNumOfVertices();j++){
            graph1[i][j]*=-1;
        }
    }
    this->loadGraph(graph1);
    return *this;
}

Graph& Graph:: operator -= (const Graph g1){
    if(g1.getNumOfVertices()!= this->getgetNumOfVertices()){
        cout<< "Matrices dimensions must be equal for subtraction"<<endl;
        exit(1);
    }

    vector<vector<int>> graph1= this->getGraph();
    vector<vector<int>> graph2= g1.getGraph();

    for(size_t i=0;i<g1.getNumOfVertices();i++){
        for(size_t j=0;j<g1.getNumOfVertices();j++){
            graph1[i][j]=graph1[i][j]-graph2[i][j];
        }
    }
    
    this->loadGraph(graph1);
    return *this;
    
}

Graph& Graph::operator-- () {
    vector<vector<int>> graph1 = this->getGraph();

    for (size_t i = 0; i < graph1.size(); i++) {
        for (size_t j = 0; j < graph1[i].size(); j++) {
            graph1[i][j]=graph1[i][j]-1 ;
        }
    }
    this->loadGraph(graph1);
    return *this;
}

Graph Graph::operator-- (int num) {
    Graph temp;
    temp.loadGraph(this->getGraph());
    vector<vector<int>> graph1 = this->getGraph();

    for (size_t i = 0; i < graph1.size(); i++) {
        for (size_t j = 0; j < graph1[i].size(); j++) {
            graph1[i][j]=graph1[i][j]-1 ;
        }
    }
    this->loadGraph(graph1);

    return temp;
}

void Graph:: operator = (const Graph g1){
    this->loadGraph(g1.getGraph()); 
    
}


Graph Graph:: operator * (const Graph g1)const{
    if(this->getNumOfVertices()!= g1.getNumOfVertices()){
        cout<< "The size of the columns in matrix A have to be equal to the size of the rows in matrix B for duplicating"<<endl;
        exit(1);
    }

    vector<vector<int>> graph1= this->getGraph();
    vector<vector<int>> graph2= g1.getGraph();
    vector<vector<int>> graph3((size_t)this->getNumOfVertices(),vector<int>((size_t)g1.getNumOfVertices(), 0));

    int temp=0;
    for(size_t i=0;i<graph1.size();i++){
        for(size_t j=0;j<graph2[0].size();j++){
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



Graph&  Graph:: operator *= ( const int num){

    vector<vector<int>> graph1= this->getGraph();

    for(size_t i=0;i<this->getNumOfVertices();i++){
        for(size_t j=0;j<this->getNumOfVertices();j++){
            graph1[i][j]*=num;
        }
    }
    
    this->loadGraph(graph1);
    return *this;
}

Graph& Graph:: operator /= (int num){

    vector<vector<int>> graph1= this->getGraph();

    for(size_t i=0;i<this->getNumOfVertices();i++){
        for(size_t j=0;j<this->getNumOfVertices();j++){
            graph1[i][j]/=num;
        }
    }
    
    this->loadGraph(graph1);
    return *this;
    
}


bool Graph:: operator == (const Graph g1)const{

    // check if the graphs has equal num of vertices
    if(g1.getNumOfVertices()!= this->getNumOfVertices()){
        return false;
    }
    vector<vector<int>> graph1= this->getGraph();
    vector<vector<int>> graph2= g1.getGraph();

    for(size_t i=0;i<g1.getNumOfVertices();i++){
        for(size_t j=0;j<g1.getNumOfVertices();j++){
            if(graph1[i][j]!=graph2[i][j] ){
                return false;
            }
        }
    }
    return true;
}

bool Graph:: operator != (const Graph g1)const{
    
    if(*this==g1){
        return false;
    }
    return true;
}

bool Graph::operator >(const Graph& g1) const {
    
    if(*this== g1){
        return false;
    }

    vector<vector<int>> graph1= this->getGraph();
    vector<vector<int>> graph2= g1.getGraph();
    
    // check if graph g1 inside the other graph
    if(this->getNumOfVertices()>=g1.getNumOfVertices()){
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
     // check if the other graph inside g1, making sure before if the num or vertices in 
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
    
    //check if the number of edges in g1 grater then g2
    if(this->getNumOfEdges()>g1.getNumOfEdges()){
        return true;
    }
    if(this->getNumOfEdges()<g1.getNumOfEdges()){
        return false;
    }
    if(this->getNumOfVertices()>g1.getNumOfVertices()){
        return true;
    }
    return false;
}

bool Graph::operator >= (const Graph& g1) const {
    

    if(*this>g1 || *this==g1){
        return true;
    }
    return false;
}


bool Graph::operator <(const Graph& g1) const {

    if(*this> g1 || *this ==g1){
        return false;
    }
    return true;

}

bool Graph::operator <= (const Graph& g1) const {
    
    if(*this<g1 || *this==g1){
        return true;
    }
    return false;
}


ostream &ariel::operator<<(ostream &os, const Graph &gr)
{
     vector<vector<int>> graph1 = gr.getGraph();
   
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
