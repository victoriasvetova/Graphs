#include <iostream>
#include "Graph_matrix.h"
#include "Graph_lists.h"
#include "Tests.h"
int main() {
    TestAll();

    std::cout << "Enter start :";
    int start;
    std::cin >> start;

    std::cout << "Enter finish :";
    int finish;
    std::cin >> finish;

    std::ifstream input1("Matrix.txt");
    Graph_matrix<int> graphMatrix(input1);
    std::cout << graphMatrix.Dijkstras_algorithm(start,finish) << std::endl;

    std::ifstream input2("List.txt");
    Graph_lists graphLists(input2);
    DynamicArray<int> comp = graphLists.Components();

    std::cout << "The number of connected components of the second graph : " << comp.GetSize() << std::endl;
    std::cout << "Cardinalities of different connectivity components : " << comp << std::endl;
    return 0;
}
