//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_agregar_libro.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en
// ventana_agregar_libro.h
//////////////////////////////////////////////////////////////////////////////

#include "ventana_agregar_libro.h"
#include "ventana_agregar_autor.h"

#include <wx/utils.h>
#include <wx/msgdlg.h>
#include <string>
using namespace std;

//////////////////////////////////////////////////////////////////////////////

ventana_agregar_libro::ventana_agregar_libro( wxWindow *_parent, const int &_pos ): vAgregarLibro( _parent ) {
	
	pos = _pos;
	anterior = Singleton::get_base_activa();
	se_agrego_autor = NULL;
	
	if ( pos >= 0 ) { // Si se abre en modo edición.
		
		this->SetTitle( "Editar libro..." );
		
		nuevo = anterior->libros.get_libro_pos( _pos );
		
		int cant_autores = nuevo.get_cant_autores();
		for ( int i=0;i<cant_autores;i++ ) { 
			
			cuadro_autores->Insert( anterior->autores.get_autor( nuevo.get_codigo_autor( i ) ).get_nombre().c_str(), i );
			
		}
		
		renglon_titulo->SetValue( nuevo.get_titulo().c_str() );
		renglon_resumen->SetValue( nuevo.get_resumen().c_str() );
		renglon_publicacion->SetValue( nuevo.get_publicacion().c_str() );
		renglon_url->SetValue( nuevo.get_url().c_str() );
		renglon_tags->SetValue( nuevo.get_tags().c_str() );
		renglon_ubicacion->SetValue( nuevo.get_ubicacion().str().c_str() );
		if ( renglon_ubicacion->GetValue() != "" ) {
			
			txt_ubicacion_no->Hide();
			txt_ubicacion_ok->Show();
			this->Layout();
			
		}
		
		if ( nuevo.get_tipo_prestamo() == 1 ) {
			
			cuadro_tipo_prestamo->SetSelection( 1 );
			
		}
		
	}
	
}

ventana_agregar_libro::~ventana_agregar_libro() {
	
	delete se_agrego_autor;
	
}

void ventana_agregar_libro::click_boton_agregar_autores ( wxCommandEvent &_event ) {
	
	ventana_autores   nueva_ventana( this, anterior, this );
	nueva_ventana.ShowModal();
	
}

void ventana_agregar_libro::click_boton_borrar_autores ( wxCommandEvent &_event ) {
	
	int tamanyo = cuadro_autores->GetCount();
	int control = 0;
	for( int i=0;i<tamanyo;i++ ) { 
		
		if( cuadro_autores->IsChecked( i ) ) {
			
			cuadro_autores->Delete( i );
			nuevo.eliminar_autor( i - control );
			++control;
			
		}
		
	}
	
}

void ventana_agregar_libro::click_boton_ir ( wxCommandEvent &_event ) {
	
	wxLaunchDefaultBrowser( renglon_url->GetValue() );
	
}

void ventana_agregar_libro::click_boton_cdu ( wxCommandEvent &_event ) {
	
	ventana_ingresar_cdu   nueva_ventana( this, this );
	if ( nueva_ventana.ShowModal() > 0 ) {
		
		txt_ubicacion_no->Hide();
		txt_ubicacion_ok->Show();
		this->Layout();
		
	}
	
}

void ventana_agregar_libro::click_boton_aceptar ( wxCommandEvent &_event ) {
	
	string titulo = renglon_titulo->GetValue().c_str();
	
	if ( titulo == "" ) {
		
		wxMessageBox( wxT("Debe ingresar el título de la obra."), wxT("Campo incompleto.") );
		
	} else if ( titulo[0] == ' ' ) {
		
		wxMessageBox( wxT("El título no puede comenzar con un espacio."), wxT("Campo mal completado.") );
		
	} else {
		
		if ( se_agrego_autor != NULL ) {
			
			anterior->autores = *se_agrego_autor;
			
		}
		
		if ( pos < 0 ) {
			
			this->guardar_datos_libro();
			nuevo.set_codigo();
			anterior->libros.push( nuevo );
			anterior->set_cambios( true );
			
		} else {
			
			libro *lib = &( anterior->libros.get_libro_pos( pos ) );
			this->guardar_datos_libro( lib );
			
		}
		
		
		EndModal( 1 );
		
	}
	
}

void ventana_agregar_libro::click_boton_cancelar ( wxCommandEvent &_event ) {
	
	EndModal( -1 );
	
}

void ventana_agregar_libro::guardar_datos_libro ( libro *_lib ) {
	
	libro *lib = _lib;
	
	if ( _lib == NULL ) {
		
		lib = &nuevo;
		
	}
	
	lib->set_titulo( renglon_titulo->GetValue().c_str() );
	lib->set_resumen( renglon_resumen->GetValue().c_str() );
	lib->set_publicacion( renglon_publicacion->GetValue().c_str() );
	lib->set_url( renglon_url->GetValue().c_str() );
	lib->set_tags( renglon_tags->GetValue().c_str() );
	lib->set_tipo_prestamo( cuadro_tipo_prestamo->GetSelection() );
	
}

