//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_login.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en ventana_login.h
//////////////////////////////////////////////////////////////////////////////

#include "ventana_login.h"

#include "Core\personas.h"

#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////////

ventana_login::ventana_login( ventana_principal *_parent ): vLogin( _parent ) {
	
	programa = Singleton::obtener_instancia();
	
}

ventana_login::~ventana_login() {
	
}

void ventana_login::enter_presionado( wxCommandEvent &_event )  {
	
	this->click_boton_aceptar( _event );
	
}

void ventana_login::click_boton_salir( wxCommandEvent &_event )  {
	
	EndModal( -1 );
	
}

void ventana_login::click_boton_aceptar( wxCommandEvent &_event )  {
	
	string usuario = renglon_usuario->GetValue().c_str();
	string pass = renglon_pass->GetValue().c_str();
	
	if ( programa->comprobar_cta_admin( usuario ) == false ) {
		
		bibliotecario *bib = NULL;
		int tamanyo = programa->bibliotecarios.size();
		for ( int i=0;i<tamanyo;i++ ) { 
			
			bib = &( programa->bibliotecarios.get_bibliotecario_pos( i ) );
			if ( bib->get_cta_usuario() != usuario ) {
				
				bib = NULL;
				
			} else {
				
				break;
				
			}
			
		}
		
		if ( bib == NULL ) {
			
			error_usuario->Show();
			error_pass->Hide();
			this->redibujar_ventana();
			
		} else if ( bib->get_cta_pass() != pass ) {
			
			error_usuario->Hide();
			error_pass->Show();
			this->redibujar_ventana();
			
		} else {
			
			programa->set_cuenta_activa( bib );
			EndModal( 1 );
			
		}
		
	} else {
		
		// Login como administrador.
		if ( programa->comprobar_pass_admin( pass ) == false ) {
			
			error_usuario->Hide();
			error_pass->Show();
			this->redibujar_ventana();
			
		} else {
			
			programa->set_cuenta_activa( NULL );
			EndModal( 1 );
			
		}
		
	}
	
}

void ventana_login::redibujar_ventana ( ) {
	
//	wxSize tamanyo = this->GetSize();
//	tamanyo.SetHeight( tamanyo.GetHeight() +1 );
//	this->SetSize( tamanyo );
//	tamanyo.SetHeight( tamanyo.GetHeight() -1 );
//	this->SetSize( tamanyo );
	this->Layout();
	this->Fit();
	
}

void ventana_login::se_cierra( wxCloseEvent& event )  {
	
	EndModal( -1 );
	
}

