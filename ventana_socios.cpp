//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_socios.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en ventana_socios.h
//////////////////////////////////////////////////////////////////////////////

#include "ventana_socios.h"
#include "ventana_agregar_socio.h"
#include "ventana_libros_pendientes_socio.h"
#include "ventana_estadisticas.h"
#include "ventana_libros.h"
#include "ventana_info_socio.h"

#include "Core\personas.h"
#include "Core\utilidades.h"

#include <wx/msgdlg.h>

using namespace std;

//////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR DESTRUCTOR
ventana_socios::ventana_socios( wxWindow *_parent, Programa *_programa ): vSocios( _parent ) {
	
	// Inicialización de atributos.
	if ( _programa == NULL ) {
		
		programa = new ProgramaSombra( Singleton::obtener_instancia() );
		anterior = NULL;
		
	} else {
		
		programa = new ProgramaSombra( _programa );
		anterior = _programa;
		
	}
	fila = -1;
	cambios = false;
	Ayuda = NULL;
	
	// Inicialización de interfaz.
	MyToolbar->EnableTool( id_vs_boton_borrar, false );
	MyToolbar->EnableTool( id_vs_boton_prestar, false );
	MyToolbar->EnableTool( id_vs_boton_devolver, false );
	MyToolbar->EnableTool( id_vs_boton_detalles, false );
	this->refresh();
	
	Singleton::set_base_activa( programa );
	
}

ventana_socios::~ventana_socios() {
	
	delete programa;
	if ( Ayuda ) {
		
		Ayuda->Close();
		
	}
	
}

// SELECCION
void ventana_socios::seleccion ( const bool &_seleccionado ) {
	
	if ( _seleccionado == true ) {
		
		grilla_socios->SelectRow( fila );
		
		MyToolbar->EnableTool( id_vs_boton_borrar, true );
		MyToolbar->EnableTool( id_vs_boton_prestar, true );
		MyToolbar->EnableTool( id_vs_boton_devolver, true );
		MyToolbar->EnableTool( id_vs_boton_detalles, true );
		
		string path_foto = programa->socios.get_socio_pos( pos_real[fila] ).get_path_foto();
		this->cargar_imagen( path_foto );
		
	} else {
		
		MyToolbar->EnableTool( id_vs_boton_borrar, false );
		MyToolbar->EnableTool( id_vs_boton_prestar, false );
		MyToolbar->EnableTool( id_vs_boton_devolver, false );
		MyToolbar->EnableTool( id_vs_boton_detalles, false );
		grilla_socios->SelectRow( -1 );
		fila =  -1;
		this->cargar_imagen( "Img\\Resources\\no-user.png" );
		
	}
	
}

// EVENTOS GRILLA
void ventana_socios::refresh ( const bool &_conservar_seleccion ) {
	
	string buscado = barra_busqueda->GetValue().c_str();
	
	wxCommandEvent eficticio;
	
	if ( buscado != "" ) {
		
		this->click_buscar( eficticio );
		
	} else {
		
		grilla_socios->ClearGrid();
		grilla_socios->DeleteRows( 0, grilla_socios->GetNumberRows(), true );
		pos_real.clear();
		
		int tamanyo = programa->socios.get_cant_socios();
		grilla_socios->AppendRows( tamanyo );
		programa->socios.sort( orden_socios->GetSelection() );
		
		socio *soc;
		
		for ( int i=0;i<tamanyo;i++ ) { 
			
			soc = &( programa->socios.get_socio_pos( i ) );
			
			grilla_socios->SetCellValue( i, 0, soc->get_nombre_completo().c_str() );
			grilla_socios->SetCellValue( i, 1, soc->get_dni_str().c_str() );
			grilla_socios->SetCellValue( i, 2, soc->get_nro_socio_str().c_str() );
			grilla_socios->SetCellValue( i, 3, soc->get_pendientes().c_str() );
			
			pos_real.push_back( i );
			
		}
		
		this->seleccion( _conservar_seleccion );
		
	}
	
}

void ventana_socios::click_izq_grilla ( wxGridEvent &_event ) {
	
	fila = _event.GetRow();
	this->seleccion();
	
}

void ventana_socios::Dclick_grilla ( wxGridEvent &_event ) {
	
	ventana_info_socio   nueva_ventana( this, pos_real[fila] );
	nueva_ventana.ShowModal();
	
	Singleton::set_base_activa( programa );
	
}

void ventana_socios::click_der_grilla ( wxGridEvent &_event ) {
	
	fila = _event.GetRow();
	this->seleccion();
	
	wxPoint posicion_click;
	posicion_click = _event.GetPosition();
	grilla_socios->PopupMenu( menu_grilla, posicion_click );
	
}

// BARRA DE HERRAMIENTAS
void ventana_socios::click_boton_borrar ( wxCommandEvent &_event ) {
	
	string aux;
	aux += "¿Seguro que desea eliminar \"";
	aux += programa->socios.get_socio_pos( pos_real[fila] ).get_nombre_completo();
	aux += "\"?";
	
	if ( wxMessageBox( aux.c_str(), wxT("Eliminar socio..."), wxYES_NO ) == wxYES && fila >= 0 ) {
		
		int pendientes = programa->socios.get_socio_pos( pos_real[fila] ).get_cant_a_devolver();
		
		if ( pendientes > 0 ) {
			
			if ( programa->socios.pop_pos( pos_real[fila] ) == false ) {
				
				wxMessageBox( wxT("No se pudo eliminar el socio."), wxT("Aviso") );
				
			} else {
				
				programa->set_cambios( true );
				cambios = true;
				
				if ( fila == programa->socios.get_cant_socios() ) {
					
					this->refresh();
					
				} else {
					
					this->refresh( true );
					
				}
				
			}
			
		} else if ( programa->socios.pop_pos( pos_real[fila] ) == false ) {
			
			wxMessageBox( wxT("No se pudo eliminar el socio."), wxT("Aviso") );
			
		} else {
			
			programa->set_cambios( true );
			cambios = true;
			
			if ( fila == programa->socios.get_cant_socios() ) {
				
				this->refresh();
				
			} else {
				
				this->refresh( true );
				
			}
			
		}
		
	}
	
}

void ventana_socios::click_boton_agregar ( wxCommandEvent &_event ) {
	
	this->seleccion( false );
	
	ventana_agregar_socio   nueva_ventana( this, -1 );
	
	if ( nueva_ventana.ShowModal() == 1 ) {
		
		programa->set_cambios( true );
		cambios = true;
		this->refresh();
		
	}
	
	Singleton::set_base_activa( programa );
	
}

void ventana_socios::click_editar_socio( wxCommandEvent &_event )  {
	
	ventana_agregar_socio   nueva_ventana( this, pos_real[fila] );
	
	if ( nueva_ventana.ShowModal() == 1 ) {
		
		programa->set_cambios( true );
		cambios = true;
		this->refresh( true );
		
	}
	
	Singleton::set_base_activa( programa );
	
}

void ventana_socios::click_boton_prestar ( wxCommandEvent &_event ) {
	
	socio *soc = &( programa->socios.get_socio_pos( pos_real[fila] ) );
	int nro_socio = soc->get_nro_socio();
	
	if ( soc->get_cant_a_devolver() >= 3 ) {
		
		wxMessageBox( wxT("El socio seleccionado posee la máxima cantidad de libros a devolver (3). No se puede realizar el préstamo."), wxT("Aviso") );
		
	} else {
		
		ventana_libros   nueva_ventana( this, programa );
		int cod_libro = nueva_ventana.ShowModal();
		
		soc = &( programa->socios.get_socio_cod( nro_socio ) ); // Por si se realizaron cambios desde ventana_libros.
		
		if ( cod_libro >= 0 ) {
			
			libro *lib = &( programa->libros.get_libro( cod_libro ) );
			
			if ( soc->push_prestamo( lib->get_codigo() ) == false ) {
				
				wxMessageBox( wxT("Se ha producido un error al intentar agregar el préstamo al socio."), wxT("Aviso") );
				
			} else {
				
				lib->set_prestado( true, soc->get_nro_socio() );
				
				bibliotecario *bib = programa->get_cuenta_activa();
				if ( bib != NULL ) {
					
					bib->sumar_prestamo();
					
				}
				
				programa->set_cambios( true );
				cambios = true;
				
				wxMessageBox( wxT("El préstamo se ha realizado de manera exitosa."), wxT("Operación finalizada") );
				
			}
			
		}	
		
	}
	
	Singleton::set_base_activa( programa );
	
}

void ventana_socios::click_boton_devolver ( wxCommandEvent &_event ) {
	
	ventana_libros_pendientes_socio   nueva_ventana( this );
	
	if ( nueva_ventana.ShowModal() >= 0 ) {
		
		programa->set_cambios( true );
		cambios = true;
		
		wxMessageBox( wxT("La devolución se ha realizado de manera exitosa."), wxT("Operación finalizada") );
		
	}
	
	Singleton::set_base_activa( programa );
	
}

void ventana_socios::click_boton_detalles ( wxCommandEvent &_event ) {
	
	ventana_info_socio   nueva_ventana( this, pos_real[fila] );
	nueva_ventana.ShowModal();
	
}

void ventana_socios::click_boton_estadisticas ( wxCommandEvent &_event ) {
	
	ventana_estadisticas   nueva_ventana( this );
	nueva_ventana.ShowModal();
	
}

void ventana_socios::cambio_orden ( wxCommandEvent &_event ) {
	
	this->refresh();
	
}

void ventana_socios::click_buscar ( wxCommandEvent &_event ) {
	
	grilla_socios->ClearGrid();
	grilla_socios->DeleteRows( 0, grilla_socios->GetNumberRows(), true );
	pos_real.clear();
	
	string buscado = barra_busqueda->GetValue().c_str();
	
	if ( buscado == "" ) {
		
		this->refresh();
		
	} else {
		
		socio *soc;
		
		const int tamanyo = programa->socios.get_cant_socios();
		
		int contador = 0;
		
		for ( int i=0;i<tamanyo;i++ ) { 
			
			soc = &( programa->socios.get_socio_pos( i ) );
			
			if ( soc->socio_buscado( buscado ) == true ) {
				
				grilla_socios->AppendRows();
				grilla_socios->SetCellValue( contador, 0, soc->get_nombre_completo().c_str() );
				grilla_socios->SetCellValue( contador, 1, soc->get_dni_str().c_str() );
				grilla_socios->SetCellValue( contador, 2, soc->get_nro_socio_str().c_str() );
				grilla_socios->SetCellValue( contador, 3, soc->get_pendientes().c_str() );
				
				++ contador;
				
				pos_real.push_back( i );
				
			}
			
			
		}
		
	}
	
}

void ventana_socios::click_boton_restaurar ( wxCommandEvent &_event ) {
	
	barra_busqueda->SetValue( wxT("") );
	
	this->refresh();
	
}

void ventana_socios::click_boton_ayuda ( wxCommandEvent &_event ) {
	
	if ( !Ayuda ) {
		
		Ayuda = new ventana_ayuda();
		
	}
	
	Ayuda->Show();
	
}

// BOTONES VENTANA
void ventana_socios::click_boton_aceptar ( wxCommandEvent &_event ) {
	
	if ( anterior != NULL ) { // Modo elegir socio para realizar préstamo.
		
		if ( MyToolbar->GetToolEnabled( id_vs_boton_borrar ) == false ) {
			
			wxMessageBox( wxT("Debe seleccionar un socio para realizar el préstamo. Si ya no desea llevar a cabo esta acción, cierre la ventana con el botón \"cancelar\""), wxT("Aviso") );
			
		} else if ( programa->socios.get_socio_pos( pos_real[fila] ).get_cant_a_devolver() >= 3 ) {
			
			wxMessageBox( wxT("El socio seleccionado posee la máxima cantidad de libros a devolver (3). No se puede realizar el préstamo."), wxT("Aviso") );
			
		} else if ( cambios == true ) {
			
			anterior->set_cambios_sombra( programa );
			EndModal( programa->socios.get_socio_pos( pos_real[fila] ).get_nro_socio() );
			
		} else {
			
			EndModal( programa->socios.get_socio_pos( pos_real[fila] ).get_nro_socio() );
			
		}	
		
	} else {
		
		if ( cambios == true ) {
			
			Programa *programa_ = Singleton::obtener_instancia();
			programa_->set_cambios_sombra( programa );
			EndModal(1);
			
		} else {
			
			EndModal(-1);
			
		}
		
	}
	
}

void ventana_socios::click_boton_cancelar ( wxCommandEvent &_event ) {
	
	EndModal(-1);
	
}

// MANEJO DE IMÁGENES
void ventana_socios::cargar_imagen ( const string &_path ) {
	
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
	foto_socio->SetBitmap( *imagen );
	
}

