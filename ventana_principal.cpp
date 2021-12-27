////////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_principal.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en ventana_principal.h
////////////////////////////////////////////////////////////////////////////////

#include "ventana_acerca_de.h"
#include "ventana_agregar_libro.h"
#include "ventana_agregar_socio.h"
#include "ventana_autores.h"
#include "ventana_bibliotecarios.h"
#include "ventana_estadisticas.h"
#include "ventana_info_libro.h"
#include "ventana_info_socio.h"
#include "ventana_libros.h"
#include "ventana_login.h"
#include "ventana_principal.h"
#include "ventana_socios.h"

#include "Core\bibliografia.h"
#include "Core\personas.h"

#include <wx/bitmap.h>
#include <wx/gdicmn.h>
#include <wx/icon.h>
#include <wx/msgdlg.h>
#include <wx/wx.h>

#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR DESTRUCTOR
ventana_principal::ventana_principal( wxWindow *parent ): vPrincipal( parent ) {
	
	this->SetIcon( wxIcon( wxT("Img\\Resources\\icono_ventana.png"), wxBITMAP_TYPE_PNG ) );
	
	Ayuda = NULL;
	programa = Singleton::obtener_instancia();
	programa->inicializar();
	Singleton::set_base_activa( programa );
	
	if ( programa->get_carga_exitosa() == false ) {
		
		wxMessageBox( wxT("Ha fallado la carga de los datos del programa. La aplicación se cerrará."), wxT("Aviso"), wxOK, this );
		this->Close();
		
	}
	
	fila_libros = fila_socios = -1;
	
	this->refresh_general();
	
	ventana_login nueva_ventana( this );
	
	if ( nueva_ventana.ShowModal() >= 0 ) {
		
		if ( programa->get_cuenta_activa() == NULL ) {
			
			menu_abrir->Enable( id_abrir_bib, true );
			
		}
		
		socio soc = programa->socios.get_socio_pos( 12 );
		this->Show();
		
	} else {
		
		this->Close();
		
	}	
	
}

ventana_principal::~ventana_principal ( ) {
	
	delete programa;
	if ( Ayuda ) {
		
		Ayuda->Destroy();
		
	}
	
}

// CLOSE EVENT
void ventana_principal::se_cierra_vPrincipal( wxCloseEvent &_event )  {
	
	if ( programa->get_cambios() == true ) {
		
		if ( wxMessageBox( wxT("¿Desea guardar los cambios?"), wxT("Se han realizado cambios"), wxYES_NO ) == wxYES ) {
			
			if ( programa->guardar() == false ) {
				
				wxMessageBox( wxT("Se ha producido un error al guardar."), wxT("Aviso") );
				
			}
			
		}
		
	}
	
	_event.Skip();
	
}

void ventana_principal::click_salir( wxCommandEvent &_event )  {
	
	this->Close();
	
}

// GUARDAR
void ventana_principal::click_guardar( wxCommandEvent &_event )  {
	
	if ( programa->guardar() == false ) {
		
		wxMessageBox( wxT("Se ha producido un error al guardar."), wxT("Aviso") );
		
	}
	
	programa->set_cambios( false );
	
	this->deseleccionar_todo();
	
}

// SELECCION
void ventana_principal::seleccion_libro ( const bool &_seleccionado ) {
	
	if ( _seleccionado == true ) {
		
		grilla_libros_principal->SelectRow( fila_libros );
		
		boton_eliminar_libro->Enable();
		if ( boton_eliminar_socio->IsEnabled() == true ) {
			
			boton_prestar->Enable();
			boton_devolver->Enable();
			
		}
		
	} else {
		
		boton_eliminar_libro->Disable();
		boton_prestar->Disable();
		boton_devolver->Disable();
		grilla_libros_principal->SelectRow( -1 );
		fila_libros =  -1;
		
	}
	
}

void ventana_principal::seleccion_socio ( const bool &_seleccionado ) {
	
	if ( _seleccionado == true ) {
		
		grilla_socios_principal->SelectRow( fila_socios );
		
		boton_eliminar_socio->Enable();
		if ( boton_eliminar_libro->IsEnabled() == true ) {
			
			boton_devolver->Enable();
			boton_prestar->Enable();
			
		}
		
	} else {
		
		boton_eliminar_socio->Disable();
		boton_devolver->Disable();
		boton_prestar->Disable();
		grilla_socios_principal->SelectRow( -1 );
		fila_socios = -1;
		
	}
	
}

void ventana_principal::deseleccionar_todo ( ) {
	
	this->seleccion_libro( false );
	this->seleccion_socio( false );
	
}

// ABRIR VENTANAS
void ventana_principal::click_abrir_libros( wxCommandEvent &_event )  {
	
	this->deseleccionar_todo();
	
	ventana_libros   nueva_ventana( this );
	
	if ( nueva_ventana.ShowModal() == 1 ) {
		
		programa->set_cambios( true );
		refresh_general();
		
	}
	
	Singleton::set_base_activa( programa );
	
}

void ventana_principal::click_abrir_autores( wxCommandEvent &_event )  {
	
	this->deseleccionar_todo();
	
	ventana_autores   nueva_ventana( this );
	
	if ( nueva_ventana.ShowModal() == 1 ) {
		
		programa->set_cambios( true );
		
	}
	
	Singleton::set_base_activa( programa );
	
}

void ventana_principal::click_abrir_socios( wxCommandEvent &_event )  {
	
	this->deseleccionar_todo();
	
	ventana_socios   nueva_ventana( this );
	
	if ( nueva_ventana.ShowModal() == 1 ) {
		
		programa->set_cambios( true );
		refresh_general();
		
	}
	
	Singleton::set_base_activa( programa );
	
}

void ventana_principal::click_abrir_bib( wxCommandEvent &_event )  {
	
	this->deseleccionar_todo();
	
	ventana_bibliotecarios   nueva_ventana( this );
	
	if ( nueva_ventana.ShowModal() == 1 ) {
		
		programa->set_cambios( true );
		
	}
	
	Singleton::set_base_activa( programa );
	
}

void ventana_principal::click_ver_ayuda( wxCommandEvent &_event )  {
	
	if ( !Ayuda ) {
		
		Ayuda = new ventana_ayuda();
		
	}
	
	Ayuda->Show();
	
}

void ventana_principal::click_acerca_de( wxCommandEvent &_event )  {
	
	this->deseleccionar_todo();
	
	ventana_acerca_de   nueva_ventana( this );
	
	nueva_ventana.ShowModal();
	
}

void ventana_principal::click_ver_estadisticas( wxCommandEvent &_event )  {
	
	ventana_estadisticas nueva_ventana( this );
	nueva_ventana.ShowModal();
	
}

// BUSQUEDA
void ventana_principal::click_buscar_libro( wxCommandEvent &_event )  {
	
	grilla_libros_principal->ClearGrid();
	grilla_libros_principal->DeleteRows( 0, grilla_libros_principal->GetNumberRows(), true );
	pos_real_libros.clear();
	
	string buscado = barra_busqueda_libros->GetValue().c_str();
	
	libro *lib;
	
	const int tamanyo = programa->libros.get_cant_libros();
	
	int contador = 0;
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		lib = &( programa->libros.get_libro_pos( i ) );
		
		if ( lib->buscar_contenido( buscado ) == true ) {
			
			grilla_libros_principal->AppendRows();
			grilla_libros_principal->SetCellValue( contador, 0, lib->get_titulo().c_str() );
			grilla_libros_principal->SetCellValue( contador, 1, lib->get_nombre_autores().c_str() );
			if ( lib->get_prestado() == true ) {
				
				grilla_libros_principal->SetCellValue( contador, 2, wxT("prestado") );
				
			} else {
				
				grilla_libros_principal->SetCellValue( contador, 2, wxT("disponible") );
				
			}
			grilla_libros_principal->SetCellValue( contador, 3, lib->get_ubicacion().str().c_str() );
			
			++contador;
			
			pos_real_libros.push_back( i );
			
		}
		
		
	}
	
}

void ventana_principal::click_buscar_socio( wxCommandEvent &_event )  {
	
	grilla_socios_principal->ClearGrid();
	grilla_socios_principal->DeleteRows( 0, grilla_socios_principal->GetNumberRows(), true );
	pos_real_socios.clear();
	
	string buscado = barra_busqueda_socios->GetValue().c_str();
	
	socio *soc;
	
	const int tamanyo = programa->socios.get_cant_socios();
	
	int contador = 0;
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		soc = &( programa->socios.get_socio_pos( i ) );
		
		if ( soc->socio_buscado( buscado ) == true ) {
			
			grilla_socios_principal->AppendRows();
			grilla_socios_principal->SetCellValue( contador, 0, soc->get_nombre_completo().c_str() );
			grilla_socios_principal->SetCellValue( contador, 1, soc->get_dni_str().c_str() );
			grilla_socios_principal->SetCellValue( contador, 2, soc->get_pendientes().c_str() );
			grilla_socios_principal->SetCellAlignment( contador, 2, wxALIGN_CENTRE, wxALIGN_CENTRE );
			
			++contador;
			
			pos_real_socios.push_back( i );
			
		}
		
		
	}
	
}

// GRILLA
void ventana_principal::refresh_libros ( const bool &_conservar_seleccion ) {
	
	grilla_libros_principal->ClearGrid();
	grilla_libros_principal->DeleteRows( 0, grilla_libros_principal->GetNumberRows(), true );
	pos_real_libros.clear();
	
	int tamanyo = programa->libros.get_cant_libros();
	grilla_libros_principal->AppendRows( tamanyo );
	programa->libros.sort( LibrosPorTitulo );
	
	libro *lib;
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		lib = &( programa->libros.get_libro_pos( i ) );
		
		grilla_libros_principal->SetCellValue( i, 0, lib->get_titulo().c_str() );
		grilla_libros_principal->SetCellValue( i, 1, lib->get_nombre_autores().c_str() );
		if ( lib->get_prestado() == true ) {
			
			grilla_libros_principal->SetCellValue( i, 2, wxT("prestado") );
			
		} else {
			
			grilla_libros_principal->SetCellValue( i, 2, wxT("disponible") );
			
		}
		grilla_libros_principal->SetCellValue( i, 3, lib->get_ubicacion().str().c_str() );
		
		pos_real_libros.push_back( i );
		
	}
	
	this->seleccion_libro( _conservar_seleccion );
	
}

void ventana_principal::refresh_socios ( const bool &_conservar_seleccion ) {
	
	grilla_socios_principal->ClearGrid();
	grilla_socios_principal->DeleteRows( 0, grilla_socios_principal->GetNumberRows(), true );
	pos_real_socios.clear();
	
	int tamanyo = programa->socios.get_cant_socios();
	grilla_socios_principal->AppendRows( tamanyo );
	programa->socios.sort( SociosPorNombre );
	
	socio *soc;
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		soc = &( programa->socios.get_socio_pos( i ) );
		
		grilla_socios_principal->SetCellValue( i, 0, soc->get_nombre_completo().c_str() );
		grilla_socios_principal->SetCellValue( i, 1, soc->get_dni_str().c_str() );
		grilla_socios_principal->SetCellValue( i, 2, soc->get_pendientes().c_str() );
		grilla_socios_principal->SetCellAlignment( i, 2, wxALIGN_CENTRE, wxALIGN_CENTRE );
		
		pos_real_socios.push_back( i );
		
	}
	
	this->seleccion_socio( _conservar_seleccion );
	
}

void ventana_principal::refresh_general ( ) {
	
	this->refresh_libros();
	this->refresh_socios();
	
}

void ventana_principal::click_iz_libro( wxGridEvent &_event )  {
	
	fila_libros = _event.GetRow();
	
	this->seleccion_libro();
	
}

void ventana_principal::click_iz_socio( wxGridEvent &_event )  {
	
	fila_socios = _event.GetRow();
	
	this->seleccion_socio();
	
}

void ventana_principal::Dclick_libro( wxGridEvent &_event )  {
	
	ventana_info_libro   nueva_ventana( this, pos_real_libros[fila_libros] );
	nueva_ventana.ShowModal();
	
}

void ventana_principal::Dclick_socio( wxGridEvent &_event )  {
	
	ventana_info_socio   nueva_ventana( this, pos_real_socios[fila_socios] );
	nueva_ventana.ShowModal();
	
}

void ventana_principal::click_der_libro( wxGridEvent &_event )  {
	
	fila_libros = _event.GetRow();
	this->seleccion_libro();
	
	wxPoint posicion_click;
	posicion_click = _event.GetPosition();
	grilla_libros_principal->PopupMenu( menu_grilla_libros, posicion_click );
	
}

void ventana_principal::click_der_socio( wxGridEvent &_event )  {
	
	fila_socios = _event.GetRow();
	this->seleccion_socio();
	
	wxPoint posicion_click;
	posicion_click = _event.GetPosition();
	grilla_socios_principal->PopupMenu( menu_grilla_socios, posicion_click );
	
}

// MENU CONTEXTUAL GRILLA
void ventana_principal::click_ver_detalles_libro( wxCommandEvent &_event )  {
	
	ventana_info_libro   nueva_ventana( this, pos_real_libros[fila_libros] );
	nueva_ventana.ShowModal();
	
}

void ventana_principal::click_editar_libro( wxCommandEvent &_event )  {
	
	ventana_agregar_libro   nueva_ventana( this, pos_real_libros[fila_libros] );
	
	if ( nueva_ventana.ShowModal() == 1 ) {
		
		programa->set_cambios( true );
		this->refresh_libros( true );
		
	}
	
}

void ventana_principal::click_ver_detalles_socio( wxCommandEvent &_event )  {
	
	ventana_info_socio   nueva_ventana( this, pos_real_socios[fila_socios] );
	nueva_ventana.ShowModal();
	
}

void ventana_principal::click_editar_socio( wxCommandEvent &_event )  {
	
	ventana_agregar_socio   nueva_ventana( this, pos_real_socios[fila_socios] );
	
	if ( nueva_ventana.ShowModal() == 1 ) {
		
		programa->set_cambios( true );
		this->refresh_socios( true );
		
	}
	
}

// BOTONES
void ventana_principal::click_reg_prestamo( wxCommandEvent &_event )  {
	
	libro *lib = &( programa->libros.get_libro_pos( pos_real_libros[fila_libros] ) );
	socio *soc = &( programa->socios.get_socio_pos( pos_real_socios[fila_socios] ) );
	
	if ( soc->get_cant_a_devolver() > 2 ) {
		
		wxMessageBox( wxT("El socio seleccionado tiene 3 libros pendientes por devolver. No se puede realizar el préstamo."), wxT("Aviso") );
		
	} else if ( lib->get_prestado() == true ) {
		
		string msg = "El libro está prestado por lo que no se encuentra disponible. Su fecha de devolución es el ";
		msg += lib->get_fecha_devolucion().str_ddmmaaaa();
		
		
	} else if ( soc->push_prestamo( lib->get_codigo() ) == false ) {
		
		wxMessageBox( wxT("Se ha producido un error al intentar agregar el préstamo al socio."), wxT("Aviso") );
		
	} else {
		
		if ( lib->get_tipo_prestamo() == 1 ) {
			
			wxMessageBox( wxT("El libro está disponible sólo para consulta en sala de lectura. Recuerde reclamar su devolución."), wxT("Aviso") );
			
		}
		
		lib->set_prestado( true, soc->get_nro_socio() );
		
		bibliotecario *bib = programa->get_cuenta_activa();
		if ( bib != NULL ) {
			
			bib->sumar_prestamo();
			
		}
		
		programa->set_cambios( true );
		this->refresh_general();
		
		wxMessageBox( wxT("El préstamo se ha realizado de manera exitosa."), wxT("Operación finalizada") );
		
	}
	
}

void ventana_principal::click_reg_devolucion( wxCommandEvent &_event )  {
	
	libro *lib = &( programa->libros.get_libro_pos( pos_real_libros[fila_libros] ) );
	socio *soc = &( programa->socios.get_socio_pos( pos_real_socios[fila_socios] ) );
	
	if ( soc->libro_devuelto( lib->get_codigo() ) == false ) {
		
		wxMessageBox( wxT("El socio seleccionado no registra el préstamo del libro en cuestión."), wxT("Error") );
		
	} else {
		
		lib->set_prestado( false );
		
		programa->set_cambios( true );
		this->refresh_general();
		
		wxMessageBox( wxT("La devolución se ha realizado de manera exitosa."), wxT("Operación finalizada") );
		
	}
	
}

void ventana_principal::click_boton_agregar_libro( wxCommandEvent &_event )  {
	
	this->deseleccionar_todo();
	
	ventana_agregar_libro   nueva_ventana( this );
	
	if ( nueva_ventana.ShowModal() == 1 ) {
		
		programa->set_cambios( true );
		this->refresh_libros( true );
		
	}
	
}

void ventana_principal::click_boton_agregar_socio( wxCommandEvent &_event )  {
	
	this->deseleccionar_todo();
	
	ventana_agregar_socio   nueva_ventana( this );
	
	if ( nueva_ventana.ShowModal() == 1 ) {
		
		programa->set_cambios( true );
		this->refresh_socios( true );
		
	}
	
}

void ventana_principal::click_eliminar_libro( wxCommandEvent &_event )  {
	
	string aux;
	aux += "¿Seguro que desea eliminar \"";
	aux += programa->libros.get_libro_pos( pos_real_libros[fila_libros] ).get_titulo();
	aux += "\"?";
	
	if ( wxMessageBox( aux.c_str(), wxT("Eliminar libro..."), wxYES_NO ) == wxYES && fila_libros >= 0 ) {
		
		if ( programa->libros.pop_pos( pos_real_libros[fila_libros] ) == false ) {
			
			wxMessageBox( wxT("No se pudo eliminar el libro."), wxT("Aviso") );
			
		} else {
			
			programa->set_cambios( true );
			
			if ( fila_libros == programa->libros.get_cant_libros() ) {
				
				this->refresh_libros();
				
			} else {
				
				this->refresh_libros( true );
				
			}
			
		}
		
	}
	
}

void ventana_principal::click_eliminar_socio( wxCommandEvent &_event )  {
	
	string aux;
	aux += "¿Seguro que desea eliminar \"";
	aux += programa->socios.get_socio_pos( pos_real_socios[fila_socios] ).get_nombre_completo();
	aux += "\"?";
	
	if ( wxMessageBox( aux.c_str(), wxT("Eliminar socio..."), wxYES_NO ) == wxYES && fila_socios >= 0 ) {
		
		int pendientes = programa->socios.get_socio_pos( pos_real_socios[fila_socios] ).get_cant_a_devolver();
		
		if ( pendientes > 0 ) {
			
			if ( wxMessageBox( wxT("El socio posee libros pendientes por devolver, ¿desea eliminarlo de todos modos?"), wxT("Eliminar socio..."), wxYES_NO ) == wxYES ) {
				
				if ( programa->socios.pop_pos( pos_real_socios[fila_socios] ) == false ) {
					
					wxMessageBox( wxT("No se pudo eliminar el socio."), wxT("Aviso") );
					
				} else {
					
					programa->set_cambios( true );
					
					if ( fila_socios == programa->socios.get_cant_socios() ) {
						
						this->refresh_socios();
						
					} else {
						
						this->refresh_socios( true );
						
					}
					
				}
				
			}
			
		} else if ( programa->socios.pop_pos( pos_real_socios[fila_socios] ) == false ) {
			
			wxMessageBox( wxT("No se pudo eliminar el socio."), wxT("Aviso") );
			
		} else {
			
			programa->set_cambios( true );
			
			if ( fila_socios == programa->socios.get_cant_socios() ) {
				
				this->refresh_socios();
				
			} else {
				
				this->refresh_socios( true );
				
			}
			
		}
		
	}
	
}
//
// NUEVOS

