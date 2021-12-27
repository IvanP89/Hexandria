//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_agregar_bibliotecario.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en
// ventana_agregar_bibliotecario.h
//////////////////////////////////////////////////////////////////////////////

#include "ventana_agregar_bibliotecario.h"

#include "Core\programa.h"

#include <wx/filedlg.h>
#include <wx/msgdlg.h>

#include <string>
#include <fstream>
#include <windows.h>
#include <shlobj.h>
#include <cstdlib>

using namespace std;

//////////////////////////////////////////////////////////////////////////////

ventana_agregar_bibliotecario::ventana_agregar_bibliotecario( wxWindow *_parent, const int &_pos ): vAgregarBibliotecario( _parent ) {
	
	pos = _pos;
	programa = Singleton::get_base_activa();
	
	if ( pos >= 0 ) { // Se abre en modo edición.
		
		this->SetTitle( wxT("Editar bibliotecario...") );
		boton_cargar_cur->SetLabel( wxT("Editar...") );
		boton_generar_cuenta->SetLabel( wxT("Cambiar...") );
		panel_fecha_ingreso->Hide();
		aviso_cta_no->Hide();
		
		const bibliotecario* const bib = &( programa->bibliotecarios.get_bibliotecario_pos( pos ) );
		
		renglon_apellido->SetValue( bib->get_apellido().c_str() );
		renglon_nombres->SetValue( bib->get_nombre().c_str() );
		renglon_dni->SetValue( bib->get_dni_str().c_str() );
		renglon_tel->SetValue( bib->get_tel().c_str() );
		renglon_domicilio->SetValue( bib->get_domicilio().c_str() );
		
		dia_nac->SetSelection( bib->get_fecha_nac().get_dia() );
		mes_nac->SetSelection( bib->get_fecha_nac().get_mes() );
		anyo_nac->SetValue( bib->get_fecha_nac().get_anyo_str() );
		
		renglon_foto->SetValue( bib->get_path_foto().c_str() );
		renglon_salario->SetValue( bib->get_salario_str().c_str() );
		
		nuevo = *bib;
		
	}
	
}

ventana_agregar_bibliotecario::~ventana_agregar_bibliotecario() {
	
}

void ventana_agregar_bibliotecario::fecha_ingreso_actual( wxCommandEvent &_event )  {
	
	ingreso_emergente->Hide();
	this->redibujar_ventana();
	
}

void ventana_agregar_bibliotecario::fecha_ingreso_manual( wxCommandEvent &_event )  {
	
	ingreso_emergente->Show();
	this->redibujar_ventana();
	
}

void ventana_agregar_bibliotecario::click_boton_explorar( wxCommandEvent &_event )  {
	
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

void ventana_agregar_bibliotecario::click_boton_cargar_cur( wxCommandEvent &_event )  {
	
	ventana_agregar_curriculum   nueva_ventana( this );
	if ( nueva_ventana.ShowModal() >= 0 ) {
		
		aviso_carga_cur->Show();
		this->redibujar_ventana();
		
	}
	
}

void ventana_agregar_bibliotecario::click_boton_generar_cuenta( wxCommandEvent &_event )  {
	
	ventana_agregar_usuario   nueva_ventana( this );
	if ( nueva_ventana.ShowModal() >= 0 ) {
		
		aviso_cta_si->Show();
		aviso_cta_no->Hide();
		this->redibujar_ventana();
		
	}
	
}

void ventana_agregar_bibliotecario::click_aceptar( wxCommandEvent &_event )  {
	
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
		
	} else if ( nuevo.get_cta_usuario() == "" ) {
		
		wxMessageBox( wxT("Debe crear una cuenta de usuario para el bibliotecario."), wxT("Campo incompleto.") );
		
	} else {
		
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
		
		nuevo.set_salario( ( float )atoi( renglon_salario->GetValue().c_str() ) );
		
		if ( pos < 0 ) { // Si está en modo agregar...
			
			programa->bibliotecarios.push( nuevo );	
			
		} else { // Si está en modo edición...
			
			bibliotecario *bib = &( programa->bibliotecarios.get_bibliotecario_pos( pos ) );
			*bib = nuevo;
			
		}
		
		EndModal( 1 );
		
	}
	
}

void ventana_agregar_bibliotecario::click_cancelar( wxCommandEvent &_event )  {
	EndModal( -1 );
}

void ventana_agregar_bibliotecario::redibujar_ventana ( ) {
	
//	wxSize tamanyo = this->GetSize();
//	tamanyo.SetHeight( tamanyo.GetHeight() +1 );
//	this->SetSize( tamanyo );
//	tamanyo.SetHeight( tamanyo.GetHeight() -1 );
//	this->SetSize( tamanyo );
	this->Layout();
	this->Fit();
	
}

bool ventana_agregar_bibliotecario::copiar_imagen (const string & _fuente) {
	
	string destino = "Img\\Local\\Bibliotecarios\\";
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

