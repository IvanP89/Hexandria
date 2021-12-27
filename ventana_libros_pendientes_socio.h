#ifndef VENTANA_LIBROS_PENDIENTES_SOCIO_H
#define VENTANA_LIBROS_PENDIENTES_SOCIO_H
#include "Ventanas.h"
#include <vector>
#include "ventana_socios.h"
using namespace std;

class ventana_libros_pendientes_socio : public vDevolverLibro {

protected:
	void click_boton_cancelar( wxCommandEvent &_event );
	void click_boton_aceptar( wxCommandEvent &_event );
	
protected:
	ventana_socios *anterior;
	vector<int> codigos;
	
public:
	ventana_libros_pendientes_socio( ventana_socios *_parent );
	~ventana_libros_pendientes_socio();
	
};

#endif

