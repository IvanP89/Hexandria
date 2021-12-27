//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_agregar_autor.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en
// ventana_agregar_autor.h
//////////////////////////////////////////////////////////////////////////////

#include "ventana_agregar_autor.h"

#include <wx/utils.h>
#include <wx/msgdlg.h>

//////////////////////////////////////////////////////////////////////////////

ventana_agregar_autor::ventana_agregar_autor( wxWindow *_parent, autores_database *_autores, const int &_pos ): vAgregarAutor( _parent ) {
	
	autores = _autores;
	pos = _pos;
	
	if ( pos >= 0 ) { // Se abre en modo edición.
		
		const autor *const autor_ = &( autores->get_autor_pos( pos ) );
		
		nombre_inicial = autor_->get_nombre().c_str();
		renglon_nombre->SetValue( nombre_inicial.c_str() );
		
		resumen_inicial = autor_->get_resumen().c_str();
		renglon_resumen->SetValue( resumen_inicial.c_str() );
		
		url_inicial = autor_->get_url().c_str();
		renglon_url->SetValue( url_inicial.c_str() );
		
		this->SetTitle( wxT("Editar autor...") );
		
	}
	
}

ventana_agregar_autor::~ventana_agregar_autor() {
	
}

void ventana_agregar_autor::click_boton_ir( wxCommandEvent &_event )  {
	
	wxLaunchDefaultBrowser( renglon_url->GetValue() );
	
}

void ventana_agregar_autor::click_boton_cancelar( wxCommandEvent &_event )  {
	
	EndModal( -1 );
	
}

void ventana_agregar_autor::click_boton_aceptar( wxCommandEvent &_event )  {
	
	if ( pos < 0 ) { // Modo agregar.
		
		string nombre = renglon_nombre->GetValue().c_str();
		
		if ( nombre == "" ) {
			
			wxMessageBox( wxT("Debe ingresar un nombre para el autor."), wxT("Campo incompleto.") );
			
		} else if ( nombre[0] == ' ' ) {
			
			wxMessageBox( wxT("El nombre no puede comenzar con un espacio."), wxT("Campo mal completado.") );
			
		} else {
			
			autor nuevo( nombre, renglon_resumen->GetValue().c_str(), renglon_url->GetValue().c_str() );
			nuevo.set_codigo();
			autores->push( nuevo );
			
			EndModal( 1 );
			
		}
		
	} else { // Modo edición.
		
		string aux;
		
		aux = renglon_nombre->GetValue().c_str();
		bool b1 = ( aux == nombre_inicial );
		
		aux = renglon_resumen->GetValue().c_str();
		bool b2 = ( aux == resumen_inicial );
		
		aux = renglon_url->GetValue().c_str();
		bool b3 = ( aux == url_inicial );
		
		if ( b1 && b2 && b3 ) {
			
			EndModal( -1 );
			
		}
		
		string nombre = renglon_nombre->GetValue().c_str();
		
		if ( nombre == "" ) {
			
			wxMessageBox( wxT("Debe ingresar un nombre para el autor."), wxT("Campo incompleto.") );
			
		} else if ( nombre[0] == ' ' ) {
			
			wxMessageBox( wxT("El nombre no puede comenzar con un espacio."), wxT("Campo mal completado.") );
			
		} else {
			
			autor *autor_ = &( autores->get_autor_pos( pos ) );
			
			autor_->set_nombre( renglon_nombre->GetValue().c_str() );
			autor_->set_resumen( renglon_resumen->GetValue().c_str() );
			autor_->set_url( aux );
			
			EndModal( 1 );
			
		}
		
	}
	
}

