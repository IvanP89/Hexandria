///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_estadisticas.h
// Prop�sito:   Visualizaci�n de estad�sticas de los objetos.
// Autor:       Iv�n Pizarro.
//
// En este archivo se declara el dise�o de la clase que que define a la ventana
// mediante la cual se pueden observar las estad�sticas basadas en algunos de
// los datos m�s relevantes de los objetos del programa.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_ESTADISTICAS_H
#define VENTANA_ESTADISTICAS_H

#include "Ventanas.h"

#include "Core\programa.h"

///////////////////////////////////////////////////////////////////////////////

class ventana_estadisticas : public vEstadisticas {

protected:
	void click_ver_ocultar_libros( wxCommandEvent &_event );
	void cambio_cant_top_libros( wxCommandEvent &_event );
	void cambio_cant_top_autores( wxCommandEvent &_event );
	void click_ver_ocultar_socios( wxCommandEvent &_event );
	void cambio_cant_top_socios_prestamos( wxCommandEvent &_event );
	void cambio_cant_top_socios_ant( wxCommandEvent &_event );
	void click_ver_ocultar_bib( wxCommandEvent &_event );
	void click_cerrar( wxCommandEvent &_event );
	void refresh_libros();
	void refresh_socios();
	void refresh_bibliotecarios();
	void redibujar_ventana();
	
protected:
	Programa *programa;
	
public:
	ventana_estadisticas( wxWindow *_parent );
	~ventana_estadisticas();
};

#endif

