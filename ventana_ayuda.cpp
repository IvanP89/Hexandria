//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_ayuda.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en ventana_ayuda.h
//////////////////////////////////////////////////////////////////////////////

#include "ventana_ayuda.h"

#include <windows.h>

//////////////////////////////////////////////////////////////////////////////

ventana_ayuda::ventana_ayuda( wxWindow *_parent ): vAyuda( _parent ) {
	
}

ventana_ayuda::~ventana_ayuda() {
	
}


void ventana_ayuda::click_boton_cerrar ( wxCommandEvent &_event ) {
	
	this->Close();
	
}

void ventana_ayuda::abrir_manual_usuario ( wxHyperlinkEvent &_event ) {
	
	ShellExecute( NULL, "open", "Manual del Usuario.pdf", NULL, NULL, SW_NORMAL );
	
}

void ventana_ayuda::abrir_manual_referencia ( wxHyperlinkEvent &_event ) {
	
	ShellExecute( NULL, "open", "Manual de Referencia.pdf", NULL, NULL, SW_NORMAL );
	
}

