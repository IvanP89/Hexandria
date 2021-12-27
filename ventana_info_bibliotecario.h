///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_info_bibliotecario.h
// Propósito:   Ver información detallada sobre un socio.
// Autor:       Iván Pizarro.
//
// En este archivo se declara el diseño de la clase que que define a la ventana
// mediante la cual se puede observar en detalle la información sobre un
// bibliotecario determinado.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_INFO_BIBLIOTECARIO_H
#define VENTANA_INFO_BIBLIOTECARIO_H

#include "Ventanas.h"

#include "Core\programa.h"

#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////

class ventana_info_bibliotecario : public vInfoBibliotecario {

protected:
	void click_boton_cerrar( wxCommandEvent &_event );
	// CARGA DE IMAGEN
	void cargar_imagen( const string &_path );
	
public:
	ventana_info_bibliotecario( wxWindow *_parent,
	                            const int &_pos );
	~ventana_info_bibliotecario();
};

#endif

