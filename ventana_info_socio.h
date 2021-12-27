///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_info_socio.h
// Propósito:   Ver información detallada sobre un bibliotecario.
// Autor:       Iván Pizarro.
//
// En este archivo se declara el diseño de la clase que que define a la ventana
// mediante la cual se puede observar en detalle la información sobre un socio
// determinado.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_INFO_SOCIO_H
#define VENTANA_INFO_SOCIO_H

#include "Ventanas.h"

#include "Core\programa.h"
#include "Core\personas.h"

#include <vector>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////

class ventana_info_socio : public vInfoSocio {

protected:
	void click_boton_historial( wxCommandEvent &_event ) ;
	void Dclick_pendiente( wxCommandEvent &_event );
	void click_boton_cerrar( wxCommandEvent &_event );
	void cargar_imagen( const string &_path );
	
protected:
	Programa *programa;
	int pos;
	vector<int> cod_pendientes;
	bool carga_desde_historial;
	
public:
	ventana_info_socio( wxWindow *_parent, const int &_pos );
	ventana_info_socio( wxWindow *_parent, const socio &_soc );
	~ventana_info_socio();
	
};

#endif

