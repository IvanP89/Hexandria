//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_agregar_socio.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en
// ventana_agregar_socio.h
//////////////////////////////////////////////////////////////////////////////

#include "ventana_agregar_socio.h"

#include <wx/filedlg.h>
#include <wx/msgdlg.h>

#include <windows.h>
#include <shlobj.h>
#include <fstream>
#include <cstdlib>

using namespace std;

//////////////////////////////////////////////////////////////////////////////

ventana_agregar_socio::ventana_agregar_socio( wxWindow *_parent, const int &_pos ): vAgregarSocio( _parent ) {
	
	anterior = Singleton::get_base_activa();
	pos = _pos;
	
	if ( pos >= 0 ) { // Se abre en modo edición.
		
		this->SetTitle( wxT("Editar socio...") );
		
		const socio* soc;
		
		soc = &( anterior->socios.get_socio_pos( pos ) );
		
		renglon_apellido->SetValue( soc->get_apellido().c_str() );
		renglon_nombres->SetValue( soc->get_nombre().c_str() );
		renglon_dni->SetValue( soc->get_dni_str().c_str() );
		renglon_tel->SetValue( soc->get_tel().c_str() );
		renglon_domicilio->SetValue( soc->get_domicilio().c_str() );
		
		dia_nac->SetSelection( soc->get_fecha_nac().get_dia() );
		mes_nac->SetSelection( soc->get_fecha_nac().get_mes() );
		anyo_nac->SetValue( soc->get_fecha_nac().get_anyo_str() );
		
		panel_fecha_ingreso->Hide();
		
		renglon_foto->SetValue( soc->get_path_foto().c_str() );
		
	}
	
}

ventana_agregar_socio::~ventana_agregar_socio() {
	
}

void ventana_agregar_socio::fecha_ingreso_actual( wxCommandEvent &_event )  {
	
	ingreso_emergente->Hide();
	this->redibujar_ventana();
	
}

void ventana_agregar_socio::fecha_ingreso_manual( wxCommandEvent &_event )  {
	
	ingreso_emergente->Show();
	this->redibujar_ventana();
	
}

void ventana_agregar_socio::click_boton_explorar( wxCommandEvent &_event )  {
	
	string ruta;
	
	char directorio_default[MAX_PATH];
	HRESULT encontro_ruta_escritorio = SHGetFolderPath( NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, directorio_default );
	
	if ( encontro_ruta_escritorio == S_OK ) {
		
		ruta = wxFileSelector( wxT("Ubicación del archivo..."), directorio_default, wxT(""), wxT(""), wxT("Archivos de imagen (*.jpg;*.png;*.bmp)|*jpg;*.png;*.bmp|Imagen jpg (*.jpg)|*.jpg|Imagen png (*.png)|*.png|Imagen bmp (*.bmp)|*.bmp"), wxFD_OPEN | wxFD_FILE_MUST_EXIST ).c_str();
		
	} else {
		
		ruta = wxFileSelector( wxT("Ubicación del archivo..."), wxT(""), wxT(""), wxT(""), wxT("Archivos de imagen (*.jpg;*.png;*.bmp)|*jpg;*.png;*.bmp|Imagen jpg (*.jpg)|*.jpg|Imagen png (*.png)|*.png|Imagen bmp (*.bmp)|*.bmp"), wxFD_OPEN | wxFD_FILE_MUST_EXIST ).c_str();
		
	}
	
	renglon_foto->SetValue( ruta.c_str() );
	
}

void ventana_agregar_socio::click_cancelar( wxCommandEvent &_event )  {
	
	EndModal( -1 );
	
}

void ventana_agregar_socio::click_aceptar( wxCommandEvent &_event )  {
	
	string apellido = renglon_apellido->GetValue().c_str();
	string nombre = renglon_nombres->GetValue().c_str();
	string dni = renglon_dni->GetValue().c_str();
	string aingreso = anyo_ingreso->GetValue().c_str();
	
	if ( nombre == "" ) {
		
		wxMessageBox( wxT("Debe ingresar un nombre."), wxT("Campo incompleto.") );
		
	} else if ( nombre[0] == ' ' ) {
		
		wxMessageBox( wxT("El nombre no puede comenzar con un espacio."), wxT("Campo mal completado.") );
		
	} else if ( apellido == "" ) {
		
		wxMessageBox( wxT("Debe ingresar un apellido."), wxT("Campo incompleto.") );
		
	} else if ( apellido[0] == ' ' ) {
		
		wxMessageBox( wxT("El apellido no puede comenzar con un espacio."), wxT("Campo mal completado.") );
		
	}else if ( dni == "" ) {
		
		wxMessageBox( wxT("Debe ingresar un DNI."), wxT("Campo incompleto.") );
		
	} else if ( dni[0] == ' ' ) {
		
		wxMessageBox( wxT("El DNI no puede comenzar con un espacio."), wxT("Campo mal completado.") );
		
	} else if ( atoi( dni.c_str() ) == 0 && dni != "0" ) {
		
		wxMessageBox( wxT("El DNI debe contener sólo caracteres numéricos."), wxT("Campo mal completado.") );
		
	}else if ( ingreso_emergente->IsShown() && aingreso == "" ) {
		
		wxMessageBox( wxT("Debe ingresar un año de ingreso si ha seleccionado ingreso manual."), wxT("Campo incompleto.") );
		
	} else if ( ingreso_emergente->IsShown() && aingreso[0] == ' ' ) {
		
		wxMessageBox( wxT("El año de ingreso no puede comenzar con un espacio."), wxT("Campo mal completado.") );
		
	} else if ( ingreso_emergente->IsShown() && atoi( anyo_ingreso->GetValue().c_str() ) == 0 && dni != "0" ) {
		
		wxMessageBox( wxT("El año de ingreso debe contener sólo caracteres numéricos."), wxT("Campo mal completado.") );
		
	} else {
		
		if ( pos < 0 ) { // Si está en modo agregar...
			
			nuevo.set_apellido( apellido );
			nuevo.set_nombre( nombre );
			nuevo.set_dni( atoi( dni.c_str() ) );
			nuevo.set_tel( renglon_tel->GetValue().c_str() );
			nuevo.set_domicilio( renglon_domicilio->GetValue().c_str() );
			nuevo.set_fecha_nac( dia_nac->GetSelection(), mes_nac->GetSelection(), atoi( anyo_nac->GetValue().c_str() ) );
			
			if ( boton_ingreso_2->GetValue() == true ) {
				
				nuevo.set_fecha_ingreso( dia_ingreso->GetSelection(), mes_ingreso->GetSelection(), atoi( anyo_ingreso->GetValue().c_str() ) );
				
			} else {
				
				nuevo.set_fecha_ingreso( fecha::get_actual() );
				
			}
			
			if ( renglon_foto->GetValue() != "" ) {
				
				this->copiar_imagen( renglon_foto->GetValue().c_str() );
				
			}			
			
			nuevo.set_nro_socio();
			
			anterior->socios.push( nuevo );
			
			EndModal( 1 );
			
		} else { // Si está en modo edición...
			
			socio* soc;
			
			soc = &( anterior->socios.get_socio_pos( pos ) );
			
			soc->set_apellido( apellido );
			soc->set_nombre( nombre );
			soc->set_dni( atoi( dni.c_str() ) );
			soc->set_tel( renglon_tel->GetValue().c_str() );
			soc->set_domicilio( renglon_domicilio->GetValue().c_str() );
			soc->set_fecha_nac( dia_nac->GetSelection(), mes_nac->GetSelection(), atoi( anyo_nac->GetValue().c_str() ) );
			
			if ( boton_ingreso_2->GetValue() == true ) {
				
				soc->set_fecha_ingreso( dia_ingreso->GetSelection(), mes_ingreso->GetSelection(), atoi( anyo_ingreso->GetValue().c_str() ) );
				
			}
			
			soc->set_path_foto( renglon_foto->GetValue().c_str() );
			if ( soc->get_path_foto() != "" && soc->get_path_foto() != "Img\\Resources\\no-user.png" ) {
				
				this->copiar_imagen( soc->get_path_foto() );
				
			}
			
			EndModal( 1 );
			
		}
		
	}
	
}

bool ventana_agregar_socio::copiar_imagen ( const string &_fuente ) {
	
	string destino = "Img\\Local\\Socios\\";
	destino += renglon_dni->GetValue().c_str();
	destino += _fuente.substr( _fuente.find_last_of( '.' ) );
	
	if ( _fuente != destino ) {
		
		ifstream lectura( _fuente.c_str(), ios::binary );
		if ( !lectura.is_open() ) {
			
			return false;
			
		}
		ofstream escritura( destino.c_str(), ios::binary );
		if ( !escritura.is_open() ) {
			
			return false;
			
		}
		
		escritura<<lectura.rdbuf();
		
		lectura.close();
		escritura.close();
		
		nuevo.set_path_foto( destino );
		
	} else {
		
		return false;
		
	}
	
	return true;
	
}

void ventana_agregar_socio::redibujar_ventana ( ) {
	
//	wxSize tamanyo = this->GetSize();
//	tamanyo.SetHeight( tamanyo.GetHeight() +1 );
//	this->SetSize( tamanyo );
//	tamanyo.SetHeight( tamanyo.GetHeight() -1 );
//	this->SetSize( tamanyo );
	this->Layout();
	this->Fit();
	
}

