///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_agregar_curriculum.h
// Prop�sito:   Interfaz para cargar o editar el curr�culum de un bibliotecario.
// Autor:       Iv�n Pizarro.
//
// En este archivo se declara el dise�o de la clase que que define a la ventana
// que provee una interfaz para agregar o editar el curr�culum de un
// bibliotecario.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_AGREGAR_CURRICULUM_H
#define VENTANA_AGREGAR_CURRICULUM_H

#include "Ventanas.h"
#include "ventana_agregar_bibliotecario.h"

using namespace std;

class ventana_agregar_bibliotecario;

///////////////////////////////////////////////////////////////////////////////

class ventana_agregar_curriculum : public vAgregarCurriculum {

protected:
	void click_boton_explorar( wxCommandEvent &_event ) ;
	void click_boton_aceptar( wxCommandEvent &_event ) ;
	void click_boton_cancelar( wxCommandEvent &_event ) ;
	
protected:
	ventana_agregar_bibliotecario *anterior;
	
public:
	ventana_agregar_curriculum( ventana_agregar_bibliotecario *_parent );
	~ventana_agregar_curriculum();
	
};

#endif

