//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_info_bibliotecario.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en
// ventana_info_bibliotecario.h
//////////////////////////////////////////////////////////////////////////////

#include "ventana_info_bibliotecario.h"

#include "Core\personas.h"
#include "Core\utilidades.h"

#include <wx/utils.h>
#include <wx/bitmap.h>

using namespace std;

//////////////////////////////////////////////////////////////////////////////

ventana_info_bibliotecario::ventana_info_bibliotecario ( wxWindow *_parent, const int &_pos ): vInfoBibliotecario( _parent ) {
	
	Programa *programa = Singleton::get_base_activa();
	
	const bibliotecario* const bib = &( programa->bibliotecarios.get_bibliotecario_pos( _pos ) );
	
	renglon_nombre->SetValue( bib->get_nombre_completo().c_str() );
	renglon_dni->SetValue( bib->get_dni_str().c_str() );
	renglon_tel->SetValue( bib->get_tel().c_str() );
	renglon_domicilio->SetValue( bib->get_domicilio().c_str() );
	renglon_edad->SetValue( bib->get_edad_str().c_str() );
	renglon_ingreso->SetValue( bib->get_fecha_ingreso().str_ddmmaaaa().c_str() );
	renglon_salario->SetValue( bib->get_salario_str().c_str() );
	renglon_prestamos->SetValue( bib->get_cant_prestamos_str().c_str() );
	renglon_cur->SetValue( bib->get_curriculum().c_str() );
	this->cargar_imagen( bib->get_path_foto() );
	
}

ventana_info_bibliotecario::~ventana_info_bibliotecario ( ) {
	
}

void ventana_info_bibliotecario::click_boton_cerrar( wxCommandEvent& event )  {
	
	EndModal( -1 );
	
}

void ventana_info_bibliotecario::cargar_imagen ( const string &_path ) {
	
	string dir_imagen = _path;
	string extension = dir_imagen.substr( dir_imagen.find_last_of( '.' ) );
	char a = extension[1]; // 'a' contiene ahora la primera letra de la extension (extension[0] es el punto).
	a = tolower(a);
	wxBitmap *imagen;
	switch ( a ) {
	case 'j':
		imagen = new wxBitmap( dir_imagen.c_str(), wxBITMAP_TYPE_JPEG );
		break;
		
	case 'p':
		imagen = new wxBitmap( dir_imagen.c_str(), wxBITMAP_TYPE_PNG );
		break;
		
	case 'b':
		imagen = new wxBitmap( dir_imagen.c_str(), wxBITMAP_TYPE_BMP );
		
	}
	
	*imagen = EditarImagen::ajustar_tamanyo( *imagen );
	foto_bibliotecario->SetBitmap( *imagen );
	
}

