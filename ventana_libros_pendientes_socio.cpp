#include "ventana_libros_pendientes_socio.h"
#include "Core\personas.h"
#include "Core\bibliografia.h"

ventana_libros_pendientes_socio::ventana_libros_pendientes_socio( ventana_socios *_parent ): vDevolverLibro( _parent ) {
	
	anterior = _parent;
	socio soc = anterior->programa->socios.get_socio_pos( anterior->pos_real[anterior->fila] );
	int tamanyo = soc.get_cant_a_devolver();
	for ( int i=0;i<tamanyo;i++ ) { 
		
		codigos.push_back( soc.get_a_devolver( i ) );
		eleccion_pendientes->Append( anterior->programa->libros.get_libro( codigos[i] ).get_titulo().c_str() );
		
	}
	
}

ventana_libros_pendientes_socio::~ventana_libros_pendientes_socio() {
	
}

void ventana_libros_pendientes_socio::click_boton_cancelar (wxCommandEvent & _event) {
	
	EndModal( -1 );
	
}

void ventana_libros_pendientes_socio::click_boton_aceptar (wxCommandEvent & _event) {
	
	bool se_eligio_uno = false;
	
	socio *soc = &( anterior->programa->socios.get_socio_pos( anterior->pos_real[anterior->fila] ) );
	libro *lib;
	
	int tamanyo = soc->get_cant_a_devolver();
	for ( int i=0;i<tamanyo;i++ ) {
		
		if ( eleccion_pendientes->IsChecked( i ) ) {
			
			lib = &( anterior->programa->libros.get_libro( codigos[i] ) );
			soc->libro_devuelto( codigos[i] );
			lib->set_prestado( false );
			se_eligio_uno = true;
			
		}
		
	}
	
	if ( se_eligio_uno == false ) {
		
		EndModal( -1 );
		
	}
	
	EndModal( 1 );
	
}

