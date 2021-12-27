////////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_principal.h
// Propósito:   Ventana principal del programa.
// Autor:       Iván Pizarro.
//
// En este archivo se declara el diseño de la clase que corresponde a la ventana
// principal del programa.
////////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_PRINCIPAL_H
#define VENTANA_PRINCIPAL_H

#include "Ventanas.h"
#include "Core\programa.h"
#include "ventana_ayuda.h"

#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

class ventana_principal : public vPrincipal {

protected:
	// CLOSE EVENT
	void se_cierra_vPrincipal( wxCloseEvent &_event ) ;
	void click_salir( wxCommandEvent &_event ) ;
	// GUARDAR
	void click_guardar( wxCommandEvent &_event ) ;
	// ABRIR VENTANAS
	void click_abrir_libros( wxCommandEvent &_event ) ;
	void click_abrir_autores( wxCommandEvent &_event ) ;
	void click_abrir_socios( wxCommandEvent &_event ) ;
	void click_abrir_bib( wxCommandEvent &_event ) ;
	void click_ver_ayuda( wxCommandEvent &_event ) ;
	void click_acerca_de( wxCommandEvent &_event ) ;
	void click_ver_estadisticas( wxCommandEvent &_event ) ;
	// BUSQUEDA
	void click_buscar_libro( wxCommandEvent &_event ) ;
	void click_buscar_socio( wxCommandEvent &_event ) ;
	// GRILLA
	void refresh_libros( const bool &_conservar_seleccion = false );
	void refresh_socios( const bool &_conservar_seleccion = false );
	void refresh_general();
	void click_iz_libro( wxGridEvent &_event ) ;
	void click_iz_socio( wxGridEvent &_event ) ;
	void Dclick_libro( wxGridEvent &_event ) ;
	void Dclick_socio( wxGridEvent &_event ) ;
	void click_der_libro( wxGridEvent &_event ) ;
	void click_der_socio( wxGridEvent &_event ) ;
	// SELECCION
	void seleccion_libro( const bool &_seleccionado = true );
	void seleccion_socio( const bool &_seleccionado = true );
	void deseleccionar_todo();
	// MENU CONTEXTUAL GRILLA
	void click_ver_detalles_libro( wxCommandEvent &_event ) ;
	void click_ver_detalles_socio( wxCommandEvent &_event ) ;
	void click_editar_libro( wxCommandEvent &_event ) ;
	void click_editar_socio( wxCommandEvent &_event ) ;
	// BOTONES
	void click_reg_prestamo( wxCommandEvent &_event ) ;
	void click_reg_devolucion( wxCommandEvent &_event ) ;
	void click_boton_agregar_libro( wxCommandEvent &_event ) ;
	void click_boton_agregar_socio( wxCommandEvent &_event ) ;
	void click_eliminar_libro( wxCommandEvent &_event ) ;
	void click_eliminar_socio( wxCommandEvent &_event ) ;
	
protected:
	Singleton *programa;
	int fila_libros;     // Para eventos de wxgrid.
	int fila_socios;     // Para eventos de wxgrid.
	vector<int> pos_real_libros;
	vector<int> pos_real_socios;
	ventana_ayuda *Ayuda;
	
public:
	ventana_principal( wxWindow *parent );
	~ventana_principal();
	
};

#endif

