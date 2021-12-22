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

    int DFS(int start,DynamicArray<int>& visited){
        int res = 1;
        visited[start] = 1;

        for (int i = 0; i < lists.Get(start).second.GetSize(); ++i) {
            if(!visited[lists.Get(start).second.Get(i)])
                res +=DFS(lists.Get(start).second.Get(i),visited);
        }
        return res;
    }

    DynamicArray<int> Components(){
        int n_comp = 0;
        int res;
        DynamicArray<int> result;
        DynamicArray<int> visited(count_of_vert, 0);
        int num_of_comp = 1;
        for (int i = 0; i < count_of_vert; ++i) {
            DynamicArray<int> tmp_vis;
            for (int j = 0; j < count_of_vert; ++j) {
                tmp_vis.Append(visited[j]);
            }
            if(!visited[i]){
                n_comp++;
                result.Append(DFS(i,visited));
            }
            for (int j = 0; j < count_of_vert; ++j) {
                tmp_vis[j] = (tmp_vis[j] + visited[j]) % 2;
            }

            bool flag = true;
            int count = 0;//проверка на то,что мы нашли новую компоненту связности
            for (int j = 0; j < count_of_vert; ++j) {
                if(tmp_vis[j] == 0)
                    ++count;
            }
            if(count == count_of_vert)
                flag = false;
            if(flag){
                std::cout << "numbers of vertices belonging to one connected component numbered " << num_of_comp << " : ";
                for (int j = 0; j < count_of_vert; ++j) {
                    if(tmp_vis[j] != 0)
                        std::cout << j << " ";
                }
                std::cout << std::endl;
                ++num_of_comp;
            }
        }
        return result;
    }

};
