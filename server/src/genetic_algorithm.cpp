#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <algorithms.hpp>

using namespace std;

const int largo = 3;
const int num = 3;
const int pressure = 2;
const double mutation_chance = 0.2;
const int valor_inicial = 3; 

// Mostrar la poblacion
void algorithms::mostrarPoblacion(vector<vector<int>> population) const{
    for (unsigned int i = 0; i < population.size(); i++) { 
        for (unsigned int j = 0; j < population[i].size(); j++) 
            cout << population[i][j] << " "; 
        cout << endl;
    }
}

// Crea la poblacion.
vector<vector<int>> algorithms::crearPoblacion() const{
    std::random_device dev;
    std::mt19937 rng(dev());
    vector<vector<int>> Poblacion;
    for(int i=0;i<num;i++){
        vector<int> individuo;
        for(int j=0;j<largo;j++){
            std::uniform_int_distribution<std::mt19937::result_type> dist1(1,3);
            individuo.push_back(int(dist1(rng))); // Valores del 1 al 3
        }        
        Poblacion.push_back(individuo);
    }
    return Poblacion;
}

// Funcion Fitness
vector<vector<int>> algorithms::fitness(vector<vector<int>> population, int valor_modelo) const{
    std::random_device dev;
    std::mt19937 rng(dev());
    vector<vector<int>> puntuados;
    for (unsigned int i = 0; i < population.size(); i++) { 
        vector<int> individuo;
        int contador = 0;
        for (unsigned int j = 0; j < population[i].size(); j++){
            individuo.push_back(population[i][j]);
        }
        // Fitness -> Contar la cantidad de numeros repetidos valor_modelo que hay
        for (unsigned int i = 0; i < individuo.size(); i++){
            if(individuo[i]==valor_modelo){
                contador += 1;
            }
        }
        // Agrega un valor al inicio con la cantidad de numero iguales
        individuo.insert(individuo.begin(), contador);
        puntuados.push_back(individuo);
    }
    population = puntuados;
    return population;
}

// Funcion seleccion y reproduccion
vector<vector<int>> algorithms::selection_and_reproduction(vector<vector<int>> population, int valor_modelo) const{
    std::random_device dev;
    std::mt19937 rng(dev());
    // Calcula el fitness
    population = fitness(population, valor_modelo);

    // Ordena el vector
    sort(population.begin(), population.end());

    // Eliminar el primer valor de cada vector
    vector<vector<int>> puntuados;
    for (unsigned int i = 0; i < population.size(); i++) { 
        vector<int> individuo;
        for (unsigned int j = 1; j < population[i].size(); j++){
            individuo.push_back(population[i][j]);
        }
        puntuados.push_back(individuo);
    }

    population = puntuados;

    // Esto selecciona los 'n' individuos del final, donde n viene dado por 'pressure'
    unsigned int individuos_quitar = int(population.size() - pressure);
    vector<vector<int>> selected;
    for (unsigned int i = 0; i < population.size(); i++) {
        vector<int> individuo2;
        if (i >= individuos_quitar){
            for (unsigned int j = 0; j < population[i].size(); j++){
                individuo2.push_back(population[i][j]);
            }
            selected.push_back(individuo2);
        }   
    }

    // Se mezcla el material genetico para crear nuevos individuos
    for (unsigned int ii = 0; ii < population.size()-pressure; ii++){
        std::uniform_int_distribution<std::mt19937::result_type> dist1(0,(largo-1)); 
        unsigned int punto = int(dist1(rng)); //Se elige un punto para hacer el intercambio

        // Se eligen dos padres
        int size_selected = selected.size();
        std::uniform_int_distribution<std::mt19937::result_type> dist2(0,(size_selected-1));
        unsigned int padre1 = int(dist2(rng));
        std::uniform_int_distribution<std::mt19937::result_type> dist3(0,(size_selected-1));
        unsigned int padre2 = int(dist3(rng));
        if (padre1==padre2){
            while (padre1==padre2){
                std::uniform_int_distribution<std::mt19937::result_type> dist4(0,(size_selected-1));
                padre2 = int(dist4(rng));
            }
        }
        vector<vector<int>> padre;
        for (unsigned int i = 0; i < selected.size(); i++) {
            vector<int> individuo3;
            if (i==padre1 || i==padre2){
                for (unsigned int j = 0; j < selected[i].size(); j++){
                        individuo3.push_back(selected[i][j]);
                }
                padre.push_back(individuo3);
            }
        }
        
        //Se mezcla el material genetico del padre 1 en cada nuevo individuo
        for (unsigned int j = 0; j <= punto; j++){
            population[ii][j] = padre[0][j];
        }
            
        //Se mezcla el material genetico del padre 1 en cada nuevo individuo
        unsigned indice_mayor = int(population[0].size() - 1);
        for (unsigned int j=indice_mayor; j>=((indice_mayor - punto)); j--) {
            population[ii][j] = padre[1][j];
            if (j==0){
                break;
            }
        }
    }

    return population;
}

// Funcion mutacion
vector<vector<int>> algorithms::mutation(vector<vector<int>> population, int max_valor) const{  
    std::random_device dev;
    std::mt19937 rng(dev());
    for (unsigned int ii = 0; ii < population.size()-pressure; ii++){
        //Cada individuo de la poblacion (menos los padres) tienen una probabilidad de mutar
            std::uniform_int_distribution<std::mt19937::result_type> dist1(1,9999);
            double aleatorio = double(dist1(rng)) / double(10000);
            if (aleatorio <= mutation_chance){
                
                //  Se elige un punto al azar
                std::uniform_int_distribution<std::mt19937::result_type> dist2(0,(largo-1)); 
                unsigned int punto = int(dist2(rng));

                // y un nuevo valor para este punto
                std::uniform_int_distribution<std::mt19937::result_type> dist3(1,max_valor);
                int nuevo_valor = int(dist3(rng));
                
    
                //Es importante mirar que el nuevo valor no sea igual al viejo
                while (nuevo_valor == population[ii][punto]){
                    std::uniform_int_distribution<std::mt19937::result_type> dist4(1,max_valor);
                    nuevo_valor = int(dist4(rng));
                }
                    
                //Se aplica la mutacion
                population[ii][punto] = nuevo_valor;
            }
    }

    return population;
}