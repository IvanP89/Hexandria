//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_autores.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en ventana_autores.h
//////////////////////////////////////////////////////////////////////////////

#include "ventana_autores.h"
#include "ventana_agregar_autor.h"

#include <wx/event.h>

#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR DESTRUCTOR
ventana_autores::ventana_autores( wxWindow *_parent, Programa *_programa, ventana_agregar_libro *_anterior  ): vAutores( _parent ) {
	
	if ( _programa != NULL ) {
		
		programa_p = NULL;
		programa_s = _programa;
		
		autores = programa_s->autores;
		
	} else {
		
		programa_p = Singleton::get_base_activa();
		programa_s = NULL;
		
		autores = programa_p->autores;
		
	}
	
	anterior = _anterior;
	
	this->refresh();
	
	pos = -1;
	cambios = false;
	Ayuda = NULL;
	
}

ventana_autores::~ventana_autores() {
	
	if ( !Ayuda ) {
		
		Ayuda->Close();
		
	}
	
}

// LISTA
void ventana_autores::refresh ( ) {
	
	string buscado = barra_busqueda->GetValue().c_str();
	
	wxCommandEvent eficticio;
	
	autores.sort();
	
	if ( buscado != "" ) {
		
		this->click_buscar( eficticio );
		
	} else if ( filtrado_iniciales->GetSelection() != 0 ) {
		
		this->cambio_filtro_iniciales( eficticio );
		
	} else {
		
		lista_autores->Clear();
		pos_real.clear();
		
		const int tamanyo = autores.size();
		
		for ( int i=0;i<tamanyo;i++ ) { 
			
			lista_autores->Append( autores.get_autor_pos( i ).get_nombre().c_str() );
			pos_real.push_back( i );
			
		}
		
	}
	
}

void ventana_autores::Dclick_autor( wxCommandEvent &_event )  {
	
	pos = _event.GetSelection();
	
	ventana_agregar_autor   nueva_ventana( this, &autores, pos_real[pos] );
	if ( nueva_ventana.ShowModal() == 1 ) {
		
		this->refresh();
		cambios = true;
		
	}
	
}

// BARRA DE HERRAMIENTAS
void ventana_autores::click_boton_borrar( wxCommandEvent &_event )  {
	
	const int tamanyo = lista_autores->GetCount();
	int control = 0;
	for ( int i=0;i<tamanyo;i++ ) {
		
		if( lista_autores->IsChecked( i - control ) ) {
			
			lista_autores->Delete( i - control );
			autores.pop_pos( ( pos_real[i] - control ) );
			cambios = true;
			++control;
			
		}
		
	}
	
}

void ventana_autores::click_boton_agregar( wxCommandEvent &_event )  {
	
	ventana_agregar_autor   nueva_ventana( this, &autores );
	if ( nueva_ventana.ShowModal() == 1 ) {
		
		this->refresh();
		cambios = true;
		
	}
	
}

void ventana_autores::click_buscar( wxCommandEvent &_event )  {
	
	lista_autores->Clear();
	pos_real.clear();
	filtrado_iniciales->SetSelection( 0 );
	
	string buscado = barra_busqueda->GetValue().c_str();
	
	autor *autorPtr;
	
	const int tamanyo = autores.size();
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		autorPtr = &( autores.get_autor_pos( i ) );
		
		if ( autorPtr->buscar_contenido( buscado ) == true ) {
			
			lista_autores->Append( autores.get_autor_pos( i ).get_nombre().c_str() );
			pos_real.push_back( i );
			
		}
		
	}
	
}

void ventana_autores::click_boton_restaurar( wxCommandEvent &_event )  {
	
	barra_busqueda->SetValue( wxT("") );
	filtrado_iniciales->SetSelection( 0 );
	this->refresh();
	
}

void ventana_autores::click_boton_ayuda( wxCommandEvent &_event )  {
	
	if ( !Ayuda ) {
		
		Ayuda = new ventana_ayuda();
		
	}
	
	Ayuda->Show();
	
}

void ventana_autores::cambio_filtro_iniciales( wxCommandEvent &_event )  {
	
	string aux = filtrado_iniciales->GetString( filtrado_iniciales->GetSelection() ).c_str();
	
	if ( aux != "..." ) {
		
		char inicial = aux[0];
		
		lista_autores->Clear();
		pos_real.clear();
		
		autor *autorPtr;
		
		const int tamanyo = autores.size();
		
		for ( int i=0;i<tamanyo;i++ ) { 
			
			autorPtr = &( autores.get_autor_pos( i ) );
			
			aux = autorPtr->get_nombre();
			
			if ( aux[0] == inicial ) {
				
				lista_autores->Append( autores.get_autor_pos( i ).get_nombre().c_str() );
				pos_real.push_back( i );
				
			}
			
		}
		
	} else {
		
		this->refresh();
		
	}
	
	
}

// BOTONES VENTANA
void ventana_autores::click_boton_aceptar( wxCommandEvent &_event )  {
	
	if ( anterior != NULL ) {
		
		const int tamanyo = lista_autores->GetCount();
		for ( int i=0;i<tamanyo;i++ ) {
			
			if( lista_autores->IsChecked( i ) ) {
				
				anterior->cuadro_autores->Insert( autores.get_autor_pos( pos_real[i] ).get_nombre().c_str(), anterior->cuadro_autores->GetCount() );
				anterior->nuevo.agregar_autor( autores.get_autor_pos( pos_real[i] ).get_codigo(), &autores );
				
			}
			
		}
		
		if ( cambios == true ) {
			
			anterior->se_agrego_autor = new autores_database;
			*(anterior->se_agrego_autor) = autores;
			
		}
		
	}
	
	if ( cambios == true ) {
		
		if ( programa_p != NULL ) {
			
			programa_p->autores = autores;
			programa_p->set_cambios( true );
			
		} else if ( programa_s != NULL ) {
			
			programa_s->autores = autores;
			programa_s->set_cambios( true );
			
		}
		
		EndModal(1);
		
	} else {
		
		EndModal(0);
		
	}
	
}

void ventana_autores::click_boton_cancelar( wxCommandEvent &_event )  {
	
	EndModal(0);
	
}

