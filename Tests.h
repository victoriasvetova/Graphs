#include "Graph_lists.h"
#include "Graph_matrix.h"
#include <fstream>

void TestAll(){

    std::ifstream input1("1.txt");//файл хранит ориентированный взвешенный граф из двух вершин
    Graph_matrix<int> graphMatrix1(input1);

    if(graphMatrix1.Dijkstras_algorithm(1,0).Get(0) != 0){//проверка вычисления недостижимости одной вершины из другой
        std::cerr << "Dijkstras algorithm ERROR !";
        std::exit(0);
    }

    std::ifstream input2("2.txt");//файл содержит обычный ориентированный взвешенный граф
    Graph_matrix<int> graphMatrix2(input2);
    DynamicArray<int> path1 = graphMatrix2.Dijkstras_algorithm(0,3);

    if(path1.Get(0) != 0 && path1.Get(1) != 2 && path1.Get(2) != 3){
        std::cerr << "Dijkstras algorithm ERROR !";
        std::exit(0);
    }

    std::ifstream input3("3.txt");//файл содержит несвязный граф из трех вершин
    Graph_lists graphLists1(input3);

    std::ifstream input4("4.txt");//файл содержит полный граф из четырех вершин
    Graph_lists graphLists2(input4);

    DynamicArray<int> test1 = graphLists1.Components();
    if(test1.GetSize() != 3){
        std::cerr << "DFS ERROR !";
        std::exit(0);
    }

    DynamicArray<int> test2 = graphLists2.Components();
    if(test2.GetSize() != 1){
        std::cerr << "DFS ERROR !";
        std::exit(0);
    }
    std::cerr << "ALL TESTS IS OK !\n";
}