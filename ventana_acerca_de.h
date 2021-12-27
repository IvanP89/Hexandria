///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_acerca_de.h
// Prop�sito:   Mostrar informaci�n sobre el programa.
// Autor:       Iv�n Pizarro.
//
// En este archivo se declara el dise�o de la clase que que define a la ventana
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

