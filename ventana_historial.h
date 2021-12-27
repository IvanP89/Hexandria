///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_historial.h
// Propósito:   Interfaz para visualizar el historial de los préstamos.
// Autor:       Iván Pizarro.
//
// En este archivo se declara el diseño de la clase que que define a la ventana
// para visualizar el historial de los préstamos realizados por un socio o los
// socios que han solicitado el préstamo de un determinado libro.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_HISTORIAL_H
#define VENTANA_HISTORIAL_H

#include "ventana_ayuda.h"
#include "Ventanas.h"

#include "Core\bibliografia.h"
#include "Core\personas.h"

#include <vector>

using namespace std;

///////////////////////////////////////////////////////////////////////////////

class ventana_historial : public vHistorial {

protected:
	// SELECCION
	void seleccion( const bool &_seleccionado = true );
	// EVENTOS GRILLA
	void refresh( const bool &_conservar_seleccion = false );
	void click_izq_grilla( wxGridEvent &_event );
	void Dclick_grilla( wxGridEvent &_event );
	// BARRA DE HERRAMIENTAS
	void click_boton_detalles( wxCommandEvent &_event );
	void click_boton_estadisticas( wxCommandEvent &_event );
	void cambio_orden( wxCommandEvent &_event );
	void click_buscar( wxCommandEvent &_event );
	void click_boton_restaurar( wxCommandEvent &_event );
	void click_boton_ayuda( wxCommandEvent &_event );
	void click_boton_CDU( wxCommandEvent &_event );
	void principal_elegido( wxCommandEvent &_event );
	void sub_1_elegido( wxCommandEvent &_event );
	void sub_2_elegido( wxCommandEvent &_event );
	// BOTONES VENTANA
	void click_boton_cerrar( wxCommandEvent &_event );
	// CARGA DE IMAGEN
	void cargar_imagen( const string &_path );
	// ORDENAR
	void sort_socios( const int &_criterio );
	void sort_libros( const int &_criterio );
	// REDIBUJAR
	void redibujar_ventana();
	
protected:
	vector<prestamo> historial;
	vector<libro> libros;
	vector<socio> socios;
	int fila;
	vector<int> pos_real;
	bool historial_socio;
	ventana_ayuda *Ayuda;
	
public:
	ventana_historial( wxWindow *_parent, const int &_codigo, const bool HistorialSocio );
	~ventana_historial();
	
};

#endif

