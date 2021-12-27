//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_agregar_usuario.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en
// ventana_agregar_usuario.h
//////////////////////////////////////////////////////////////////////////////

#include "ventana_agregar_usuario.h"

#include "Core\programa.h"

#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////////

ventana_agregar_usuario::ventana_agregar_usuario( ventana_agregar_bibliotecario *_parent ): vAgregarUsuario( _parent ) {
	
	anterior = _parent;
	
	if ( anterior->pos >= 0 ) { // Modo edición.
		
		renglon_usuario->SetValue( anterior->nuevo.get_cta_usuario().c_str() );
		renglon_pass->SetValue( anterior->nuevo.get_cta_pass().c_str() );
		renglon_confirmacion->SetValue( anterior->nuevo.get_cta_pass().c_str() );
		
	}
	
}

ventana_agregar_usuario::~ventana_agregar_usuario() {
	
}

void ventana_agregar_usuario::click_boton_cancelar( wxCommandEvent &_event )  {
	
	EndModal( -1 );
	
}

void ventana_agregar_usuario::click_boton_aceptar( wxCommandEvent &_event )  {
	
	string aux = renglon_usuario->GetValue().c_str();
	
	if ( aux[0] == ' ' ) {
		
		error_usuario->SetLabel( wxT("* El nombre de usuario no puede comenzar con un espacio.") );
		error_usuario->Show();
		this->redibujar_ventana();
		
	} else if ( this->ya_existe_usuario() == true ) {
		
		error_usuario->SetLabel( wxT("* El usuario ingresado ya existe.") );
		error_usuario->Show();
		this->redibujar_ventana();
		
	} else if ( renglon_pass->GetValue() != renglon_confirmacion->GetValue() ) {
		
		error_confirmacion->Show();
		error_usuario->Hide();
		this->redibujar_ventana();
		
	} else {
		
		anterior->nuevo.set_cta_usuario( aux );
		anterior->nuevo.set_cta_pass( renglon_pass->GetValue().c_str() );
		EndModal( 1 );
		
	}
	
}

bool ventana_agregar_usuario::ya_existe_usuario ( ) const {
	
	string usuario = renglon_usuario->GetValue().c_str();
	
	const int cant_bib = anterior->programa->bibliotecarios.size();
	
	int contador = 0;
	
	for( int i=0;i<cant_bib;i++ ) { 
		
		if ( anterior->programa->bibliotecarios.get_bibliotecario_pos( i ).get_cta_usuario() == usuario ) {
			
			++contador;
			
		}
		
	}
	
	if ( anterior->pos < 0 ) {
		
		return ( contador > 0 );	
		
	}
	
	return ( contador > 1 );
	
}

void ventana_agregar_usuario::redibujar_ventana ( ) {
	
//	wxSize tamanyo = this->GetSize();
//	tamanyo.SetHeight( tamanyo.GetHeight() +1 );
//	this->SetSize( tamanyo );
//	tamanyo.SetHeight( tamanyo.GetHeight() -1 );
//	this->SetSize( tamanyo );
	this->Layout();
	this->Fit();
	
}

