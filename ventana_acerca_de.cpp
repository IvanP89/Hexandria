//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_acerca_de.cpp
// Autor:       Iv�n Pizarro.
//
// Implementaciones de los m�todos y funciones declarados en
// ventana_acerca_de.h
//////////////////////////////////////////////////////////////////////////////

#include "ventana_acerca_de.h"

//////////////////////////////////////////////////////////////////////////////

ventana_acerca_de::ventana_acerca_de( wxWindow *_parent ): vAbout( _parent ) {
	
}

ventana_acerca_de::~ventana_acerca_de() {
	
}

void ventana_acerca_de::click_cerrar( wxCommandEvent &_event )  {
	
	this->Close();
	
}

