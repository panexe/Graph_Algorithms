#include <iostream>

#include "graph.h"

using namespace std;

int main()
{
    Graph graph;

    graph.insertVertex(0,"Augusta");
    graph.insertVertex(1,"Bangstadt");
    graph.insertVertex(2,"Chemograd");
    graph.insertVertex(3,"Domchurch");
    graph.insertVertex(4,"Entfield");
    graph.insertVertex(5,"Fangen");
    graph.insertVertex(6,"Geksenmund");
    graph.insertVertex(7,"Hollidings");

    // from A
    graph.insertBiArc(0,1,14);
    graph.insertBiArc(0,2,4);
    graph.insertBiArc(0,3,2);
    graph.insertBiArc(0,4,8);
    graph.insertBiArc(0,7,16);

    // from B
    graph.insertBiArc(1,2,11);
    graph.insertBiArc(1,4,15);

    // from C
    graph.insertBiArc(2,3,4);
    graph.insertBiArc(2,4,5);

    // from D
    graph.insertBiArc(3,4,6);
    graph.insertBiArc(3,5,15);
    graph.insertBiArc(3,6,7);
    graph.insertBiArc(3,7,14);

    // from E
    graph.insertBiArc(4,5,10);

    // from F
    graph.insertBiArc(5,6,9);

    // from G
    graph.insertBiArc(6,7,8);

    graph.printVertecies();
    std::cout << "---------------------------------------------\n";
    graph.printAdj();
    std::cout << "Gewicht vom Graphen: " << totalGraphWeight(graph)/2 << '\n';
    std::cout << "---------------------------------------------\n";

    Graph* mst = MST(graph);
    mst->printVertecies();
    std::cout << "---------------------------------------------\n";
    mst->printAdj();
    std::cout << "Gewicht vom mst: " << totalGraphWeight(*mst)/2 << '\n';
    std::cout << "---------------------------------------------\n";

    Dijkstra(&graph,0);
    std::cout << "---------------------------------------------\n";
    Dijkstra(mst,0);
    std::cout << "---------------------------------------------\n";

    Graph graph2;
    graph2.insertVertex(0,"0");
    graph2.insertVertex(1,"1");
    graph2.insertVertex(2,"2");
    graph2.insertVertex(3,"3");

    graph2.insertArc(0,1);
    graph2.insertArc(0,2);
    graph2.insertArc(1,2);
    graph2.insertArc(2,0);
    graph2.insertArc(2,3);
    graph2.insertArc(3,3);

    DFS(graph,4);
    std::cout << "---------------------------------------------\n";
    BFS(graph,4);
    std::cout << "---------------------------------------------\n";

    Graph graph3;
    graph3.insertVertex(0,"A");
    graph3.insertVertex(1,"B");
    graph3.insertVertex(2,"C");
    graph3.insertVertex(3,"D");
    graph3.insertVertex(4,"E");
    graph3.insertVertex(5,"F");
    graph3.insertVertex(6,"G");
    graph3.insertVertex(7,"H");

    graph3.insertBiArc(0,1);
    graph3.insertBiArc(0,2);
    graph3.insertBiArc(1,3);
    graph3.insertBiArc(1,4);
    graph3.insertBiArc(2,5);
    graph3.insertBiArc(2,6);
    graph3.insertBiArc(4,7);

    BFS(graph3,0);
    std::cout << "---------------------------------------------\n";

    Graph graph4;

    graph4.insertVertex(0,"Socken");
    graph4.insertVertex(1,"Schuhe");
    graph4.insertVertex(2,"Uhr");
    graph4.insertVertex(3,"Unterhose");
    graph4.insertVertex(4,"Hose");
    graph4.insertVertex(5,"Hemd");
    graph4.insertVertex(6,"Guertel");
    graph4.insertVertex(7,"Sakko");
    graph4.insertVertex(8,"Krawatte");

    graph4.insertArc(0,1);
    graph4.insertArc(3,1);
    graph4.insertArc(3,4);
    graph4.insertArc(4,6);
    graph4.insertArc(4,1);
    graph4.insertArc(6,7);
    graph4.insertArc(5,6);
    graph4.insertArc(5,8);
    graph4.insertArc(8,7);

    topsort(graph4);
    std::cout << "---------------------------------------------\n";

    Graph graph5;
    graph5.insertVertex(0,"a");
    graph5.insertVertex(1,"b");
    graph5.insertVertex(2,"c");
    graph5.insertVertex(3,"d");
    graph5.insertVertex(4,"e");
    graph5.insertVertex(5,"f");
    graph5.insertVertex(6,"g");
    graph5.insertVertex(7,"h");

    // from a
    graph5.insertArc(0,1,4);
    graph5.insertArc(0,6,7);
    graph5.insertArc(0,7,4);

    // from b
    graph5.insertArc(1,7,1);
    graph5.insertArc(1,2,9);
    graph5.insertArc(1,5,6);
    graph5.insertArc(1,6,8);

    // from c
    graph5.insertArc(2,4,10);

    // from d

    // from e
    graph5.insertArc(4,3,6);
    graph5.insertArc(4,2,8);
    graph5.insertArc(4,5,5);

    // from f
    graph5.insertArc(5,4,6);

    // from g
    graph5.insertArc(6,1,4);
    graph5.insertArc(6,5,7);


    // from h
    graph5.insertArc(7,2,3);

    //graph5.printAdj();
    //std::cout << "---------------------------------------------\n";
    FloydWarshall(graph5);





    return 0;
}
