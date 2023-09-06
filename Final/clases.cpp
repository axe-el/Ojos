#include "clases.h"

void Unir::juntar(Skeleto &skull){

    for(unsigned int i=0;i<	skull.matrix.size() ;i++){
        for(unsigned int j=0; j<skull.matrix[i].size();j++){
            if(skull.matrix[i][j]!=0 && matrix[i][j]!=3 && matrix[i][j]!=2 ){
				matrix[i][j]=4;
			}

		}
	}	
}

double algebrita::distancia(Punto p, Punto a, Punto b){
	vector <double> ap(2,0);
	vector <double> ab(2,0);
	
	double X1=p.x-a.x;
	double Y1=p.y-a.y;
	double X2=b.x-a.x;
	double Y2=b.y-a.y;
	
	double norma=sqrt((X2*X2) +(Y2*Y2) );
			
	ap[0]=X1;
	ap[1]=Y1;
	ab[0]=X2;
	ab[1]=Y2;

	ab[0]= ab[0]/norma; 
	ab[1]=ab[1]/norma;

	double pro_punto= ( ap[0]*ab[0] ) + ( ap[1]*ab[1]);
		
	ab[0]=ab[0]*pro_punto;		
	ab[1]=ab[1]*pro_punto;
	
	double nx=a.x+ab[0];
	double ny= a.y+ab[1];
	
	return sqrt ( ((p.x-nx)*(p.x-nx)) + ((p.y-ny)*(p.y-ny))  );
	
}

double algebrita::Area(Punto p, Punto a, Punto b){
	vector <double> ap(2,0);
	vector <double> ab(2,0);
	
	double X1=p.x-a.x;
	double Y1=p.y-a.y;
	double X2=b.x-a.x;
	double Y2=b.y-a.y;
	
	double norma=sqrt((X2*X2) +(Y2*Y2) );
			
	ap[0]=X1;
	ap[1]=Y1;
	ab[0]=X2;
	ab[1]=Y2;

	ab[0]= ab[0]/norma; 
	ab[1]=ab[1]/norma;

	double pro_punto= ( ap[0]*ab[0] ) + ( ap[1]*ab[1]);
		
	ab[0]=ab[0]*pro_punto;		
	ab[1]=ab[1]*pro_punto;
	
	double nx=a.x+ab[0];
	double ny= a.y+ab[1];
	
	double altura = sqrt ( ((p.x-nx)*(p.x-nx)) + ((p.y-ny)*(p.y-ny))  );
	double base= sqrt( ((b.x-a.x)*(b.x-a.x)) + ((b.y-a.y)*(b.y-a.y))   );
	return (base*altura)/2;	
}

double Unir::Hausdorf(segmentos &seg ){


	
	double d_inf,d_max,d_total;	
	double d,d1,d2;
	double X,Y;		
    for(unsigned int i=0;i<Nuevo_puntitos.size();i++){
	
        for(unsigned int j=0; j<Nuevo_puntitos[i].size();j++){
            for(unsigned int k=0; k< seg.puntitos[i].size(); k++){
				X=(Nuevo_puntitos[i][j].x-seg.puntitos[i][k].x);
				Y=(Nuevo_puntitos[i][j].y-seg.puntitos[i][k].y);
				d= sqrt ( (X*X) + (Y*Y)  );
				if(k==0){
					d_inf=d;
				}
				else{
					if(d<d_inf){
						d_inf=d;
					}
				}
			}	
			if (j==0){
				d_max=d_inf;	
			}
			else{
				if(d_inf>d_max){
					d_max=d_inf;
				}				
			}
		}
		d1=d_max;
		
		
        for(unsigned int j=0; j<seg.puntitos[i].size()	;j++){
            for(unsigned int k=0; k< Nuevo_puntitos[i].size(); k++){
				X=(Nuevo_puntitos[i][k].x-seg.puntitos[i][j].x);
				Y=(Nuevo_puntitos[i][k].y-seg.puntitos[i][j].y);
				d= sqrt ( (X*X) + (Y*Y)  );
				if(k==0){
					d_inf=d;
				}
				else{
					if(d<d_inf){
						d_inf=d;
					}
				}
			}	
			if (j==0){
				d_max=d_inf;	
			}
			else{
				if(d_inf>d_max){
					d_max=d_inf;
				}				
			}
		}		
		d2=d_max;
		
		if(d1>d2){
			d_total=d_total+d1;
		}
		else{
			d_total=d_total+d2;		
		}
	}
	return d_total - Nuevo_puntitos.size();
}

void Unir::WriteMatrix(string nombre){
	//Escribir nueva imagen .PGM
	ofstream file;	
	int m =matrix.size();
	int n =matrix[0].size();
	int I=0,J=0;
	
	//Escribir encabezados		
	file.open(nombre);
	file << "P2\n";
	file << n <<" "<<m<<"\n" ;
	file << "255\n";
	
	//Escribir datos
	for(int i = 0; i < m*n; i++) {
		if(matrix[I][J]==0 ){
			file << "0\n";
		}		
		else if (matrix[I][J]==1 || matrix[I][J]==-2 || matrix[I][J]==-1 ){
			file <<"255\n" ;	
		}
		
		else if (matrix[I][J]==2 ){
			file <<"140\n" ;	
		}
		else if (matrix[I][J]==3){
			file <<"70\n" ;	
		}
		else if (matrix[I][J]==4){
			file <<"210\n" ;	
		}								
		J=J+1;
		if(J==n){
			J=0;
			I=I+1;
		}	
	}	
	file.close();

}


	
void Unir::entrelazar( vector < vector<int> > &figuras,vector <Punto> &nuevos_p,int x1,int y1, int x2,int y2){
    QString equis,ye,equis2,ye2,A,B,C;

    equis.sprintf("%d",x1);
    ye.sprintf("%d",y1);
    equis2.sprintf("%d",x2);
    ye2.sprintf("%d",y2);
    splines=splines+ "-----Recta de ("+equis+","+ye+") -> ("+equis2 +","+ye2+")\n";
	//Si pixeles estan en la misma fila
	if(y1==y2){
        splines = splines + ye + "= x\n";
		if(x1<x2){
			for (int i=x1;i<x2;i++){
				figuras[i][y1]=-1;
				
				Punto actual(i,y1);
				nuevos_p.push_back(actual);
			}
		}
		else if(x2<x1){
			for (int i=x2;i<x1;i++){
				figuras[i][y1]=-1;
				
				Punto actual(i,y1);
				nuevos_p.push_back(actual);
			}
		}		
	}
	//Si pixeles estan en la misma columna	
    else if(x1==x2){
        splines = splines + equis + "= y\n";

		if(y1<y2){
			for (int i=y1;i<y2;i++){
				figuras[x1][i]=-1;

				Punto actual(x1,i);
				nuevos_p.push_back(actual);
			}
		}
		else if(y2<y1){
			for (int i=y2;i<y1;i++){
				figuras[x1][i]=-1;

				Punto actual(x1,i);
				nuevos_p.push_back(actual);
			}
		}		
	}
	// SI no estan en la misma fila ni columna
	else if(x1!=x2 && y1!=y2 ){
		//Si deferencia entre cordenadas x's mayor a la de y's
		if(abs(x2-x1)>abs(y2-y1)){

            A.sprintf("%d",-(y2-y1));
            B.sprintf("%d",x2-x1);
            C.sprintf("%d",(y2-y1)*x1 - (x2-x1)*y1);
            splines = splines + A+" x +"+B+"y +"+C +"\n";
			int yint;
			double yi;
			if(x1<x2){
				for (int i=x1;i<x2;i++){
					yi=(double)(y1-y2);
					yi=(yi/(x1-x2))*(i-x1);
					yi=yi+y1;
					yi=round(yi);
					yint=(int)yi;
					figuras[i][yint]=-1;
					
					Punto actual(i,yint);
					nuevos_p.push_back(actual);
				}


			}
			else if(x2<x1){
				for (int i=x2;i<x1;i++){
					yi=(double)(y1-y2);
					yi=(yi/(x1-x2))*(i-x1);
					yi=yi+y1;
					yi=round(yi);
					yint=(int)yi;
					figuras[i][yint]=-1;

					Punto actual(i,yint);
					nuevos_p.push_back(actual);
				}
			}	
		}
		//Si deferencia entre cordenadas y's mayor a la de x's		
		else if(abs(x2-x1)<=abs(y2-y1)){
            A.sprintf("%d",-(y2-y1));
            B.sprintf("%d",x2-x1);
            C.sprintf("%d",(y2-y1)*x1 - (x2-x1)*y1);
            splines = splines + A+" x +"+B+"y +"+C +"\n";
			int yint;
			double yi;
			if(y1<y2){

				for (int i=y1;i<y2;i++){
					yi=(double)(x1-x2);
					yi=(yi/(y1-y2))*(i-y1);
					yi=yi+x1;
					yi=round(yi);
					yint=(int)yi;
					figuras[yint][i]=-1;
					
					Punto actual(yint,i);
					nuevos_p.push_back(actual);
				}


			}
			else if(y2<y1){
				for (int i=y2;i<y1;i++){
					yi=(double)(x1-x2);
					yi=(yi/(y1-y2))*(i-y1);
					yi=yi+x1;
					yi=round(yi);
					yint=(int)yi;
					figuras[yint][i]=-1;

					Punto actual(yint,i);
					nuevos_p.push_back(actual);
				}
			}		
		
		
		}
	}	
	
}



void Unir::lineal(){


    for (unsigned int i = 0; i < puntitos.size() ; i++){
		vector <Punto> nuevos_p;	
		
        for (unsigned int j = 0; j < puntitos[i].size() -1 ; j++){
		
            entrelazar(matrix,nuevos_p, puntitos[i][j].x, puntitos[i][j].y, puntitos[i][j+1].x, puntitos[i][j+1].y );
		
			matrix[puntitos[i][j].x][puntitos[i][j].y]=2;
			matrix[puntitos[i][j+1].x][puntitos[i][j+1].y]=2;
		}
		
		Nuevo_puntitos.push_back(nuevos_p);		
		matrix[puntitos[i][0].x][puntitos[i][0].y]=3;
		matrix[puntitos[i][puntitos[i].size()-1].x][puntitos[i][puntitos[i].size()-1].y]=3;		
	}

}


Unir::Unir(Douglas &inicio){
	alto=inicio.alto;
	ancho=inicio.ancho;
	puntitos=inicio.Nuevo_puntitos;
	matrix.assign(alto,vector<int>(ancho,0));		
}

Unir::Unir(Visvalingam &inicio){
	alto=inicio.alto;
	ancho=inicio.ancho;
	puntitos=inicio.Nuevo_puntitos;
	matrix.assign(alto,vector<int>(ancho,0));		
}


///////////////////////////////////--------Visvalingam---//////////////////////////////////////////////////





void Visvalingam::curva(){
    for (unsigned int i = 0; i < puntitos.size() ; i++){
		curva2(puntitos[i]);	
	}	
}

void Visvalingam::curva2(vector <Punto> vectorp){		
	int i=1;
	while (i !=-1){
		i=Buscar(vectorp);

		if(i!=-1){
			vectorp.erase( vectorp.begin()+i );
		}

	}	
	Nuevo_puntitos.push_back(vectorp);				
}

int Visvalingam::Buscar(vector <Punto> vectorp){
	double Area_m=2*epsilon;
	double a;	
	int index=-1;
	int total=vectorp.size();
	for (int i = 1; i < total-1 ; i++){	
		Punto anterior(vectorp[i-1].x,vectorp[i-1].y);
		Punto actual(vectorp[i].x,vectorp[i].y);
		Punto siguiente(vectorp[i+1].x,vectorp[i+1].y);
		a=Area(actual,anterior,siguiente);			
		if(a < Area_m ){
			Area_m=a;	
			index=i;
		}	
	}

	if(Area_m < epsilon){
		return index;
	}
		
	else{
		return -1;
	}
}




Visvalingam::Visvalingam(segmentos &seg, double e){
	ancho=seg.ancho;	
	alto=seg.alto;
	matrix.assign(alto,vector<int>(ancho,0));	
	puntitos=seg.puntitos;	
	epsilon=e;
}


///////////////////////////////////--------Douglas---//////////////////////////////////////////////////





int Douglas::Buscar(vector <Punto> vectorp, int a, int b){
	double Dist_m=-1;
	double d;	
	int index=-1;

	Punto inicio(vectorp[a].x,vectorp[a].y);
	Punto fin(vectorp[b].x,vectorp[b].y);
	
	for (int i = a+1; i < b ; i++){		
		Punto actual(vectorp[i].x,vectorp[i].y);
		d=distancia(actual,inicio,fin);
		
		if(d > Dist_m){
			Dist_m=d;	
			index=i;
		}	
	}

    if(Dist_m >= epsilon){
		return index;
	}
		
	else{
		return -1;
	}
}

void Douglas::curva2(vector <Punto> vectorp ){
	int total=vectorp.size();
	vector <Punto> nuevos_p;
	Punto inicio(vectorp[0].x,vectorp[0].y);
	Punto fin(vectorp[total-1].x,vectorp[total-1].y);
	nuevos_p.push_back(inicio);
	RDP(0,total-1,vectorp,nuevos_p);	
	nuevos_p.push_back(fin);
	Nuevo_puntitos.push_back(nuevos_p);		
}

void Douglas::curva(){
    for (unsigned int i = 0; i < puntitos.size() ; i++){
		curva2(puntitos[i]);	
	}	
}

Douglas::Douglas(segmentos &seg, double e){
	ancho=seg.ancho;	
	alto=seg.alto;
	matrix.assign(alto,vector<int>(ancho,0));	
	puntitos=seg.puntitos;	
	epsilon=e;
}

void Douglas::RDP(int i_start,int i_end,vector <Punto> vectorp ,vector <Punto> &nuevos_p){

	int i_nuevo;			
	i_nuevo=Buscar( vectorp ,i_start,i_end);

	if (i_nuevo > 0){
	
		if(i_start!=i_nuevo){
			RDP(i_start,i_nuevo,vectorp,nuevos_p);
		}
		
		nuevos_p.push_back(vectorp[i_nuevo]);
				
		if(i_end!=i_nuevo){		
			RDP(i_nuevo,i_end,vectorp,nuevos_p);		
		}	
		
	}

}	



///////////////////////////////////--------segmentos---//////////////////////////////////////////////////


void segmentos::recorrido2(vector < vector<int> > &matrix,vector<Punto> &pixeles,int i, int j){
	matrix[i][j]=-2;
	Punto a(i,j);
	pixeles.push_back(a);
	
	//P6
	if( i+1<=matrix.size()-1 && matrix[i+1][j]==1){
		i=i+1;
		matrix[i][j]=-2;				
		Punto a(i,j);
		pixeles.push_back(a);			
	}	
	
	//P8
	else if( j-1>=0 && matrix[i][j-1]==1){
		j=j-1;
		matrix[i][j]=-2;				
		Punto a(i,j);
		pixeles.push_back(a);			
	}
	//P4
	else if(  j+1<=matrix[0].size()-1 && matrix[i][j+1]==1){
		j=j+1;
		matrix[i][j]=-2;				
		Punto a(i,j);
		pixeles.push_back(a);			
	}				
	//P2
	else if( i-1>=0 && matrix[i-1][j]==1){
		i=i-1;
		matrix[i][j]=-2;		
		Punto a(i,j);
		pixeles.push_back(a);						
	}
	
	
	
	
	int fin=1;
	while(fin!=0){
		//P6
		if( i+1<=matrix.size()-1 && matrix[i+1][j]!=0 && matrix[i+1][j]!=-2){
			i=i+1;
			if(matrix[i][j]==2){
				fin=0;
			}
			else if(matrix[i][j]==1){
				matrix[i][j]=-2;
			}			
			Punto a(i,j);
			pixeles.push_back(a);			
		}	
		
		//P8
		else if( j-1>=0 && matrix[i][j-1]!=0 && matrix[i][j-1]!=-2){
			j=j-1;
			if(matrix[i][j]==2){
				fin=0;
			}
			else if(matrix[i][j]==1){
				matrix[i][j]=-2;
			}			
			Punto a(i,j);
			pixeles.push_back(a);			
		}	
		//P4
		else if(  j+1<=matrix[0].size()-1 && matrix[i][j+1]!=0 && matrix[i][j+1]!=-2){
			j=j+1;
			if(matrix[i][j]==2){
				fin=0;
			}
			else if(matrix[i][j]==1){
				matrix[i][j]=-2;
			}			
			Punto a(i,j);
			pixeles.push_back(a);			
		}	
		//P2
		else if( i-1>=0 && matrix[i-1][j]!=0 && matrix[i-1][j]!=-2){
			i=i-1;
			if(matrix[i][j]==2){
				fin=0;
			}
			else if(matrix[i][j]==1){
				matrix[i][j]=-2;
			}
			Punto a(i,j);
			pixeles.push_back(a);	
								
		}
		
	
			
	
	}

}


void segmentos::recorrido(vector < vector<int> > &matrix,vector<Punto> &pixeles,int i, int j){
	matrix[i][j]=-2;
	Punto a(i,j);
	pixeles.push_back(a);		
	//P2
	if( i-1>=0 && matrix[i-1][j]==1){
		i=i-1;
		matrix[i][j]=-2;		
		Punto a(i,j);
		pixeles.push_back(a);						
	}
	
	//P4
	else if(  j+1<=matrix[0].size()-1 && matrix[i][j+1]==1){
		j=j+1;
		matrix[i][j]=-2;				
		Punto a(i,j);
		pixeles.push_back(a);			
	}	
	
	//P6
	else if( i+1<=matrix.size()-1 && matrix[i+1][j]==1){
		i=i+1;
		matrix[i][j]=-2;				
		Punto a(i,j);
		pixeles.push_back(a);			
	}	
	
	//P8
	else if( j-1>=0 && matrix[i][j-1]==1){
		j=j-1;
		matrix[i][j]=-2;				
		Punto a(i,j);
		pixeles.push_back(a);			
	}	
	int fin=1;
	while(fin!=0){
		//P2
		if( i-1>=0 && matrix[i-1][j]!=0 && matrix[i-1][j]!=-2){
			i=i-1;
			if(matrix[i][j]==2){
				fin=0;
			}
			else if(matrix[i][j]==1){
				matrix[i][j]=-2;
			}
			Punto a(i,j);
			pixeles.push_back(a);	
								
		}
		
		//P4
		else if(  j+1<=matrix[0].size()-1 && matrix[i][j+1]!=0 && matrix[i][j+1]!=-2){
			j=j+1;
			if(matrix[i][j]==2){
				fin=0;
			}
			else if(matrix[i][j]==1){
				matrix[i][j]=-2;
			}			
			Punto a(i,j);
			pixeles.push_back(a);			
		}	
		
		//P6
		else if( i+1<=matrix.size()-1 && matrix[i+1][j]!=0 && matrix[i+1][j]!=-2){
			i=i+1;
			if(matrix[i][j]==2){
				fin=0;
			}
			else if(matrix[i][j]==1){
				matrix[i][j]=-2;
			}			
			Punto a(i,j);
			pixeles.push_back(a);			
		}	
		
		//P8
		else if( j-1>=0 && matrix[i][j-1]!=0 && matrix[i][j-1]!=-2){
			j=j-1;
			if(matrix[i][j]==2){
				fin=0;
			}
			else if(matrix[i][j]==1){
				matrix[i][j]=-2;
			}			
			Punto a(i,j);
			pixeles.push_back(a);			
		}			
	
	}

}

segmentos::segmentos(Skeleto &skull){
	ancho=skull.ancho;
	alto=skull.alto;
	vector<Punto> pixeles;
	for(int i = 0; i < skull.alto; i++) {
		for(int j = 0; j < skull.ancho; j++) {
			if(skull.matrix[i][j]==2){
				Punto inicio(i,j);
				if(i-1>=0 && skull.matrix[i-1][j]==1 ){
					pixeles.push_back(inicio);
					recorrido(skull.matrix,pixeles,i-1,j);
					puntitos.push_back(pixeles);
					pixeles.clear();				
				}
				if( j+1<=skull.matrix[0].size()-1 && skull.matrix[i][j+1]==1){
					pixeles.push_back(inicio);				
					recorrido(skull.matrix,pixeles,i,j+1);

					puntitos.push_back(pixeles);
					pixeles.clear();																	
				}
				if( i+1<=skull.matrix.size()-1 && skull.matrix[i+1][j]==1){
					pixeles.push_back(inicio);				
					recorrido2(skull.matrix,pixeles,i+1,j);

					puntitos.push_back(pixeles);
					pixeles.clear();
																											
				}
				if( j-1>=0 && skull.matrix[i][j-1]==1){
					pixeles.push_back(inicio);				
					recorrido2(skull.matrix,pixeles,i,j-1);

					puntitos.push_back(pixeles);
					pixeles.clear();
																											
				}
			}	
		}
	}	
}

///////////////////////////////////--------Skeleto---//////////////////////////////////////////////////

void Skeleto::Bifurcaciones( ){
	for(int i = 0; i < alto; i++) {
		for(int j = 0; j < ancho; j++) {
			if(matrix[i][j]==1){
				Punto a(i,j);	
				if(a.vecinos(matrix)==1){
					matrix[i][j]=2;				
				}
				else if(a.vecinos(matrix)>2){
					matrix[i][j]=2;
				}
			}
		}
	}		
}
void Skeleto::WriteMatrix(string nombre){
	//Escribir nueva imagen .PGM
	ofstream file;	
	int m =matrix.size();
	int n =matrix[0].size();
	int I=0,J=0;
	
	//Escribir encabezados		
	file.open(nombre);
	file << "P2\n";
	file << n <<" "<<m<<"\n" ;
	file << "255\n";
	
	//Escribir datos
	for(int i = 0; i < m*n; i++) {
		if(matrix[I][J]==0 ){
			file << "0\n";
		}		
		else if (matrix[I][J]==1 || matrix[I][J]==-2 || matrix[I][J]==-1){
			file <<"255\n" ;	
		}
		
		else if (matrix[I][J]==2 ){
			file <<"150\n" ;	
		}
						
		J=J+1;
		if(J==n){
			J=0;
			I=I+1;
		}	
	}	
	file.close();

}

void Skeleto::skeletizacion(){
	int borrar=0;
	int borre=1;
	while(borre!=0){
		borre=0;
		for(int i = 1; i < alto-1; i++) {
			for(int j = 1; j < ancho-1; j++) {	
				if(matrix[i][j]==1){
					Punto a(i,j);
					if(a.B_p(matrix) >=2 && a.B_p(matrix)<=6){
						borrar=borrar+1;
					}
					if(a.A_p(matrix)==1){
						borrar=borrar+1;
					}
					if( (a.valor(matrix,i-1,j) * a.valor(matrix,i,j+1)* a.valor(matrix,i+1,j))==0 ){
						borrar=borrar+1;
					}
					if( (  a.valor(matrix,i,j+1) * a.valor(matrix,i+1,j) * a.valor(matrix,i,j-1))==0 ){
						borrar=borrar+1;
					}	
					if(borrar==4){

						borre=borre+1;
						matrix[i][j]=0;
						borrar=0;
					}	
					borrar=0;								
				}

			}
		}
		if(borre!=0){
			borre=0;
			for(int i = 1; i < alto-1; i++) {
				for(int j = 1; j < ancho-1; j++) {	
					if(matrix[i][j]==1){
						Punto a(i,j);
						if(a.B_p(matrix) >=2 && a.B_p(matrix)<=6){
							borrar=borrar+1;
						}
						if(a.A_p(matrix)==1){
							borrar=borrar+1;
						}
						if( (a.valor(matrix,i-1,j) * a.valor(matrix,i,j+1)* a.valor(matrix,i,j-1))==0 ){
							borrar=borrar+1;
						}
						if( (  a.valor(matrix,i-1,j) * a.valor(matrix,i+1,j) * a.valor(matrix,i,j-1))==0 ){
							borrar=borrar+1;
						}	
						if(borrar==4){

							borre=borre+1;
							matrix[i][j]=0;
							borrar=0;
						}
						borrar=0;									
					}
				}
			}	
		}					
	}	
}

Skeleto::Skeleto(Imagen &img){
	ancho=img.ancho;	
	alto=img.alto;
	max=img.max;	
	matrix=img.matrix;		
}

///////////////////////////////////--------Punto---//////////////////////////////////////////////////

int Punto::vecinos(vector < vector<int> > &matrix){
	int contador=0;
	//P2
	if( x-1>=0 ){
		contador=contador+valor(matrix,x-1,y);
	}
	
	//P4
	if(  y+1<=matrix[0].size()-1 ){
		contador=contador+valor(matrix,x,y+1);
	}	
	
	//P6
	if( x+1<=matrix.size()-1){
		contador=contador+valor(matrix,x+1,y);
	}	
	
	//P8
	if( y-1>=0 ){
		contador=contador+valor(matrix,x,y-1);
	}
	
						
	return contador;

}

int Punto::A_p(vector < vector<int> > &matrix){
	int contador=0;
	vector<int> vecinos(8,0);
	//P2
	if( x-1>=0 ){
		vecinos[0]=valor(matrix,x-1,y);
	}
	//P3
	if( x-1>=0 && y+1<=matrix[0].size()-1 ){
		vecinos[1]=valor(matrix,x-1,y+1);	
	}	
	//P4
	if(  y+1<=matrix[0].size()-1 ){
		vecinos[2]=valor(matrix,x,y+1);
	}	
	//P5
	if( x+1<=matrix.size()-1 && y+1<=matrix[0].size()-1 ){
		vecinos[3]=valor(matrix,x+1,y+1);
	}	
	//P6
	if( x+1<=matrix.size()-1){
		vecinos[4]=valor(matrix,x+1,y);
	}	
	//P7
	if( x+1<=matrix.size()-1 && y-1>=0 ){
		vecinos[5]=valor(matrix,x+1,y-1);
	}	
	//P8
	if( y-1>=0 ){
		vecinos[6]=valor(matrix,x,y-1);
	}	
	//P9
	if( x-1>=0 && y-1>=0 ){
		vecinos[7]=valor(matrix,x-1,y-1);					
	}
	for(int i = 0; i < 8-1; i++) {	
		if(vecinos[i]==0 && vecinos[i+1]==1){
			contador=contador+1;
		}
	}	
	if(vecinos[7]==0 && vecinos[0]==1){
		contador=contador+1;
	}								
	return contador;		
}

int Punto::B_p(vector < vector<int> > &matrix){
	int contador=0;
	//P2
	if( x-1>=0 ){
		contador=contador+valor(matrix,x-1,y);
	}
	//P3
	if( x-1>=0 && y+1<=matrix[0].size()-1 ){
		contador=contador+valor(matrix,x-1,y+1);	
	}	
	//P4
	if(  y+1<=matrix[0].size()-1 ){
		contador=contador+valor(matrix,x,y+1);
	}	
	//P5
	if( x+1<=matrix.size()-1 && y+1<=matrix[0].size()-1 ){
		contador=contador+valor(matrix,x+1,y+1);
	}	
	//P6
	if( x+1<=matrix.size()-1){
		contador=contador+valor(matrix,x+1,y);
	}	
	//P7
	if( x+1<=matrix.size()-1 && y-1>=0 ){
		contador=contador+valor(matrix,x+1,y-1);
	}	
	//P8
	if( y-1>=0 ){
		contador=contador+valor(matrix,x,y-1);
	}
	//P9
	if( x-1>=0 && y-1>=0 ){
		contador=contador+valor(matrix,x-1,y-1);					
	}	
						
	return contador;		
}

int Punto::valor(vector < vector<int> > &matrix){
	if(matrix[x][y]!=0){
		return 1;
	}
	else
		return 0;
		
}

int Punto::valor(vector < vector<int> > &matrix,int X, int Y){
	if(matrix[X][Y]!=0){
		return 1;
	}
	else 
		return 0;	
}

Punto::Punto(int X, int Y){
	x=X;
	y=Y;
}

///////////////////////////////////--------Imagen---//////////////////////////////////////////////////

Imagen::Imagen(string nombre){
	//Accdere archivo 
    ifstream myfile(nombre.c_str());
	//Si el archivo existe
	if(myfile.is_open()){	
		//Leer primera fila
		string line, word;
		getline (myfile, line);
		if(line.compare("P2")!=0){
			cout << "Error archivo incorrecto\n";
		}
		//Leer segunda fila
		getline (myfile, line);
		stringstream s(line);
		getline (s, word, ' ');		
		//Saltar comentario si existe		
		if(word=="#"){
			getline (myfile, line);						
		}
		//Leer ancho y alto
		stringstream ss(line);
		getline (ss, word, ' ');		
		ancho=stoi(word);
		getline (ss, word, ' ');
		alto=stoi(word);
		//Leer valor maximo
		getline (myfile, line);
		max=stoi(line);
		//Modificar tamaño matriz		
		matrix.assign(alto,vector<int>(ancho,0));
		int I=0,J=0;			
		//Leer las otras filas del archivo (Datos)
		for(int i = 0; i < alto*ancho; i++) {
			getline (myfile, line);
			stringstream ss(line);
			getline (ss, word,' ');
			if(stoi(word)!=0){
				matrix[I][J]=1;
			}
			else
				matrix[I][J]=0;	
			J=J+1;
			if(J==ancho){
				J=0;
				I=I+1;
			}	
		}
		//Cerrar archivo
		myfile.close();
		
	}
	
	//Si el archivo no existe		
	else{
		cout << "Error archivo dado no existe\n";
	}	
}	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////


