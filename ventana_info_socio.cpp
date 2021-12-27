//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_info_socio.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en
// ventana_info_socio.h
//////////////////////////////////////////////////////////////////////////////

#include "ventana_info_socio.h"
#include "ventana_info_libro.h"
#include "ventana_socios.h"
#include "ventana_historial.h"

#include "Core\personas.h"
#include "Core\bibliografia.h"
#include "Core\utilidades.h"

#include <wx/bitmap.h>

#include <cctype>
#include <cstdlib>

using namespace std;

//////////////////////////////////////////////////////////////////////////////

ventana_info_socio::ventana_info_socio( wxWindow *_parent, const int &_pos ): vInfoSocio( _parent ) {
	
	carga_desde_historial = false;
	pos = _pos;
	programa = Singleton::get_base_activa();
	
	const socio* const soc = &( programa->socios.get_socio_pos( _pos ) );
	
	renglon_nombre->SetValue( soc->get_nombre_completo().c_str() );
	renglon_dni->SetValue( soc->get_dni_str().c_str() );
	renglon_nro_socio->SetValue( soc->get_nro_socio_str().c_str() );
	renglon_tel->SetValue( soc->get_tel().c_str() );
	renglon_domicilio->SetValue( soc->get_domicilio().c_str() );
	renglon_edad->SetValue( soc->get_edad_str().c_str() );
	renglon_ingreso->SetValue( soc->get_fecha_ingreso().str_ddmmaaaa().c_str() );
	
	const libro *lib;
	const int cant_pendientes = soc->get_cant_a_devolver();
	for ( int i=0;i<cant_pendientes;i++ ) { 
		
		cod_pendientes.push_back( soc->get_a_devolver( i ) );
		lib = &( programa->libros.get_libro( cod_pendientes[i] ) );
		cuadro_pendientes->Insert( lib->get_titulo().c_str(), i );
		
	}
	
	this->cargar_imagen( soc->get_path_foto() );
	
}

ventana_info_socio::ventana_info_socio ( wxWindow *_parent, const socio &_soc ): vInfoSocio( _parent ) {
	
	renglon_nombre->SetValue( _soc.get_nombre_completo().c_str() );
	renglon_dni->SetValue( _soc.get_dni_str().c_str() );
	renglon_nro_socio->SetValue( _soc.get_nro_socio_str().c_str() );
	renglon_tel->SetValue( _soc.get_tel().c_str() );
	renglon_domicilio->SetValue( _soc.get_domicilio().c_str() );
	renglon_edad->SetValue( _soc.get_edad_str().c_str() );
	renglon_ingreso->SetValue( _soc.get_fecha_ingreso().str_ddmmaaaa().c_str() );
	
	const libro *lib;
	const int cant_pendientes = _soc.get_cant_a_devolver();
	programa = Singleton::get_base_activa();
	
	for ( int i=0;i<cant_pendientes;i++ ) { 
		
		cod_pendientes.push_back( _soc.get_a_devolver( i ) );
		lib = &( programa->libros.get_libro( cod_pendientes[i] ) );
		cuadro_pendientes->Insert( lib->get_titulo().c_str(), i );
		
	}
	
	this->cargar_imagen( _soc.get_path_foto() );
	
}

ventana_info_socio::~ventana_info_socio() {
	
}

void ventana_info_socio::Dclick_pendiente( wxCommandEvent &_event )  {
	
	int pos_ = cuadro_pendientes->GetSelection();
	ventana_info_libro   nueva_ventana( this, pos_, true );
	nueva_ventana.ShowModal();
	
}

void ventana_info_socio::click_boton_cerrar( wxCommandEvent &_event )  {
	
	EndModal( -1 );
	
}

void ventana_info_socio::cargar_imagen ( const string &_path ) {
	
	string extension = _path.substr( _path.find_last_of( '.' ) );
	char a = extension[1]; // 'a' contiene ahora la primera letra de la extension (extension[0] es el punto).
	a = tolower(a);
	wxBitmap *imagen;
	switch ( a ) {
	case 'j':
		imagen = new wxBitmap( _path.c_str(), wxBITMAP_TYPE_JPEG );
		break;
		
	case 'p':
		imagen = new wxBitmap( _path.c_str(), wxBITMAP_TYPE_PNG );
		break;
		
	case 'b':
		imagen = new wxBitmap( _path.c_str(), wxBITMAP_TYPE_BMP );
		
	}
	
	*imagen = EditarImagen::ajustar_tamanyo( *imagen );
	foto_socio->SetBitmap( *imagen );
	
}

void ventana_info_socio::click_boton_historial( wxCommandEvent &_event )  {
	
	ventana_historial nueva_ventana( this, atoi( renglon_nro_socio->GetValue().c_str() ), true );
	nueva_ventana.ShowModal();
	
}

