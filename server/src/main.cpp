#include<bits/stdc++.h> 
#include <algorithms.hpp>
#include <iostream>
#include <string>
#include <aixlog.hpp>

using namespace std;

int main()
{
    AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace);
    LOG(INFO) << "Mensaje inicial\n";
    algorithms *g1 = new algorithms();
    
    /*vector<vector<int>> population = g1->crearPoblacion();

      // Se muestra la poblacion inicial
    cout << "Poblacion Inicial:" << endl;
    g1->mostrarPoblacion(population);

    // Algunos de la poblacion 1 + otros creados(en caso que hayan muerto)
    population = { {2,3,3},
                   {3,3,3},
                   {3,2,3} 
    };
    
    //Se evoluciona la poblacion
    for (int i = 0; i<10; i++){ // generaciones
        population = g1->selection_and_reproduction(population, 3); // Valor_modelo
        population = g1->mutation(population, 3); // Valor_maximo
    }

    // Se muestra la poblacion final
    cout << "Poblacion Final:" << endl;
    g1->mostrarPoblacion(population);*/

    // ---- Ejecutar Bresenham (x_inicial, y_inicial, x_final, y_final)
    g1->algoritmo_bresenham(1,1,8,5);

    /*vector<vector<int>> mapa = {
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, 
		{ 1, 0, 1, 0, 1, 1, 1, 0, 1, 1 }, 
		{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 }, 
		{ 1, 0, 1, 0, 1, 0, 0, 0, 0, 1 }, 
		{ 1, 1, 1, 0, 0, 0, 0, 0, 1, 0 }, 
		{ 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 }, 
		{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 }, 
		{ 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, 
		{ 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } 
    };*/

    // ---- Ejecutar Backtracking (y_inicial, x_inicial, y_final, x_final)    
    /*if(g1->algoritmo_backtracking(1, 3, 7, 6, mapa)){
        g1->ruta_backtracking();
    }else{
        std::cout << "No hay solucion" << endl;
    }*/
    
    // ---- Ejecutar A Star
    /*typedef pair<int, int> Pair; 
	Pair src = make_pair(3, 0); // y_inicial, x_inicial
	Pair dest = make_pair(8, 2); // y_final, x_final
	g1->algoritmo_aStar(src, dest, mapa);*/


    return 0;
}