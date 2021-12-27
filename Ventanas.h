///////////////////////////////////////////////////////////////////////////

#ifndef __Ventanas__
#define __Ventanas__

#include "mi_grilla.h"

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/srchctrl.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/choice.h>
#include <wx/toolbar.h>
#include <wx/statline.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/checklst.h>
#include <wx/statbmp.h>
#include <wx/textctrl.h>
#include <wx/radiobox.h>
#include <wx/radiobut.h>
#include <wx/statbox.h>
#include <wx/listbox.h>
#include <wx/scrolwin.h>
#include <wx/hyperlink.h>

///////////////////////////////////////////////////////////////////////////

#define id_abrir_libros 1000
#define id_abrir_autores 1001
#define id_abrir_socios 1002
#define id_abrir_bib 1003
#define id_guardar 1004
#define id_menu_salir 1005
#define id_ver_estadisticas 1006
#define id_ver_ayuda 1007
#define id_ver_acerca_de 1008
#define id_ml_ver_detalles 1009
#define id_ml_editar 1010
#define id_ml_borrar 1011
#define id_ms_ver_detalles 1012
#define id_ms_editar 1013
#define id_ms_borrar 1014
#define id_vl_boton_borrar 1015
#define id_vl_boton_agregar 1016
#define id_vl_boton_prestar 1017
#define id_vl_boton_devolver 1018
#define id_vl_boton_detalles 1019
#define id_vl_boton_estadisticas 1020
#define id_vl_boton_restaurar 1021
#define id_vl_boton_cdu 1022
#define id_vl_boton_ayuda 1023
#define id_va_boton_borrar 1024
#define id_va_boton_agregar 1025
#define id_va_boton_restaurar 1026
#define id_va_boton_ayuda 1027
#define id_vs_boton_borrar 1028
#define id_vs_boton_agregar 1029
#define id_vs_boton_prestar 1030
#define id_vs_boton_devolver 1031
#define id_vs_boton_detalles 1032
#define id_vs_boton_estadisticas 1033
#define id_vs_boton_restaurar 1034
#define id_vs_boton_ayuda 1035
#define id_vb_boton_borrar 1036
#define id_vb_boton_agregar 1037
#define id_vb_boton_detalles 1038
#define id_vb_boton_estadisticas 1039
#define id_vb_boton_restaurar 1040
#define id_vb_boton_ayuda 1041
#define id_vhs_boton_detalles 1042
#define id_vhs_boton_estadisticas 1043
#define id_vhs_boton_restaurar 1044
#define id_vhs_boton_ayuda 1045
#define id_vhl_boton_detalles 1046
#define id_vhl_boton_estadisticas 1047
#define id_vhl_boton_restaurar 1048
#define id_vhl_boton_cdu 1049
#define id_vhl_boton_ayuda 1050

///////////////////////////////////////////////////////////////////////////////
/// Class vPrincipal
///////////////////////////////////////////////////////////////////////////////
class vPrincipal : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* barra_menus;
		wxMenu* menu_archivo;
		wxMenu* menu_abrir;
		wxMenu* menu_ver;
		wxMenu* menu_ayuda;
		wxPanel* panel_libros;
		wxBitmapButton* boton_principal_libros;
		wxSearchCtrl* barra_busqueda_libros;
		mi_grilla* grilla_libros_principal;
		wxMenu* menu_grilla_libros;
		
		wxBitmapButton* boton_eliminar_libro;
		
		wxBitmapButton* boton_agregar_libro;
		
		wxBitmapButton* boton_prestar;
		
		wxPanel* panel_usuarios;
		wxBitmapButton* boton_principal_socios;
		wxSearchCtrl* barra_busqueda_socios;
		mi_grilla* grilla_socios_principal;
		wxMenu* menu_grilla_socios;
		
		wxBitmapButton* boton_devolver;
		
		wxBitmapButton* boton_agregar_socio;
		
		wxBitmapButton* boton_eliminar_socio;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void se_cierra_vPrincipal( wxCloseEvent& event ) { event.Skip(); }
		virtual void click_abrir_libros( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_abrir_autores( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_abrir_socios( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_abrir_bib( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_guardar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_salir( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_ver_estadisticas( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_ver_ayuda( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_acerca_de( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_buscar_libro( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_iz_libro( wxGridEvent& event ) { event.Skip(); }
		virtual void Dclick_libro( wxGridEvent& event ) { event.Skip(); }
		virtual void click_der_libro( wxGridEvent& event ) { event.Skip(); }
		virtual void click_ver_detalles_libro( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_editar_libro( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_eliminar_libro( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_agregar_libro( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_reg_prestamo( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_buscar_socio( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_iz_socio( wxGridEvent& event ) { event.Skip(); }
		virtual void Dclick_socio( wxGridEvent& event ) { event.Skip(); }
		virtual void click_der_socio( wxGridEvent& event ) { event.Skip(); }
		virtual void click_ver_detalles_socio( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_editar_socio( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_eliminar_socio( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_reg_devolucion( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_agregar_socio( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vPrincipal( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Hexandria"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 930,490 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~vPrincipal();
		
		void grilla_libros_principalOnContextMenu( wxMouseEvent &event )
		{
			grilla_libros_principal->PopupMenu( menu_grilla_libros, event.GetPosition() );
		}
		
		void grilla_socios_principalOnContextMenu( wxMouseEvent &event )
		{
			grilla_socios_principal->PopupMenu( menu_grilla_socios, event.GetPosition() );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vLibros
///////////////////////////////////////////////////////////////////////////////
class vLibros : public wxDialog 
{
	private:
	
	protected:
		wxToolBar* MyToolbar;
		wxChoice* orden_libros;
		wxSearchCtrl* barra_busqueda;
		wxChoice* eleccion_principal;
		wxChoice* eleccion_sub_1;
		wxChoice* eleccion_sub_2;
		mi_grilla* grilla_libros;
		wxMenu* menu_grilla;
		wxStaticLine* m_staticline1;
		wxButton* boton_aceptar;
		wxButton* boton_cancelar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void click_boton_borrar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_agregar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_prestar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_devolver( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_detalles( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_estadisticas( wxCommandEvent& event ) { event.Skip(); }
		virtual void cambio_orden( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_buscar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_restaurar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_CDU( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_ayuda( wxCommandEvent& event ) { event.Skip(); }
		virtual void principal_elegido( wxCommandEvent& event ) { event.Skip(); }
		virtual void sub_1_elegido( wxCommandEvent& event ) { event.Skip(); }
		virtual void sub_2_elegido( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_izq_grilla( wxGridEvent& event ) { event.Skip(); }
		virtual void Dclick_grilla( wxGridEvent& event ) { event.Skip(); }
		virtual void click_der_grilla( wxGridEvent& event ) { event.Skip(); }
		virtual void click_editar_libro( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_aceptar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_cancelar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vLibros( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Base de datos de libros"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,500 ), long style = wxDEFAULT_DIALOG_STYLE );
		~vLibros();
		
		void grilla_librosOnContextMenu( wxMouseEvent &event )
		{
			grilla_libros->PopupMenu( menu_grilla, event.GetPosition() );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vAutores
///////////////////////////////////////////////////////////////////////////////
class vAutores : public wxDialog 
{
	private:
	
	protected:
		wxToolBar* MyToolbar;
		wxSearchCtrl* barra_busqueda;
		wxStaticText* m_staticText1;
		wxChoice* filtrado_iniciales;
		wxCheckListBox* lista_autores;
		wxStaticLine* m_staticline5;
		wxButton* boton_aceptar;
		wxButton* boton_cancelar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void click_boton_borrar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_agregar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_buscar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_restaurar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_ayuda( wxCommandEvent& event ) { event.Skip(); }
		virtual void cambio_filtro_iniciales( wxCommandEvent& event ) { event.Skip(); }
		virtual void Dclick_autor( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_aceptar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_cancelar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vAutores( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Base de datos de autores"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 480,480 ), long style = wxDEFAULT_DIALOG_STYLE );
		~vAutores();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vSocios
///////////////////////////////////////////////////////////////////////////////
class vSocios : public wxDialog 
{
	private:
	
	protected:
		wxToolBar* MyToolbar;
		wxChoice* orden_socios;
		wxSearchCtrl* barra_busqueda;
		mi_grilla* grilla_socios;
		wxMenu* menu_grilla;
		wxStaticBitmap* foto_socio;
		wxStaticLine* m_staticline2;
		wxButton* boton_aceptar;
		wxButton* boton_cancelar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void click_boton_borrar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_agregar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_prestar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_devolver( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_detalles( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_estadisticas( wxCommandEvent& event ) { event.Skip(); }
		virtual void cambio_orden( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_buscar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_restaurar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_ayuda( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_izq_grilla( wxGridEvent& event ) { event.Skip(); }
		virtual void Dclick_grilla( wxGridEvent& event ) { event.Skip(); }
		virtual void click_der_grilla( wxGridEvent& event ) { event.Skip(); }
		virtual void click_editar_socio( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_aceptar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_cancelar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vSocios( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Base de datos de socios"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 770,500 ), long style = wxDEFAULT_DIALOG_STYLE );
		~vSocios();
		
		void grilla_sociosOnContextMenu( wxMouseEvent &event )
		{
			grilla_socios->PopupMenu( menu_grilla, event.GetPosition() );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vDevolverLibro
///////////////////////////////////////////////////////////////////////////////
class vDevolverLibro : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText106;
		wxCheckListBox* eleccion_pendientes;
		wxStaticLine* m_staticline18;
		wxButton* boton_aceptar;
		wxButton* boton_cancelar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void click_boton_aceptar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_cancelar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vDevolverLibro( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Libros pendientes a devolver"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 524,242 ), long style = wxDEFAULT_DIALOG_STYLE );
		~vDevolverLibro();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vBibliotecarios
///////////////////////////////////////////////////////////////////////////////
class vBibliotecarios : public wxDialog 
{
	private:
	
	protected:
		wxToolBar* MyToolbar;
		wxChoice* orden_bibliotecarios;
		wxSearchCtrl* barra_busqueda;
		mi_grilla* grilla_bibliotecarios;
		wxMenu* menu_grilla;
		wxStaticBitmap* foto_bibliotecario;
		wxStaticLine* m_staticline2;
		wxButton* boton_aceptar;
		wxButton* boton_cancelar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void click_boton_borrar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_agregar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_detalles( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_estadisticas( wxCommandEvent& event ) { event.Skip(); }
		virtual void cambio_orden( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_buscar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_restaurar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_ayuda( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_izq_grilla( wxGridEvent& event ) { event.Skip(); }
		virtual void Dclick_grilla( wxGridEvent& event ) { event.Skip(); }
		virtual void click_der_grilla( wxGridEvent& event ) { event.Skip(); }
		virtual void click_editar_bib( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_aceptar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_cancelar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vBibliotecarios( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Base de datos de bibliotecarios"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 770,500 ), long style = wxDEFAULT_DIALOG_STYLE );
		~vBibliotecarios();
		
		void grilla_bibliotecariosOnContextMenu( wxMouseEvent &event )
		{
			grilla_bibliotecarios->PopupMenu( menu_grilla, event.GetPosition() );
		}
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vAgregarLibro
///////////////////////////////////////////////////////////////////////////////
class vAgregarLibro : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText2;
		wxTextCtrl* renglon_titulo;
		wxStaticText* m_staticText4;
		wxCheckListBox* cuadro_autores;
		wxButton* boton_agregar_autores;
		wxButton* boton_borrar_autores;
		wxStaticText* m_staticText5;
		wxTextCtrl* renglon_resumen;
		wxStaticText* m_staticText6;
		wxTextCtrl* renglon_publicacion;
		wxStaticText* m_staticText61;
		wxTextCtrl* renglon_url;
		wxButton* boton_ir;
		wxStaticText* m_staticText7;
		wxTextCtrl* renglon_tags;
		
		wxRadioBox* cuadro_tipo_prestamo;
		
		wxButton* boton_ingresar_cdu;
		wxStaticText* txt_ubicacion_ok;
		wxTextCtrl* renglon_ubicacion;
		wxStaticText* txt_ubicacion_no;
		
		wxStaticLine* m_staticline5;
		wxButton* boton_aceptar;
		wxButton* boton_cancelar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void click_boton_agregar_autores( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_borrar_autores( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_ir( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_cdu( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_aceptar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_cancelar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vAgregarLibro( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Agregar nuevo libro..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 480,480 ), long style = wxDEFAULT_DIALOG_STYLE );
		~vAgregarLibro();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vIngresarCDU
///////////////////////////////////////////////////////////////////////////////
class vIngresarCDU : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText100;
		wxChoice* eleccion_principal;
		wxStaticText* m_staticText101;
		wxChoice* eleccion_sub_1;
		wxStaticText* m_staticText102;
		wxChoice* eleccion_sub_2;
		wxStaticText* m_staticText103;
		wxChoice* eleccion_inicial_ape;
		wxStaticText* m_staticText104;
		wxChoice* eleccion_inicial_nom;
		wxStaticLine* m_staticline17;
		wxButton* boton_aceptar;
		wxButton* boton_cancelar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void principal_elegido( wxCommandEvent& event ) { event.Skip(); }
		virtual void sub_1_elegido( wxCommandEvent& event ) { event.Skip(); }
		virtual void sub_2_elegido( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_aceptar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_cancelar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vIngresarCDU( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Ingreso de ubicación CDU..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~vIngresarCDU();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vAgregarAutor
///////////////////////////////////////////////////////////////////////////////
class vAgregarAutor : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText2;
		wxTextCtrl* renglon_nombre;
		wxStaticText* m_staticText5;
		wxTextCtrl* renglon_resumen;
		wxStaticText* m_staticText61;
		wxTextCtrl* renglon_url;
		wxButton* boton_ir;
		wxStaticLine* m_staticline5;
		wxButton* boton_aceptar;
		wxButton* boton_cancelar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void click_boton_ir( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_aceptar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_cancelar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vAgregarAutor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Agregar nuevo autor..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 480,320 ), long style = wxDEFAULT_DIALOG_STYLE );
		~vAgregarAutor();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vAgregarSocio
///////////////////////////////////////////////////////////////////////////////
class vAgregarSocio : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText20;
		wxTextCtrl* renglon_apellido;
		wxStaticText* m_staticText45;
		wxTextCtrl* renglon_nombres;
		wxStaticText* m_staticText201;
		wxTextCtrl* renglon_dni;
		wxStaticText* m_staticText202;
		wxTextCtrl* renglon_tel;
		wxStaticText* m_staticText203;
		wxTextCtrl* renglon_domicilio;
		wxStaticText* m_staticText33;
		wxStaticText* m_staticText2029;
		wxChoice* dia_nac;
		wxStaticText* m_staticText2023;
		wxChoice* mes_nac;
		wxStaticText* m_staticText2024;
		wxTextCtrl* anyo_nac;
		wxPanel* panel_fecha_ingreso;
		wxStaticText* m_staticText43;
		
		wxRadioButton* boton_ingreso_1;
		wxRadioButton* boton_ingreso_2;
		wxPanel* ingreso_emergente;
		
		wxStaticText* m_staticText2013;
		wxChoice* dia_ingreso;
		wxStaticText* m_staticText2014;
		wxChoice* mes_ingreso;
		wxStaticText* m_staticText2015;
		wxTextCtrl* anyo_ingreso;
		wxStaticText* m_staticText46;
		wxTextCtrl* renglon_foto;
		wxButton* boton_explorar;
		wxStaticLine* m_staticline8;
		wxButton* boton_aceptar;
		wxButton* boton_cancelar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void fecha_ingreso_actual( wxCommandEvent& event ) { event.Skip(); }
		virtual void fecha_ingreso_manual( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_explorar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_aceptar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_cancelar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vAgregarSocio( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Agregar nuevo socio..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~vAgregarSocio();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vAgregarBibliotecario
///////////////////////////////////////////////////////////////////////////////
class vAgregarBibliotecario : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText20;
		wxTextCtrl* renglon_apellido;
		wxStaticText* m_staticText45;
		wxTextCtrl* renglon_nombres;
		wxStaticText* m_staticText201;
		wxTextCtrl* renglon_dni;
		wxStaticText* m_staticText202;
		wxTextCtrl* renglon_tel;
		wxStaticText* m_staticText203;
		wxTextCtrl* renglon_domicilio;
		wxStaticText* m_staticText33;
		wxStaticText* m_staticText2029;
		wxChoice* dia_nac;
		wxStaticText* m_staticText2023;
		wxChoice* mes_nac;
		wxStaticText* m_staticText2024;
		wxTextCtrl* anyo_nac;
		wxPanel* panel_fecha_ingreso;
		wxStaticText* m_staticText43;
		
		wxRadioButton* boton_ingreso_1;
		wxRadioButton* boton_ingreso_2;
		wxPanel* ingreso_emergente;
		
		wxStaticText* m_staticText2013;
		wxChoice* dia_ingreso;
		wxStaticText* m_staticText2014;
		wxChoice* mes_ingreso;
		wxStaticText* m_staticText2015;
		wxTextCtrl* anyo_ingreso;
		wxStaticText* m_staticText46;
		wxTextCtrl* renglon_foto;
		wxButton* boton_explorar;
		wxStaticText* m_staticText75;
		wxTextCtrl* renglon_salario;
		wxStaticText* m_staticText76;
		wxButton* boton_cargar_cur;
		wxStaticText* aviso_carga_cur;
		wxStaticText* m_staticText751;
		wxButton* boton_generar_cuenta;
		wxStaticText* aviso_cta_no;
		wxStaticText* aviso_cta_si;
		wxStaticLine* m_staticline8;
		wxButton* boton_aceptar;
		wxButton* boton_cancelar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void fecha_ingreso_actual( wxCommandEvent& event ) { event.Skip(); }
		virtual void fecha_ingreso_manual( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_explorar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_cargar_cur( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_generar_cuenta( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_aceptar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_cancelar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vAgregarBibliotecario( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Agregar nuevo bibliotecario..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~vAgregarBibliotecario();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vAgregarCurriculum
///////////////////////////////////////////////////////////////////////////////
class vAgregarCurriculum : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText78;
		wxStaticText* m_staticText79;
		wxTextCtrl* renglon_path;
		wxButton* boton_explorar;
		wxTextCtrl* renglon_cur;
		wxStaticLine* m_staticline11;
		wxButton* boton_aceptar;
		wxButton* boton_cancelar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void click_boton_explorar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_aceptar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_cancelar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vAgregarCurriculum( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Agregar currículum..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,400 ), long style = wxDEFAULT_DIALOG_STYLE );
		~vAgregarCurriculum();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vInfoLibro
///////////////////////////////////////////////////////////////////////////////
class vInfoLibro : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText55;
		wxTextCtrl* renglon_titulo;
		wxStaticText* m_staticText56;
		wxTextCtrl* renglon_autores;
		wxStaticText* m_staticText561;
		wxTextCtrl* renglon_publicacion;
		wxStaticText* m_staticText60;
		wxTextCtrl* renglon_prestamo;
		wxStaticText* m_staticText105;
		wxTextCtrl* renglon_estado;
		wxStaticText* m_staticText601;
		wxTextCtrl* renglon_solicitar;
		wxStaticText* m_staticText602;
		wxTextCtrl* renglon_fecha;
		wxStaticText* m_staticText603;
		wxTextCtrl* renglon_codigo;
		wxStaticText* m_staticText65;
		wxTextCtrl* renglon_contenido;
		wxStaticText* m_staticText66;
		wxTextCtrl* renglon_resumen;
		wxStaticText* m_staticText67;
		wxTextCtrl* renglon_url;
		wxButton* boton_ir;
		wxStaticLine* m_staticline11;
		wxButton* boton_ver_historial;
		
		wxButton* boton_cerrar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void click_boton_ir( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_historial( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_cerrar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vInfoLibro( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Detalles de obra bibliográfica"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,466 ), long style = wxDEFAULT_DIALOG_STYLE );
		~vInfoLibro();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vInfoSocio
///////////////////////////////////////////////////////////////////////////////
class vInfoSocio : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText96;
		wxTextCtrl* renglon_nombre;
		wxStaticText* m_staticText961;
		wxTextCtrl* renglon_dni;
		wxStaticText* m_staticText967;
		wxTextCtrl* renglon_nro_socio;
		wxStaticText* m_staticText962;
		wxTextCtrl* renglon_tel;
		wxStaticText* m_staticText963;
		wxTextCtrl* renglon_domicilio;
		wxStaticText* m_staticText964;
		wxTextCtrl* renglon_edad;
		wxStaticText* m_staticText965;
		wxTextCtrl* renglon_ingreso;
		wxStaticText* m_staticText966;
		wxListBox* cuadro_pendientes;
		wxStaticBitmap* foto_socio;
		wxButton* boton_ver_historial;
		wxStaticLine* m_staticline14;
		wxButton* boton_cerrar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void Dclick_pendiente( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_historial( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_cerrar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vInfoSocio( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Información de socio"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~vInfoSocio();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vInfoBibliotecario
///////////////////////////////////////////////////////////////////////////////
class vInfoBibliotecario : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText96;
		wxTextCtrl* renglon_nombre;
		wxStaticText* m_staticText961;
		wxTextCtrl* renglon_dni;
		wxStaticText* m_staticText962;
		wxTextCtrl* renglon_tel;
		wxStaticText* m_staticText963;
		wxTextCtrl* renglon_domicilio;
		wxStaticText* m_staticText964;
		wxTextCtrl* renglon_edad;
		wxStaticText* m_staticText965;
		wxTextCtrl* renglon_ingreso;
		wxStaticText* m_staticText9651;
		wxTextCtrl* renglon_salario;
		wxStaticText* m_staticText9652;
		wxTextCtrl* renglon_prestamos;
		wxStaticBitmap* foto_bibliotecario;
		wxTextCtrl* renglon_cur;
		wxStaticLine* m_staticline14;
		wxButton* boton_cerrar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void click_boton_cerrar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vInfoBibliotecario( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Información de bibliotecario"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,480 ), long style = wxDEFAULT_DIALOG_STYLE );
		~vInfoBibliotecario();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vEstadisticas
///////////////////////////////////////////////////////////////////////////////
class vEstadisticas : public wxDialog 
{
	private:
	
	protected:
		wxScrolledWindow* m_scrolledWindow1;
		wxButton* boton_ver_ocultar_libros;
		wxPanel* panel_libros;
		wxStaticText* m_staticText74;
		wxChoice* cant_top_libros;
		wxListBox* cuadro_top_libros;
		wxStaticText* m_staticText741;
		wxChoice* cant_top_autores;
		wxListBox* cuadro_top_autores;
		wxButton* boton_ver_ocultar_socios;
		wxPanel* panel_socios;
		wxStaticText* m_staticText742;
		wxChoice* cant_top_socios_prestamos;
		wxListBox* cuadro_top_socios_prestamos;
		wxStaticText* m_staticText7411;
		wxChoice* cant_top_socios_ant;
		wxListBox* cuadro_top_socios_antig;
		wxPanel* panel_emergente_bib;
		wxButton* boton_ver_ocultar_bib;
		wxPanel* panel_bibliotecarios;
		wxStaticText* m_staticText7421;
		wxListBox* cuadro_bib_prestamos;
		wxStaticText* m_staticText74111;
		wxListBox* cuadro_bib_antiguedad;
		wxStaticText* m_staticText82;
		wxListBox* cuadro_bib_salario;
		wxStaticLine* m_staticline13;
		wxButton* boton_cerrar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void click_ver_ocultar_libros( wxCommandEvent& event ) { event.Skip(); }
		virtual void cambio_cant_top_libros( wxCommandEvent& event ) { event.Skip(); }
		virtual void cambio_cant_top_autores( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_ver_ocultar_socios( wxCommandEvent& event ) { event.Skip(); }
		virtual void cambio_cant_top_socios_prestamos( wxCommandEvent& event ) { event.Skip(); }
		virtual void cambio_cant_top_socios_ant( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_ver_ocultar_bib( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_cerrar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vEstadisticas( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Estadísticas"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 611,484 ), long style = wxDEFAULT_DIALOG_STYLE );
		~vEstadisticas();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vLogin
///////////////////////////////////////////////////////////////////////////////
class vLogin : public wxDialog 
{
	private:
	
	protected:
		
		wxStaticText* error_usuario;
		wxStaticText* m_staticText79;
		wxTextCtrl* renglon_usuario;
		wxStaticText* m_staticText791;
		wxTextCtrl* renglon_pass;
		wxStaticText* error_pass;
		
		wxStaticLine* m_staticline14;
		wxButton* boton_salir;
		wxButton* boton_aceptar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void se_cierra( wxCloseEvent& event ) { event.Skip(); }
		virtual void enter_presionado( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_salir( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_aceptar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vLogin( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Iniciar sesión"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~vLogin();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vAgregarUsuario
///////////////////////////////////////////////////////////////////////////////
class vAgregarUsuario : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText86;
		wxTextCtrl* renglon_usuario;
		wxStaticText* error_usuario;
		wxStaticText* m_staticText862;
		wxTextCtrl* renglon_pass;
		wxStaticText* m_staticText863;
		wxTextCtrl* renglon_confirmacion;
		wxStaticText* error_confirmacion;
		wxStaticLine* m_staticline15;
		wxButton* boton_cancelar;
		wxButton* boton_aceptar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void click_boton_cancelar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_aceptar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vAgregarUsuario( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Agregar usuario..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~vAgregarUsuario();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vAyuda
///////////////////////////////////////////////////////////////////////////////
class vAyuda : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText103;
		
		wxHyperlinkCtrl* m_hyperlink1;
		wxHyperlinkCtrl* m_hyperlink11;
		
		wxStaticText* m_staticText104;
		wxStaticText* m_staticText105;
		wxHyperlinkCtrl* m_hyperlink5;
		wxStaticText* m_staticText106;
		wxStaticLine* m_staticline21;
		wxButton* boton_cerrar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void abrir_manual_usuario( wxHyperlinkEvent& event ) { event.Skip(); }
		virtual void abrir_manual_referencia( wxHyperlinkEvent& event ) { event.Skip(); }
		virtual void click_boton_cerrar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vAyuda( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Ayuda"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxDIALOG_NO_PARENT );
		~vAyuda();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vAbout
///////////////////////////////////////////////////////////////////////////////
class vAbout : public wxDialog 
{
	private:
	
	protected:
		wxStaticBitmap* m_bitmap5;
		
		wxStaticText* m_staticText100;
		wxStaticText* m_staticText101;
		wxStaticText* m_staticText102;
		
		wxStaticText* m_staticText103;
		wxStaticText* m_staticText104;
		
		wxStaticLine* m_staticline19;
		wxButton* boton_cerrar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void click_cerrar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vAbout( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Acerca de..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~vAbout();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class vHistorial
///////////////////////////////////////////////////////////////////////////////
class vHistorial : public wxDialog 
{
	private:
	
	protected:
		wxPanel* panel_historial_libro;
		wxToolBar* barra_socios;
		wxChoice* orden_socios;
		wxSearchCtrl* barra_busqueda_s;
		mi_grilla* grilla_socios;
		wxStaticBitmap* foto_socio;
		wxPanel* panel_historial_socio;
		wxToolBar* MyToolbar;
		wxChoice* orden_libros;
		wxSearchCtrl* barra_busqueda_l;
		wxChoice* eleccion_principal;
		wxChoice* eleccion_sub_1;
		wxChoice* eleccion_sub_2;
		mi_grilla* grilla_libros;
		wxStaticLine* m_staticline20;
		wxButton* boton_cerrar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void click_boton_detalles( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_estadisticas( wxCommandEvent& event ) { event.Skip(); }
		virtual void cambio_orden( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_buscar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_restaurar( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_ayuda( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_izq_grilla( wxGridEvent& event ) { event.Skip(); }
		virtual void Dclick_grilla( wxGridEvent& event ) { event.Skip(); }
		virtual void click_boton_CDU( wxCommandEvent& event ) { event.Skip(); }
		virtual void principal_elegido( wxCommandEvent& event ) { event.Skip(); }
		virtual void sub_1_elegido( wxCommandEvent& event ) { event.Skip(); }
		virtual void sub_2_elegido( wxCommandEvent& event ) { event.Skip(); }
		virtual void click_boton_cerrar( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		vHistorial( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Historial de préstamos"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		~vHistorial();
	
};

#endif //__Ventanas__
