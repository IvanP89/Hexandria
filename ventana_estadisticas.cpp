//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_estadisticas.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en
// ventana_estadisticas.h
//////////////////////////////////////////////////////////////////////////////

#include "ventana_estadisticas.h"

#include "Core\bibliografia.h"
#include "Core\personas.h"

#include <cstdlib>

using namespace std;

//////////////////////////////////////////////////////////////////////////////

ventana_estadisticas::ventana_estadisticas( wxWindow *_parent ): vEstadisticas( _parent ) {
	
	programa = new ProgramaSombra( Singleton::get_base_activa() );
	
	this->refresh_libros();
	this->refresh_socios();
	
	if ( programa->get_cuenta_activa() == NULL ) {
		
		panel_emergente_bib->Show();
		this->refresh_bibliotecarios();
		this->redibujar_ventana();
		
	}
	
}

ventana_estadisticas::~ventana_estadisticas() {
	
	delete programa;
	
}

void ventana_estadisticas::refresh_libros ( ) {
	
	// LIBROS MAS LEIDOS
	programa->libros.sort( LibrosPorPrestamos );
	
	int cuantos = atoi( cant_top_libros->GetString( cant_top_libros->GetSelection() ).c_str() );
	if ( cuantos > programa->libros.get_cant_libros() ) {
		
		cuantos = programa->libros.get_cant_libros();
		
	}
	
	cuadro_top_libros->Clear();
	
	for ( int i=0;i<cuantos;i++ ) { 
		
		cuadro_top_libros->Insert( programa->libros.get_libro_pos( i ).get_titulo().c_str(), i );
		
	}
	
	// AUTORES MÁS SOLICITADOS
	programa->autores.sort( AutoresPorPrestamos );
	
	cuantos = atoi( cant_top_autores->GetString( cant_top_autores->GetSelection() ).c_str() );
	if ( cuantos > programa->autores.size() ) {
		
		cuantos = programa->autores.size();
		
	}
	
	cuadro_top_autores->Clear();
	
	for ( int i=0;i<cuantos;i++ ) { 
		
		cuadro_top_autores->Insert( programa->autores.get_autor_pos( i ).get_nombre().c_str(), i );
		
	}
	
}

void ventana_estadisticas::refresh_socios ( ) {
	
	// SOCIOS QUE MÁS LIBROS RETIRARON
	programa->socios.sort( SociosPorLecturas );
	
	int cuantos = atoi( cant_top_socios_prestamos->GetString( cant_top_socios_prestamos->GetSelection() ).c_str() );
	if ( cuantos > programa->socios.get_cant_socios() ) {
		
		cuantos = programa->socios.get_cant_socios();
		
	}
	
	cuadro_top_socios_prestamos->Clear();
	
	for ( int i=0;i<cuantos;i++ ) { 
		
		cuadro_top_socios_prestamos->Insert( programa->socios.get_socio_pos( i ).get_nombre_completo().c_str(), i );
		
	}
	
	// SOCIOS CON MÁS ANTIGÜEDAD
	programa->socios.sort( SociosPorAntig );
	
	cuantos = atoi( cant_top_socios_ant->GetString( cant_top_socios_ant->GetSelection() ).c_str() );
	if ( cuantos > programa->socios.get_cant_socios() ) {
		
		cuantos = programa->socios.get_cant_socios();
		
	}
	
	cuadro_top_socios_antig->Clear();
	
	for ( int i=0;i<cuantos;i++ ) { 
		
		cuadro_top_socios_antig->Insert( programa->socios.get_socio_pos( i ).get_nombre_completo().c_str(), i );
		
	}
	
}

void ventana_estadisticas::refresh_bibliotecarios ( ) {
	
	// BIBLIOTECARIOS QUE EFECTUARON MÁS PRESTAMOS
	programa->bibliotecarios.sort( BibPorPrestamos );
	cuadro_bib_prestamos->Clear();
	int cuantos = programa->bibliotecarios.size();
	for ( int i=0;i<cuantos;i++ ) { 
		
		cuadro_bib_prestamos->Insert( programa->bibliotecarios.get_bibliotecario_pos( i ).get_nombre_completo().c_str(), i );
		
	}
	
	// BIBLIOTECARIOS CON MÁS ANTIGÜEDAD
	programa->bibliotecarios.sort( BibPorAntig );
	cuadro_bib_antiguedad->Clear();
	cuantos = programa->bibliotecarios.size();
	for ( int i=0;i<cuantos;i++ ) { 
		
		cuadro_bib_antiguedad->Insert( programa->bibliotecarios.get_bibliotecario_pos( i ).get_nombre_completo().c_str(), i );
		
	}
	
	// BIBLIOTECARIOS CON MAYOR SALARIO
	programa->bibliotecarios.sort( BibPorSalario );
	cuadro_bib_salario->Clear();
	cuantos = programa->bibliotecarios.size();
	for ( int i=0;i<cuantos;i++ ) { 
		
		cuadro_bib_salario->Insert( programa->bibliotecarios.get_bibliotecario_pos( i ).get_nombre_completo().c_str(), i );
		
	}
	
}

void ventana_estadisticas::click_ver_ocultar_libros( wxCommandEvent &_event )  {
	
	panel_libros->Show( !panel_libros->IsShown() );
	this->redibujar_ventana();
	
}

void ventana_estadisticas::cambio_cant_top_libros( wxCommandEvent &_event )  {
	
	this->refresh_libros();
	
}

void ventana_estadisticas::cambio_cant_top_autores( wxCommandEvent &_event )  {
	this->refresh_libros();
}

void ventana_estadisticas::click_ver_ocultar_socios( wxCommandEvent &_event )  {
	
	panel_socios->Show( !panel_socios->IsShown() );
	this->redibujar_ventana();
	
}

void ventana_estadisticas::cambio_cant_top_socios_prestamos( wxCommandEvent &_event )  {
	
	this->refresh_socios();
	
}

void ventana_estadisticas::cambio_cant_top_socios_ant( wxCommandEvent &_event )  {
	
	this->refresh_socios();
	
}

void ventana_estadisticas::click_ver_ocultar_bib( wxCommandEvent &_event )  {
	
	panel_bibliotecarios->Show( !panel_bibliotecarios->IsShown() );
	this->redibujar_ventana();
	
}

void ventana_estadisticas::click_cerrar( wxCommandEvent &_event )  {
	
	EndModal( -1 );
	
}

void ventana_estadisticas::redibujar_ventana ( ) {
	
	wxSize tamanyo = this->GetSize();
	tamanyo.SetHeight( tamanyo.GetHeight() +1 );
	this->SetSize( tamanyo );
	tamanyo.SetHeight( tamanyo.GetHeight() -1 );
	this->SetSize( tamanyo );
	this->Layout();
	
}

