/*BRESENHAAM ALGORITHM FOR LINE DRAWING*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<vector>
#include <algorithms.hpp>
#include <iostream>
#include <string>

using namespace std;

void algorithms::ruta_bresenham(vector<vector<int>> ruta) const{
	AixLog::Log::init<AixLog::SinkCout>(AixLog::Severity::trace);
	for(auto rows: ruta){
		for(auto elem: rows){
			LOG(INFO) << (elem);
			LOG(INFO) << (" ");
		}
		LOG(INFO) << ("\n");
	}
}

void algorithms::algoritmo_bresenham(int x1, int y1, int x2, int y2) const{
	vector<vector<int>> ruta;
	vector<int> coordenada;
	
	int x;
	int y;
	int dx;
	int dy;
	int dx1;
	int dy1;
	int px;
	int py;
	int xe;
	dx=x2-x1;
	dy=y2-y1;
	dx1= abs(dx);
	dy1= abs(dy);
	px=2*dy1-dx1;
	py=2*dx1-dy1;

	if(dy1<=dx1) {
		if(dx>=0) {
			x=x1;
			y=y1;
			xe=x2;
		}

		else {
			x=x2;
			y=y2;
			xe=x1;
		}

		coordenada.push_back(x);
		coordenada.push_back(y);
		ruta.push_back(coordenada);
		
		while(x<xe) {
			x=x+1;

			if(px<0) {
				px=px+2*dy1;
			}
			else if((dx<0 && dy<0) || (dx>0 && dy>0)) {
				y=y+1;
				px=px+2*(dy1-dx1);
			}else {
				y=y-1;
				px=px+2*(dy1-dx1);	
			}
			vector<int> coordenada1;
			coordenada1.push_back(x);
			coordenada1.push_back(y);
			ruta.push_back(coordenada1);
		}
		ruta_bresenham(ruta);
	}

	else {
		a(x1, y1, x2, y2,ruta);
	}
}

void algorithms::a(int x1, int y1, int x2, int y2, vector<vector<int>> ruta) const{
	vector<int> coordenada2;
	vector<int> coordenada3;
	int x;
	int y;
	int dx;
	int dy;
	int dx1;
	int dy1;
	int px;
	int py;
	int ye;
	dx=x2-x1;
	dy=y2-y1;
	dx1= abs(dx);
	dy1= abs(dy);
	px=2*dy1-dx1;
	py=2*dx1-dy1;

			if(dy>=0) {
			x=x1;
			y=y1;
			ye=y2;
		}

		else {
			x=x2;
			y=y2;
			ye=y1;
		}

		coordenada2.push_back(x);
		coordenada2.push_back(y);
		ruta.push_back(coordenada2);

		while(y<ye) {
			y=y+1;

			if(py<=0) {
				py=py+2*dx1;
			}
			else if((dx<0 && dy<0) || (dx>0 && dy>0)) {
				x=x+1;
				py=py+2*(dx1-dy1);
			}

			else {
				x=x-1;
				py=py+2*(dx1-dy1);	
			}

			coordenada3.push_back(x);
			coordenada3.push_back(y);
			ruta.push_back(coordenada3);
		}
	
	ruta_bresenham(ruta);	
}