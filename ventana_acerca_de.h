///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_acerca_de.h
// Propósito:   Mostrar información sobre el programa.
// Autor:       Iván Pizarro.
//
// En este archivo se declara el diseño de la clase que que define a la ventana
// para mostrar el "acerca de" o "about" del programa.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_ACERCA_DE_H
#define VENTANA_ACERCA_DE_H

#include "Ventanas.h"

///////////////////////////////////////////////////////////////////////////////

class ventana_acerca_de : public vAbout {

protected:
	void click_cerrar( wxCommandEvent &_event );
	
public:
	ventana_acerca_de( wxWindow *_parent );
	~ventana_acerca_de();
	
};

#endif

