///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_autores.h
// Propósito:   Visualizar la base de datos de autores del programa.
// Autor:       Iván Pizarro.
//
// En este archivo se declara el diseño de la clase que que define a la ventana
// que trabaja exclusivamente con la base de datos de los autores.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_AUTORES_H
#define VENTANA_AUTORES_H

#include "Ventanas.h"
#include "ventana_agregar_libro.h"
#include "ventana_ayuda.h"

#include "Core\bibliografia.h"
#include "Core\programa.h"

#include <vector>

using namespace std;

class ventana_agregar_libro;

///////////////////////////////////////////////////////////////////////////////

class ventana_autores : public vAutores {
	
protected:
	void refresh();
	void click_boton_borrar( wxCommandEvent &_event ) ;
	void click_boton_agregar( wxCommandEvent &_event ) ;
	void click_buscar( wxCommandEvent &_event ) ;
	void click_boton_restaurar( wxCommandEvent &_event ) ;
	void click_boton_ayuda( wxCommandEvent &_event ) ;
	void cambio_filtro_iniciales( wxCommandEvent &_event ) ;
	void Dclick_autor( wxCommandEvent &_event ) ;
	void click_boton_aceptar( wxCommandEvent &_event ) ;
	void click_boton_cancelar( wxCommandEvent &_event ) ;
	
protected:
	autores_database autores;
	int pos;
	vector<int> pos_real;
	Programa *programa_s;
	ventana_agregar_libro *anterior;
	Programa *programa_p;
	bool cambios;
	ventana_ayuda *Ayuda;
	
public:
	ventana_autores( wxWindow *_parent,
	                 Programa *_programa = NULL,
	                 ventana_agregar_libro *_anterior = NULL );
	~ventana_autores();
	
};

#endif

