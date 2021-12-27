///////////////////////////////////////////////////////////////////////////

#include "Ventanas.h"

///////////////////////////////////////////////////////////////////////////

vPrincipal::vPrincipal( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	barra_menus = new wxMenuBar( 0 );
	menu_archivo = new wxMenu();
	menu_abrir = new wxMenu();
	wxMenuItem* menu_abrir_libros;
	menu_abrir_libros = new wxMenuItem( menu_abrir, id_abrir_libros, wxString( wxT("Libros") ) , wxEmptyString, wxITEM_NORMAL );
	menu_abrir->Append( menu_abrir_libros );
	
	wxMenuItem* menu_abrir_autores;
	menu_abrir_autores = new wxMenuItem( menu_abrir, id_abrir_autores, wxString( wxT("Autores") ) , wxEmptyString, wxITEM_NORMAL );
	menu_abrir->Append( menu_abrir_autores );
	
	wxMenuItem* menu_abrir_socios;
	menu_abrir_socios = new wxMenuItem( menu_abrir, id_abrir_socios, wxString( wxT("Socios") ) , wxEmptyString, wxITEM_NORMAL );
	menu_abrir->Append( menu_abrir_socios );
	
	wxMenuItem* menu_abrir_bib;
	menu_abrir_bib = new wxMenuItem( menu_abrir, id_abrir_bib, wxString( wxT("Bibliotecarios") ) , wxEmptyString, wxITEM_NORMAL );
	menu_abrir->Append( menu_abrir_bib );
	menu_abrir_bib->Enable( false );
	
	menu_archivo->Append( -1, wxT("Abrir base de datos..."), menu_abrir );
	
	wxMenuItem* menu_guardar;
	menu_guardar = new wxMenuItem( menu_archivo, id_guardar, wxString( wxT("Guardar") ) , wxEmptyString, wxITEM_NORMAL );
	menu_archivo->Append( menu_guardar );
	
	wxMenuItem* m_separator5;
	m_separator5 = menu_archivo->AppendSeparator();
	
	wxMenuItem* menu_salir;
	menu_salir = new wxMenuItem( menu_archivo, id_menu_salir, wxString( wxT("Salir") ) , wxEmptyString, wxITEM_NORMAL );
	menu_archivo->Append( menu_salir );
	
	barra_menus->Append( menu_archivo, wxT("Archivo") ); 
	
	menu_ver = new wxMenu();
	wxMenuItem* menu_ver_estadisticas;
	menu_ver_estadisticas = new wxMenuItem( menu_ver, id_ver_estadisticas, wxString( wxT("Estadísticas") ) , wxEmptyString, wxITEM_NORMAL );
	menu_ver->Append( menu_ver_estadisticas );
	
	barra_menus->Append( menu_ver, wxT("Ver") ); 
	
	menu_ayuda = new wxMenu();
	wxMenuItem* menu_ver_ayuda;
	menu_ver_ayuda = new wxMenuItem( menu_ayuda, id_ver_ayuda, wxString( wxT("Ver la ayuda") ) , wxEmptyString, wxITEM_NORMAL );
	menu_ayuda->Append( menu_ver_ayuda );
	
	wxMenuItem* menu_acerca_de;
	menu_acerca_de = new wxMenuItem( menu_ayuda, id_ver_acerca_de, wxString( wxT("Acerca de...") ) , wxEmptyString, wxITEM_NORMAL );
	menu_ayuda->Append( menu_acerca_de );
	
	barra_menus->Append( menu_ayuda, wxT("Ayuda") ); 
	
	this->SetMenuBar( barra_menus );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	panel_libros = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	panel_libros->SetBackgroundColour( wxColour( 185, 185, 255 ) );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	boton_principal_libros = new wxBitmapButton( panel_libros, wxID_ANY, wxBitmap( wxT("Img/Resources/folder_libros.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	boton_principal_libros->SetBackgroundColour( wxColour( 185, 185, 255 ) );
	boton_principal_libros->SetToolTip( wxT("Abrir base de datos de libros...") );
	
	boton_principal_libros->SetBackgroundColour( wxColour( 185, 185, 255 ) );
	boton_principal_libros->SetToolTip( wxT("Abrir base de datos de libros...") );
	
	bSizer7->Add( boton_principal_libros, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	barra_busqueda_libros = new wxSearchCtrl( panel_libros, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	#ifndef __WXMAC__
	barra_busqueda_libros->ShowSearchButton( true );
	#endif
	barra_busqueda_libros->ShowCancelButton( false );
	bSizer7->Add( barra_busqueda_libros, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	grilla_libros_principal = new mi_grilla( panel_libros, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	grilla_libros_principal->CreateGrid( 10, 4 );
	grilla_libros_principal->EnableEditing( false );
	grilla_libros_principal->EnableGridLines( true );
	grilla_libros_principal->SetGridLineColour( wxColour( 136, 136, 136 ) );
	grilla_libros_principal->EnableDragGridSize( false );
	grilla_libros_principal->SetMargins( 0, 0 );
	
	// Columns
	grilla_libros_principal->SetColSize( 0, 140 );
	grilla_libros_principal->SetColSize( 1, 140 );
	grilla_libros_principal->SetColSize( 2, 65 );
	grilla_libros_principal->SetColSize( 3, 65 );
	grilla_libros_principal->EnableDragColMove( false );
	grilla_libros_principal->EnableDragColSize( true );
	grilla_libros_principal->SetColLabelSize( 20 );
	grilla_libros_principal->SetColLabelValue( 0, wxT("Título") );
	grilla_libros_principal->SetColLabelValue( 1, wxT("Autor") );
	grilla_libros_principal->SetColLabelValue( 2, wxT("Estado") );
	grilla_libros_principal->SetColLabelValue( 3, wxT("Ubicación") );
	grilla_libros_principal->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	grilla_libros_principal->EnableDragRowSize( false );
	grilla_libros_principal->SetRowLabelSize( 0 );
	grilla_libros_principal->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	grilla_libros_principal->SetDefaultCellBackgroundColour( wxColour( 185, 185, 255 ) );
	grilla_libros_principal->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	grilla_libros_principal->SetBackgroundColour( wxColour( 185, 185, 255 ) );
	
	menu_grilla_libros = new wxMenu();
	wxMenuItem* menu_libros_detalles;
	menu_libros_detalles = new wxMenuItem( menu_grilla_libros, id_ml_ver_detalles, wxString( wxT("Ver detalles....") ) , wxEmptyString, wxITEM_NORMAL );
	menu_grilla_libros->Append( menu_libros_detalles );
	
	wxMenuItem* menu_libros_editar;
	menu_libros_editar = new wxMenuItem( menu_grilla_libros, id_ml_editar, wxString( wxT("Editar...") ) , wxEmptyString, wxITEM_NORMAL );
	menu_grilla_libros->Append( menu_libros_editar );
	
	wxMenuItem* menu_libros_borrar;
	menu_libros_borrar = new wxMenuItem( menu_grilla_libros, id_ml_borrar, wxString( wxT("Borrar") ) , wxEmptyString, wxITEM_NORMAL );
	menu_grilla_libros->Append( menu_libros_borrar );
	
	grilla_libros_principal->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( vPrincipal::grilla_libros_principalOnContextMenu ), NULL, this ); 
	
	bSizer7->Add( grilla_libros_principal, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	boton_eliminar_libro = new wxBitmapButton( panel_libros, wxID_ANY, wxBitmap( wxT("Img/Resources/book_delete.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	boton_eliminar_libro->Enable( false );
	boton_eliminar_libro->SetToolTip( wxT("Eliminar el libro seleccionado.") );
	
	boton_eliminar_libro->Enable( false );
	boton_eliminar_libro->SetToolTip( wxT("Eliminar el libro seleccionado.") );
	
	bSizer9->Add( boton_eliminar_libro, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	boton_agregar_libro = new wxBitmapButton( panel_libros, wxID_ANY, wxBitmap( wxT("Img/Resources/book_add.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	boton_agregar_libro->SetToolTip( wxT("Agregar libro...") );
	
	boton_agregar_libro->SetToolTip( wxT("Agregar libro...") );
	
	bSizer9->Add( boton_agregar_libro, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	boton_prestar = new wxBitmapButton( panel_libros, wxID_ANY, wxBitmap( wxT("Img/Resources/flecha_der.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	boton_prestar->Enable( false );
	boton_prestar->SetToolTip( wxT("Registrar préstamo.") );
	
	boton_prestar->Enable( false );
	boton_prestar->SetToolTip( wxT("Registrar préstamo.") );
	
	bSizer9->Add( boton_prestar, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer9->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizer7->Add( bSizer9, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	panel_libros->SetSizer( bSizer7 );
	panel_libros->Layout();
	bSizer7->Fit( panel_libros );
	bSizer2->Add( panel_libros, 1, wxEXPAND | wxALL, 5 );
	
	panel_usuarios = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	panel_usuarios->SetBackgroundColour( wxColour( 129, 243, 177 ) );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	boton_principal_socios = new wxBitmapButton( panel_usuarios, wxID_ANY, wxBitmap( wxT("Img/Resources/folder_socios.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	boton_principal_socios->SetBackgroundColour( wxColour( 129, 243, 177 ) );
	boton_principal_socios->SetToolTip( wxT("Abrir base de datos de socios...") );
	
	boton_principal_socios->SetBackgroundColour( wxColour( 129, 243, 177 ) );
	boton_principal_socios->SetToolTip( wxT("Abrir base de datos de socios...") );
	
	bSizer8->Add( boton_principal_socios, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	barra_busqueda_socios = new wxSearchCtrl( panel_usuarios, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	#ifndef __WXMAC__
	barra_busqueda_socios->ShowSearchButton( true );
	#endif
	barra_busqueda_socios->ShowCancelButton( false );
	bSizer8->Add( barra_busqueda_socios, 0, wxALL|wxEXPAND, 5 );
	
	grilla_socios_principal = new mi_grilla( panel_usuarios, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	grilla_socios_principal->CreateGrid( 10, 3 );
	grilla_socios_principal->EnableEditing( false );
	grilla_socios_principal->EnableGridLines( true );
	grilla_socios_principal->SetGridLineColour( wxColour( 136, 136, 136 ) );
	grilla_socios_principal->EnableDragGridSize( false );
	grilla_socios_principal->SetMargins( 0, 0 );
	
	// Columns
	grilla_socios_principal->SetColSize( 0, 200 );
	grilla_socios_principal->SetColSize( 1, 145 );
	grilla_socios_principal->SetColSize( 2, 70 );
	grilla_socios_principal->EnableDragColMove( false );
	grilla_socios_principal->EnableDragColSize( true );
	grilla_socios_principal->SetColLabelSize( 20 );
	grilla_socios_principal->SetColLabelValue( 0, wxT("Nombre") );
	grilla_socios_principal->SetColLabelValue( 1, wxT("DNI") );
	grilla_socios_principal->SetColLabelValue( 2, wxT("Pendientes") );
	grilla_socios_principal->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	grilla_socios_principal->EnableDragRowSize( false );
	grilla_socios_principal->SetRowLabelSize( 0 );
	grilla_socios_principal->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	grilla_socios_principal->SetDefaultCellBackgroundColour( wxColour( 129, 243, 177 ) );
	grilla_socios_principal->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_CENTRE );
	grilla_socios_principal->SetBackgroundColour( wxColour( 185, 185, 255 ) );
	
	menu_grilla_socios = new wxMenu();
	wxMenuItem* menu_socios_detalles;
	menu_socios_detalles = new wxMenuItem( menu_grilla_socios, id_ms_ver_detalles, wxString( wxT("Ver detalles....") ) , wxEmptyString, wxITEM_NORMAL );
	menu_grilla_socios->Append( menu_socios_detalles );
	
	wxMenuItem* menu_socios_editar;
	menu_socios_editar = new wxMenuItem( menu_grilla_socios, id_ms_editar, wxString( wxT("Editar...") ) , wxEmptyString, wxITEM_NORMAL );
	menu_grilla_socios->Append( menu_socios_editar );
	
	wxMenuItem* menu_socios_borrar;
	menu_socios_borrar = new wxMenuItem( menu_grilla_socios, id_ms_borrar, wxString( wxT("Borrar") ) , wxEmptyString, wxITEM_NORMAL );
	menu_grilla_socios->Append( menu_socios_borrar );
	
	grilla_socios_principal->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( vPrincipal::grilla_socios_principalOnContextMenu ), NULL, this ); 
	
	bSizer8->Add( grilla_socios_principal, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer91;
	bSizer91 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer91->Add( 0, 0, 1, wxEXPAND, 5 );
	
	boton_devolver = new wxBitmapButton( panel_usuarios, wxID_ANY, wxBitmap( wxT("Img/Resources/flecha_iz.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	boton_devolver->Enable( false );
	boton_devolver->SetToolTip( wxT("Registrar devolución.") );
	
	boton_devolver->Enable( false );
	boton_devolver->SetToolTip( wxT("Registrar devolución.") );
	
	bSizer91->Add( boton_devolver, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer91->Add( 0, 0, 1, wxEXPAND, 5 );
	
	boton_agregar_socio = new wxBitmapButton( panel_usuarios, wxID_ANY, wxBitmap( wxT("Img/Resources/socio_add.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	boton_agregar_socio->SetToolTip( wxT("Agregar socio...") );
	
	boton_agregar_socio->SetToolTip( wxT("Agregar socio...") );
	
	bSizer91->Add( boton_agregar_socio, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer91->Add( 0, 0, 1, wxEXPAND, 5 );
	
	boton_eliminar_socio = new wxBitmapButton( panel_usuarios, wxID_ANY, wxBitmap( wxT("Img/Resources/socio_del.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	boton_eliminar_socio->Enable( false );
	boton_eliminar_socio->SetToolTip( wxT("Eliminar el socio seleccionado.") );
	
	boton_eliminar_socio->Enable( false );
	boton_eliminar_socio->SetToolTip( wxT("Eliminar el socio seleccionado.") );
	
	bSizer91->Add( boton_eliminar_socio, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer91->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizer8->Add( bSizer91, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	panel_usuarios->SetSizer( bSizer8 );
	panel_usuarios->Layout();
	bSizer8->Fit( panel_usuarios );
	bSizer2->Add( panel_usuarios, 1, wxALL|wxEXPAND, 5 );
	
	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( vPrincipal::se_cierra_vPrincipal ) );
	this->Connect( menu_abrir_libros->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_abrir_libros ) );
	this->Connect( menu_abrir_autores->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_abrir_autores ) );
	this->Connect( menu_abrir_socios->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_abrir_socios ) );
	this->Connect( menu_abrir_bib->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_abrir_bib ) );
	this->Connect( menu_guardar->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_guardar ) );
	this->Connect( menu_salir->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_salir ) );
	this->Connect( menu_ver_estadisticas->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_ver_estadisticas ) );
	this->Connect( menu_ver_ayuda->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_ver_ayuda ) );
	this->Connect( menu_acerca_de->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_acerca_de ) );
	boton_principal_libros->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vPrincipal::click_abrir_libros ), NULL, this );
	barra_busqueda_libros->Connect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( vPrincipal::click_buscar_libro ), NULL, this );
	barra_busqueda_libros->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( vPrincipal::click_buscar_libro ), NULL, this );
	barra_busqueda_libros->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vPrincipal::click_buscar_libro ), NULL, this );
	grilla_libros_principal->Connect( wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler( vPrincipal::click_iz_libro ), NULL, this );
	grilla_libros_principal->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( vPrincipal::Dclick_libro ), NULL, this );
	grilla_libros_principal->Connect( wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler( vPrincipal::click_der_libro ), NULL, this );
	this->Connect( menu_libros_detalles->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_ver_detalles_libro ) );
	this->Connect( menu_libros_editar->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_editar_libro ) );
	this->Connect( menu_libros_borrar->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_eliminar_libro ) );
	boton_eliminar_libro->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vPrincipal::click_eliminar_libro ), NULL, this );
	boton_agregar_libro->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vPrincipal::click_boton_agregar_libro ), NULL, this );
	boton_prestar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vPrincipal::click_reg_prestamo ), NULL, this );
	boton_principal_socios->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vPrincipal::click_abrir_socios ), NULL, this );
	barra_busqueda_socios->Connect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( vPrincipal::click_buscar_socio ), NULL, this );
	barra_busqueda_socios->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( vPrincipal::click_buscar_socio ), NULL, this );
	barra_busqueda_socios->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vPrincipal::click_buscar_socio ), NULL, this );
	grilla_socios_principal->Connect( wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler( vPrincipal::click_iz_socio ), NULL, this );
	grilla_socios_principal->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( vPrincipal::Dclick_socio ), NULL, this );
	grilla_socios_principal->Connect( wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler( vPrincipal::click_der_socio ), NULL, this );
	this->Connect( menu_socios_detalles->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_ver_detalles_socio ) );
	this->Connect( menu_socios_editar->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_editar_socio ) );
	this->Connect( menu_socios_borrar->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_eliminar_socio ) );
	boton_devolver->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vPrincipal::click_reg_devolucion ), NULL, this );
	boton_agregar_socio->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vPrincipal::click_boton_agregar_socio ), NULL, this );
	boton_eliminar_socio->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vPrincipal::click_eliminar_socio ), NULL, this );
}

vPrincipal::~vPrincipal()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( vPrincipal::se_cierra_vPrincipal ) );
	this->Disconnect( id_abrir_libros, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_abrir_libros ) );
	this->Disconnect( id_abrir_autores, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_abrir_autores ) );
	this->Disconnect( id_abrir_socios, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_abrir_socios ) );
	this->Disconnect( id_abrir_bib, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_abrir_bib ) );
	this->Disconnect( id_guardar, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_guardar ) );
	this->Disconnect( id_menu_salir, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_salir ) );
	this->Disconnect( id_ver_estadisticas, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_ver_estadisticas ) );
	this->Disconnect( id_ver_ayuda, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_ver_ayuda ) );
	this->Disconnect( id_ver_acerca_de, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_acerca_de ) );
	boton_principal_libros->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vPrincipal::click_abrir_libros ), NULL, this );
	barra_busqueda_libros->Disconnect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( vPrincipal::click_buscar_libro ), NULL, this );
	barra_busqueda_libros->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( vPrincipal::click_buscar_libro ), NULL, this );
	barra_busqueda_libros->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vPrincipal::click_buscar_libro ), NULL, this );
	grilla_libros_principal->Disconnect( wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler( vPrincipal::click_iz_libro ), NULL, this );
	grilla_libros_principal->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( vPrincipal::Dclick_libro ), NULL, this );
	grilla_libros_principal->Disconnect( wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler( vPrincipal::click_der_libro ), NULL, this );
	this->Disconnect( id_ml_ver_detalles, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_ver_detalles_libro ) );
	this->Disconnect( id_ml_editar, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_editar_libro ) );
	this->Disconnect( id_ml_borrar, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_eliminar_libro ) );
	boton_eliminar_libro->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vPrincipal::click_eliminar_libro ), NULL, this );
	boton_agregar_libro->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vPrincipal::click_boton_agregar_libro ), NULL, this );
	boton_prestar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vPrincipal::click_reg_prestamo ), NULL, this );
	boton_principal_socios->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vPrincipal::click_abrir_socios ), NULL, this );
	barra_busqueda_socios->Disconnect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( vPrincipal::click_buscar_socio ), NULL, this );
	barra_busqueda_socios->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( vPrincipal::click_buscar_socio ), NULL, this );
	barra_busqueda_socios->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vPrincipal::click_buscar_socio ), NULL, this );
	grilla_socios_principal->Disconnect( wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler( vPrincipal::click_iz_socio ), NULL, this );
	grilla_socios_principal->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( vPrincipal::Dclick_socio ), NULL, this );
	grilla_socios_principal->Disconnect( wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler( vPrincipal::click_der_socio ), NULL, this );
	this->Disconnect( id_ms_ver_detalles, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_ver_detalles_socio ) );
	this->Disconnect( id_ms_editar, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_editar_socio ) );
	this->Disconnect( id_ms_borrar, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vPrincipal::click_eliminar_socio ) );
	boton_devolver->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vPrincipal::click_reg_devolucion ), NULL, this );
	boton_agregar_socio->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vPrincipal::click_boton_agregar_socio ), NULL, this );
	boton_eliminar_socio->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vPrincipal::click_eliminar_socio ), NULL, this );
	
	delete menu_grilla_libros; 
	delete menu_grilla_socios; 
}

vLibros::vLibros( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	MyToolbar = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL ); 
	MyToolbar->AddTool( id_vl_boton_borrar, wxT("tool"), wxBitmap( wxT("Img/Resources/toolbar_del.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Eliminar el libro seleccionado de la base de datos."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vl_boton_agregar, wxT("tool"), wxBitmap( wxT("Img/Resources/toolbar_add.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Agregar nuevo libro..."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vl_boton_prestar, wxT("tool"), wxBitmap( wxT("Img/Resources/l_prestar.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Realizar el préstamo del libro seleccionado..."), wxEmptyString ); 
	MyToolbar->AddTool( id_vl_boton_devolver, wxT("tool"), wxBitmap( wxT("Img/Resources/l_devolver.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Registrar devolución del libro seleccionado."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vl_boton_detalles, wxT("tool"), wxBitmap( wxT("Img/Resources/detalles.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver detalles del libro seleccionado..."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vl_boton_estadisticas, wxT("tool"), wxBitmap( wxT("Img/Resources/estadisticas.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver estadísticas..."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	wxString orden_librosChoices[] = { wxT("ordenar por título"), wxT("ordenar por préstamos"), wxT("ordenar por autor"), wxT("ordenar por fecha de alta") };
	int orden_librosNChoices = sizeof( orden_librosChoices ) / sizeof( wxString );
	orden_libros = new wxChoice( MyToolbar, wxID_ANY, wxDefaultPosition, wxDefaultSize, orden_librosNChoices, orden_librosChoices, 0 );
	orden_libros->SetSelection( 0 );
	orden_libros->SetToolTip( wxT("Elegir el criterio para ordenar los libros de la grilla.") );
	
	MyToolbar->AddControl( orden_libros );
	MyToolbar->AddSeparator(); 
	barra_busqueda = new wxSearchCtrl( MyToolbar, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	#ifndef __WXMAC__
	barra_busqueda->ShowSearchButton( true );
	#endif
	barra_busqueda->ShowCancelButton( false );
	MyToolbar->AddControl( barra_busqueda );
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vl_boton_restaurar, wxT("tool"), wxBitmap( wxT("Img/Resources/actualizar.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Restaurar vista."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vl_boton_cdu, wxT("tool"), wxBitmap( wxT("Img/Resources/btn_cdu.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver las herramientas de filtrado CDU..."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vl_boton_ayuda, wxT("tool"), wxBitmap( wxT("Img/Resources/ayuda.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver la ayuda..."), wxEmptyString ); 
	MyToolbar->Realize();
	
	bSizer8->Add( MyToolbar, 0, wxEXPAND, 5 );
	
	wxString eleccion_principalChoices[] = { wxT("Generalidades. Ciencia y conocimiento. Organización. Información. Documentación. Enciclopedias. Biblioteconomía. Instituciones. Documentos y publicaciones"), wxT("Filosofía. Psicología."), wxT("Religión. Teología."), wxT("Ciencias sociales."), wxT("Vacante"), wxT("Matemáticas. Ciencias Naturales."), wxT("Ciencias aplicadas. Medicina. Tecnología."), wxT("Bellas artes. Juegos. Espectáculos. Deportes."), wxT("Lenguaje. Lingüística. Literatura."), wxT("Geografía. Biografías. Historia.") };
	int eleccion_principalNChoices = sizeof( eleccion_principalChoices ) / sizeof( wxString );
	eleccion_principal = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, eleccion_principalNChoices, eleccion_principalChoices, 0 );
	eleccion_principal->SetSelection( 0 );
	eleccion_principal->Hide();
	
	bSizer8->Add( eleccion_principal, 0, wxALL|wxEXPAND, 1 );
	
	wxArrayString eleccion_sub_1Choices;
	eleccion_sub_1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, eleccion_sub_1Choices, 0 );
	eleccion_sub_1->SetSelection( 0 );
	eleccion_sub_1->Hide();
	
	bSizer8->Add( eleccion_sub_1, 0, wxALL|wxEXPAND, 1 );
	
	wxArrayString eleccion_sub_2Choices;
	eleccion_sub_2 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, eleccion_sub_2Choices, 0 );
	eleccion_sub_2->SetSelection( 0 );
	eleccion_sub_2->Hide();
	
	bSizer8->Add( eleccion_sub_2, 0, wxALL|wxEXPAND, 1 );
	
	grilla_libros = new mi_grilla( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	grilla_libros->CreateGrid( 30, 5 );
	grilla_libros->EnableEditing( false );
	grilla_libros->EnableGridLines( true );
	grilla_libros->EnableDragGridSize( false );
	grilla_libros->SetMargins( 0, 0 );
	
	// Columns
	grilla_libros->SetColSize( 0, 200 );
	grilla_libros->SetColSize( 1, 150 );
	grilla_libros->SetColSize( 2, 240 );
	grilla_libros->SetColSize( 3, 80 );
	grilla_libros->SetColSize( 4, 80 );
	grilla_libros->EnableDragColMove( false );
	grilla_libros->EnableDragColSize( true );
	grilla_libros->SetColLabelSize( 20 );
	grilla_libros->SetColLabelValue( 0, wxT("Título") );
	grilla_libros->SetColLabelValue( 1, wxT("Autor") );
	grilla_libros->SetColLabelValue( 2, wxT("Datos de publicación") );
	grilla_libros->SetColLabelValue( 3, wxT("T/préstamo") );
	grilla_libros->SetColLabelValue( 4, wxT("Ubicación") );
	grilla_libros->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	grilla_libros->EnableDragRowSize( true );
	grilla_libros->SetRowLabelSize( 0 );
	grilla_libros->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	grilla_libros->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	menu_grilla = new wxMenu();
	wxMenuItem* menu_libros_detalles;
	menu_libros_detalles = new wxMenuItem( menu_grilla, wxID_ANY, wxString( wxT("Ver detalles....") ) , wxEmptyString, wxITEM_NORMAL );
	menu_grilla->Append( menu_libros_detalles );
	
	wxMenuItem* menu_libros_editar;
	menu_libros_editar = new wxMenuItem( menu_grilla, wxID_ANY, wxString( wxT("Editar...") ) , wxEmptyString, wxITEM_NORMAL );
	menu_grilla->Append( menu_libros_editar );
	
	wxMenuItem* menu_libros_borrar;
	menu_libros_borrar = new wxMenuItem( menu_grilla, wxID_ANY, wxString( wxT("Borrar") ) , wxEmptyString, wxITEM_NORMAL );
	menu_grilla->Append( menu_libros_borrar );
	
	grilla_libros->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( vLibros::grilla_librosOnContextMenu ), NULL, this ); 
	
	bSizer8->Add( grilla_libros, 1, wxALL|wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer8->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	boton_aceptar = new wxButton( this, wxID_ANY, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( boton_aceptar, 0, wxALL, 5 );
	
	boton_cancelar = new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( boton_cancelar, 0, wxALL, 5 );
	
	bSizer8->Add( bSizer10, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer8 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( id_vl_boton_borrar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_borrar ) );
	this->Connect( id_vl_boton_agregar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_agregar ) );
	this->Connect( id_vl_boton_prestar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_prestar ) );
	this->Connect( id_vl_boton_devolver, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_devolver ) );
	this->Connect( id_vl_boton_detalles, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_detalles ) );
	this->Connect( id_vl_boton_estadisticas, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_estadisticas ) );
	orden_libros->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vLibros::cambio_orden ), NULL, this );
	barra_busqueda->Connect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( vLibros::click_buscar ), NULL, this );
	barra_busqueda->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( vLibros::click_buscar ), NULL, this );
	barra_busqueda->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vLibros::click_buscar ), NULL, this );
	this->Connect( id_vl_boton_restaurar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_restaurar ) );
	this->Connect( id_vl_boton_cdu, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_CDU ) );
	this->Connect( id_vl_boton_ayuda, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_ayuda ) );
	eleccion_principal->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vLibros::principal_elegido ), NULL, this );
	eleccion_sub_1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vLibros::sub_1_elegido ), NULL, this );
	eleccion_sub_2->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vLibros::sub_2_elegido ), NULL, this );
	grilla_libros->Connect( wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler( vLibros::click_izq_grilla ), NULL, this );
	grilla_libros->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( vLibros::Dclick_grilla ), NULL, this );
	grilla_libros->Connect( wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler( vLibros::click_der_grilla ), NULL, this );
	this->Connect( menu_libros_detalles->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vLibros::click_boton_detalles ) );
	this->Connect( menu_libros_editar->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vLibros::click_editar_libro ) );
	this->Connect( menu_libros_borrar->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vLibros::click_boton_borrar ) );
	boton_aceptar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vLibros::click_boton_aceptar ), NULL, this );
	boton_cancelar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vLibros::click_boton_cancelar ), NULL, this );
}

vLibros::~vLibros()
{
	// Disconnect Events
	this->Disconnect( id_vl_boton_borrar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_borrar ) );
	this->Disconnect( id_vl_boton_agregar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_agregar ) );
	this->Disconnect( id_vl_boton_prestar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_prestar ) );
	this->Disconnect( id_vl_boton_devolver, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_devolver ) );
	this->Disconnect( id_vl_boton_detalles, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_detalles ) );
	this->Disconnect( id_vl_boton_estadisticas, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_estadisticas ) );
	orden_libros->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vLibros::cambio_orden ), NULL, this );
	barra_busqueda->Disconnect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( vLibros::click_buscar ), NULL, this );
	barra_busqueda->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( vLibros::click_buscar ), NULL, this );
	barra_busqueda->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vLibros::click_buscar ), NULL, this );
	this->Disconnect( id_vl_boton_restaurar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_restaurar ) );
	this->Disconnect( id_vl_boton_cdu, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_CDU ) );
	this->Disconnect( id_vl_boton_ayuda, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vLibros::click_boton_ayuda ) );
	eleccion_principal->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vLibros::principal_elegido ), NULL, this );
	eleccion_sub_1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vLibros::sub_1_elegido ), NULL, this );
	eleccion_sub_2->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vLibros::sub_2_elegido ), NULL, this );
	grilla_libros->Disconnect( wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler( vLibros::click_izq_grilla ), NULL, this );
	grilla_libros->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( vLibros::Dclick_grilla ), NULL, this );
	grilla_libros->Disconnect( wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler( vLibros::click_der_grilla ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vLibros::click_boton_detalles ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vLibros::click_editar_libro ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vLibros::click_boton_borrar ) );
	boton_aceptar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vLibros::click_boton_aceptar ), NULL, this );
	boton_cancelar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vLibros::click_boton_cancelar ), NULL, this );
	
	delete menu_grilla; 
}

vAutores::vAutores( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	MyToolbar = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL ); 
	MyToolbar->AddTool( id_va_boton_borrar, wxT("tool"), wxBitmap( wxT("Img/Resources/toolbar_del.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Borrar los autores seleccionados de la base de datos."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_va_boton_agregar, wxT("tool"), wxBitmap( wxT("Img/Resources/toolbar_add.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Agregar nuevo autor..."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	barra_busqueda = new wxSearchCtrl( MyToolbar, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	#ifndef __WXMAC__
	barra_busqueda->ShowSearchButton( true );
	#endif
	barra_busqueda->ShowCancelButton( false );
	MyToolbar->AddControl( barra_busqueda );
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_va_boton_restaurar, wxT("tool"), wxBitmap( wxT("Img/Resources/actualizar.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Restaurar vista."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_va_boton_ayuda, wxT("tool"), wxBitmap( wxT("Img/Resources/ayuda.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver la ayuda..."), wxEmptyString ); 
	MyToolbar->Realize();
	
	bSizer14->Add( MyToolbar, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer141;
	bSizer141 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Filtrar por inicial: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer141->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString filtrado_inicialesChoices[] = { wxT("..."), wxT("A"), wxT("B"), wxT("C"), wxT("D"), wxT("E"), wxT("F"), wxT("G"), wxT("H"), wxT("I"), wxT("J"), wxT("K"), wxT("L"), wxT("M"), wxT("N"), wxT("Ñ"), wxT("O"), wxT("P"), wxT("Q"), wxT("R"), wxT("S"), wxT("T"), wxT("U"), wxT("V"), wxT("W"), wxT("X"), wxT("Y"), wxT("Z") };
	int filtrado_inicialesNChoices = sizeof( filtrado_inicialesChoices ) / sizeof( wxString );
	filtrado_iniciales = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, filtrado_inicialesNChoices, filtrado_inicialesChoices, 0 );
	filtrado_iniciales->SetSelection( 0 );
	bSizer141->Add( filtrado_iniciales, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer14->Add( bSizer141, 0, wxEXPAND, 5 );
	
	wxArrayString lista_autoresChoices;
	lista_autores = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, lista_autoresChoices, 0 );
	bSizer14->Add( lista_autores, 1, wxALL|wxEXPAND, 5 );
	
	m_staticline5 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer14->Add( m_staticline5, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );
	
	boton_aceptar = new wxButton( this, wxID_ANY, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( boton_aceptar, 0, wxALL, 5 );
	
	boton_cancelar = new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( boton_cancelar, 0, wxALL, 5 );
	
	bSizer14->Add( bSizer15, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer14 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( id_va_boton_borrar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vAutores::click_boton_borrar ) );
	this->Connect( id_va_boton_agregar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vAutores::click_boton_agregar ) );
	barra_busqueda->Connect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( vAutores::click_buscar ), NULL, this );
	barra_busqueda->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( vAutores::click_buscar ), NULL, this );
	barra_busqueda->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vAutores::click_buscar ), NULL, this );
	this->Connect( id_va_boton_restaurar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vAutores::click_boton_restaurar ) );
	this->Connect( id_va_boton_ayuda, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vAutores::click_boton_ayuda ) );
	filtrado_iniciales->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vAutores::cambio_filtro_iniciales ), NULL, this );
	lista_autores->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( vAutores::Dclick_autor ), NULL, this );
	boton_aceptar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAutores::click_boton_aceptar ), NULL, this );
	boton_cancelar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAutores::click_boton_cancelar ), NULL, this );
}

vAutores::~vAutores()
{
	// Disconnect Events
	this->Disconnect( id_va_boton_borrar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vAutores::click_boton_borrar ) );
	this->Disconnect( id_va_boton_agregar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vAutores::click_boton_agregar ) );
	barra_busqueda->Disconnect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( vAutores::click_buscar ), NULL, this );
	barra_busqueda->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( vAutores::click_buscar ), NULL, this );
	barra_busqueda->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vAutores::click_buscar ), NULL, this );
	this->Disconnect( id_va_boton_restaurar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vAutores::click_boton_restaurar ) );
	this->Disconnect( id_va_boton_ayuda, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vAutores::click_boton_ayuda ) );
	filtrado_iniciales->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vAutores::cambio_filtro_iniciales ), NULL, this );
	lista_autores->Disconnect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( vAutores::Dclick_autor ), NULL, this );
	boton_aceptar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAutores::click_boton_aceptar ), NULL, this );
	boton_cancelar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAutores::click_boton_cancelar ), NULL, this );
	
}

vSocios::vSocios( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	MyToolbar = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL ); 
	MyToolbar->AddTool( id_vs_boton_borrar, wxT("tool"), wxBitmap( wxT("Img/Resources/toolbar_del.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Borrar el socio seleccionado de la base de datos."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vs_boton_agregar, wxT("tool"), wxBitmap( wxT("Img/Resources/toolbar_add.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Agregar nuevo socio..."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vs_boton_prestar, wxT("tool"), wxBitmap( wxT("Img/Resources/l_prestar.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Realizar préstamo..."), wxEmptyString ); 
	MyToolbar->AddTool( id_vs_boton_devolver, wxT("tool"), wxBitmap( wxT("Img/Resources/l_devolver.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Registrar devolución."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vs_boton_detalles, wxT("tool"), wxBitmap( wxT("Img/Resources/detalles.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver detalles del socio seleccionado..."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vs_boton_estadisticas, wxT("tool"), wxBitmap( wxT("Img/Resources/estadisticas.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver estadísticas..."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	wxString orden_sociosChoices[] = { wxT("ordenar por nombre"), wxT("ordenar por edad"), wxT("ordenar por cant lecturas"), wxT("ordenar por fecha de alta"), wxT("ordenar por pendientes"), wxT("ordenar por antigüedad") };
	int orden_sociosNChoices = sizeof( orden_sociosChoices ) / sizeof( wxString );
	orden_socios = new wxChoice( MyToolbar, wxID_ANY, wxDefaultPosition, wxDefaultSize, orden_sociosNChoices, orden_sociosChoices, 0 );
	orden_socios->SetSelection( 0 );
	orden_socios->SetToolTip( wxT("Elegir el criterio para ordenar los socios en la grilla.") );
	
	MyToolbar->AddControl( orden_socios );
	MyToolbar->AddSeparator(); 
	barra_busqueda = new wxSearchCtrl( MyToolbar, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	#ifndef __WXMAC__
	barra_busqueda->ShowSearchButton( true );
	#endif
	barra_busqueda->ShowCancelButton( false );
	MyToolbar->AddControl( barra_busqueda );
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vs_boton_restaurar, wxT("tool"), wxBitmap( wxT("Img/Resources/actualizar.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Restaurar vista."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vs_boton_ayuda, wxT("tool"), wxBitmap( wxT("Img/Resources/ayuda.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver la ayuda..."), wxEmptyString ); 
	MyToolbar->Realize();
	
	bSizer11->Add( MyToolbar, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	grilla_socios = new mi_grilla( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	grilla_socios->CreateGrid( 30, 4 );
	grilla_socios->EnableEditing( false );
	grilla_socios->EnableGridLines( true );
	grilla_socios->EnableDragGridSize( false );
	grilla_socios->SetMargins( 0, 0 );
	
	// Columns
	grilla_socios->SetColSize( 0, 210 );
	grilla_socios->SetColSize( 1, 110 );
	grilla_socios->SetColSize( 2, 110 );
	grilla_socios->SetColSize( 3, 120 );
	grilla_socios->EnableDragColMove( false );
	grilla_socios->EnableDragColSize( true );
	grilla_socios->SetColLabelSize( 20 );
	grilla_socios->SetColLabelValue( 0, wxT("Nombre") );
	grilla_socios->SetColLabelValue( 1, wxT("DNI") );
	grilla_socios->SetColLabelValue( 2, wxT("Nro. socio") );
	grilla_socios->SetColLabelValue( 3, wxT("Libros a devolver") );
	grilla_socios->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	grilla_socios->EnableDragRowSize( true );
	grilla_socios->SetRowLabelSize( 0 );
	grilla_socios->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	grilla_socios->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	menu_grilla = new wxMenu();
	wxMenuItem* menu_socios_detalles;
	menu_socios_detalles = new wxMenuItem( menu_grilla, wxID_ANY, wxString( wxT("Ver detalles....") ) , wxEmptyString, wxITEM_NORMAL );
	menu_grilla->Append( menu_socios_detalles );
	
	wxMenuItem* menu_socios_editar;
	menu_socios_editar = new wxMenuItem( menu_grilla, wxID_ANY, wxString( wxT("Editar...") ) , wxEmptyString, wxITEM_NORMAL );
	menu_grilla->Append( menu_socios_editar );
	
	wxMenuItem* menu_socios_borrar;
	menu_socios_borrar = new wxMenuItem( menu_grilla, wxID_ANY, wxString( wxT("Borrar") ) , wxEmptyString, wxITEM_NORMAL );
	menu_grilla->Append( menu_socios_borrar );
	
	grilla_socios->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( vSocios::grilla_sociosOnContextMenu ), NULL, this ); 
	
	bSizer13->Add( grilla_socios, 1, wxALL|wxEXPAND, 5 );
	
	foto_socio = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("Img/Resources/no-user.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( foto_socio, 0, wxALL, 5 );
	
	bSizer11->Add( bSizer13, 1, wxEXPAND, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer11->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	boton_aceptar = new wxButton( this, wxID_ANY, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( boton_aceptar, 0, wxALL, 5 );
	
	boton_cancelar = new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( boton_cancelar, 0, wxALL, 5 );
	
	bSizer11->Add( bSizer12, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer11 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( id_vs_boton_borrar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vSocios::click_boton_borrar ) );
	this->Connect( id_vs_boton_agregar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vSocios::click_boton_agregar ) );
	this->Connect( id_vs_boton_prestar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vSocios::click_boton_prestar ) );
	this->Connect( id_vs_boton_devolver, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vSocios::click_boton_devolver ) );
	this->Connect( id_vs_boton_detalles, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vSocios::click_boton_detalles ) );
	this->Connect( id_vs_boton_estadisticas, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vSocios::click_boton_estadisticas ) );
	orden_socios->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vSocios::cambio_orden ), NULL, this );
	barra_busqueda->Connect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( vSocios::click_buscar ), NULL, this );
	barra_busqueda->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( vSocios::click_buscar ), NULL, this );
	barra_busqueda->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vSocios::click_buscar ), NULL, this );
	this->Connect( id_vs_boton_restaurar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vSocios::click_boton_restaurar ) );
	this->Connect( id_vs_boton_ayuda, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vSocios::click_boton_ayuda ) );
	grilla_socios->Connect( wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler( vSocios::click_izq_grilla ), NULL, this );
	grilla_socios->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( vSocios::Dclick_grilla ), NULL, this );
	grilla_socios->Connect( wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler( vSocios::click_der_grilla ), NULL, this );
	this->Connect( menu_socios_detalles->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vSocios::click_boton_detalles ) );
	this->Connect( menu_socios_editar->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vSocios::click_editar_socio ) );
	this->Connect( menu_socios_borrar->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vSocios::click_boton_borrar ) );
	boton_aceptar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vSocios::click_boton_aceptar ), NULL, this );
	boton_cancelar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vSocios::click_boton_cancelar ), NULL, this );
}

vSocios::~vSocios()
{
	// Disconnect Events
	this->Disconnect( id_vs_boton_borrar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vSocios::click_boton_borrar ) );
	this->Disconnect( id_vs_boton_agregar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vSocios::click_boton_agregar ) );
	this->Disconnect( id_vs_boton_prestar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vSocios::click_boton_prestar ) );
	this->Disconnect( id_vs_boton_devolver, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vSocios::click_boton_devolver ) );
	this->Disconnect( id_vs_boton_detalles, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vSocios::click_boton_detalles ) );
	this->Disconnect( id_vs_boton_estadisticas, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vSocios::click_boton_estadisticas ) );
	orden_socios->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vSocios::cambio_orden ), NULL, this );
	barra_busqueda->Disconnect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( vSocios::click_buscar ), NULL, this );
	barra_busqueda->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( vSocios::click_buscar ), NULL, this );
	barra_busqueda->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vSocios::click_buscar ), NULL, this );
	this->Disconnect( id_vs_boton_restaurar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vSocios::click_boton_restaurar ) );
	this->Disconnect( id_vs_boton_ayuda, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vSocios::click_boton_ayuda ) );
	grilla_socios->Disconnect( wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler( vSocios::click_izq_grilla ), NULL, this );
	grilla_socios->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( vSocios::Dclick_grilla ), NULL, this );
	grilla_socios->Disconnect( wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler( vSocios::click_der_grilla ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vSocios::click_boton_detalles ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vSocios::click_editar_socio ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vSocios::click_boton_borrar ) );
	boton_aceptar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vSocios::click_boton_aceptar ), NULL, this );
	boton_cancelar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vSocios::click_boton_cancelar ), NULL, this );
	
	delete menu_grilla; 
}

vDevolverLibro::vDevolverLibro( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer120;
	bSizer120 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText106 = new wxStaticText( this, wxID_ANY, wxT("Elija los libros pendientes a registrar como devueltos:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText106->Wrap( -1 );
	bSizer120->Add( m_staticText106, 0, wxALL, 5 );
	
	wxArrayString eleccion_pendientesChoices;
	eleccion_pendientes = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, eleccion_pendientesChoices, 0 );
	bSizer120->Add( eleccion_pendientes, 1, wxALL|wxEXPAND, 5 );
	
	m_staticline18 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer120->Add( m_staticline18, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxHORIZONTAL );
	
	boton_aceptar = new wxButton( this, wxID_ANY, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer121->Add( boton_aceptar, 0, wxALL, 5 );
	
	boton_cancelar = new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer121->Add( boton_cancelar, 0, wxALL, 5 );
	
	bSizer120->Add( bSizer121, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer120 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	boton_aceptar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vDevolverLibro::click_boton_aceptar ), NULL, this );
	boton_cancelar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vDevolverLibro::click_boton_cancelar ), NULL, this );
}

vDevolverLibro::~vDevolverLibro()
{
	// Disconnect Events
	boton_aceptar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vDevolverLibro::click_boton_aceptar ), NULL, this );
	boton_cancelar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vDevolverLibro::click_boton_cancelar ), NULL, this );
	
}

vBibliotecarios::vBibliotecarios( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	MyToolbar = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL ); 
	MyToolbar->AddTool( id_vb_boton_borrar, wxT("tool"), wxBitmap( wxT("Img/Resources/toolbar_del.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Borrar el bibliotecario seleccionado de la base de datos."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vb_boton_agregar, wxT("tool"), wxBitmap( wxT("Img/Resources/toolbar_add.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Agregar nuevo bibliotecario..."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vb_boton_detalles, wxT("tool"), wxBitmap( wxT("Img/Resources/detalles.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver detalles del bibliotecario seleccionado..."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vb_boton_estadisticas, wxT("tool"), wxBitmap( wxT("Img/Resources/estadisticas.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver estadísticas..."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	wxString orden_bibliotecariosChoices[] = { wxT("ordenar por nombre"), wxT("ordenar por cant préstamos"), wxT("ordenar por antigüedad"), wxT("ordenar por fecha de alta"), wxT("ordenar por salario") };
	int orden_bibliotecariosNChoices = sizeof( orden_bibliotecariosChoices ) / sizeof( wxString );
	orden_bibliotecarios = new wxChoice( MyToolbar, wxID_ANY, wxDefaultPosition, wxDefaultSize, orden_bibliotecariosNChoices, orden_bibliotecariosChoices, 0 );
	orden_bibliotecarios->SetSelection( 0 );
	orden_bibliotecarios->SetToolTip( wxT("Elegir el criterio para ordenar los socios en la grilla.") );
	
	MyToolbar->AddControl( orden_bibliotecarios );
	MyToolbar->AddSeparator(); 
	barra_busqueda = new wxSearchCtrl( MyToolbar, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	#ifndef __WXMAC__
	barra_busqueda->ShowSearchButton( true );
	#endif
	barra_busqueda->ShowCancelButton( false );
	MyToolbar->AddControl( barra_busqueda );
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vb_boton_restaurar, wxT("tool"), wxBitmap( wxT("Img/Resources/actualizar.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Restaurar vista."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vb_boton_ayuda, wxT("tool"), wxBitmap( wxT("Img/Resources/ayuda.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver la ayuda..."), wxEmptyString ); 
	MyToolbar->Realize();
	
	bSizer11->Add( MyToolbar, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	grilla_bibliotecarios = new mi_grilla( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	grilla_bibliotecarios->CreateGrid( 30, 5 );
	grilla_bibliotecarios->EnableEditing( false );
	grilla_bibliotecarios->EnableGridLines( true );
	grilla_bibliotecarios->EnableDragGridSize( false );
	grilla_bibliotecarios->SetMargins( 0, 0 );
	
	// Columns
	grilla_bibliotecarios->SetColSize( 0, 210 );
	grilla_bibliotecarios->SetColSize( 1, 50 );
	grilla_bibliotecarios->SetColSize( 2, 100 );
	grilla_bibliotecarios->SetColSize( 3, 100 );
	grilla_bibliotecarios->EnableDragColMove( false );
	grilla_bibliotecarios->EnableDragColSize( true );
	grilla_bibliotecarios->SetColLabelSize( 20 );
	grilla_bibliotecarios->SetColLabelValue( 0, wxT("Nombre") );
	grilla_bibliotecarios->SetColLabelValue( 1, wxT("Edad") );
	grilla_bibliotecarios->SetColLabelValue( 2, wxT("Cant. préstamos") );
	grilla_bibliotecarios->SetColLabelValue( 3, wxT("Salario") );
	grilla_bibliotecarios->SetColLabelValue( 4, wxT("Antigüedad") );
	grilla_bibliotecarios->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	grilla_bibliotecarios->EnableDragRowSize( true );
	grilla_bibliotecarios->SetRowLabelSize( 0 );
	grilla_bibliotecarios->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	grilla_bibliotecarios->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	menu_grilla = new wxMenu();
	wxMenuItem* menu_bib_detalles;
	menu_bib_detalles = new wxMenuItem( menu_grilla, wxID_ANY, wxString( wxT("Ver detalles....") ) , wxEmptyString, wxITEM_NORMAL );
	menu_grilla->Append( menu_bib_detalles );
	
	wxMenuItem* menu_bib_editar;
	menu_bib_editar = new wxMenuItem( menu_grilla, wxID_ANY, wxString( wxT("Editar...") ) , wxEmptyString, wxITEM_NORMAL );
	menu_grilla->Append( menu_bib_editar );
	
	wxMenuItem* menu_bib_borrar;
	menu_bib_borrar = new wxMenuItem( menu_grilla, wxID_ANY, wxString( wxT("Borrar") ) , wxEmptyString, wxITEM_NORMAL );
	menu_grilla->Append( menu_bib_borrar );
	
	grilla_bibliotecarios->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( vBibliotecarios::grilla_bibliotecariosOnContextMenu ), NULL, this ); 
	
	bSizer13->Add( grilla_bibliotecarios, 1, wxALL|wxEXPAND, 5 );
	
	foto_bibliotecario = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("Img/Resources/no-user.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( foto_bibliotecario, 0, wxALL, 5 );
	
	bSizer11->Add( bSizer13, 1, wxEXPAND, 5 );
	
	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer11->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	boton_aceptar = new wxButton( this, wxID_ANY, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( boton_aceptar, 0, wxALL, 5 );
	
	boton_cancelar = new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( boton_cancelar, 0, wxALL, 5 );
	
	bSizer11->Add( bSizer12, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer11 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( id_vb_boton_borrar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vBibliotecarios::click_boton_borrar ) );
	this->Connect( id_vb_boton_agregar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vBibliotecarios::click_boton_agregar ) );
	this->Connect( id_vb_boton_detalles, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vBibliotecarios::click_boton_detalles ) );
	this->Connect( id_vb_boton_estadisticas, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vBibliotecarios::click_boton_estadisticas ) );
	orden_bibliotecarios->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vBibliotecarios::cambio_orden ), NULL, this );
	barra_busqueda->Connect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( vBibliotecarios::click_buscar ), NULL, this );
	barra_busqueda->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( vBibliotecarios::click_buscar ), NULL, this );
	barra_busqueda->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vBibliotecarios::click_buscar ), NULL, this );
	this->Connect( id_vb_boton_restaurar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vBibliotecarios::click_boton_restaurar ) );
	this->Connect( id_vb_boton_ayuda, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vBibliotecarios::click_boton_ayuda ) );
	grilla_bibliotecarios->Connect( wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler( vBibliotecarios::click_izq_grilla ), NULL, this );
	grilla_bibliotecarios->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( vBibliotecarios::Dclick_grilla ), NULL, this );
	grilla_bibliotecarios->Connect( wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler( vBibliotecarios::click_der_grilla ), NULL, this );
	this->Connect( menu_bib_detalles->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vBibliotecarios::click_boton_detalles ) );
	this->Connect( menu_bib_editar->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vBibliotecarios::click_editar_bib ) );
	this->Connect( menu_bib_borrar->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vBibliotecarios::click_boton_borrar ) );
	boton_aceptar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vBibliotecarios::click_boton_aceptar ), NULL, this );
	boton_cancelar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vBibliotecarios::click_boton_cancelar ), NULL, this );
}

vBibliotecarios::~vBibliotecarios()
{
	// Disconnect Events
	this->Disconnect( id_vb_boton_borrar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vBibliotecarios::click_boton_borrar ) );
	this->Disconnect( id_vb_boton_agregar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vBibliotecarios::click_boton_agregar ) );
	this->Disconnect( id_vb_boton_detalles, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vBibliotecarios::click_boton_detalles ) );
	this->Disconnect( id_vb_boton_estadisticas, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vBibliotecarios::click_boton_estadisticas ) );
	orden_bibliotecarios->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vBibliotecarios::cambio_orden ), NULL, this );
	barra_busqueda->Disconnect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( vBibliotecarios::click_buscar ), NULL, this );
	barra_busqueda->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( vBibliotecarios::click_buscar ), NULL, this );
	barra_busqueda->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vBibliotecarios::click_buscar ), NULL, this );
	this->Disconnect( id_vb_boton_restaurar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vBibliotecarios::click_boton_restaurar ) );
	this->Disconnect( id_vb_boton_ayuda, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vBibliotecarios::click_boton_ayuda ) );
	grilla_bibliotecarios->Disconnect( wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler( vBibliotecarios::click_izq_grilla ), NULL, this );
	grilla_bibliotecarios->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( vBibliotecarios::Dclick_grilla ), NULL, this );
	grilla_bibliotecarios->Disconnect( wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler( vBibliotecarios::click_der_grilla ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vBibliotecarios::click_boton_detalles ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vBibliotecarios::click_editar_bib ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( vBibliotecarios::click_boton_borrar ) );
	boton_aceptar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vBibliotecarios::click_boton_aceptar ), NULL, this );
	boton_cancelar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vBibliotecarios::click_boton_cancelar ), NULL, this );
	
	delete menu_grilla; 
}

vAgregarLibro::vAgregarLibro( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Título:          "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	m_staticText2->SetToolTip( wxT("Escriba el título del libro en el recuadro de la derecha.") );
	
	bSizer23->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_titulo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	renglon_titulo->SetMaxLength( 99 ); 
	bSizer23->Add( renglon_titulo, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer22->Add( bSizer23, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Autores:      "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	m_staticText4->SetToolTip( wxT("Haga click en el botón \"Agregar...\" de la derecha y seleccione los autores del libro en la ventana emergente.") );
	
	bSizer25->Add( m_staticText4, 0, wxALL, 5 );
	
	wxArrayString cuadro_autoresChoices;
	cuadro_autores = new wxCheckListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cuadro_autoresChoices, 0 );
	bSizer25->Add( cuadro_autores, 1, wxALL, 5 );
	
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxVERTICAL );
	
	boton_agregar_autores = new wxButton( this, wxID_ANY, wxT("Agregar..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( boton_agregar_autores, 0, wxALL, 5 );
	
	boton_borrar_autores = new wxButton( this, wxID_ANY, wxT("Borrar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( boton_borrar_autores, 0, wxALL, 5 );
	
	bSizer25->Add( bSizer26, 0, 0, 5 );
	
	bSizer22->Add( bSizer25, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Resumen:    "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	m_staticText5->SetToolTip( wxT("Escriba una breve reseña del libro en el recuadro de la derecha.") );
	
	bSizer27->Add( m_staticText5, 0, wxALL, 5 );
	
	renglon_resumen = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	renglon_resumen->SetMaxLength( 1999 ); 
	bSizer27->Add( renglon_resumen, 1, wxALL|wxEXPAND, 5 );
	
	bSizer22->Add( bSizer27, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Publicación: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	m_staticText6->SetToolTip( wxT("Ingrese los datos de la publicación (Nro edición. Lugar: Editorial, año.-cantidad de páginas) en el recuadro de la derecha.") );
	
	bSizer28->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_publicacion = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	renglon_publicacion->SetMaxLength( 199 ); 
	bSizer28->Add( renglon_publicacion, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer22->Add( bSizer28, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText61 = new wxStaticText( this, wxID_ANY, wxT("Url:              "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText61->Wrap( -1 );
	m_staticText61->SetToolTip( wxT("Ingrese la dirección de una página web con más información sobre el libro en el recuadro de la derecha.") );
	
	bSizer24->Add( m_staticText61, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_url = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	renglon_url->SetMaxLength( 99 ); 
	bSizer24->Add( renglon_url, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	boton_ir = new wxButton( this, wxID_ANY, wxT("ir"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer24->Add( boton_ir, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer22->Add( bSizer24, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer251;
	bSizer251 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Contenido:  "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	m_staticText7->SetToolTip( wxT("Ingrese palabras clave (o tags) que representen el contenido del libro, separados por coma, en el recuadro de la derecha.") );
	
	bSizer251->Add( m_staticText7, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_tags = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	renglon_tags->SetMaxLength( 499 ); 
	bSizer251->Add( renglon_tags, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer22->Add( bSizer251, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer261;
	bSizer261 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer261->Add( 70, 0, 0, wxEXPAND, 5 );
	
	wxString cuadro_tipo_prestamoChoices[] = { wxT("A domicilio."), wxT("Sólo consulta en sala de lectura.") };
	int cuadro_tipo_prestamoNChoices = sizeof( cuadro_tipo_prestamoChoices ) / sizeof( wxString );
	cuadro_tipo_prestamo = new wxRadioBox( this, wxID_ANY, wxT("Tipo de préstamo"), wxDefaultPosition, wxDefaultSize, cuadro_tipo_prestamoNChoices, cuadro_tipo_prestamoChoices, 2, wxRA_SPECIFY_ROWS );
	cuadro_tipo_prestamo->SetSelection( 0 );
	bSizer261->Add( cuadro_tipo_prestamo, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer116;
	bSizer116 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer116->Add( 0, 0, 1, wxEXPAND, 5 );
	
	boton_ingresar_cdu = new wxButton( this, wxID_ANY, wxT("Ingresar ubicación..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer116->Add( boton_ingresar_cdu, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	txt_ubicacion_ok = new wxStaticText( this, wxID_ANY, wxT("La ubicación se ha registrado."), wxDefaultPosition, wxDefaultSize, 0 );
	txt_ubicacion_ok->Wrap( -1 );
	txt_ubicacion_ok->SetForegroundColour( wxColour( 53, 255, 53 ) );
	txt_ubicacion_ok->Hide();
	
	bSizer116->Add( txt_ubicacion_ok, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	renglon_ubicacion = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer116->Add( renglon_ubicacion, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	txt_ubicacion_no = new wxStaticText( this, wxID_ANY, wxT("No ha ingresado la ubicación."), wxDefaultPosition, wxDefaultSize, 0 );
	txt_ubicacion_no->Wrap( -1 );
	txt_ubicacion_no->SetForegroundColour( wxColour( 255, 0, 0 ) );
	
	bSizer116->Add( txt_ubicacion_no, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer116->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizer261->Add( bSizer116, 1, wxEXPAND, 5 );
	
	bSizer22->Add( bSizer261, 0, wxEXPAND, 5 );
	
	m_staticline5 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer22->Add( m_staticline5, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer271;
	bSizer271 = new wxBoxSizer( wxHORIZONTAL );
	
	boton_aceptar = new wxButton( this, wxID_ANY, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer271->Add( boton_aceptar, 0, wxALL, 5 );
	
	boton_cancelar = new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer271->Add( boton_cancelar, 0, wxALL, 5 );
	
	bSizer22->Add( bSizer271, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer22 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	boton_agregar_autores->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarLibro::click_boton_agregar_autores ), NULL, this );
	boton_borrar_autores->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarLibro::click_boton_borrar_autores ), NULL, this );
	boton_ir->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarLibro::click_boton_ir ), NULL, this );
	boton_ingresar_cdu->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarLibro::click_boton_cdu ), NULL, this );
	boton_aceptar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarLibro::click_boton_aceptar ), NULL, this );
	boton_cancelar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarLibro::click_boton_cancelar ), NULL, this );
}

vAgregarLibro::~vAgregarLibro()
{
	// Disconnect Events
	boton_agregar_autores->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarLibro::click_boton_agregar_autores ), NULL, this );
	boton_borrar_autores->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarLibro::click_boton_borrar_autores ), NULL, this );
	boton_ir->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarLibro::click_boton_ir ), NULL, this );
	boton_ingresar_cdu->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarLibro::click_boton_cdu ), NULL, this );
	boton_aceptar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarLibro::click_boton_aceptar ), NULL, this );
	boton_cancelar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarLibro::click_boton_cancelar ), NULL, this );
	
}

vIngresarCDU::vIngresarCDU( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer117;
	bSizer117 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer120;
	bSizer120 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText100 = new wxStaticText( this, wxID_ANY, wxT("Grupo principal:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText100->Wrap( -1 );
	bSizer120->Add( m_staticText100, 0, wxALL, 5 );
	
	wxString eleccion_principalChoices[] = { wxT("Generalidades. Ciencia y conocimiento. Organización. Información. Documentación. Enciclopedias. Biblioteconomía. Instituciones. Documentos y publicaciones"), wxT("Filosofía. Psicología."), wxT("Religión. Teología."), wxT("Ciencias sociales."), wxT("Vacante"), wxT("Matemáticas. Ciencias Naturales."), wxT("Ciencias aplicadas. Medicina. Tecnología."), wxT("Bellas artes. Juegos. Espectáculos. Deportes."), wxT("Lenguaje. Lingüística. Literatura."), wxT("Geografía. Biografías. Historia.") };
	int eleccion_principalNChoices = sizeof( eleccion_principalChoices ) / sizeof( wxString );
	eleccion_principal = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, eleccion_principalNChoices, eleccion_principalChoices, 0 );
	eleccion_principal->SetSelection( 0 );
	bSizer120->Add( eleccion_principal, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText101 = new wxStaticText( this, wxID_ANY, wxT("Subgrupo 1:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText101->Wrap( -1 );
	bSizer120->Add( m_staticText101, 0, wxALL, 5 );
	
	wxArrayString eleccion_sub_1Choices;
	eleccion_sub_1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, eleccion_sub_1Choices, 0 );
	eleccion_sub_1->SetSelection( 0 );
	bSizer120->Add( eleccion_sub_1, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText102 = new wxStaticText( this, wxID_ANY, wxT("Subgrupo 2:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText102->Wrap( -1 );
	bSizer120->Add( m_staticText102, 0, wxALL, 5 );
	
	wxArrayString eleccion_sub_2Choices;
	eleccion_sub_2 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, eleccion_sub_2Choices, 0 );
	eleccion_sub_2->SetSelection( 0 );
	bSizer120->Add( eleccion_sub_2, 0, wxALL|wxEXPAND, 5 );
	
	m_staticText103 = new wxStaticText( this, wxID_ANY, wxT("Inicial del apellido del autor:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText103->Wrap( -1 );
	bSizer120->Add( m_staticText103, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString eleccion_inicial_apeChoices[] = { wxT("A"), wxT("B"), wxT("C"), wxT("D"), wxT("E"), wxT("F"), wxT("G"), wxT("H"), wxT("I"), wxT("J"), wxT("K"), wxT("L"), wxT("M"), wxT("N"), wxT("Ñ"), wxT("O"), wxT("P"), wxT("Q"), wxT("R"), wxT("S"), wxT("T"), wxT("U"), wxT("V"), wxT("W"), wxT("X"), wxT("Y"), wxT("Z") };
	int eleccion_inicial_apeNChoices = sizeof( eleccion_inicial_apeChoices ) / sizeof( wxString );
	eleccion_inicial_ape = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, eleccion_inicial_apeNChoices, eleccion_inicial_apeChoices, 0 );
	eleccion_inicial_ape->SetSelection( 0 );
	bSizer120->Add( eleccion_inicial_ape, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText104 = new wxStaticText( this, wxID_ANY, wxT("Inicial del nombre del autor:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText104->Wrap( -1 );
	bSizer120->Add( m_staticText104, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString eleccion_inicial_nomChoices[] = { wxT("A"), wxT("B"), wxT("C"), wxT("D"), wxT("E"), wxT("F"), wxT("G"), wxT("H"), wxT("I"), wxT("J"), wxT("K"), wxT("L"), wxT("M"), wxT("N"), wxT("Ñ"), wxT("O"), wxT("P"), wxT("Q"), wxT("R"), wxT("S"), wxT("T"), wxT("U"), wxT("V"), wxT("W"), wxT("X"), wxT("Y"), wxT("Z") };
	int eleccion_inicial_nomNChoices = sizeof( eleccion_inicial_nomChoices ) / sizeof( wxString );
	eleccion_inicial_nom = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, eleccion_inicial_nomNChoices, eleccion_inicial_nomChoices, 0 );
	eleccion_inicial_nom->SetSelection( 0 );
	bSizer120->Add( eleccion_inicial_nom, 0, wxALL, 5 );
	
	bSizer117->Add( bSizer120, 1, wxEXPAND, 5 );
	
	m_staticline17 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer117->Add( m_staticline17, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer119;
	bSizer119 = new wxBoxSizer( wxHORIZONTAL );
	
	boton_aceptar = new wxButton( this, wxID_ANY, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer119->Add( boton_aceptar, 0, wxALL, 5 );
	
	boton_cancelar = new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer119->Add( boton_cancelar, 0, wxALL, 5 );
	
	bSizer117->Add( bSizer119, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer117 );
	this->Layout();
	bSizer117->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	eleccion_principal->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vIngresarCDU::principal_elegido ), NULL, this );
	eleccion_sub_1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vIngresarCDU::sub_1_elegido ), NULL, this );
	eleccion_sub_2->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vIngresarCDU::sub_2_elegido ), NULL, this );
	boton_aceptar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vIngresarCDU::click_boton_aceptar ), NULL, this );
	boton_cancelar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vIngresarCDU::click_boton_cancelar ), NULL, this );
}

vIngresarCDU::~vIngresarCDU()
{
	// Disconnect Events
	eleccion_principal->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vIngresarCDU::principal_elegido ), NULL, this );
	eleccion_sub_1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vIngresarCDU::sub_1_elegido ), NULL, this );
	eleccion_sub_2->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vIngresarCDU::sub_2_elegido ), NULL, this );
	boton_aceptar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vIngresarCDU::click_boton_aceptar ), NULL, this );
	boton_cancelar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vIngresarCDU::click_boton_cancelar ), NULL, this );
	
}

vAgregarAutor::vAgregarAutor( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Nombre:  "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	m_staticText2->SetToolTip( wxT("Escriba el nombre del autor en formato \"Apellido, Nombres\" en el recuadro de la derecha.") );
	
	bSizer23->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_nombre = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	renglon_nombre->SetMaxLength( 99 ); 
	bSizer23->Add( renglon_nombre, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer22->Add( bSizer23, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Resumen:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	m_staticText5->SetToolTip( wxT("Escriba un breve resumen biográfico del autor en el recuadro de la derecha.") );
	
	bSizer27->Add( m_staticText5, 0, wxALL, 5 );
	
	renglon_resumen = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	renglon_resumen->SetMaxLength( 1999 ); 
	bSizer27->Add( renglon_resumen, 1, wxALL|wxEXPAND, 5 );
	
	bSizer22->Add( bSizer27, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText61 = new wxStaticText( this, wxID_ANY, wxT("Url:          "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText61->Wrap( -1 );
	m_staticText61->SetToolTip( wxT("Ingrese la dirección de una página web con más información sobre el autor en el recuadro de la derecha.") );
	
	bSizer24->Add( m_staticText61, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_url = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	renglon_url->SetMaxLength( 99 ); 
	bSizer24->Add( renglon_url, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	boton_ir = new wxButton( this, wxID_ANY, wxT("ir"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer24->Add( boton_ir, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer22->Add( bSizer24, 0, wxEXPAND, 5 );
	
	m_staticline5 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer22->Add( m_staticline5, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer271;
	bSizer271 = new wxBoxSizer( wxHORIZONTAL );
	
	boton_aceptar = new wxButton( this, wxID_ANY, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer271->Add( boton_aceptar, 0, wxALL, 5 );
	
	boton_cancelar = new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer271->Add( boton_cancelar, 0, wxALL, 5 );
	
	bSizer22->Add( bSizer271, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer22 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	boton_ir->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarAutor::click_boton_ir ), NULL, this );
	boton_aceptar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarAutor::click_boton_aceptar ), NULL, this );
	boton_cancelar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarAutor::click_boton_cancelar ), NULL, this );
}

vAgregarAutor::~vAgregarAutor()
{
	// Disconnect Events
	boton_ir->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarAutor::click_boton_ir ), NULL, this );
	boton_aceptar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarAutor::click_boton_aceptar ), NULL, this );
	boton_cancelar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarAutor::click_boton_cancelar ), NULL, this );
	
}

vAgregarSocio::vAgregarSocio( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer49;
	bSizer49 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText20 = new wxStaticText( this, wxID_ANY, wxT("Apellido:  "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	bSizer50->Add( m_staticText20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_apellido = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer50->Add( renglon_apellido, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText45 = new wxStaticText( this, wxID_ANY, wxT("Nombres:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText45->Wrap( -1 );
	bSizer50->Add( m_staticText45, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_nombres = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer50->Add( renglon_nombres, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer49->Add( bSizer50, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer501;
	bSizer501 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText201 = new wxStaticText( this, wxID_ANY, wxT("DNI:        "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText201->Wrap( -1 );
	bSizer501->Add( m_staticText201, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_dni = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	renglon_dni->SetMinSize( wxSize( 400,-1 ) );
	
	bSizer501->Add( renglon_dni, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer49->Add( bSizer501, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer502;
	bSizer502 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText202 = new wxStaticText( this, wxID_ANY, wxT("Teléfono:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText202->Wrap( -1 );
	bSizer502->Add( m_staticText202, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_tel = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer502->Add( renglon_tel, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer49->Add( bSizer502, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer503;
	bSizer503 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText203 = new wxStaticText( this, wxID_ANY, wxT("Domicilio: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText203->Wrap( -1 );
	bSizer503->Add( m_staticText203, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_domicilio = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer503->Add( renglon_domicilio, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer49->Add( bSizer503, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer67;
	bSizer67 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText33 = new wxStaticText( this, wxID_ANY, wxT("Fecha de nacimiento:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	bSizer67->Add( m_staticText33, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2029 = new wxStaticText( this, wxID_ANY, wxT("día:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2029->Wrap( -1 );
	bSizer67->Add( m_staticText2029, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString dia_nacChoices[] = { wxT("..."), wxT("1"), wxT("2"), wxT("3"), wxT("4"), wxT("5"), wxT("6"), wxT("7"), wxT("8"), wxT("9"), wxT("10"), wxT("11"), wxT("12"), wxT("13"), wxT("14"), wxT("15"), wxT("16"), wxT("17"), wxT("18"), wxT("19"), wxT("20"), wxT("21"), wxT("22"), wxT("23"), wxT("24"), wxT("25"), wxT("26"), wxT("27"), wxT("28"), wxT("29"), wxT("30"), wxT("31") };
	int dia_nacNChoices = sizeof( dia_nacChoices ) / sizeof( wxString );
	dia_nac = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, dia_nacNChoices, dia_nacChoices, 0 );
	dia_nac->SetSelection( 0 );
	bSizer67->Add( dia_nac, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2023 = new wxStaticText( this, wxID_ANY, wxT("mes:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2023->Wrap( -1 );
	bSizer67->Add( m_staticText2023, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mes_nacChoices[] = { wxT("..."), wxT("enero"), wxT("febrero"), wxT("marzo"), wxT("abril"), wxT("mayo"), wxT("junio"), wxT("julio"), wxT("agosto"), wxT("septiembre"), wxT("octubre"), wxT("noviembre"), wxT("diciembre") };
	int mes_nacNChoices = sizeof( mes_nacChoices ) / sizeof( wxString );
	mes_nac = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, mes_nacNChoices, mes_nacChoices, 0 );
	mes_nac->SetSelection( 0 );
	bSizer67->Add( mes_nac, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2024 = new wxStaticText( this, wxID_ANY, wxT("año:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2024->Wrap( -1 );
	bSizer67->Add( m_staticText2024, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	anyo_nac = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	anyo_nac->SetMaxLength( 4 ); 
	bSizer67->Add( anyo_nac, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer49->Add( bSizer67, 1, wxEXPAND, 5 );
	
	panel_fecha_ingreso = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer68;
	bSizer68 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText43 = new wxStaticText( panel_fecha_ingreso, wxID_ANY, wxT("Fecha de ingreso:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	bSizer68->Add( m_staticText43, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer68->Add( 20, 0, 0, 0, 5 );
	
	boton_ingreso_1 = new wxRadioButton( panel_fecha_ingreso, wxID_ANY, wxT("Fecha actual."), wxDefaultPosition, wxDefaultSize, 0 );
	boton_ingreso_1->SetValue( true ); 
	boton_ingreso_1->SetToolTip( wxT("Selecciona la fecha actual como la fecha de ingreso del socio a la institución.") );
	
	bSizer68->Add( boton_ingreso_1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	boton_ingreso_2 = new wxRadioButton( panel_fecha_ingreso, wxID_ANY, wxT("Ingresar manualmente."), wxDefaultPosition, wxDefaultSize, 0 );
	boton_ingreso_2->SetToolTip( wxT("Si el socio ingresó a la institución en una fecha anterior, elija esta opción para indicarla manualmente.") );
	
	bSizer68->Add( boton_ingreso_2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	panel_fecha_ingreso->SetSizer( bSizer68 );
	panel_fecha_ingreso->Layout();
	bSizer68->Fit( panel_fecha_ingreso );
	bSizer49->Add( panel_fecha_ingreso, 1, wxEXPAND | wxALL, 1 );
	
	ingreso_emergente = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	ingreso_emergente->Hide();
	
	wxBoxSizer* bSizer169;
	bSizer169 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer169->Add( 120, 0, 0, 0, 5 );
	
	m_staticText2013 = new wxStaticText( ingreso_emergente, wxID_ANY, wxT("día:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2013->Wrap( -1 );
	bSizer169->Add( m_staticText2013, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString dia_ingresoChoices[] = { wxT("..."), wxT("1"), wxT("2"), wxT("3"), wxT("4"), wxT("5"), wxT("6"), wxT("7"), wxT("8"), wxT("9"), wxT("10"), wxT("11"), wxT("12"), wxT("13"), wxT("14"), wxT("15"), wxT("16"), wxT("17"), wxT("18"), wxT("19"), wxT("20"), wxT("21"), wxT("22"), wxT("23"), wxT("24"), wxT("25"), wxT("26"), wxT("27"), wxT("28"), wxT("29"), wxT("30"), wxT("31") };
	int dia_ingresoNChoices = sizeof( dia_ingresoChoices ) / sizeof( wxString );
	dia_ingreso = new wxChoice( ingreso_emergente, wxID_ANY, wxDefaultPosition, wxDefaultSize, dia_ingresoNChoices, dia_ingresoChoices, 0 );
	dia_ingreso->SetSelection( 0 );
	bSizer169->Add( dia_ingreso, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2014 = new wxStaticText( ingreso_emergente, wxID_ANY, wxT("mes:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2014->Wrap( -1 );
	bSizer169->Add( m_staticText2014, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mes_ingresoChoices[] = { wxT("..."), wxT("enero"), wxT("febrero"), wxT("marzo"), wxT("abril"), wxT("mayo"), wxT("junio"), wxT("julio"), wxT("agosto"), wxT("septiembre"), wxT("octubre"), wxT("noviembre"), wxT("diciembre") };
	int mes_ingresoNChoices = sizeof( mes_ingresoChoices ) / sizeof( wxString );
	mes_ingreso = new wxChoice( ingreso_emergente, wxID_ANY, wxDefaultPosition, wxDefaultSize, mes_ingresoNChoices, mes_ingresoChoices, 0 );
	mes_ingreso->SetSelection( 0 );
	bSizer169->Add( mes_ingreso, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2015 = new wxStaticText( ingreso_emergente, wxID_ANY, wxT("año:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2015->Wrap( -1 );
	bSizer169->Add( m_staticText2015, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	anyo_ingreso = new wxTextCtrl( ingreso_emergente, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	anyo_ingreso->SetMaxLength( 4 ); 
	bSizer169->Add( anyo_ingreso, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	ingreso_emergente->SetSizer( bSizer169 );
	ingreso_emergente->Layout();
	bSizer169->Fit( ingreso_emergente );
	bSizer49->Add( ingreso_emergente, 1, wxEXPAND | wxALL, 1 );
	
	wxBoxSizer* bSizer69;
	bSizer69 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText46 = new wxStaticText( this, wxID_ANY, wxT("Foto:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	m_staticText46->SetToolTip( wxT("Escriba la dirección en el disco de la foto personal del socio o haga click en el botón \"Explorar\" para buscarla manualmente.") );
	
	bSizer69->Add( m_staticText46, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_foto = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	renglon_foto->SetToolTip( wxT("Escriba la dirección en el disco de la foto personal del socio o haga click en el botón \"Explorar\" para buscarla manualmente.") );
	
	bSizer69->Add( renglon_foto, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	boton_explorar = new wxButton( this, wxID_ANY, wxT("Explorar..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer69->Add( boton_explorar, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer49->Add( bSizer69, 1, wxEXPAND, 5 );
	
	m_staticline8 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer49->Add( m_staticline8, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer70;
	bSizer70 = new wxBoxSizer( wxHORIZONTAL );
	
	boton_aceptar = new wxButton( this, wxID_ANY, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer70->Add( boton_aceptar, 0, wxALL, 5 );
	
	boton_cancelar = new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer70->Add( boton_cancelar, 0, wxALL, 5 );
	
	bSizer49->Add( bSizer70, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer49 );
	this->Layout();
	bSizer49->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	boton_ingreso_1->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( vAgregarSocio::fecha_ingreso_actual ), NULL, this );
	boton_ingreso_2->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( vAgregarSocio::fecha_ingreso_manual ), NULL, this );
	boton_explorar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarSocio::click_boton_explorar ), NULL, this );
	boton_aceptar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarSocio::click_aceptar ), NULL, this );
	boton_cancelar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarSocio::click_cancelar ), NULL, this );
}

vAgregarSocio::~vAgregarSocio()
{
	// Disconnect Events
	boton_ingreso_1->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( vAgregarSocio::fecha_ingreso_actual ), NULL, this );
	boton_ingreso_2->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( vAgregarSocio::fecha_ingreso_manual ), NULL, this );
	boton_explorar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarSocio::click_boton_explorar ), NULL, this );
	boton_aceptar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarSocio::click_aceptar ), NULL, this );
	boton_cancelar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarSocio::click_cancelar ), NULL, this );
	
}

vAgregarBibliotecario::vAgregarBibliotecario( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer49;
	bSizer49 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText20 = new wxStaticText( this, wxID_ANY, wxT("Apellido:  "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	bSizer50->Add( m_staticText20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_apellido = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	renglon_apellido->SetMaxLength( 99 ); 
	bSizer50->Add( renglon_apellido, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText45 = new wxStaticText( this, wxID_ANY, wxT("Nombres:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText45->Wrap( -1 );
	bSizer50->Add( m_staticText45, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_nombres = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	renglon_nombres->SetMaxLength( 99 ); 
	bSizer50->Add( renglon_nombres, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer49->Add( bSizer50, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer501;
	bSizer501 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText201 = new wxStaticText( this, wxID_ANY, wxT("DNI:        "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText201->Wrap( -1 );
	bSizer501->Add( m_staticText201, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_dni = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	renglon_dni->SetMaxLength( 9 ); 
	renglon_dni->SetMinSize( wxSize( 450,-1 ) );
	
	bSizer501->Add( renglon_dni, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer49->Add( bSizer501, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer502;
	bSizer502 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText202 = new wxStaticText( this, wxID_ANY, wxT("Teléfono:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText202->Wrap( -1 );
	bSizer502->Add( m_staticText202, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_tel = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	renglon_tel->SetMaxLength( 49 ); 
	bSizer502->Add( renglon_tel, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer49->Add( bSizer502, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer503;
	bSizer503 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText203 = new wxStaticText( this, wxID_ANY, wxT("Domicilio: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText203->Wrap( -1 );
	bSizer503->Add( m_staticText203, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_domicilio = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	renglon_domicilio->SetMaxLength( 99 ); 
	bSizer503->Add( renglon_domicilio, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer49->Add( bSizer503, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer67;
	bSizer67 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText33 = new wxStaticText( this, wxID_ANY, wxT("Fecha de nacimiento:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	bSizer67->Add( m_staticText33, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2029 = new wxStaticText( this, wxID_ANY, wxT("día:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2029->Wrap( -1 );
	bSizer67->Add( m_staticText2029, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString dia_nacChoices[] = { wxT("..."), wxT("1"), wxT("2"), wxT("3"), wxT("4"), wxT("5"), wxT("6"), wxT("7"), wxT("8"), wxT("9"), wxT("10"), wxT("11"), wxT("12"), wxT("13"), wxT("14"), wxT("15"), wxT("16"), wxT("17"), wxT("18"), wxT("19"), wxT("20"), wxT("21"), wxT("22"), wxT("23"), wxT("24"), wxT("25"), wxT("26"), wxT("27"), wxT("28"), wxT("29"), wxT("30"), wxT("31") };
	int dia_nacNChoices = sizeof( dia_nacChoices ) / sizeof( wxString );
	dia_nac = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, dia_nacNChoices, dia_nacChoices, 0 );
	dia_nac->SetSelection( 0 );
	bSizer67->Add( dia_nac, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2023 = new wxStaticText( this, wxID_ANY, wxT("mes:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2023->Wrap( -1 );
	bSizer67->Add( m_staticText2023, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mes_nacChoices[] = { wxT("..."), wxT("enero"), wxT("febrero"), wxT("marzo"), wxT("abril"), wxT("mayo"), wxT("junio"), wxT("julio"), wxT("agosto"), wxT("septiembre"), wxT("octubre"), wxT("noviembre"), wxT("diciembre") };
	int mes_nacNChoices = sizeof( mes_nacChoices ) / sizeof( wxString );
	mes_nac = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, mes_nacNChoices, mes_nacChoices, 0 );
	mes_nac->SetSelection( 0 );
	bSizer67->Add( mes_nac, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2024 = new wxStaticText( this, wxID_ANY, wxT("año:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2024->Wrap( -1 );
	bSizer67->Add( m_staticText2024, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	anyo_nac = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	anyo_nac->SetMaxLength( 4 ); 
	bSizer67->Add( anyo_nac, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer49->Add( bSizer67, 1, wxEXPAND, 5 );
	
	panel_fecha_ingreso = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer68;
	bSizer68 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText43 = new wxStaticText( panel_fecha_ingreso, wxID_ANY, wxT("Fecha de ingreso:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	bSizer68->Add( m_staticText43, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer68->Add( 20, 0, 0, 0, 5 );
	
	boton_ingreso_1 = new wxRadioButton( panel_fecha_ingreso, wxID_ANY, wxT("Fecha actual."), wxDefaultPosition, wxDefaultSize, 0 );
	boton_ingreso_1->SetValue( true ); 
	boton_ingreso_1->SetToolTip( wxT("Selecciona la fecha actual como la fecha de ingreso del socio a la institución.") );
	
	bSizer68->Add( boton_ingreso_1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	boton_ingreso_2 = new wxRadioButton( panel_fecha_ingreso, wxID_ANY, wxT("Ingresar manualmente."), wxDefaultPosition, wxDefaultSize, 0 );
	boton_ingreso_2->SetToolTip( wxT("Si el socio ingresó a la institución en una fecha anterior, elija esta opción para indicarla manualmente.") );
	
	bSizer68->Add( boton_ingreso_2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	panel_fecha_ingreso->SetSizer( bSizer68 );
	panel_fecha_ingreso->Layout();
	bSizer68->Fit( panel_fecha_ingreso );
	bSizer49->Add( panel_fecha_ingreso, 1, wxEXPAND | wxALL, 1 );
	
	ingreso_emergente = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	ingreso_emergente->Hide();
	
	wxBoxSizer* bSizer169;
	bSizer169 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer169->Add( 120, 0, 0, 0, 5 );
	
	m_staticText2013 = new wxStaticText( ingreso_emergente, wxID_ANY, wxT("día:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2013->Wrap( -1 );
	bSizer169->Add( m_staticText2013, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString dia_ingresoChoices[] = { wxT("..."), wxT("1"), wxT("2"), wxT("3"), wxT("4"), wxT("5"), wxT("6"), wxT("7"), wxT("8"), wxT("9"), wxT("10"), wxT("11"), wxT("12"), wxT("13"), wxT("14"), wxT("15"), wxT("16"), wxT("17"), wxT("18"), wxT("19"), wxT("20"), wxT("21"), wxT("22"), wxT("23"), wxT("24"), wxT("25"), wxT("26"), wxT("27"), wxT("28"), wxT("29"), wxT("30"), wxT("31") };
	int dia_ingresoNChoices = sizeof( dia_ingresoChoices ) / sizeof( wxString );
	dia_ingreso = new wxChoice( ingreso_emergente, wxID_ANY, wxDefaultPosition, wxDefaultSize, dia_ingresoNChoices, dia_ingresoChoices, 0 );
	dia_ingreso->SetSelection( 0 );
	bSizer169->Add( dia_ingreso, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2014 = new wxStaticText( ingreso_emergente, wxID_ANY, wxT("mes:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2014->Wrap( -1 );
	bSizer169->Add( m_staticText2014, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString mes_ingresoChoices[] = { wxT("..."), wxT("enero"), wxT("febrero"), wxT("marzo"), wxT("abril"), wxT("mayo"), wxT("junio"), wxT("julio"), wxT("agosto"), wxT("septiembre"), wxT("octubre"), wxT("noviembre"), wxT("diciembre") };
	int mes_ingresoNChoices = sizeof( mes_ingresoChoices ) / sizeof( wxString );
	mes_ingreso = new wxChoice( ingreso_emergente, wxID_ANY, wxDefaultPosition, wxDefaultSize, mes_ingresoNChoices, mes_ingresoChoices, 0 );
	mes_ingreso->SetSelection( 0 );
	bSizer169->Add( mes_ingreso, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText2015 = new wxStaticText( ingreso_emergente, wxID_ANY, wxT("año:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2015->Wrap( -1 );
	bSizer169->Add( m_staticText2015, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	anyo_ingreso = new wxTextCtrl( ingreso_emergente, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer169->Add( anyo_ingreso, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	ingreso_emergente->SetSizer( bSizer169 );
	ingreso_emergente->Layout();
	bSizer169->Fit( ingreso_emergente );
	bSizer49->Add( ingreso_emergente, 1, wxEXPAND | wxALL, 1 );
	
	wxBoxSizer* bSizer69;
	bSizer69 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText46 = new wxStaticText( this, wxID_ANY, wxT("Foto:   "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	m_staticText46->SetToolTip( wxT("Escriba la dirección en el disco de la foto personal del socio o haga click en el botón \"Explorar\" para buscarla manualmente.") );
	
	bSizer69->Add( m_staticText46, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_foto = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	renglon_foto->SetToolTip( wxT("Escriba la dirección en el disco de la foto personal del socio o haga click en el botón \"Explorar\" para buscarla manualmente.") );
	
	bSizer69->Add( renglon_foto, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	boton_explorar = new wxButton( this, wxID_ANY, wxT("Explorar..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer69->Add( boton_explorar, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer49->Add( bSizer69, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer91;
	bSizer91 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText75 = new wxStaticText( this, wxID_ANY, wxT("Salario:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText75->Wrap( -1 );
	bSizer91->Add( m_staticText75, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_salario = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer91->Add( renglon_salario, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer49->Add( bSizer91, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer92;
	bSizer92 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText76 = new wxStaticText( this, wxID_ANY, wxT("Currículum:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText76->Wrap( -1 );
	bSizer92->Add( m_staticText76, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	boton_cargar_cur = new wxButton( this, wxID_ANY, wxT("Ingresar..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer92->Add( boton_cargar_cur, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	aviso_carga_cur = new wxStaticText( this, wxID_ANY, wxT("<< El currículum se ha cargado."), wxDefaultPosition, wxDefaultSize, 0 );
	aviso_carga_cur->Wrap( -1 );
	aviso_carga_cur->SetForegroundColour( wxColour( 0, 0, 255 ) );
	aviso_carga_cur->Hide();
	
	bSizer92->Add( aviso_carga_cur, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer49->Add( bSizer92, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer911;
	bSizer911 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText751 = new wxStaticText( this, wxID_ANY, wxT("Cuenta de usuario:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText751->Wrap( -1 );
	bSizer911->Add( m_staticText751, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	boton_generar_cuenta = new wxButton( this, wxID_ANY, wxT("Generar..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer911->Add( boton_generar_cuenta, 0, wxALL, 5 );
	
	aviso_cta_no = new wxStaticText( this, wxID_ANY, wxT("No se ha creado una cuenta de usuario."), wxDefaultPosition, wxDefaultSize, 0 );
	aviso_cta_no->Wrap( -1 );
	aviso_cta_no->SetForegroundColour( wxColour( 255, 0, 0 ) );
	
	bSizer911->Add( aviso_cta_no, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	aviso_cta_si = new wxStaticText( this, wxID_ANY, wxT("La cuenta de usuario ha sido creada."), wxDefaultPosition, wxDefaultSize, 0 );
	aviso_cta_si->Wrap( -1 );
	aviso_cta_si->SetForegroundColour( wxColour( 0, 0, 255 ) );
	aviso_cta_si->Hide();
	
	bSizer911->Add( aviso_cta_si, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer49->Add( bSizer911, 1, wxEXPAND, 5 );
	
	m_staticline8 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer49->Add( m_staticline8, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer70;
	bSizer70 = new wxBoxSizer( wxHORIZONTAL );
	
	boton_aceptar = new wxButton( this, wxID_ANY, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer70->Add( boton_aceptar, 0, wxALL, 5 );
	
	boton_cancelar = new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer70->Add( boton_cancelar, 0, wxALL, 5 );
	
	bSizer49->Add( bSizer70, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer49 );
	this->Layout();
	bSizer49->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	boton_ingreso_1->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( vAgregarBibliotecario::fecha_ingreso_actual ), NULL, this );
	boton_ingreso_2->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( vAgregarBibliotecario::fecha_ingreso_manual ), NULL, this );
	boton_explorar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarBibliotecario::click_boton_explorar ), NULL, this );
	boton_cargar_cur->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarBibliotecario::click_boton_cargar_cur ), NULL, this );
	boton_generar_cuenta->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarBibliotecario::click_boton_generar_cuenta ), NULL, this );
	boton_aceptar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarBibliotecario::click_aceptar ), NULL, this );
	boton_cancelar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarBibliotecario::click_cancelar ), NULL, this );
}

vAgregarBibliotecario::~vAgregarBibliotecario()
{
	// Disconnect Events
	boton_ingreso_1->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( vAgregarBibliotecario::fecha_ingreso_actual ), NULL, this );
	boton_ingreso_2->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( vAgregarBibliotecario::fecha_ingreso_manual ), NULL, this );
	boton_explorar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarBibliotecario::click_boton_explorar ), NULL, this );
	boton_cargar_cur->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarBibliotecario::click_boton_cargar_cur ), NULL, this );
	boton_generar_cuenta->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarBibliotecario::click_boton_generar_cuenta ), NULL, this );
	boton_aceptar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarBibliotecario::click_aceptar ), NULL, this );
	boton_cancelar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarBibliotecario::click_cancelar ), NULL, this );
	
}

vAgregarCurriculum::vAgregarCurriculum( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer93;
	bSizer93 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText78 = new wxStaticText( this, wxID_ANY, wxT("Cargue el currículum desde un archivo de texto (*.txt) o péguelo directamente en el recuadro de abajo."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText78->Wrap( -1 );
	bSizer93->Add( m_staticText78, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer94;
	bSizer94 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText79 = new wxStaticText( this, wxID_ANY, wxT("Cargar desde archivo:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText79->Wrap( -1 );
	m_staticText79->SetToolTip( wxT("Ingrese la dirección de un archivo en el disco o haga click en \"Explorar\" para buscarlo manualmente.") );
	
	bSizer94->Add( m_staticText79, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_path = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	renglon_path->SetToolTip( wxT("Ingrese la dirección de un archivo en el disco o haga click en \"Explorar\" para buscarlo manualmente.") );
	
	bSizer94->Add( renglon_path, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	boton_explorar = new wxButton( this, wxID_ANY, wxT("Explorar..."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer94->Add( boton_explorar, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer93->Add( bSizer94, 0, wxEXPAND, 5 );
	
	renglon_cur = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	renglon_cur->SetMaxLength( 9999 ); 
	bSizer93->Add( renglon_cur, 1, wxALL|wxEXPAND, 5 );
	
	m_staticline11 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer93->Add( m_staticline11, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer95;
	bSizer95 = new wxBoxSizer( wxHORIZONTAL );
	
	boton_aceptar = new wxButton( this, wxID_ANY, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer95->Add( boton_aceptar, 0, wxALL, 5 );
	
	boton_cancelar = new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer95->Add( boton_cancelar, 0, wxALL, 5 );
	
	bSizer93->Add( bSizer95, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer93 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	boton_explorar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarCurriculum::click_boton_explorar ), NULL, this );
	boton_aceptar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarCurriculum::click_boton_aceptar ), NULL, this );
	boton_cancelar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarCurriculum::click_boton_cancelar ), NULL, this );
}

vAgregarCurriculum::~vAgregarCurriculum()
{
	// Disconnect Events
	boton_explorar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarCurriculum::click_boton_explorar ), NULL, this );
	boton_aceptar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarCurriculum::click_boton_aceptar ), NULL, this );
	boton_cancelar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarCurriculum::click_boton_cancelar ), NULL, this );
	
}

vInfoLibro::vInfoLibro( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer82;
	bSizer82 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer83;
	bSizer83 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer84;
	bSizer84 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Datos generales:") ), wxVERTICAL );
	
	wxBoxSizer* bSizer86;
	bSizer86 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText55 = new wxStaticText( this, wxID_ANY, wxT("Título:        "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText55->Wrap( -1 );
	bSizer86->Add( m_staticText55, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_titulo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer86->Add( renglon_titulo, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer1->Add( bSizer86, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer87;
	bSizer87 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText56 = new wxStaticText( this, wxID_ANY, wxT("Autores:    "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText56->Wrap( -1 );
	bSizer87->Add( m_staticText56, 0, wxALL, 5 );
	
	renglon_autores = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer87->Add( renglon_autores, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	sbSizer1->Add( bSizer87, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer871;
	bSizer871 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText561 = new wxStaticText( this, wxID_ANY, wxT("Publicación:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText561->Wrap( -1 );
	bSizer871->Add( m_staticText561, 0, wxALL, 5 );
	
	renglon_publicacion = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer871->Add( renglon_publicacion, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	sbSizer1->Add( bSizer871, 1, wxEXPAND, 5 );
	
	bSizer84->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Biblioteca") ), wxVERTICAL );
	
	wxBoxSizer* bSizer93;
	bSizer93 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText60 = new wxStaticText( this, wxID_ANY, wxT("Tipo de préstamo:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText60->Wrap( -1 );
	bSizer93->Add( m_staticText60, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_prestamo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer93->Add( renglon_prestamo, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText105 = new wxStaticText( this, wxID_ANY, wxT("Estado:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText105->Wrap( -1 );
	bSizer93->Add( m_staticText105, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_estado = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer93->Add( renglon_estado, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer2->Add( bSizer93, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer931;
	bSizer931 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText601 = new wxStaticText( this, wxID_ANY, wxT("Solicitar por:         "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText601->Wrap( -1 );
	bSizer931->Add( m_staticText601, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_solicitar = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer931->Add( renglon_solicitar, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer2->Add( bSizer931, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer932;
	bSizer932 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText602 = new wxStaticText( this, wxID_ANY, wxT("Fecha de alta:      "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText602->Wrap( -1 );
	bSizer932->Add( m_staticText602, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_fecha = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer932->Add( renglon_fecha, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer2->Add( bSizer932, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer933;
	bSizer933 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText603 = new wxStaticText( this, wxID_ANY, wxT("Código:                 "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText603->Wrap( -1 );
	bSizer933->Add( m_staticText603, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_codigo = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer933->Add( renglon_codigo, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sbSizer2->Add( bSizer933, 0, wxEXPAND, 5 );
	
	bSizer84->Add( sbSizer2, 0, wxEXPAND, 5 );
	
	bSizer83->Add( bSizer84, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Detalles") ), wxVERTICAL );
	
	wxBoxSizer* bSizer101;
	bSizer101 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText65 = new wxStaticText( this, wxID_ANY, wxT("Contenido:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText65->Wrap( -1 );
	bSizer101->Add( m_staticText65, 0, wxALL, 5 );
	
	renglon_contenido = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer101->Add( renglon_contenido, 1, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	sbSizer3->Add( bSizer101, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer102;
	bSizer102 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText66 = new wxStaticText( this, wxID_ANY, wxT("Resumen:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText66->Wrap( -1 );
	bSizer102->Add( m_staticText66, 0, wxALL, 5 );
	
	renglon_resumen = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer102->Add( renglon_resumen, 1, wxALL|wxEXPAND, 5 );
	
	sbSizer3->Add( bSizer102, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer103;
	bSizer103 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText67 = new wxStaticText( this, wxID_ANY, wxT("Url:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText67->Wrap( -1 );
	bSizer103->Add( m_staticText67, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_url = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer103->Add( renglon_url, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	boton_ir = new wxButton( this, wxID_ANY, wxT("ir"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer103->Add( boton_ir, 0, wxALL, 5 );
	
	sbSizer3->Add( bSizer103, 0, wxEXPAND, 5 );
	
	bSizer83->Add( sbSizer3, 1, wxEXPAND, 5 );
	
	bSizer82->Add( bSizer83, 1, wxEXPAND, 5 );
	
	m_staticline11 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer82->Add( m_staticline11, 0, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizer105;
	bSizer105 = new wxBoxSizer( wxHORIZONTAL );
	
	boton_ver_historial = new wxButton( this, wxID_ANY, wxT("Ver el historial de préstamos"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer105->Add( boton_ver_historial, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer105->Add( 0, 0, 1, wxEXPAND, 5 );
	
	boton_cerrar = new wxButton( this, wxID_ANY, wxT("Cerrar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer105->Add( boton_cerrar, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer82->Add( bSizer105, 0, wxALIGN_RIGHT|wxEXPAND, 5 );
	
	this->SetSizer( bSizer82 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	boton_ir->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vInfoLibro::click_boton_ir ), NULL, this );
	boton_ver_historial->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vInfoLibro::click_boton_historial ), NULL, this );
	boton_cerrar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vInfoLibro::click_boton_cerrar ), NULL, this );
}

vInfoLibro::~vInfoLibro()
{
	// Disconnect Events
	boton_ir->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vInfoLibro::click_boton_ir ), NULL, this );
	boton_ver_historial->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vInfoLibro::click_boton_historial ), NULL, this );
	boton_cerrar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vInfoLibro::click_boton_cerrar ), NULL, this );
	
}

vInfoSocio::vInfoSocio( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer127;
	bSizer127 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer128;
	bSizer128 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer129;
	bSizer129 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer132;
	bSizer132 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText96 = new wxStaticText( this, wxID_ANY, wxT("Nombre:  "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText96->Wrap( -1 );
	bSizer132->Add( m_staticText96, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_nombre = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	renglon_nombre->SetMinSize( wxSize( 350,-1 ) );
	
	bSizer132->Add( renglon_nombre, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer129->Add( bSizer132, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1321;
	bSizer1321 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText961 = new wxStaticText( this, wxID_ANY, wxT("DNI:         "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText961->Wrap( -1 );
	bSizer1321->Add( m_staticText961, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_dni = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer1321->Add( renglon_dni, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer129->Add( bSizer1321, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1327;
	bSizer1327 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText967 = new wxStaticText( this, wxID_ANY, wxT("Nro Socio:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText967->Wrap( -1 );
	bSizer1327->Add( m_staticText967, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_nro_socio = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer1327->Add( renglon_nro_socio, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer129->Add( bSizer1327, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1322;
	bSizer1322 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText962 = new wxStaticText( this, wxID_ANY, wxT("Teléfono: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText962->Wrap( -1 );
	bSizer1322->Add( m_staticText962, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_tel = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer1322->Add( renglon_tel, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer129->Add( bSizer1322, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1323;
	bSizer1323 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText963 = new wxStaticText( this, wxID_ANY, wxT("Domicilio:  "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText963->Wrap( -1 );
	bSizer1323->Add( m_staticText963, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_domicilio = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer1323->Add( renglon_domicilio, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer129->Add( bSizer1323, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1324;
	bSizer1324 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText964 = new wxStaticText( this, wxID_ANY, wxT("Edad:       "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText964->Wrap( -1 );
	bSizer1324->Add( m_staticText964, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_edad = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer1324->Add( renglon_edad, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer129->Add( bSizer1324, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1325;
	bSizer1325 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText965 = new wxStaticText( this, wxID_ANY, wxT("Ingreso:   "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText965->Wrap( -1 );
	bSizer1325->Add( m_staticText965, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_ingreso = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer1325->Add( renglon_ingreso, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer129->Add( bSizer1325, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1326;
	bSizer1326 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText966 = new wxStaticText( this, wxID_ANY, wxT("A devolver:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText966->Wrap( -1 );
	bSizer1326->Add( m_staticText966, 0, wxALL, 5 );
	
	cuadro_pendientes = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	bSizer1326->Add( cuadro_pendientes, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer129->Add( bSizer1326, 0, wxEXPAND, 5 );
	
	bSizer128->Add( bSizer129, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer133;
	bSizer133 = new wxBoxSizer( wxVERTICAL );
	
	foto_socio = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("Img/Resources/no-user.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer133->Add( foto_socio, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	boton_ver_historial = new wxButton( this, wxID_ANY, wxT("Ver el historial de préstamos"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer133->Add( boton_ver_historial, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer128->Add( bSizer133, 0, 0, 5 );
	
	bSizer127->Add( bSizer128, 1, wxEXPAND, 5 );
	
	m_staticline14 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer127->Add( m_staticline14, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxHORIZONTAL );
	
	boton_cerrar = new wxButton( this, wxID_ANY, wxT("Cerrar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer131->Add( boton_cerrar, 0, wxALL, 5 );
	
	bSizer127->Add( bSizer131, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer127 );
	this->Layout();
	bSizer127->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	cuadro_pendientes->Connect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( vInfoSocio::Dclick_pendiente ), NULL, this );
	boton_ver_historial->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vInfoSocio::click_boton_historial ), NULL, this );
	boton_cerrar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vInfoSocio::click_boton_cerrar ), NULL, this );
}

vInfoSocio::~vInfoSocio()
{
	// Disconnect Events
	cuadro_pendientes->Disconnect( wxEVT_COMMAND_LISTBOX_DOUBLECLICKED, wxCommandEventHandler( vInfoSocio::Dclick_pendiente ), NULL, this );
	boton_ver_historial->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vInfoSocio::click_boton_historial ), NULL, this );
	boton_cerrar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vInfoSocio::click_boton_cerrar ), NULL, this );
	
}

vInfoBibliotecario::vInfoBibliotecario( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer127;
	bSizer127 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer128;
	bSizer128 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer129;
	bSizer129 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer132;
	bSizer132 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText96 = new wxStaticText( this, wxID_ANY, wxT("Nombre:   "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText96->Wrap( -1 );
	bSizer132->Add( m_staticText96, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_nombre = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer132->Add( renglon_nombre, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer129->Add( bSizer132, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1321;
	bSizer1321 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText961 = new wxStaticText( this, wxID_ANY, wxT("DNI:          "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText961->Wrap( -1 );
	bSizer1321->Add( m_staticText961, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_dni = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer1321->Add( renglon_dni, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer129->Add( bSizer1321, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1322;
	bSizer1322 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText962 = new wxStaticText( this, wxID_ANY, wxT("Teléfono:  "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText962->Wrap( -1 );
	bSizer1322->Add( m_staticText962, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_tel = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer1322->Add( renglon_tel, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer129->Add( bSizer1322, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1323;
	bSizer1323 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText963 = new wxStaticText( this, wxID_ANY, wxT("Domicilio:   "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText963->Wrap( -1 );
	bSizer1323->Add( m_staticText963, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_domicilio = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer1323->Add( renglon_domicilio, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer129->Add( bSizer1323, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1324;
	bSizer1324 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText964 = new wxStaticText( this, wxID_ANY, wxT("Edad:        "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText964->Wrap( -1 );
	bSizer1324->Add( m_staticText964, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_edad = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer1324->Add( renglon_edad, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer129->Add( bSizer1324, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1325;
	bSizer1325 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText965 = new wxStaticText( this, wxID_ANY, wxT("Ingreso:    "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText965->Wrap( -1 );
	bSizer1325->Add( m_staticText965, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_ingreso = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer1325->Add( renglon_ingreso, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer129->Add( bSizer1325, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer13251;
	bSizer13251 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText9651 = new wxStaticText( this, wxID_ANY, wxT("Salario:      "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9651->Wrap( -1 );
	bSizer13251->Add( m_staticText9651, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_salario = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer13251->Add( renglon_salario, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer129->Add( bSizer13251, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer13252;
	bSizer13252 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText9652 = new wxStaticText( this, wxID_ANY, wxT("Préstamos:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9652->Wrap( -1 );
	bSizer13252->Add( m_staticText9652, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_prestamos = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer13252->Add( renglon_prestamos, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer129->Add( bSizer13252, 0, wxEXPAND, 5 );
	
	bSizer128->Add( bSizer129, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer177;
	bSizer177 = new wxBoxSizer( wxVERTICAL );
	
	foto_bibliotecario = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("Img/Resources/no-user.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer177->Add( foto_bibliotecario, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	renglon_cur = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer177->Add( renglon_cur, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	bSizer128->Add( bSizer177, 1, wxEXPAND, 5 );
	
	bSizer127->Add( bSizer128, 1, wxEXPAND, 5 );
	
	m_staticline14 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer127->Add( m_staticline14, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxHORIZONTAL );
	
	boton_cerrar = new wxButton( this, wxID_ANY, wxT("Cerrar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer131->Add( boton_cerrar, 0, wxALL, 5 );
	
	bSizer127->Add( bSizer131, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer127 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	boton_cerrar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vInfoBibliotecario::click_boton_cerrar ), NULL, this );
}

vInfoBibliotecario::~vInfoBibliotecario()
{
	// Disconnect Events
	boton_cerrar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vInfoBibliotecario::click_boton_cerrar ), NULL, this );
	
}

vEstadisticas::vEstadisticas( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer100;
	bSizer100 = new wxBoxSizer( wxVERTICAL );
	
	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer1022;
	bSizer1022 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow1, wxID_ANY, wxT("Libros") ), wxVERTICAL );
	
	boton_ver_ocultar_libros = new wxButton( m_scrolledWindow1, wxID_ANY, wxT("Ocultar"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( boton_ver_ocultar_libros, 0, wxALL, 5 );
	
	panel_libros = new wxPanel( m_scrolledWindow1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer103;
	bSizer103 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer102;
	bSizer102 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText74 = new wxStaticText( panel_libros, wxID_ANY, wxT("Libros más leídos - Top:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText74->Wrap( -1 );
	bSizer102->Add( m_staticText74, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString cant_top_librosChoices[] = { wxT("3"), wxT("10"), wxT("50"), wxT("100") };
	int cant_top_librosNChoices = sizeof( cant_top_librosChoices ) / sizeof( wxString );
	cant_top_libros = new wxChoice( panel_libros, wxID_ANY, wxDefaultPosition, wxDefaultSize, cant_top_librosNChoices, cant_top_librosChoices, 0 );
	cant_top_libros->SetSelection( 0 );
	bSizer102->Add( cant_top_libros, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer103->Add( bSizer102, 0, 0, 5 );
	
	cuadro_top_libros = new wxListBox( panel_libros, wxID_ANY, wxDefaultPosition, wxSize( -1,150 ), 0, NULL, 0 ); 
	bSizer103->Add( cuadro_top_libros, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1021;
	bSizer1021 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText741 = new wxStaticText( panel_libros, wxID_ANY, wxT("Autores más solicitados - Top:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText741->Wrap( -1 );
	bSizer1021->Add( m_staticText741, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString cant_top_autoresChoices[] = { wxT("3"), wxT("10"), wxT("50"), wxT("100") };
	int cant_top_autoresNChoices = sizeof( cant_top_autoresChoices ) / sizeof( wxString );
	cant_top_autores = new wxChoice( panel_libros, wxID_ANY, wxDefaultPosition, wxDefaultSize, cant_top_autoresNChoices, cant_top_autoresChoices, 0 );
	cant_top_autores->SetSelection( 0 );
	bSizer1021->Add( cant_top_autores, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer103->Add( bSizer1021, 0, wxEXPAND, 5 );
	
	cuadro_top_autores = new wxListBox( panel_libros, wxID_ANY, wxDefaultPosition, wxSize( -1,150 ), 0, NULL, 0 ); 
	bSizer103->Add( cuadro_top_autores, 1, wxALL|wxEXPAND, 5 );
	
	panel_libros->SetSizer( bSizer103 );
	panel_libros->Layout();
	bSizer103->Fit( panel_libros );
	sbSizer5->Add( panel_libros, 0, wxALL|wxEXPAND, 1 );
	
	bSizer1022->Add( sbSizer5, 0, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer51;
	sbSizer51 = new wxStaticBoxSizer( new wxStaticBox( m_scrolledWindow1, wxID_ANY, wxT("Socios") ), wxVERTICAL );
	
	boton_ver_ocultar_socios = new wxButton( m_scrolledWindow1, wxID_ANY, wxT("Ocultar"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer51->Add( boton_ver_ocultar_socios, 0, wxALL, 5 );
	
	panel_socios = new wxPanel( m_scrolledWindow1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer1031;
	bSizer1031 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer1023;
	bSizer1023 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText742 = new wxStaticText( panel_socios, wxID_ANY, wxT("Socios que más libros retiraron - Top:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText742->Wrap( -1 );
	bSizer1023->Add( m_staticText742, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString cant_top_socios_prestamosChoices[] = { wxT("3"), wxT("10"), wxT("50"), wxT("100") };
	int cant_top_socios_prestamosNChoices = sizeof( cant_top_socios_prestamosChoices ) / sizeof( wxString );
	cant_top_socios_prestamos = new wxChoice( panel_socios, wxID_ANY, wxDefaultPosition, wxDefaultSize, cant_top_socios_prestamosNChoices, cant_top_socios_prestamosChoices, 0 );
	cant_top_socios_prestamos->SetSelection( 0 );
	bSizer1023->Add( cant_top_socios_prestamos, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1031->Add( bSizer1023, 0, 0, 5 );
	
	cuadro_top_socios_prestamos = new wxListBox( panel_socios, wxID_ANY, wxDefaultPosition, wxSize( -1,150 ), 0, NULL, 0 ); 
	bSizer1031->Add( cuadro_top_socios_prestamos, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10211;
	bSizer10211 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText7411 = new wxStaticText( panel_socios, wxID_ANY, wxT("Socios con más antigüedad - Top:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7411->Wrap( -1 );
	bSizer10211->Add( m_staticText7411, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxString cant_top_socios_antChoices[] = { wxT("3"), wxT("10"), wxT("50"), wxT("100") };
	int cant_top_socios_antNChoices = sizeof( cant_top_socios_antChoices ) / sizeof( wxString );
	cant_top_socios_ant = new wxChoice( panel_socios, wxID_ANY, wxDefaultPosition, wxDefaultSize, cant_top_socios_antNChoices, cant_top_socios_antChoices, 0 );
	cant_top_socios_ant->SetSelection( 0 );
	bSizer10211->Add( cant_top_socios_ant, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer1031->Add( bSizer10211, 0, wxEXPAND, 5 );
	
	cuadro_top_socios_antig = new wxListBox( panel_socios, wxID_ANY, wxDefaultPosition, wxSize( -1,150 ), 0, NULL, 0 ); 
	bSizer1031->Add( cuadro_top_socios_antig, 1, wxALL|wxEXPAND, 5 );
	
	panel_socios->SetSizer( bSizer1031 );
	panel_socios->Layout();
	bSizer1031->Fit( panel_socios );
	sbSizer51->Add( panel_socios, 0, wxEXPAND | wxALL, 1 );
	
	bSizer1022->Add( sbSizer51, 0, wxEXPAND, 5 );
	
	panel_emergente_bib = new wxPanel( m_scrolledWindow1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	panel_emergente_bib->Hide();
	
	wxStaticBoxSizer* sbSizer511;
	sbSizer511 = new wxStaticBoxSizer( new wxStaticBox( panel_emergente_bib, wxID_ANY, wxT("Bibliotecarios") ), wxVERTICAL );
	
	boton_ver_ocultar_bib = new wxButton( panel_emergente_bib, wxID_ANY, wxT("Ocultar"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer511->Add( boton_ver_ocultar_bib, 0, wxALL, 5 );
	
	panel_bibliotecarios = new wxPanel( panel_emergente_bib, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer10311;
	bSizer10311 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText7421 = new wxStaticText( panel_bibliotecarios, wxID_ANY, wxT("Préstamos efectuados:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7421->Wrap( -1 );
	bSizer10311->Add( m_staticText7421, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	cuadro_bib_prestamos = new wxListBox( panel_bibliotecarios, wxID_ANY, wxDefaultPosition, wxSize( -1,150 ), 0, NULL, 0 ); 
	bSizer10311->Add( cuadro_bib_prestamos, 1, wxALL|wxEXPAND, 5 );
	
	m_staticText74111 = new wxStaticText( panel_bibliotecarios, wxID_ANY, wxT("Antigüedad:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText74111->Wrap( -1 );
	bSizer10311->Add( m_staticText74111, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	cuadro_bib_antiguedad = new wxListBox( panel_bibliotecarios, wxID_ANY, wxDefaultPosition, wxSize( -1,150 ), 0, NULL, 0 ); 
	bSizer10311->Add( cuadro_bib_antiguedad, 1, wxALL|wxEXPAND, 5 );
	
	m_staticText82 = new wxStaticText( panel_bibliotecarios, wxID_ANY, wxT("Salario:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText82->Wrap( -1 );
	bSizer10311->Add( m_staticText82, 0, wxALL, 5 );
	
	cuadro_bib_salario = new wxListBox( panel_bibliotecarios, wxID_ANY, wxDefaultPosition, wxSize( -1,150 ), 0, NULL, 0 ); 
	bSizer10311->Add( cuadro_bib_salario, 1, wxALL|wxEXPAND, 5 );
	
	panel_bibliotecarios->SetSizer( bSizer10311 );
	panel_bibliotecarios->Layout();
	bSizer10311->Fit( panel_bibliotecarios );
	sbSizer511->Add( panel_bibliotecarios, 0, wxEXPAND | wxALL, 1 );
	
	panel_emergente_bib->SetSizer( sbSizer511 );
	panel_emergente_bib->Layout();
	sbSizer511->Fit( panel_emergente_bib );
	bSizer1022->Add( panel_emergente_bib, 0, wxEXPAND | wxALL, 1 );
	
	m_scrolledWindow1->SetSizer( bSizer1022 );
	m_scrolledWindow1->Layout();
	bSizer1022->Fit( m_scrolledWindow1 );
	bSizer100->Add( m_scrolledWindow1, 1, wxALL|wxEXPAND, 5 );
	
	m_staticline13 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer100->Add( m_staticline13, 0, wxEXPAND | wxALL, 5 );
	
	boton_cerrar = new wxButton( this, wxID_ANY, wxT("Cerrar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer100->Add( boton_cerrar, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer100 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	boton_ver_ocultar_libros->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vEstadisticas::click_ver_ocultar_libros ), NULL, this );
	cant_top_libros->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vEstadisticas::cambio_cant_top_libros ), NULL, this );
	cant_top_autores->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vEstadisticas::cambio_cant_top_autores ), NULL, this );
	boton_ver_ocultar_socios->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vEstadisticas::click_ver_ocultar_socios ), NULL, this );
	cant_top_socios_prestamos->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vEstadisticas::cambio_cant_top_socios_prestamos ), NULL, this );
	cant_top_socios_ant->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vEstadisticas::cambio_cant_top_socios_ant ), NULL, this );
	boton_ver_ocultar_bib->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vEstadisticas::click_ver_ocultar_bib ), NULL, this );
	boton_cerrar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vEstadisticas::click_cerrar ), NULL, this );
}

vEstadisticas::~vEstadisticas()
{
	// Disconnect Events
	boton_ver_ocultar_libros->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vEstadisticas::click_ver_ocultar_libros ), NULL, this );
	cant_top_libros->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vEstadisticas::cambio_cant_top_libros ), NULL, this );
	cant_top_autores->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vEstadisticas::cambio_cant_top_autores ), NULL, this );
	boton_ver_ocultar_socios->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vEstadisticas::click_ver_ocultar_socios ), NULL, this );
	cant_top_socios_prestamos->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vEstadisticas::cambio_cant_top_socios_prestamos ), NULL, this );
	cant_top_socios_ant->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vEstadisticas::cambio_cant_top_socios_ant ), NULL, this );
	boton_ver_ocultar_bib->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vEstadisticas::click_ver_ocultar_bib ), NULL, this );
	boton_cerrar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vEstadisticas::click_cerrar ), NULL, this );
	
}

vLogin::vLogin( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer123;
	bSizer123 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer123->Add( 0, 15, 0, 0, 5 );
	
	error_usuario = new wxStaticText( this, wxID_ANY, wxT("* El usuario ingresado no existe."), wxDefaultPosition, wxDefaultSize, 0 );
	error_usuario->Wrap( -1 );
	error_usuario->SetForegroundColour( wxColour( 255, 0, 0 ) );
	error_usuario->Hide();
	
	bSizer123->Add( error_usuario, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer109;
	bSizer109 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText79 = new wxStaticText( this, wxID_ANY, wxT("Usuario:        "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText79->Wrap( -1 );
	bSizer109->Add( m_staticText79, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_usuario = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	renglon_usuario->SetMinSize( wxSize( 250,-1 ) );
	
	bSizer109->Add( renglon_usuario, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer123->Add( bSizer109, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1091;
	bSizer1091 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText791 = new wxStaticText( this, wxID_ANY, wxT("Constraseña:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText791->Wrap( -1 );
	bSizer1091->Add( m_staticText791, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_pass = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD|wxTE_PROCESS_ENTER );
	bSizer1091->Add( renglon_pass, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer123->Add( bSizer1091, 0, wxEXPAND, 5 );
	
	error_pass = new wxStaticText( this, wxID_ANY, wxT("* La contraseña ingresada es incorrecta."), wxDefaultPosition, wxDefaultSize, 0 );
	error_pass->Wrap( -1 );
	error_pass->SetForegroundColour( wxColour( 255, 0, 0 ) );
	error_pass->Hide();
	
	bSizer123->Add( error_pass, 0, wxALL, 5 );
	
	
	bSizer123->Add( 0, 15, 0, 0, 5 );
	
	m_staticline14 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer123->Add( m_staticline14, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer113;
	bSizer113 = new wxBoxSizer( wxHORIZONTAL );
	
	boton_salir = new wxButton( this, wxID_ANY, wxT("Salir"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer113->Add( boton_salir, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	boton_aceptar = new wxButton( this, wxID_ANY, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer113->Add( boton_aceptar, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer123->Add( bSizer113, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer123 );
	this->Layout();
	bSizer123->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( vLogin::se_cierra ) );
	renglon_usuario->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vLogin::enter_presionado ), NULL, this );
	renglon_pass->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vLogin::enter_presionado ), NULL, this );
	boton_salir->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vLogin::click_boton_salir ), NULL, this );
	boton_aceptar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vLogin::click_boton_aceptar ), NULL, this );
}

vLogin::~vLogin()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( vLogin::se_cierra ) );
	renglon_usuario->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vLogin::enter_presionado ), NULL, this );
	renglon_pass->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vLogin::enter_presionado ), NULL, this );
	boton_salir->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vLogin::click_boton_salir ), NULL, this );
	boton_aceptar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vLogin::click_boton_aceptar ), NULL, this );
	
}

vAgregarUsuario::vAgregarUsuario( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer114;
	bSizer114 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer122;
	bSizer122 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText86 = new wxStaticText( this, wxID_ANY, wxT("Usuario:                                        "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText86->Wrap( -1 );
	bSizer122->Add( m_staticText86, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_usuario = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	renglon_usuario->SetMaxLength( 20 ); 
	renglon_usuario->SetMinSize( wxSize( 400,-1 ) );
	
	bSizer122->Add( renglon_usuario, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	error_usuario = new wxStaticText( this, wxID_ANY, wxT("* El usuario ingresado ya existe."), wxDefaultPosition, wxDefaultSize, 0 );
	error_usuario->Wrap( -1 );
	error_usuario->SetForegroundColour( wxColour( 255, 0, 0 ) );
	error_usuario->Hide();
	
	bSizer122->Add( error_usuario, 0, wxALL, 5 );
	
	m_staticText862 = new wxStaticText( this, wxID_ANY, wxT("Contraseña:                       "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText862->Wrap( -1 );
	bSizer122->Add( m_staticText862, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_pass = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	renglon_pass->SetMaxLength( 20 ); 
	bSizer122->Add( renglon_pass, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	m_staticText863 = new wxStaticText( this, wxID_ANY, wxT("Vuelva a escribir la contraseña:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText863->Wrap( -1 );
	bSizer122->Add( m_staticText863, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	renglon_confirmacion = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	renglon_confirmacion->SetMaxLength( 20 ); 
	bSizer122->Add( renglon_confirmacion, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxEXPAND, 5 );
	
	error_confirmacion = new wxStaticText( this, wxID_ANY, wxT("* La confirmación no coincide con la contraseña."), wxDefaultPosition, wxDefaultSize, 0 );
	error_confirmacion->Wrap( -1 );
	error_confirmacion->SetForegroundColour( wxColour( 255, 0, 0 ) );
	error_confirmacion->Hide();
	
	bSizer122->Add( error_confirmacion, 0, wxALL, 5 );
	
	bSizer114->Add( bSizer122, 1, wxEXPAND, 5 );
	
	m_staticline15 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer114->Add( m_staticline15, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxHORIZONTAL );
	
	boton_cancelar = new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer121->Add( boton_cancelar, 0, wxALL, 5 );
	
	boton_aceptar = new wxButton( this, wxID_ANY, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer121->Add( boton_aceptar, 0, wxALL, 5 );
	
	bSizer114->Add( bSizer121, 0, wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer114 );
	this->Layout();
	bSizer114->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	boton_cancelar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarUsuario::click_boton_cancelar ), NULL, this );
	boton_aceptar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarUsuario::click_boton_aceptar ), NULL, this );
}

vAgregarUsuario::~vAgregarUsuario()
{
	// Disconnect Events
	boton_cancelar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarUsuario::click_boton_cancelar ), NULL, this );
	boton_aceptar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAgregarUsuario::click_boton_aceptar ), NULL, this );
	
}

vAyuda::vAyuda( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer132;
	bSizer132 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText103 = new wxStaticText( this, wxID_ANY, wxT("Ayuda de Hexandria"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText103->Wrap( -1 );
	m_staticText103->SetFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer132->Add( m_staticText103, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer132->Add( 0, 30, 0, 0, 5 );
	
	m_hyperlink1 = new wxHyperlinkCtrl( this, wxID_ANY, wxT("Abrir el manual del usuario"), wxT("http://www.wxformbuilder.org"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	m_hyperlink1->SetFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer132->Add( m_hyperlink1, 0, wxALL, 5 );
	
	m_hyperlink11 = new wxHyperlinkCtrl( this, wxID_ANY, wxT("Abrir el manual de referencia"), wxT("http://www.wxformbuilder.org"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	m_hyperlink11->SetFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer132->Add( m_hyperlink11, 0, wxALL, 5 );
	
	
	bSizer132->Add( 0, 30, 0, 0, 5 );
	
	m_staticText104 = new wxStaticText( this, wxID_ANY, wxT("Los manuales están en formato .pdf, por lo que para leerlos será necesario que tenga instalado algún lector"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText104->Wrap( -1 );
	bSizer132->Add( m_staticText104, 0, wxALL, 5 );
	
	m_staticText105 = new wxStaticText( this, wxID_ANY, wxT(" capaz de abrir dicho formato. Si no lo tiene, puede dirigirse a:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText105->Wrap( -1 );
	bSizer132->Add( m_staticText105, 0, wxALL, 5 );
	
	m_hyperlink5 = new wxHyperlinkCtrl( this, wxID_ANY, wxT("http://get.adobe.com/es/reader/"), wxT("http://get.adobe.com/es/reader/"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer132->Add( m_hyperlink5, 0, wxALL, 5 );
	
	m_staticText106 = new wxStaticText( this, wxID_ANY, wxT("Para descargar de forma gratuita el programa Adobe Reader."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText106->Wrap( -1 );
	bSizer132->Add( m_staticText106, 0, wxALL, 5 );
	
	m_staticline21 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer132->Add( m_staticline21, 0, wxEXPAND | wxALL, 5 );
	
	boton_cerrar = new wxButton( this, wxID_ANY, wxT("Cerrar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer132->Add( boton_cerrar, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer132 );
	this->Layout();
	bSizer132->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_hyperlink1->Connect( wxEVT_COMMAND_HYPERLINK, wxHyperlinkEventHandler( vAyuda::abrir_manual_usuario ), NULL, this );
	m_hyperlink11->Connect( wxEVT_COMMAND_HYPERLINK, wxHyperlinkEventHandler( vAyuda::abrir_manual_referencia ), NULL, this );
	boton_cerrar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAyuda::click_boton_cerrar ), NULL, this );
}

vAyuda::~vAyuda()
{
	// Disconnect Events
	m_hyperlink1->Disconnect( wxEVT_COMMAND_HYPERLINK, wxHyperlinkEventHandler( vAyuda::abrir_manual_usuario ), NULL, this );
	m_hyperlink11->Disconnect( wxEVT_COMMAND_HYPERLINK, wxHyperlinkEventHandler( vAyuda::abrir_manual_referencia ), NULL, this );
	boton_cerrar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAyuda::click_boton_cerrar ), NULL, this );
	
}

vAbout::vAbout( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer125;
	bSizer125 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer126;
	bSizer126 = new wxBoxSizer( wxHORIZONTAL );
	
	m_bitmap5 = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("Img/Resources/about_img.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer126->Add( m_bitmap5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxBoxSizer* bSizer127;
	bSizer127 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer127->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText100 = new wxStaticText( this, wxID_ANY, wxT("Hexandria"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText100->Wrap( -1 );
	m_staticText100->SetFont( wxFont( 24, 70, 90, 92, false, wxEmptyString ) );
	
	bSizer127->Add( m_staticText100, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText101 = new wxStaticText( this, wxID_ANY, wxT("Versión 1.0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText101->Wrap( -1 );
	m_staticText101->SetFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer127->Add( m_staticText101, 1, wxALL|wxALIGN_RIGHT, 5 );
	
	bSizer126->Add( bSizer127, 1, wxEXPAND, 5 );
	
	bSizer125->Add( bSizer126, 1, wxEXPAND, 5 );
	
	m_staticText102 = new wxStaticText( this, wxID_ANY, wxT("Un software simple de gestión para bibliotecas"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText102->Wrap( -1 );
	m_staticText102->SetFont( wxFont( 10, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer125->Add( m_staticText102, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer125->Add( 0, 20, 0, 0, 5 );
	
	m_staticText103 = new wxStaticText( this, wxID_ANY, wxT("Desarrollado por:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText103->Wrap( -1 );
	m_staticText103->SetFont( wxFont( 10, 70, 90, 92, false, wxEmptyString ) );
	
	bSizer125->Add( m_staticText103, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_staticText104 = new wxStaticText( this, wxID_ANY, wxT("Iván Pizarro"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText104->Wrap( -1 );
	m_staticText104->SetFont( wxFont( 10, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer125->Add( m_staticText104, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer125->Add( 0, 20, 0, 0, 5 );
	
	m_staticline19 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer125->Add( m_staticline19, 0, wxEXPAND | wxALL, 5 );
	
	boton_cerrar = new wxButton( this, wxID_ANY, wxT("Cerrar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer125->Add( boton_cerrar, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer125 );
	this->Layout();
	bSizer125->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	boton_cerrar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAbout::click_cerrar ), NULL, this );
}

vAbout::~vAbout()
{
	// Disconnect Events
	boton_cerrar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vAbout::click_cerrar ), NULL, this );
	
}

vHistorial::vHistorial( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer128;
	bSizer128 = new wxBoxSizer( wxVERTICAL );
	
	panel_historial_libro = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxVERTICAL );
	
	barra_socios = new wxToolBar( panel_historial_libro, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL ); 
	barra_socios->AddTool( id_vhs_boton_detalles, wxT("tool"), wxBitmap( wxT("Img/Resources/detalles.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver detalles del socio seleccionado..."), wxEmptyString ); 
	barra_socios->AddSeparator(); 
	barra_socios->AddTool( id_vhs_boton_estadisticas, wxT("tool"), wxBitmap( wxT("Img/Resources/estadisticas.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver estadísticas..."), wxEmptyString ); 
	barra_socios->AddSeparator(); 
	wxString orden_sociosChoices[] = { wxT("ordenar por nombre"), wxT("ordenar por edad"), wxT("ordenar por cant lecturas"), wxT("ordenar por fecha de alta"), wxT("ordenar por pendientes"), wxT("ordenar por antigüedad") };
	int orden_sociosNChoices = sizeof( orden_sociosChoices ) / sizeof( wxString );
	orden_socios = new wxChoice( barra_socios, wxID_ANY, wxDefaultPosition, wxDefaultSize, orden_sociosNChoices, orden_sociosChoices, 0 );
	orden_socios->SetSelection( 0 );
	orden_socios->SetToolTip( wxT("Elegir el criterio para ordenar los socios en la grilla.") );
	
	barra_socios->AddControl( orden_socios );
	barra_socios->AddSeparator(); 
	barra_busqueda_s = new wxSearchCtrl( barra_socios, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	#ifndef __WXMAC__
	barra_busqueda_s->ShowSearchButton( true );
	#endif
	barra_busqueda_s->ShowCancelButton( false );
	barra_socios->AddControl( barra_busqueda_s );
	barra_socios->AddSeparator(); 
	barra_socios->AddTool( id_vhs_boton_restaurar, wxT("tool"), wxBitmap( wxT("Img/Resources/actualizar.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Restaurar vista."), wxEmptyString ); 
	barra_socios->AddSeparator(); 
	barra_socios->AddTool( id_vhs_boton_ayuda, wxT("tool"), wxBitmap( wxT("Img/Resources/ayuda.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver la ayuda..."), wxEmptyString ); 
	barra_socios->Realize();
	
	bSizer131->Add( barra_socios, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	grilla_socios = new mi_grilla( panel_historial_libro, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	grilla_socios->CreateGrid( 30, 4 );
	grilla_socios->EnableEditing( false );
	grilla_socios->EnableGridLines( true );
	grilla_socios->EnableDragGridSize( false );
	grilla_socios->SetMargins( 0, 0 );
	
	// Columns
	grilla_socios->SetColSize( 0, 210 );
	grilla_socios->SetColSize( 1, 110 );
	grilla_socios->SetColSize( 2, 110 );
	grilla_socios->SetColSize( 3, 180 );
	grilla_socios->EnableDragColMove( false );
	grilla_socios->EnableDragColSize( true );
	grilla_socios->SetColLabelSize( 20 );
	grilla_socios->SetColLabelValue( 0, wxT("Nombre") );
	grilla_socios->SetColLabelValue( 1, wxT("DNI") );
	grilla_socios->SetColLabelValue( 2, wxT("Nro. socio") );
	grilla_socios->SetColLabelValue( 3, wxT("Fechas préstamo-devolución") );
	grilla_socios->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	grilla_socios->EnableDragRowSize( true );
	grilla_socios->SetRowLabelSize( 0 );
	grilla_socios->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	grilla_socios->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	grilla_socios->SetMaxSize( wxSize( -1,600 ) );
	
	bSizer13->Add( grilla_socios, 1, wxALL|wxEXPAND, 5 );
	
	foto_socio = new wxStaticBitmap( panel_historial_libro, wxID_ANY, wxBitmap( wxT("Img/Resources/no-user.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( foto_socio, 0, wxALL, 5 );
	
	bSizer131->Add( bSizer13, 1, wxEXPAND, 5 );
	
	panel_historial_libro->SetSizer( bSizer131 );
	panel_historial_libro->Layout();
	bSizer131->Fit( panel_historial_libro );
	bSizer128->Add( panel_historial_libro, 1, wxALL|wxEXPAND, 1 );
	
	panel_historial_socio = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer135;
	bSizer135 = new wxBoxSizer( wxVERTICAL );
	
	MyToolbar = new wxToolBar( panel_historial_socio, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_FLAT|wxTB_HORIZONTAL ); 
	MyToolbar->AddTool( id_vhl_boton_detalles, wxT("tool"), wxBitmap( wxT("Img/Resources/detalles.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver detalles del libro seleccionado..."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vhl_boton_estadisticas, wxT("tool"), wxBitmap( wxT("Img/Resources/estadisticas.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver estadísticas..."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	wxString orden_librosChoices[] = { wxT("ordenar por título"), wxT("ordenar por préstamos"), wxT("ordenar por autor"), wxT("ordenar por fecha de alta") };
	int orden_librosNChoices = sizeof( orden_librosChoices ) / sizeof( wxString );
	orden_libros = new wxChoice( MyToolbar, wxID_ANY, wxDefaultPosition, wxDefaultSize, orden_librosNChoices, orden_librosChoices, 0 );
	orden_libros->SetSelection( 0 );
	orden_libros->SetToolTip( wxT("Elegir el criterio para ordenar los libros de la grilla.") );
	
	MyToolbar->AddControl( orden_libros );
	MyToolbar->AddSeparator(); 
	barra_busqueda_l = new wxSearchCtrl( MyToolbar, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	#ifndef __WXMAC__
	barra_busqueda_l->ShowSearchButton( true );
	#endif
	barra_busqueda_l->ShowCancelButton( false );
	MyToolbar->AddControl( barra_busqueda_l );
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vhl_boton_restaurar, wxT("tool"), wxBitmap( wxT("Img/Resources/actualizar.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Restaurar vista."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vhl_boton_cdu, wxT("tool"), wxBitmap( wxT("Img/Resources/btn_cdu.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver las herramientas de filtrado CDU..."), wxEmptyString ); 
	MyToolbar->AddSeparator(); 
	MyToolbar->AddTool( id_vhl_boton_ayuda, wxT("tool"), wxBitmap( wxT("Img/Resources/ayuda.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Ver la ayuda..."), wxEmptyString ); 
	MyToolbar->Realize();
	
	bSizer135->Add( MyToolbar, 0, wxEXPAND, 5 );
	
	wxString eleccion_principalChoices[] = { wxT("Generalidades. Ciencia y conocimiento. Organización. Información. Documentación. Enciclopedias. Biblioteconomía. Instituciones. Documentos y publicaciones"), wxT("Filosofía. Psicología."), wxT("Religión. Teología."), wxT("Ciencias sociales."), wxT("Vacante"), wxT("Matemáticas. Ciencias Naturales."), wxT("Ciencias aplicadas. Medicina. Tecnología."), wxT("Bellas artes. Juegos. Espectáculos. Deportes."), wxT("Lenguaje. Lingüística. Literatura."), wxT("Geografía. Biografías. Historia.") };
	int eleccion_principalNChoices = sizeof( eleccion_principalChoices ) / sizeof( wxString );
	eleccion_principal = new wxChoice( panel_historial_socio, wxID_ANY, wxDefaultPosition, wxDefaultSize, eleccion_principalNChoices, eleccion_principalChoices, 0 );
	eleccion_principal->SetSelection( 0 );
	eleccion_principal->Hide();
	
	bSizer135->Add( eleccion_principal, 0, wxALL, 5 );
	
	wxArrayString eleccion_sub_1Choices;
	eleccion_sub_1 = new wxChoice( panel_historial_socio, wxID_ANY, wxDefaultPosition, wxDefaultSize, eleccion_sub_1Choices, 0 );
	eleccion_sub_1->SetSelection( 0 );
	eleccion_sub_1->Hide();
	
	bSizer135->Add( eleccion_sub_1, 0, wxALL, 5 );
	
	wxArrayString eleccion_sub_2Choices;
	eleccion_sub_2 = new wxChoice( panel_historial_socio, wxID_ANY, wxDefaultPosition, wxDefaultSize, eleccion_sub_2Choices, 0 );
	eleccion_sub_2->SetSelection( 0 );
	eleccion_sub_2->Hide();
	
	bSizer135->Add( eleccion_sub_2, 0, wxALL, 5 );
	
	grilla_libros = new mi_grilla( panel_historial_socio, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	
	// Grid
	grilla_libros->CreateGrid( 30, 3 );
	grilla_libros->EnableEditing( false );
	grilla_libros->EnableGridLines( true );
	grilla_libros->EnableDragGridSize( false );
	grilla_libros->SetMargins( 0, 0 );
	
	// Columns
	grilla_libros->SetColSize( 0, 200 );
	grilla_libros->SetColSize( 1, 150 );
	grilla_libros->SetColSize( 2, 240 );
	grilla_libros->EnableDragColMove( false );
	grilla_libros->EnableDragColSize( true );
	grilla_libros->SetColLabelSize( 20 );
	grilla_libros->SetColLabelValue( 0, wxT("Título") );
	grilla_libros->SetColLabelValue( 1, wxT("Autor") );
	grilla_libros->SetColLabelValue( 2, wxT("Fechas Préstamo-Devolución") );
	grilla_libros->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	grilla_libros->EnableDragRowSize( true );
	grilla_libros->SetRowLabelSize( 0 );
	grilla_libros->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	
	// Cell Defaults
	grilla_libros->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	grilla_libros->SetMaxSize( wxSize( -1,600 ) );
	
	bSizer135->Add( grilla_libros, 1, wxALL|wxEXPAND, 5 );
	
	panel_historial_socio->SetSizer( bSizer135 );
	panel_historial_socio->Layout();
	bSizer135->Fit( panel_historial_socio );
	bSizer128->Add( panel_historial_socio, 1, wxALL|wxEXPAND, 1 );
	
	m_staticline20 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	m_staticline20->SetMinSize( wxSize( 610,-1 ) );
	
	bSizer128->Add( m_staticline20, 0, wxEXPAND | wxALL, 5 );
	
	boton_cerrar = new wxButton( this, wxID_ANY, wxT("Cerrar"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer128->Add( boton_cerrar, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	this->SetSizer( bSizer128 );
	this->Layout();
	bSizer128->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( id_vhs_boton_detalles, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_detalles ) );
	this->Connect( id_vhs_boton_estadisticas, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_estadisticas ) );
	orden_socios->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vHistorial::cambio_orden ), NULL, this );
	barra_busqueda_s->Connect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( vHistorial::click_buscar ), NULL, this );
	barra_busqueda_s->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( vHistorial::click_buscar ), NULL, this );
	barra_busqueda_s->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vHistorial::click_buscar ), NULL, this );
	this->Connect( id_vhs_boton_restaurar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_restaurar ) );
	this->Connect( id_vhs_boton_ayuda, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_ayuda ) );
	grilla_socios->Connect( wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler( vHistorial::click_izq_grilla ), NULL, this );
	grilla_socios->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( vHistorial::Dclick_grilla ), NULL, this );
	this->Connect( id_vhl_boton_detalles, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_detalles ) );
	this->Connect( id_vhl_boton_estadisticas, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_estadisticas ) );
	orden_libros->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vHistorial::cambio_orden ), NULL, this );
	barra_busqueda_l->Connect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( vHistorial::click_buscar ), NULL, this );
	barra_busqueda_l->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( vHistorial::click_buscar ), NULL, this );
	barra_busqueda_l->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vHistorial::click_buscar ), NULL, this );
	this->Connect( id_vhl_boton_restaurar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_restaurar ) );
	this->Connect( id_vhl_boton_cdu, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_CDU ) );
	this->Connect( id_vhl_boton_ayuda, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_ayuda ) );
	eleccion_principal->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vHistorial::principal_elegido ), NULL, this );
	eleccion_sub_1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vHistorial::sub_1_elegido ), NULL, this );
	eleccion_sub_2->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vHistorial::sub_2_elegido ), NULL, this );
	grilla_libros->Connect( wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler( vHistorial::click_izq_grilla ), NULL, this );
	grilla_libros->Connect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( vHistorial::Dclick_grilla ), NULL, this );
	boton_cerrar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vHistorial::click_boton_cerrar ), NULL, this );
}

vHistorial::~vHistorial()
{
	// Disconnect Events
	this->Disconnect( id_vhs_boton_detalles, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_detalles ) );
	this->Disconnect( id_vhs_boton_estadisticas, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_estadisticas ) );
	orden_socios->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vHistorial::cambio_orden ), NULL, this );
	barra_busqueda_s->Disconnect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( vHistorial::click_buscar ), NULL, this );
	barra_busqueda_s->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( vHistorial::click_buscar ), NULL, this );
	barra_busqueda_s->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vHistorial::click_buscar ), NULL, this );
	this->Disconnect( id_vhs_boton_restaurar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_restaurar ) );
	this->Disconnect( id_vhs_boton_ayuda, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_ayuda ) );
	grilla_socios->Disconnect( wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler( vHistorial::click_izq_grilla ), NULL, this );
	grilla_socios->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( vHistorial::Dclick_grilla ), NULL, this );
	this->Disconnect( id_vhl_boton_detalles, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_detalles ) );
	this->Disconnect( id_vhl_boton_estadisticas, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_estadisticas ) );
	orden_libros->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vHistorial::cambio_orden ), NULL, this );
	barra_busqueda_l->Disconnect( wxEVT_COMMAND_SEARCHCTRL_SEARCH_BTN, wxCommandEventHandler( vHistorial::click_buscar ), NULL, this );
	barra_busqueda_l->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( vHistorial::click_buscar ), NULL, this );
	barra_busqueda_l->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( vHistorial::click_buscar ), NULL, this );
	this->Disconnect( id_vhl_boton_restaurar, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_restaurar ) );
	this->Disconnect( id_vhl_boton_cdu, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_CDU ) );
	this->Disconnect( id_vhl_boton_ayuda, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( vHistorial::click_boton_ayuda ) );
	eleccion_principal->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vHistorial::principal_elegido ), NULL, this );
	eleccion_sub_1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vHistorial::sub_1_elegido ), NULL, this );
	eleccion_sub_2->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( vHistorial::sub_2_elegido ), NULL, this );
	grilla_libros->Disconnect( wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler( vHistorial::click_izq_grilla ), NULL, this );
	grilla_libros->Disconnect( wxEVT_GRID_CELL_LEFT_DCLICK, wxGridEventHandler( vHistorial::Dclick_grilla ), NULL, this );
	boton_cerrar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( vHistorial::click_boton_cerrar ), NULL, this );
	
}
