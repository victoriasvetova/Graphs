#pragma once
#include "DynamicArray.h"
#include "Pair.h"
#include <fstream>

template<typename T>
class Graph_matrix{
public:
    T INF;
    int n;//количество вершин
    DynamicArray<DynamicArray<T>> matrix;//матрица смежности графа

    Graph_matrix(std::ifstream& input){
        input >> INF;
        input >> n;//количество вершин,о которых содержится информания в файле
        matrix.Resize(n);
        for (int i = 0; i < n; ++i) {
            matrix.Get(i).Resize(n);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matrix.Get(i).Get(j) = INF;
                if(j == i)
                    matrix.Get(i).Get(j) = T();//начальная инициализация матрицы смежности очень большими значениями
                //это сделано для того,чтобы показать,что между вершинами,не представленными в файле,нет рёбер,
                //а значит можно сказать,что между ними бесконечное расстояние
            }
        }
        //вершины нумеруются с нуля
        int count_of_vert;//количество ребер,заданных в файле
        input >> count_of_vert;
        for (int k = 0; k < count_of_vert; ++k) {
            int i;
            int j;
            T tmp;
            input >> i >> j >> tmp;
            matrix[i][j] = tmp;
        }
    }


    void print(){
        for (int i = 0; i < n; ++i) {
            std::cout << matrix.Get(i) <<std::endl;
        }
    }
    T Get(int i,int j){
        return matrix.Get(i).Get(j);
    }

    DynamicArray<int> Dijkstras_algorithm(int start,int finish){
        DynamicArray<T> dist(n,INF);
        dist[start] = 0;

        DynamicArray<bool> used(n, false);
        DynamicArray<int> prev(n,-1);

        int min_distance = 0;//значение наименьшего расстояния до непокрашенной вершины(изначально 0 тк до непокрашенной вершины start расстояние 0)
        int u = start;//номер вершины,которая сейчас обрабатывается(как раз та вершина,до которой расстояние равно min_distance)

        while (min_distance < INF){
            used[u] = true;
            for (int v = 0; v < n; ++v) {
                if(dist[u] + matrix[u][v] < dist[v]){
                    dist[v] = dist[u] + matrix[u][v];
                    prev[v] = u;
                }
            }
            min_distance = INF;
            for (int v = 0; v < n; ++v) {
                if(!used[v] && dist[v] < min_distance){
                    min_distance = dist[v];
                    u = v;
                }
            }
        }

        DynamicArray<int> result_path;
        int curr = finish;
        while (curr != -1){
            result_path.Append(curr);
            curr = prev[curr];
        }
        result_path.reverse();

        return result_path;
    }
};



/*   Pair<long long ,DynamicArray<int>> Prim(){//почему то не работает
        DynamicArray<int> ans_vertexes;

        long long ans = 0;
        DynamicArray<int> dist(n);
        for (int i = 0; i < n; ++i) {
            dist[i] = INF;
        }
        dist[0] = 0;
        DynamicArray<bool> used(n);
        for (int i = 0; i < n; ++i) {
            used[i] = false;
        }

        for (int i = 0; i < n; ++i) {
            int min_dist = INF;
            int min_vertex;
            for (int u = 0; u < n; ++u) {
                if(!used[u] && dist[u] < min_dist){
                    min_dist = dist[u];
                    min_vertex = u;
                }
            }
            ans_vertexes.Append(min_vertex);
            ans += min_dist;
            used[min_dist] = true;
            for (int next = 0; next < n; ++next) {
                if(matrix.Get(min_vertex).Get(next) < dist[next])
                    dist[next] = matrix.Get(min_vertex).Get(next);
            }
        }
        std::cout << ans << ' ' << ans_vertexes << "\n";
        return {ans,ans_vertexes};
    }
*/