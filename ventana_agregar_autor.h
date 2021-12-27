///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_agregar_autor.h
// Propósito:   Agregar un nuevo autor a la base de datos del programa.
// Autor:       Iván Pizarro.
//
// En este archivo se declara el diseño de la clase que que define a la ventana
// que provee una interfaz para agregar un nuevo autor a la base del programa.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_AGREGAR_AUTOR_H
#define VENTANA_AGREGAR_AUTOR_H

#include "Ventanas.h"

#include "Core\bibliografia.h"

#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////

class ventana_agregar_autor : public vAgregarAutor {

protected:
	void click_boton_ir( wxCommandEvent &_event ) ;
	void click_boton_aceptar( wxCommandEvent &_event ) ;
	void click_boton_cancelar( wxCommandEvent &_event ) ;
	
protected:
	autores_database *autores;
	int pos;
	string nombre_inicial;
	string resumen_inicial;
	string url_inicial;
	
public:
	ventana_agregar_autor( wxWindow *_parent,
	                       autores_database *_autores,
						   const int &_pos = -1 );
	~ventana_agregar_autor();
	
};

#endif

