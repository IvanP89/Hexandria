///////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_agregar_usuario.h
// Propósito:   Interfaz para cargar o editar cuentas de usuario.
// Autor:       Iván Pizarro.
//
// En este archivo se declara el diseño de la clase que que define a la ventana
// que provee una interfaz para definir o cambiar la cuenta de usuario de un
// bibliotecario.
///////////////////////////////////////////////////////////////////////////////

#ifndef VENTANA_AGREGAR_USUARIO_H
#define VENTANA_AGREGAR_USUARIO_H

#include "Ventanas.h"
#include "ventana_agregar_bibliotecario.h"

class ventana_agregar_bibliotecario;

///////////////////////////////////////////////////////////////////////////////

class ventana_agregar_usuario : public vAgregarUsuario {

protected:
	void click_boton_cancelar( wxCommandEvent &_event );
	void click_boton_aceptar( wxCommandEvent &_event );
	void redibujar_ventana();
	bool ya_existe_usuario() const;
	
protected:
	ventana_agregar_bibliotecario *anterior;
	
public:
	ventana_agregar_usuario( ventana_agregar_bibliotecario *_parent );
	~ventana_agregar_usuario();
	
};

#endif

