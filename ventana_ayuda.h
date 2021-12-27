///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_ayuda.h
// Propósito:   Mostrar la ayuda - Manual de referencia.
// Autor:       Iván Pizarro.
//
// En este archivo se declara el diseño de la clase que que define a la ventana
// para mostrar el manual de referencia como la ayuda del programa.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_AYUDA_H
#define VENTANA_AYUDA_H

#include "Ventanas.h"

///////////////////////////////////////////////////////////////////////////////

class ventana_ayuda : public vAyuda {

protected:
	void abrir_manual_referencia( wxHyperlinkEvent &_event ) ;
	void abrir_manual_usuario( wxHyperlinkEvent &_event ) ;
	void click_boton_cerrar( wxCommandEvent &_event );
	
public:
	ventana_ayuda( wxWindow *_parent = NULL );
	~ventana_ayuda();
	
};

#endif

