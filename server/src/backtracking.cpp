#include <stdio.h>
#include <algorithms.hpp>
#include <vector>
#include<bits/stdc++.h> 
 
void algorithms::generar(int row1, int col1, vector<vector<int>> solution) const{
    for(unsigned int i=0; i<row1; i++){
        vector<int> v1; 
        for(unsigned int j=0; j<col1; j++){
            v1.push_back(0);
        }
        solution.push_back(v1); 
    }
}

//function to print the solution matrix
void algorithms::ruta_backtracking(vector< pair <int,int> > solution1) const{
    AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace);  
    int a = int(solution1.size());
    for(int i=0;i<a;i++)
    {    
        LOG(INFO) << solution1[i].first;
        LOG(INFO) << " ";
        LOG(INFO) << solution1[i].second;
        LOG(INFO) << "\n";
    }
}

//function to solve the maze
//using backtracking
int algorithms::algoritmo_backtracking(int r, int c, int x_end, int y_end, vector<vector<int>> mapa, vector<vector<int>> solution, vector< pair <int,int> > solution1, bool entrar) const{

    if (entrar!=false){  
        generar(mapa.size(), mapa[0].size(), solution);
        entrar = false;
    }
    //if destination is reached, maze is solved
    //destination is the last cell(maze[SIZE-1][SIZE-1])
    if((r==y_end) && (c==x_end))
    {
        solution[r][c] = 1;
        solution1.push_back(make_pair(r,c));
        return 1;
    }
    //checking if we can visit in this cell or not
    //the indices of the cell must be in (0,SIZE-1)
    //and solution[r][c] == 0 is making sure that the cell is not already visited
    //maze[r][c] == 0 is making sure that the cell is not blocked
    if(r>=0 && c>=0 && r<mapa.size() && c<mapa[0].size() && solution[r][c] == 0 && mapa[r][c] == 0)
    {
        //if safe to visit then visit the cell
        solution[r][c] = 1;
        solution1.push_back(make_pair(r,c));
        //going down
        if(algoritmo_backtracking(r+1, c, x_end, y_end, mapa, solution, solution1, entrar))
            return 1;
        //going right
        if(algoritmo_backtracking(r, c+1, x_end, y_end, mapa, solution, solution1, entrar))
            return 1;
        //going up
        if(algoritmo_backtracking(r-1, c, x_end, y_end, mapa, solution, solution1, entrar))
            return 1;
        //going left
        if(algoritmo_backtracking(r, c-1, x_end, y_end, mapa, solution, solution1, entrar))
            return 1;
        //backtracking
        solution[r][c] = 0;
        return 0;
    }
    return 0;

}