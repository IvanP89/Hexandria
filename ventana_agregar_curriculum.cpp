//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_agregar_curriculum.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en
// ventana_agregar_curriculum.h
//////////////////////////////////////////////////////////////////////////////

#include "ventana_agregar_curriculum.h"

#include "Core\personas.h"

#include <wx/filedlg.h>

#include <string>
#include <fstream>
#include <windows.h>
#include <shlobj.h>

using namespace std;

//////////////////////////////////////////////////////////////////////////////

ventana_agregar_curriculum::ventana_agregar_curriculum( ventana_agregar_bibliotecario *_parent ): vAgregarCurriculum( _parent ) {
	
	anterior = _parent;
	if ( anterior->pos >= 0 ) { // Modo edición.
		
		this->SetTitle( wxT("Editar currículum...") );
		renglon_cur->SetValue( anterior->nuevo.get_curriculum().c_str() );
		
	}
	
}

ventana_agregar_curriculum::~ventana_agregar_curriculum() {
	
}

void ventana_agregar_curriculum::click_boton_explorar( wxCommandEvent &_event )  {
	
	string ruta, aux, contenido;
	
	char directorio_default[MAX_PATH];
	HRESULT encontro_ruta_escritorio = SHGetFolderPath( NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, directorio_default );
	
	if ( encontro_ruta_escritorio == S_OK ) {
		
		ruta = wxFileSelector( wxT("Ubicación del archivo..."), directorio_default, wxT(""), wxT(""), wxT("Archivos de texto (*.txt)|*.txt"), wxFD_OPEN | wxFD_FILE_MUST_EXIST ).c_str();
		
	} else {
		
		ruta = wxFileSelector( wxT("Ubicación del archivo..."), wxT(""), wxT(""), wxT(""), wxT("Archivos de texto (*.txt)|*.txt"), wxFD_OPEN | wxFD_FILE_MUST_EXIST ).c_str();
		
	}
	
	renglon_path->SetValue( ruta.c_str() );
	
	ifstream archi( ruta.c_str() );
	while ( getline( archi, aux ) ) {
		
		contenido += aux;
		contenido += "\n";
		
	}
	
	if ( contenido.size() > 9999 ) {
		
		contenido = contenido.substr( 0, 9999 );
		
	}
	renglon_cur->SetValue( contenido.c_str() );
	
	archi.close();
	
}

void ventana_agregar_curriculum::click_boton_aceptar( wxCommandEvent &_event )  {
	
	if ( anterior->pos >= 0 ) { // Modo edición.
		
		string curriculum_nuevo = renglon_cur->GetValue().c_str();
		
		if ( curriculum_nuevo == anterior->nuevo.get_curriculum() ) {
			
			EndModal( -1 );
			
		}
		
		anterior->nuevo.set_curriculum( curriculum_nuevo );
		
		EndModal( 1 );
		
	} else { // Modo agregar.
		
		string curriculum_nuevo = renglon_cur->GetValue().c_str();
		
		if ( curriculum_nuevo.size() > 0 ) {
			
			anterior->nuevo.set_curriculum( curriculum_nuevo );
			EndModal( 1 );
			
		}
		
		EndModal( -1 );
		
	}
	
}

void ventana_agregar_curriculum::click_boton_cancelar( wxCommandEvent &_event )  {
	
	EndModal( -1 );
	
}

