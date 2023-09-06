#ifndef CLASES_H
#define CLASES_H

#include <bits/stdc++.h>
#include <time.h>

#include<QMainWindow>
#include<QObject>
#include<QSharedDataPointer>
#include<QWidget>


using namespace std;



class Imagen{ 
	private:  
		int ancho;
		int alto;
		int max;
		vector < vector<int> > matrix;
	public:  		
		Imagen(string nombre);

	friend class Skeleto;	
};

class Skeleto{ 
	private:  
		int ancho;
		int alto;	 	
		int max;
		vector < vector<int> > matrix;		
		
	public: 
		Skeleto(Imagen &img);
		void skeletizacion();
		void WriteMatrix(string nombre);		
		void Bifurcaciones();


	friend class segmentos;				
	friend class Unir;
};

class Punto{ 
	private:  
		int x;
		int y;	
	public:  
		
		Punto(int X, int Y);
        int valor(vector < vector<int> > &matrix);
        int valor(vector < vector<int> > &matrix,int X, int Y);
        int B_p(vector < vector<int> > &matrix);
        int A_p(vector < vector<int> > &matrix);
        int vecinos(vector < vector<int> > &matrix);
		
	friend class segmentos;	
	friend class Douglas;				
	friend class Visvalingam;	
	friend class Unir;				
	friend class algebrita;					
};
	
class segmentos{ 
	private:  
		int ancho;
		int alto;
        vector < vector<Punto> > puntitos;
	public:		
		segmentos(Skeleto &skull);
        void recorrido(vector < vector<int> > &matrix, vector<Punto> &pixeles,int i, int j);
        void recorrido2(vector < vector<int> > &matrix, vector<Punto> &pixeles,int i, int j);
	friend class Douglas;
	friend class Visvalingam;
	friend class Unir;					
};

class algebrita{
	protected:
		double Area(Punto p, Punto a, Punto b);
		double distancia(Punto a, Punto b, Punto c);				
};

class Douglas:public algebrita{ 
	private:  
		int ancho;
		int alto;	
		double epsilon;
        vector < vector<Punto> > puntitos;
        vector < vector<Punto> > Nuevo_puntitos;
		vector < vector<int> > matrix;				
	public:		
		Douglas(segmentos &seg, double e);
		void curva();
		void curva2(vector <Punto> vectorp );	
		int Buscar(vector <Punto> vectorp, int a, int b);

		void RDP(int i_start,int i_end,vector <Punto> vectorp,vector <Punto> &nuevos_p);
	friend class Unir;							
};

class Visvalingam: public algebrita{ 
	private:  
		int ancho;
		int alto;	
		double epsilon;
        vector < vector<Punto> > puntitos;
        vector < vector<Punto> > Nuevo_puntitos;
		vector < vector<int> > matrix;
						
	public:		
		Visvalingam(segmentos &seg, double e);
		void curva();		
		void curva2(vector <Punto> vectorp);					
		int Buscar(vector <Punto> vectorp);			

	friend class Unir;											
};



class Unir{ 
	private:  
		int ancho;
		int alto;	
		double epsilon;
        vector < vector<Punto> > puntitos;
        vector < vector<Punto> > Nuevo_puntitos;
		vector < vector<int> > matrix;
						
    public:
        QString splines;
		Unir(Visvalingam &inicio);
		Unir(Douglas &inicio);
		void lineal();	
		void WriteMatrix(string nombre);
        void entrelazar( vector < vector<int> > &figuras,vector <Punto> &nuevos_p,int x1,int y1, int x2,int y2);
		double Hausdorf(segmentos &seg );
		void juntar(Skeleto &skull);
    friend class MainWindow;
};

#endif 
