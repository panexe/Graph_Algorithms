#ifndef GRAPH_H
#define GRAPH_H

#include <limits>
#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>

#include <queue>
#include <stack>

/*****************************************/
/*            GLOABL CONSTANTS           */
/*****************************************/

constexpr const int MAX_NODES = 25; // global max to limit the size of the adj.-matrix
constexpr const double NO_ARC = std::numeric_limits<double>::max();
constexpr const double INFINITY = std::numeric_limits<double>::max();

const std::string out_of_range_error = "The index must be between 0 and" + MAX_NODES;

/*****************************************/
/*                 GRAPH                 */
/*****************************************/

/* Adj. Matrix implementation of a directed Graph
 * uses string as data, could(should) be replaced by a template argument
 */
class Graph{

protected:
    /* Vertex helper-class
     * Represents a single node of the graph
     */
    class Vertex{
    public:
        Vertex(){
            living = visited = false;
            indegree = outdegree = ord = 0;
            data = "";
        }
        bool living, visited;
        int indegree, outdegree, ord;
        std::string data;
    };

    /*****************************************/
    /*               ATTRIBUTES              */
    /*****************************************/

    Vertex vertex[MAX_NODES]; // stores the nodes
    double arc[MAX_NODES][MAX_NODES]; // the adj-matrix

    size_t size;
    size_t num_arcs;

public:
    /*****************************************/
    /*            GETTER & SETTER            */
    /*****************************************/

    /*
     *
     */
    size_t Size(){
        return this->size;
    }

    /*
     *
     */
    size_t numArcs(){
        return this->num_arcs;
    }

    /*
     *
     */
    std::string getData(const int& n){
        if(n < 0 || n > MAX_NODES)
            throw std::out_of_range(out_of_range_error);

        return vertex[n].data;
    } // end getData

    /*
     *
     */
    int getIndegree(const int& n){
        if(n < 0 || n > MAX_NODES)
            throw std::out_of_range(out_of_range_error);

        return vertex[n].indegree;
    } // end getIndegree

    /*
     *
     */
    int getOutdegree(const int& n){
        if(n < 0 || n > MAX_NODES)
            throw std::out_of_range(out_of_range_error);

        return vertex[n].outdegree;
    } // end getOurdegree

    /*
     *
     */
    int getOrd(const int& n){
        if(n < 0 || n > MAX_NODES)
            throw std::out_of_range(out_of_range_error);

        return vertex[n].ord;
    } // end getOrd

    /*
     *
     */
    bool getVisited(const int& n){
        if(n < 0 || n > MAX_NODES)
            throw std::out_of_range(out_of_range_error);

        return vertex[n].visited;
    } // end getVisited

    /*
     *
     */
    void setVisited(const int& n, const bool& value){
        if(n < 0 || n > MAX_NODES)
            throw std::out_of_range(out_of_range_error);

        vertex[n].visited = value;
    } // end setVisited

    /* sets all nodes visited-attr. to the given value
     *
     */
    void setAllVisited(const bool& value){
        for(int i=firstVertex(); i!=-1; i=nextVertex(i)){
            setVisited(i,value);
        }

    } // end setAllVisited

    bool getAlive(const int& n){
        if(n < 0 || n > MAX_NODES)
            throw std::out_of_range(out_of_range_error);

        return vertex[n].living;
    }

    double getArc(const int& from, const int& to){
        if(from < 0 || from > MAX_NODES)
            throw std::out_of_range(out_of_range_error);
        if(to < 0 || to > MAX_NODES)
            throw std::out_of_range(out_of_range_error);

        return arc[from][to];

    }

    /*****************************************/
    /*               TRAVERSAL               */
    /*****************************************/

    /* returns the index of the first living node
     * -1 if empty
     */
    int firstVertex(){
        for(int i=0; i<MAX_NODES; ++i){
            if(vertex[i].living)
                return i;
        }
        return -1;
    } // end firstVertex

    /* returns the index of the next living node after the given one
     * -1 if there isn't one
     */
    int nextVertex(const int& from){
        if(from < 0 || from > MAX_NODES)
            return -1;

        for(int i=from+1; i<MAX_NODES; i++){
            if(vertex[i].living)
                return i;
        }
        return -1;
    } // end nextVertex

    /* returns the index of the first outgoing arc from the given node
     * -1 if there isn't one
     */
    int firstArc(const int& from){
        if(from < 0 || from > MAX_NODES)
            return -1;

        for(int to=0; to<MAX_NODES; to++){
            if(arc[from][to] < NO_ARC)
                return to;
        }
        return -1;
    } // end firstArc

    /* returns the index of the next outgoing arc after the given one
     * -1 if there isn't one
     */
    int nextArc(const int& from,int to){
        if(from < 0 || from > MAX_NODES)
            return -1;
        if(to < 0 || to > MAX_NODES)
            return -1;

        for(to++; to<MAX_NODES; to++){
            if(arc[from][to] < NO_ARC)
                return to;
        }
        return -1;
    } // end nextArc

    /*****************************************/
    /*              CONSTRUCTORS             */
    /*****************************************/


    /* Constructor
     *
     */
    Graph(){
        size = 0;

        // init the nodes and matrix to 0
        for(size_t i=0; i<MAX_NODES; i++){
            vertex[i] = Vertex();
            for(size_t j=0; j<MAX_NODES; j++){
                arc[i][j] = NO_ARC;
            }
        }

    } // end constructor

    /* copy-constructor
     *
     */
    Graph(const Graph& other){
        size = other.size;

        // init the nodes and matrix to 0
        for(size_t i=0; i<MAX_NODES; i++){
            vertex[i] = other.vertex[i];
            for(size_t j=0; j<MAX_NODES; j++){
                arc[i][j] = other.arc[i][j];
            }
        }
    } // end copy constructor

    /* Destructor
     *
     */
    ~Graph(){
        // nothign to delete here
    } // end destructor


    /*****************************************/
    /*            MEMBER FUNCTIONS           */
    /*****************************************/

    /* inserts a new vertex to the graph
     * retunrs -1 if node(n) already is alive
     */
    int insertVertex(const int& n, const std::string& data){
        if(n < 0 || n > MAX_NODES)
            throw std::out_of_range(out_of_range_error);

        if(vertex[n].living)
            return -1;

        vertex[n].living = true;
        vertex[n].data = data;
        size++;
        return 0;
    } // end insertVertex

    /* inserts a new Arc between the given nodes
     * return -1 if one of the arcs isnt alive
     */
    int insertArc(const int& from,const int& to, const double& weight = 0){
        if(from < 0 || from > MAX_NODES)
            throw std::out_of_range(out_of_range_error);
        if(from < 0 || from > MAX_NODES)
            throw std::out_of_range(out_of_range_error);

        if(!vertex[from].living || !vertex[to].living)
            return -1;

        arc[from][to] = weight;

        vertex[from].ord++;
        vertex[from].outdegree++;

        vertex[to].ord++;
        vertex[to].indegree++;

        return 0;
    } // end insertArc

    /* inserts an arc from a->b and b->a, thus acting like an undirected arc
     *
     */
    int insertBiArc(const int& from, const int& to, const double weight=0){
        insertArc(from,to,weight);
        return insertArc(to,from,weight);
    } // end insertBiArc

    /*****************************************/
    /*            PRINT FUNCITONS            */
    /*****************************************/

    /* prints a single node to the screen
     * n | data | indegree | outdegree | \n
     * string_limit limits the length of the data-string to the given value
     */
    void printVertex(const int& n, const size_t string_limit = 15){
        if(n < 0 || n > MAX_NODES)
            return;

        std::cout << n << ": " << vertex[n].data.substr(0,string_limit);
        std::cout << "\tIndegree: " << vertex[n].indegree;
        std::cout << "\tOutdegree: " << vertex[n].outdegree << '\n';
    } // end printVertex

    /* calls the printVertex function for all living nodes
     * string_limit limits the length of the data-strings to the given value
     */
    void printVertecies(const size_t string_limit = 15){
        std::cout << "All vertecies: \n";

        for(int i=firstVertex(); i!=-1; i=nextVertex(i)){
            printVertex(i,string_limit);
        }

    } // end printVertecies

    /* prints the adj-matrix to the console
     *
     */
    void printAdj(){
        std::cout << "Adj.-Matrix:\n";
        // first row of indices
        std::cout << "  \t";
        for(int i=firstVertex(); i!=-1; i=nextVertex(i)){
            std::cout << i << '\t';
        }
        std::cout << '\n';

        for(int i=firstVertex(); i!=-1; i=nextVertex(i)){
            std::cout << std::setw(2) << i << ": " << '\t';
            for(int j=firstVertex(); j!=-1; j=nextVertex(j)){
                if(arc[i][j] < NO_ARC){
                    std::cout << std::setprecision(3) << arc[i][j] << '\t';
                }
                else{
                    std::cout << "   \t";
                }
            }
            std::cout << '\n';
        }

    } // end printAdj

};


/*****************************************/
/*          DIJKSTRA ALGORITHM           */
/*****************************************/

typedef std::pair<int,double> pair;

/* Compare class to sort the std::priority_queue
 *
 */
class ComparePair{
public:
    bool operator()(pair p1,pair p2){
        return p1.second < p2.second;
    }
};

/* implementation of the Dijkstra shortest path algorithm
 *
 */
void Dijkstra(Graph* g, const int& start){
    if(start < 0 || start > MAX_NODES)
        throw std::out_of_range(out_of_range_error);
    if(!g->getAlive(start))
        return;

    std::cout << "Dijkstra starting from: " << g->getData(start).substr(0,15)<<'(' << start << ')' << "\n\n";

    double* dist = new double[MAX_NODES]; //stores the calced distance to all nodes
    int* prev = new int[MAX_NODES]; // stores the previos node to get the shortest path

    // init distances & prev-nodes & visited
    for(size_t i=0; i<MAX_NODES; i++){
        dist[i] = INFINITY;
        prev[i] = -1;
    }
    g->setAllVisited(false);
    std::priority_queue<pair,std::vector<pair>,ComparePair> q;

    // set values for the first node
    dist[start] = 0;
    prev[start] = -2;
    g->setVisited(start,true);
    q.push(pair(start,0));

    // main loop
    while(!q.empty()){
        // get the arc with the shortest distance nad remove it from the q
        pair current = q.top();
        q.pop();

        // go trough every outgoing connection
        for(int i=g->firstArc(current.first); i!=-1; i=g->nextArc(current.first,i)){
            // calc the distance
            double distance = g->getArc(current.first,i) + dist[current.first];

            // update the distance
            if(distance < dist[i] && g->getVisited(i)){
                dist[i] = distance;
                prev[i] = current.first;
            }
            // set the first distance and push to the q
            else if(!g->getVisited(i)){
                g->setVisited(i,true);
                dist[i] = distance;
                prev[i] = current.first;
                q.push(pair(i,distance));
            }

        }


    } // end main loop

    // output for every node
    for(int i=g->firstVertex(); i!=-1; i=g->nextVertex(i)){
        std::cout << g->getData(i) << ": " << dist[i] << '\n';
        int j=i;
        // put the path onto the stack
        std::stack<int> path;
        while(prev[j]!=-2){
            path.push(j);
            j = prev[j];
        }
        path.push(start);

        // print the path in order
        while(!path.empty()){
            std::cout << "->" << g->getData(path.top());
            path.pop();
        }
        std::cout << "\n\n";
    }

    // freeing up memory
    delete[] dist;
    delete [] prev;

} // end Dijkstra

/*****************************************/
/*             DFS TRAVERSAL             */
/*****************************************/

/* recursive helper method for dfs
 *
 */
void _dfs(Graph& g,const int& s, const size_t& string_limit=15){
    std::cout << g.getData(s).substr(0,string_limit) << ' ';
    g.setVisited(s,true);
    for(int i=g.firstArc(s);i!=-1; i=g.nextArc(s,i)){
        if(!g.getVisited(i)){
            _dfs(g,i,string_limit);
        }
    }

} // end _dfs

/* Depth-First-Search Traversal of the graph
 * doesnt include segment checking, just the nodes
 * that can be reached from the start-node
 */
void DFS(Graph& g,const int& start, const size_t& string_limit=15){
    if(start < 0 || start > MAX_NODES)
        throw std::out_of_range(out_of_range_error);

    std::cout << "DFS starting from: " << start << '\n';


    // init visited value
    g.setAllVisited(false);
    _dfs(g,start,string_limit);
    std::cout << '\n';
} // end DFS

/*****************************************/
/*             BFS TRAVERSAL             */
/*****************************************/

/* Breadth-First-Search Traversal of the graph
 *
 */
void BFS(Graph& g,const int& start){
    if(start < 0 || start > MAX_NODES)
        throw std::out_of_range(out_of_range_error);

    std::cout << "BFS starting from: " << start << '\n';

    // init visited values
    g.setAllVisited(false);
    std::queue<int> q;
    q.push(start);

    // main loop
    while(!q.empty()){
        // get first node & visit (set visited & print)
        int current = q.front();
        g.setVisited(current,true);
        std::cout << g.getData(current) << ' ';
        q.pop();

        // push every adjacent node that hasn't been visited to the q
        for(int i=g.firstArc(current); i!=-1; i=g.nextArc(current,i)){
            if(!g.getVisited(i)){
                g.setVisited(i,true);
                q.push(i);
            }
        }

    }
    std::cout << '\n';

} // end BFS


/*****************************************/
/*       TOPSORT (KAHN ALGORITHM)        */
/*****************************************/

/* topological sorting using the indegree of each node
 *
 */
void topsort(Graph& g){
    std::vector<int> order;
    std::queue<int> q;
    int indegree[MAX_NODES];
    int count{0};

    for(int i=0; i<MAX_NODES; i++){
        indegree[i] = g.getIndegree(i);
    }

    for(int i=g.firstVertex(); i!=-1; i=g.nextVertex(i)){
        if(g.getIndegree(i) == 0){
            q.push(i);
        }
    }

    while(!q.empty()){
        int current = q.front();
        q.pop();
        order.push_back(current);
        for(int i=g.firstArc(current); i!=-1; i=g.nextArc(current,i)){
            --indegree[i];
            if(indegree[i] == 0){
                q.push(i);
            }
        }

        count++;

        if(count > g.Size()){
            std::cout << "The graph is cyclic! \n";
            return;
        }
    }

    std::cout << "Topsort: \n";
    for(auto it=order.begin(); it!=order.end(); it++){
        std::cout << g.getData(*it) << '\n';
    }

}

/*****************************************/
/*         MINIMAL SPANNING TREE         */
/*****************************************/

struct arc{
    arc(int from_,int to_,double weight_){
        from = from_;
        to = to_;
        weight = weight_;
    }
    int from,to;
    double weight;
};

class CompareArc{
public:
    bool operator()(arc a1, arc a2){
        return a1.weight > a2.weight;
    }
};

/* creates a minimal spanning tree from the given graph
 *
 */
Graph* MST(Graph& g){

    Graph* ret = new Graph();

    g.setAllVisited(false);
    std::priority_queue<arc,std::vector<arc>,CompareArc> q;
    // copy vertecies from old graph
    // and put all arcs into the queue
    for(int i=g.firstVertex(); i!=-1; i=g.nextVertex(i)){
        ret->insertVertex(i,g.getData(i));

        for(int j=g.firstArc(i); j!=-1; j=g.nextArc(i,j)){
            q.push(arc(i,j,g.getArc(i,j)));
        }

    }

    // main loop
    while(!q.empty()){
        // take the smallest arc
        arc current = q.top();
        q.pop();

        // if one of the both nodes hasnt been visited
        // add it to the new graph
        if(!g.getVisited(current.from)){
            ret->insertBiArc(current.from,current.to,current.weight);
            g.setVisited(current.from,true);
            g.setVisited(current.to,true);
        }
        else if(!g.getVisited(current.to)){
            ret->insertBiArc(current.from,current.to,current.weight);
            g.setVisited(current.from,true);
            g.setVisited(current.to,true);
        }

    }

    return ret;

}

/* returns the sum of all arc weights
 *
 */
double totalGraphWeight(Graph& g){
    double sum{0};
    for(int i=g.firstVertex(); i!=-1; i=g.nextVertex(i)){
        for(int j=g.firstArc(i); j!=-1; j=g.nextArc(i,j)){
            sum+=g.getArc(i,j);
        }

    }
    return sum;

}

/*****************************************/
/*     Floyd-Warshall Shortest Path      */
/*****************************************/

/* calculates the shortest path for all nodes
 * for this implementation to work, all nodes have
 * to be inserted in sequence
 */
void FloydWarshall(Graph& g){
    std::cout << "Floyd-Warshall: \n";

    // create distance matrix
    double** dist = new double*[g.Size()];
    for(int i=0; i<g.Size(); i++){
        dist[i] = new double[g.Size()];
    }
    for(int i=0; i<g.Size(); i++){
        for(int j=0; j<g.Size(); j++){
            dist[i][j] = INFINITY;
        }
    }


    // copy distances from graph
    for(int i=g.firstVertex(); i!=-1; i=g.nextVertex(i)){
        for(int j=g.firstVertex(); j!=-1; j=g.nextVertex(j)){
            dist[i][j] = g.getArc(i,j);
        }
    }
    // set distances to self to 0
    for(int i=g.firstVertex(); i!=-1; i=g.nextVertex(i)){
        dist[i][i] = 0;
    }

    // calc the min distances
    for(int k=g.firstVertex(); k!=-1; k=g.nextVertex(k)){
        for(int i=g.firstVertex(); i!=-1; i=g.nextVertex(i)){
            for(int j=g.firstVertex(); j!=-1; j=g.nextVertex(j)){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // first row of indices
    std::cout << "  \t";
    for(int i=g.firstVertex(); i!=-1; i=g.nextVertex(i)){
        std::cout << i << '\t';
    }
    std::cout << '\n';

    for(int i=g.firstVertex(); i!=-1; i=g.nextVertex(i)){
        std::cout << std::setw(2) << i << ": " << '\t';
        for(int j=g.firstVertex(); j!=-1; j=g.nextVertex(j)){
            if(dist[i][j] < NO_ARC){
                std::cout << std::setprecision(3) << dist[i][j] << '\t';
            }
            else{
                std::cout << "   \t";
            }
        }
        std::cout << '\n';
    }




}


#endif // GRAPH_H
