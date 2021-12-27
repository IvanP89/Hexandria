//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_info_libro.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en
// ventana_info_libro.h
//////////////////////////////////////////////////////////////////////////////

#include "ventana_info_libro.h"
#include "ventana_historial.h"

#include "Core\programa.h"

#include <wx/utils.h>

#include <cstdlib>

using namespace std;

//////////////////////////////////////////////////////////////////////////////

ventana_info_libro::ventana_info_libro( wxWindow *_parent, const unsigned int &_pos, bool parent_es_infosocio ): vInfoLibro( _parent ) {
	
	carga_desde_historial = false;
	
	const libro *lib;
	Programa *programa = Singleton::get_base_activa();
	
	if ( parent_es_infosocio == false ) {
		
		lib = &( programa->libros.get_libro_pos( _pos ) );
		
	} else {
		
		lib = &( programa->libros.get_libro( _pos ) );
		
	}
	
	renglon_titulo->SetValue( lib->get_titulo().c_str() );
	renglon_autores->SetValue( lib->get_nombre_autores().c_str() );
	renglon_publicacion->SetValue( lib->get_publicacion().c_str() );
	if ( lib->get_tipo_prestamo() == 0 ) {
		
		renglon_prestamo->SetValue( wxT("A domicilio") );
		
	} else {
		
		renglon_prestamo->SetValue( wxT("Consulta") );
		
	}
	if ( lib->get_prestado() == true ) {
		
		renglon_estado->SetValue( wxT("Prestado") );
		
	} else {
		
		renglon_estado->SetValue( wxT("Disponible") );
		
	}
	renglon_solicitar->SetValue( lib->get_ubicacion().str().c_str() );
	renglon_fecha->SetValue( lib->get_fecha_agregado().str_ddmmaaaa().c_str() );
	renglon_codigo->SetValue( lib->get_codigo_str().c_str() );
	renglon_contenido->SetValue( lib->get_tags().c_str() );
	renglon_resumen->SetValue( lib->get_resumen().c_str() );
	renglon_url->SetValue( lib->get_url().c_str() );
	
}

ventana_info_libro::ventana_info_libro ( wxWindow *_parent, const libro &_lib ): vInfoLibro( _parent ) {
	
	carga_desde_historial = true;
	
	renglon_titulo->SetValue( _lib.get_titulo().c_str() );
	renglon_autores->SetValue( _lib.get_nombre_autores().c_str() );
	renglon_publicacion->SetValue( _lib.get_publicacion().c_str() );
	if ( _lib.get_tipo_prestamo() == 0 ) {
		
		renglon_prestamo->SetValue( wxT("A domicilio") );
		
	} else {
		
		renglon_prestamo->SetValue( wxT("Consulta") );
		
	}
	if ( _lib.get_prestado() == true ) {
		
		renglon_estado->SetValue( wxT("Prestado") );
		
	} else {
		
		renglon_estado->SetValue( wxT("Disponible") );
		
	}
	renglon_solicitar->SetValue( _lib.get_ubicacion().str().c_str() );
	renglon_fecha->SetValue( _lib.get_fecha_agregado().str_ddmmaaaa().c_str() );
	renglon_codigo->SetValue( _lib.get_codigo_str().c_str() );
	renglon_contenido->SetValue( _lib.get_tags().c_str() );
	renglon_resumen->SetValue( _lib.get_resumen().c_str() );
	renglon_url->SetValue( _lib.get_url().c_str() );
	
}

ventana_info_libro::~ventana_info_libro() {
	
}

void ventana_info_libro::click_boton_ir( wxCommandEvent &_event )  {
	
	wxLaunchDefaultBrowser( renglon_url->GetValue() );
	
}

void ventana_info_libro::click_boton_cerrar( wxCommandEvent &_event )  {
	
	EndModal( -1 );
	
}

void ventana_info_libro::click_boton_historial( wxCommandEvent &_event )  {
	
	ventana_historial nueva_ventana( this, atoi( renglon_codigo->GetValue().c_str() ), false );
	nueva_ventana.ShowModal();
	
}

