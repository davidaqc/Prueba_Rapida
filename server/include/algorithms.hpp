#include <iostream>
#include <vector>
#include <algorithm>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

using namespace std;

class algorithms{
    public:

        // Metodos algoritmo genetico
        void mostrarPoblacion(vector<vector<int>> population);
        vector<vector<int>> crearPoblacion();
        vector<vector<int>> fitness(vector<vector<int>> population, int valor_modelo);
        vector<vector<int>> selection_and_reproduction(vector<vector<int>> population, int valor_modelo);
        vector<vector<int>> mutation(vector<vector<int>> population, int max_valor);

        // Metodos algoritmo Bresenham
        void algoritmo_bresenham(int x_begin, int y_begin, int x_end1, int y_end1) const;
        void ruta_bresenham(vector<vector<int>> mapa) const;
        void a(int x1, int y1, int x2, int y2, vector<vector<int>> mapa) const;

        // Metodos algoritmo Backtracking
        int algoritmo_backtracking(int r, int c, int x_end, int y_end, vector<vector<int>> mapa);
        void ruta_backtracking();
        void generar(int row, int col);

        // Metodos algortimo A Star
        typedef pair<int, int> Pair;
        void algoritmo_aStar(Pair src, Pair dest, vector<vector<int>> mapa);
        void generar1(int row, int col);
};