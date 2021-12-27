///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_login.h
// Prop�sito:   Ventana para iniciar sesi�n en el programa.
// Autor:       Iv�n Pizarro.
//
// En este archivo se declara el dise�o de la clase que que define a la ventana
// mediante la cual se inicia la sesi�n del programa a atrav�s de un sistema
// de usuario y contrase�a.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_LOGIN_H
#define VENTANA_LOGIN_H

#include "Ventanas.h"
#include "ventana_principal.h"

#include "Core\programa.h"

///////////////////////////////////////////////////////////////////////////////

class ventana_login : public vLogin {

protected:
	void enter_presionado( wxCommandEvent &_event ) ;
	void click_boton_salir( wxCommandEvent &_event ) ;
	void click_boton_aceptar( wxCommandEvent &_event ) ;
	void se_cierra( wxCloseEvent &_event ) ;
	void redibujar_ventana();
	
protected:
	Singleton *programa;
	
public:
	ventana_login( ventana_principal *_parent );
	~ventana_login();
	
};

#endif

