///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_login.h
// Propósito:   Ventana para iniciar sesión en el programa.
// Autor:       Iván Pizarro.
//
// En este archivo se declara el diseño de la clase que que define a la ventana
// mediante la cual se inicia la sesión del programa a através de un sistema
// de usuario y contraseña.
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

