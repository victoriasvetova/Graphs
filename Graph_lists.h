#pragma once
#include "DynamicArray.h"
#include "Pair.h"
#include <fstream>

class Graph_lists{
public:
    int count_of_vert;

    DynamicArray<Pair<int,DynamicArray<int>>> lists;
    Graph_lists(std::ifstream& input){
        //вершины нумеруются с 0
        input >> count_of_vert;//количество вершин,о которых содержится информания в файле
        lists.Resize(count_of_vert);
        int index = 0;
        for (int i = 0; i < count_of_vert; ++i) {
            int tmp_v;//номер вершины для которой в данной строке указана окрестность
            int size_of_vicinity;//размер окрестности данной вершины
            input >> tmp_v >> size_of_vicinity;

            DynamicArray<int> tmp_vicinity;
            for (int j = 0; j < size_of_vicinity; ++j) {
                int tmp_vicinity_vertice;
                input >> tmp_vicinity_vertice;
                tmp_vicinity.Append(tmp_vicinity_vertice);
            }
            lists[index] = {tmp_v,tmp_vicinity};
            index++;
        }

    }
    void print(){
        for (int i = 0; i < count_of_vert; ++i) {
            std::cout << lists.Get(i) << std::endl;
        }
    }
    DynamicArray<int> Get(int value_num){//в случае нахождения в графе вершины и её окрестности возвращает список окрестности вершины value_num

        for (int i = 0; i < lists.GetSize(); ++i) {
            if(lists.Get(i).first == value_num)
                return lists.Get(i).second;
        }
        return DynamicArray<int>();

    }

    void DFS(int start,DynamicArray<bool>& visited){

        visited[start] = true;

        for (int i = 0; i < lists.Get(start).second.GetSize(); ++i) {
            if(!visited[lists.Get(start).second.Get(i)])
                DFS(lists.Get(start).second.Get(i),visited);
        }

    }

    int Components(){
        int n_comp = 0;
        DynamicArray<bool> visited(count_of_vert, false);
        for (int i = 0; i < count_of_vert; ++i) {

            if(!visited[i]){
                n_comp++;
                DFS(i,visited);
            }
        }
        return n_comp;
    }

};
