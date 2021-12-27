//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_bibliotecarios.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en
// ventana_bibliotecarios.h
//////////////////////////////////////////////////////////////////////////////

#include "ventana_bibliotecarios.h"
#include "ventana_info_bibliotecario.h"
#include "ventana_agregar_bibliotecario.h"
#include "ventana_estadisticas.h"

#include "Core\personas.h"

#include <wx/msgdlg.h>

#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR DESTRUCTOR
ventana_bibliotecarios::ventana_bibliotecarios( wxWindow *_parent ): vBibliotecarios( _parent ) {
	
	// Inicialización de atributos.
	programa = new ProgramaSombra( Singleton::obtener_instancia() );
	fila = -1;
	cambios = false;
	Ayuda = NULL;
	
	// Inicialización de interfaz.
	MyToolbar->EnableTool( id_vb_boton_borrar, false );
	MyToolbar->EnableTool( id_vb_boton_detalles, false );
	this->refresh();
	
	Singleton::set_base_activa( programa );
	
}

ventana_bibliotecarios::~ventana_bibliotecarios() {
	
	delete programa;
	if ( Ayuda ) {
		
		Ayuda->Close();
		
	}
	
}

// SELECCIÓN
void ventana_bibliotecarios::seleccion ( const bool &_seleccionado ) {
	
	if ( _seleccionado == true ) {
		
		grilla_bibliotecarios->SelectRow( fila );
		
		MyToolbar->EnableTool( id_vb_boton_borrar, true );
		MyToolbar->EnableTool( id_vb_boton_detalles, true );
		
		string path_foto = programa->bibliotecarios.get_bibliotecario_pos( pos_real[fila] ).get_path_foto();
		this->cargar_imagen( path_foto );
		
	} else {
		
		MyToolbar->EnableTool( id_vb_boton_borrar, false );
		MyToolbar->EnableTool( id_vb_boton_detalles, false );
		grilla_bibliotecarios->SelectRow( -1 );
		fila =  -1;
		this->cargar_imagen( "Img\\Resources\\no-user.png" );
		
	}
	
}

// EVENTOS GRILLA
void ventana_bibliotecarios::refresh ( const bool &_conservar_seleccion ) {
	
	string buscado = barra_busqueda->GetValue().c_str();
	
	wxCommandEvent eficticio;
	
	if ( buscado != "" ) {
		
		this->click_buscar( eficticio );
		
	} else {
		
		grilla_bibliotecarios->ClearGrid();
		grilla_bibliotecarios->DeleteRows( 0, grilla_bibliotecarios->GetNumberRows(), true );
		pos_real.clear();
		
		int tamanyo = programa->bibliotecarios.size();
		grilla_bibliotecarios->AppendRows( tamanyo );
		programa->bibliotecarios.sort( orden_bibliotecarios->GetSelection() );
		
		bibliotecario *bib;
		
		for ( int i=0;i<tamanyo;i++ ) { 
			
			bib = &( programa->bibliotecarios.get_bibliotecario_pos( i ) );
			
			grilla_bibliotecarios->SetCellValue( i, 0, bib->get_nombre_completo().c_str() );
			grilla_bibliotecarios->SetCellValue( i, 1, bib->get_edad_str().c_str() );
			grilla_bibliotecarios->SetCellValue( i, 2, bib->get_cant_prestamos_str().c_str() );
			grilla_bibliotecarios->SetCellValue( i, 3, bib->get_salario_str().c_str() );
			grilla_bibliotecarios->SetCellValue( i, 4, bib->get_antiguedad_str().c_str() );
			
			pos_real.push_back( i );
			
		}
		
		this->seleccion( _conservar_seleccion );
		
	}
	
}

void ventana_bibliotecarios::click_izq_grilla( wxGridEvent &_event )  {
	
	fila = _event.GetRow();
	this->seleccion();
	
}

void ventana_bibliotecarios::Dclick_grilla( wxGridEvent &_event )  {
	
	ventana_info_bibliotecario   nueva_ventana( this, pos_real[fila] );
	nueva_ventana.ShowModal();
	
}

void ventana_bibliotecarios::click_der_grilla( wxGridEvent &_event )  {
	
	fila = _event.GetRow();
	this->seleccion();
	
	wxPoint posicion_click;
	posicion_click = _event.GetPosition();
	grilla_bibliotecarios->PopupMenu( menu_grilla, posicion_click );
	
}

// BARRA DE HERRAMIENTAS
void ventana_bibliotecarios::click_boton_borrar( wxCommandEvent &_event )  {
	
	string aux;
	aux += "¿Seguro que desea eliminar \"";
	aux += programa->bibliotecarios.get_bibliotecario_pos( pos_real[fila] ).get_nombre_completo();
	aux += "\"?";
	
	if ( wxMessageBox( aux.c_str(), wxT("Eliminar bibliotecario..."), wxYES_NO ) == wxYES && fila >= 0 ) {
		
		if ( programa->bibliotecarios.pop_pos( pos_real[fila] ) == false ) {
			
			wxMessageBox( wxT("No se pudo eliminar el bibliotecario."), wxT("Aviso") );
			
		} else {
			
			programa->set_cambios( true );
			cambios = true;
			
			if ( fila == programa->bibliotecarios.size() ) {
				
				this->refresh();
				
			} else {
				
				this->refresh( true );
				
			}
			
		}
		
	}
	
}

void ventana_bibliotecarios::click_boton_agregar( wxCommandEvent &_event )  {
	
	this->seleccion( false );
	
	ventana_agregar_bibliotecario   nueva_ventana( this );
	
	if ( nueva_ventana.ShowModal() == 1 ) {
		
		programa->set_cambios( true );
		cambios = true;
		this->refresh();
		
	}
	
	Singleton::set_base_activa( programa );
	
}

void ventana_bibliotecarios::click_editar_bib( wxCommandEvent &_event )  {
	
	ventana_agregar_bibliotecario   nueva_ventana( this, pos_real[fila] );
	
	if ( nueva_ventana.ShowModal() == 1 ) {
		
		programa->set_cambios( true );
		cambios = true;
		this->refresh( true );
		
	}
	
	Singleton::set_base_activa( programa );
	
}

void ventana_bibliotecarios::click_boton_detalles( wxCommandEvent &_event )  {
	
	ventana_info_bibliotecario   nueva_ventana( this, pos_real[fila] );
	nueva_ventana.ShowModal();
	
}

void ventana_bibliotecarios::click_boton_estadisticas( wxCommandEvent &_event )  {
	
	ventana_estadisticas   nueva_ventana( this );
	nueva_ventana.ShowModal();
	
}

void ventana_bibliotecarios::cambio_orden( wxCommandEvent &_event )  {
	
	this->refresh();
	
}

void ventana_bibliotecarios::click_buscar( wxCommandEvent &_event )  {
	
	grilla_bibliotecarios->ClearGrid();
	grilla_bibliotecarios->DeleteRows( 0, grilla_bibliotecarios->GetNumberRows(), true );
	pos_real.clear();
	
	string buscado = barra_busqueda->GetValue().c_str();
	
	if ( buscado == "" ) {
		
		this->refresh();
		
	} else {
		
		bibliotecario *bib;
		
		int contador = 0;
		const int tamanyo = programa->bibliotecarios.size();
		
		for ( int i=0;i<tamanyo;i++ ) { 
			
			bib = &( programa->bibliotecarios.get_bibliotecario_pos( i ) );
			
			if ( bib->buscado( buscado ) == true ) {
				
				grilla_bibliotecarios->AppendRows();
				grilla_bibliotecarios->SetCellValue( contador, 0, bib->get_nombre_completo().c_str() );
				grilla_bibliotecarios->SetCellValue( contador, 1, bib->get_edad_str().c_str() );
				grilla_bibliotecarios->SetCellValue( contador, 2, bib->get_cant_prestamos_str().c_str() );
				grilla_bibliotecarios->SetCellValue( contador, 3, bib->get_salario_str().c_str() );
				grilla_bibliotecarios->SetCellValue( contador, 4, bib->get_antiguedad_str().c_str() );
				
				++contador;
				
				pos_real.push_back( i );
				
			}
			
			
		}
		
	}
	
}

void ventana_bibliotecarios::click_boton_restaurar( wxCommandEvent &_event )  {
	
	barra_busqueda->SetValue( wxT("") );
	
	this->refresh();
	
}

void ventana_bibliotecarios::click_boton_ayuda( wxCommandEvent &_event )  {
	
	if ( !Ayuda ) {
		
		Ayuda = new ventana_ayuda();
		
	}
	
	Ayuda->Show();
	
}

// BOTONES VENTANA
void ventana_bibliotecarios::click_boton_aceptar( wxCommandEvent &_event )  {
	
	if ( cambios == true ) {
		
		Programa *programa_ = Singleton::obtener_instancia();
		programa_->set_cambios_sombra( programa );
		EndModal(1);
		
	} else {
		
		EndModal(-1);
		
	}
	
}

void ventana_bibliotecarios::click_boton_cancelar( wxCommandEvent &_event )  {
	
	EndModal(-1);
	
}

// MANEJO DE IMÁGENES
void ventana_bibliotecarios::cargar_imagen ( const string &_path ) {
	
	string dir_imagen = _path;
	string extension = dir_imagen.substr( dir_imagen.find_last_of( '.' ) );
	char a = extension[1]; // 'a' contiene ahora la primera letra de la extension (extension[0] es el punto).
	a = tolower(a);
	wxBitmap *imagen;
	switch ( a ) {
	case 'j':
		imagen = new wxBitmap( dir_imagen.c_str(), wxBITMAP_TYPE_JPEG );
		break;
		
	case 'p':
		imagen = new wxBitmap( dir_imagen.c_str(), wxBITMAP_TYPE_PNG );
		break;
		
	case 'b':
		imagen = new wxBitmap( dir_imagen.c_str(), wxBITMAP_TYPE_BMP );
		
	}
	
	*imagen = EditarImagen::ajustar_tamanyo( *imagen );
	foto_bibliotecario->SetBitmap( *imagen );
	
}

// NUEVOS

