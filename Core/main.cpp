#include<iostream>
#include "programa.h"
#include "utilidades.h"
using namespace std;

int main (int argc, char *argv[]) {
	fecha f1( 1989,4,15);
	fecha f2 = fecha::get_actual();
	cerr<<"Anyo cumpleanyos: "<<f1.get_anyo_str()<<endl;
	cerr<<"Anyo actual: "<<f2.get_anyo_str()<<endl;
	cerr<<"Mes cumpleanyos: "<<f1.get_mes_str()<<endl;
	cerr<<"Mes actual: "<<f2.get_mes_str()<<endl;
	cerr<<"Dia cumpleanyos: "<<f1.get_dia_str()<<endl;
	cerr<<"Dia actual: "<<f2.get_dia_str()<<endl;
	cerr<<endl<<"Restando cumpleaños a fecha actual..."<<endl<<endl;
	fecha f3 = f2 - f1;
	cerr<<"Anyo actual: "<<f3.get_anyo_str()<<endl;
	cerr<<"Mes actual: "<<f3.get_mes_str()<<endl;
	cerr<<"Dia actual: "<<f3.get_dia_str()<<endl;
	return 0;
}

