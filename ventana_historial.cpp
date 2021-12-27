//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_historial.cpp
// Autor:       Iv�n Pizarro.
//
// Implementaciones de los m�todos y funciones declarados en 
// ventana_historial.h
//////////////////////////////////////////////////////////////////////////////

#include "Core\programa.h"
#include "Core\utilidades.h"

#include "ventana_historial.h"
#include "ventana_info_socio.h"
#include "ventana_info_libro.h"
#include "ventana_estadisticas.h"

#include <string>
#include <algorithm>

using namespace std;

//////////////////////////////////////////////////////////////////////////////

ventana_historial::ventana_historial ( wxWindow *_parent, const int &_codigo, const bool HistorialSocio ): vHistorial( _parent ) {
	
	// Inicializaci�n de atributos.
	fila = -1;
	historial_socio = HistorialSocio;
	Ayuda = NULL;
	
	Programa *programa = Singleton::get_base_activa();
	
	if ( historial_socio == true ) {
		
		const socio *const soc = &( programa->socios.get_socio_cod( _codigo ) );
		
		string titulo = "Historial de pr�stamos de ";
		titulo += soc->get_nombre_completo();
		this->SetTitle( titulo.c_str() );
		
		historial = soc->get_historial();
		
		const int tamanyo = historial.size();
		for ( int i=0;i<tamanyo;i++ ) { 
			
			libros.push_back( programa->libros.get_libro( historial[i].codigo_libro ) );
			
		}
		
		panel_historial_libro->Hide();
		
	} else {
		
		const libro *const lib = &( programa->libros.get_libro( _codigo ) );
		
		string titulo = "Historial de pr�stamos del libro \"";
		titulo += lib->get_titulo();
		titulo += "\"";
		this->SetTitle( titulo.c_str() );
		
		historial = lib->get_historial();
		
		const int tamanyo = historial.size();
		for ( int i=0;i<tamanyo;i++ ) { 
			
			socios.push_back( programa->socios.get_socio_cod( historial[i].nro_socio ) );
			
		}
		
		panel_historial_socio->Hide();
		
	}
	
	// Inicializaci�n de interfaz.
	MyToolbar->EnableTool( id_vhs_boton_detalles, false );
	MyToolbar->EnableTool( id_vhl_boton_detalles, false );
	this->refresh();
	this->redibujar_ventana();
	
}

ventana_historial::~ventana_historial() {
	
	if ( !Ayuda ) {
		
		Ayuda->Close();
		
	}
	
}

// SELECCION
void ventana_historial::seleccion ( const bool &_seleccionado ) {
	
	if ( _seleccionado == true ) {
		
		if ( historial_socio == true ) {
			
			grilla_libros->SelectRow( fila );
			
			
		} else {
			
			grilla_socios->SelectRow( fila );
			string path_foto = socios[pos_real[fila]].get_path_foto();
			this->cargar_imagen( path_foto );
			
		}
		
		MyToolbar->EnableTool( id_vhs_boton_detalles, true );
		MyToolbar->EnableTool( id_vhl_boton_detalles, true );
		
	} else {
		
		MyToolbar->EnableTool( id_vhs_boton_detalles, false );
		MyToolbar->EnableTool( id_vhl_boton_detalles, false );
		grilla_socios->SelectRow( -1 );
		grilla_libros->SelectRow( -1 );
		fila =  -1;
		if ( historial_socio == false ) {
			
			this->cargar_imagen( "Img\\Resources\\no-user.png" );
			
		}
		
	}
	
}

// EVENTOS GRILLA
void ventana_historial::refresh ( const bool &_conservar_seleccion ) {
	
	if ( historial_socio == false ) {
		
		string buscado = barra_busqueda_s->GetValue().c_str();
		
		wxCommandEvent eficticio;
		
		if ( buscado != "" ) {
			
			this->click_buscar( eficticio );
			
		} else {
			
			grilla_socios->ClearGrid();
			grilla_socios->DeleteRows( 0, grilla_socios->GetNumberRows(), true );
			pos_real.clear();
			
			int tamanyo = socios.size();
			grilla_socios->AppendRows( tamanyo );
			this->sort_socios( orden_socios->GetSelection() );
			
			for ( int i=0;i<tamanyo;i++ ) { 
				
				grilla_socios->SetCellValue( i, 0, socios[i].get_nombre_completo().c_str() );
				grilla_socios->SetCellValue( i, 1, socios[i].get_dni_str().c_str() );
				grilla_socios->SetCellValue( i, 2, socios[i].get_nro_socio_str().c_str() );
				
				buscado = "";
				for ( int j=0;j<tamanyo;j++ ) { 
					
					if ( historial[j].nro_socio == socios[i].get_nro_socio() ) {
						
						buscado = historial[j].fecha_prestamo.str_ddmmaaaa();
						buscado += " al ";
						buscado += historial[j].fecha_devolucion.str_ddmmaaaa();
						break;
						
					}
					
				}
				grilla_socios->SetCellValue( i, 3, buscado.c_str() );
				
				pos_real.push_back( i );
				
			}
			
			this->seleccion( _conservar_seleccion );
			
		}
		
	} else {
		
		string buscado = barra_busqueda_l->GetValue().c_str();
		
		wxCommandEvent eficticio;
		
		if ( buscado != "" ) {
			
			this->click_buscar( eficticio );
			
		} else if ( eleccion_principal->IsShown() ) {
			
			if ( eleccion_sub_2->GetCount() > 0 ) {
				
				this->sub_2_elegido( eficticio );
				
			} else if ( eleccion_sub_1->GetCount() > 0 ) {
				
				this->sub_1_elegido( eficticio );
				
			} else {
				
				this->principal_elegido( eficticio );
				
			}
			
		} else {
			
			grilla_libros->ClearGrid();
			grilla_libros->DeleteRows( 0, grilla_libros->GetNumberRows(), true );
			pos_real.clear();
			
			int tamanyo = libros.size();
			grilla_libros->AppendRows( tamanyo );
			this->sort_libros( orden_libros->GetSelection() );
			
			for ( int i=0;i<tamanyo;i++ ) { 
				
				grilla_libros->SetCellValue( i, 0, libros[i].get_titulo().c_str() );
				grilla_libros->SetCellValue( i, 1, libros[i].get_nombre_autores().c_str() );
				
				buscado = "";
				for ( int j=0;j<tamanyo;j++ ) { 
					
					if ( historial[j].codigo_libro == libros[i].get_codigo() ) {
						
						buscado = historial[j].fecha_prestamo.str_ddmmaaaa();
						buscado += " al ";
						buscado += historial[j].fecha_devolucion.str_ddmmaaaa();
						break;
						
					}
					
				}
				grilla_libros->SetCellValue( i, 2, buscado.c_str() );
				
				pos_real.push_back( i );
				
			}
			
			this->seleccion( _conservar_seleccion );
			
		}
		
	}
	
}

void ventana_historial::click_izq_grilla( wxGridEvent &_event )  {
	
	fila = _event.GetRow();
	this->seleccion();
	
}

void ventana_historial::Dclick_grilla( wxGridEvent &_event )  {
	
	if ( historial_socio == true ) {
		
		ventana_info_libro   nueva_ventana( this, libros[pos_real[fila]] );
		nueva_ventana.ShowModal();
		
	} else {
		
		ventana_info_socio   nueva_ventana( this, socios[pos_real[fila]] );
		nueva_ventana.ShowModal();
		
	}
	
}

// BARRA DE HERRAMIENTAS
void ventana_historial::click_boton_detalles( wxCommandEvent &_event )  {
	
	if ( historial_socio == true ) {
		
		ventana_info_libro   nueva_ventana( this, libros[pos_real[fila]] );
		nueva_ventana.ShowModal();
		
	} else {
		
		ventana_info_socio   nueva_ventana( this, socios[pos_real[fila]] );
		nueva_ventana.ShowModal();
		
	}
	
}

void ventana_historial::click_boton_estadisticas( wxCommandEvent &_event )  {
	
	ventana_estadisticas   nueva_ventana( this );
	nueva_ventana.ShowModal();
	
}

void ventana_historial::cambio_orden( wxCommandEvent &_event )  {
	
	this->refresh();
	
}

void ventana_historial::click_buscar( wxCommandEvent &_event )  {
	
	if ( historial_socio == true ) {
		
		grilla_libros->ClearGrid();
		grilla_libros->DeleteRows( 0, grilla_libros->GetNumberRows(), true );
		pos_real.clear();
		
		string buscado = barra_busqueda_l->GetValue().c_str();
		
		if ( buscado == "" ) {
			
			this->refresh();
			
		} else {
			
			const int tamanyo = libros.size();
			
			int contador = 0;
			string hist;
			
			for ( int i=0;i<tamanyo;i++ ) { 
				
				if ( libros[i].buscar_contenido( buscado ) == true ) {
					
					grilla_libros->AppendRows();
					grilla_libros->SetCellValue( i, 0, libros[i].get_titulo().c_str() );
					grilla_libros->SetCellValue( i, 1, libros[i].get_nombre_autores().c_str() );
					
					for ( int j=0;j<tamanyo;j++ ) { 
						
						if ( historial[j].codigo_libro == libros[i].get_codigo() ) {
							
							hist = historial[j].fecha_prestamo.str_ddmmaaaa();
							hist += " al ";
							hist += historial[j].fecha_devolucion.str_ddmmaaaa();
							break;
							
						}
						
					}
					grilla_libros->SetCellValue( i, 2, hist.c_str() );
					
					++contador;
					
					pos_real.push_back( i );
					
				}
				
				
			}
			
		}
		
	} else {
		
		grilla_socios->ClearGrid();
		grilla_socios->DeleteRows( 0, grilla_socios->GetNumberRows(), true );
		pos_real.clear();
		
		string buscado = barra_busqueda_s->GetValue().c_str();
		
		if ( buscado == "" ) {
			
			this->refresh();
			
		} else {
			
			const int tamanyo = socios.size();
			
			int contador = 0;
			string hist;
			
			for ( int i=0;i<tamanyo;i++ ) { 
				
				if ( socios[i].socio_buscado( buscado ) == true ) {
					
					grilla_socios->AppendRows();
					grilla_socios->SetCellValue( i, 0, socios[i].get_nombre_completo().c_str() );
					grilla_socios->SetCellValue( i, 1, socios[i].get_dni_str().c_str() );
					grilla_socios->SetCellValue( i, 2, socios[i].get_nro_socio_str().c_str() );
					
					for ( int j=0;j<tamanyo;j++ ) { 
						
						if ( historial[j].nro_socio == socios[i].get_nro_socio() ) {
							
							hist = historial[j].fecha_prestamo.str_ddmmaaaa();
							hist += " al ";
							hist += historial[j].fecha_devolucion.str_ddmmaaaa();
							break;
							
						}
						
					}
					grilla_socios->SetCellValue( i, 3, hist.c_str() );
					
					++ contador;
					
					pos_real.push_back( i );
					
				}
				
				
			}
			
		}
		
	}
	
}

void ventana_historial::click_boton_restaurar( wxCommandEvent &_event )  {
	
	if ( historial_socio == true ) {
		
		barra_busqueda_l->SetValue( wxT("") );
		
		eleccion_principal->Hide();
		eleccion_sub_1->Hide();
		eleccion_sub_1->Clear();
		eleccion_sub_2->Hide();
		eleccion_sub_2->Clear();
		
		wxSize tamanyo = this->GetSize();
		tamanyo.SetHeight( tamanyo.GetHeight() +1 );
		this->SetSize( tamanyo );
		tamanyo.SetHeight( tamanyo.GetHeight() -1 );
		this->SetSize( tamanyo );
		this->Layout();
		
	} else {
		
		barra_busqueda_s->SetValue( wxT("") );
		
	}
	
	this->refresh();
	
}

void ventana_historial::click_boton_ayuda( wxCommandEvent &_event )  {
	
	if ( !Ayuda ) {
		
		Ayuda = new ventana_ayuda();
		
	}
	
	Ayuda->Show();
	
}

void ventana_historial::click_boton_CDU( wxCommandEvent &_event )  {
	
	if ( eleccion_principal->IsShown() ) {
		
		eleccion_principal->Hide();
		eleccion_sub_1->Hide();
		eleccion_sub_1->Clear();
		eleccion_sub_2->Hide();
		eleccion_sub_2->Clear();
		this->refresh();
		
	} else {
		
		eleccion_principal->Show();
		eleccion_sub_1->Show();
		eleccion_sub_2->Show();	
		wxCommandEvent evento_ficticio;
		this->principal_elegido( evento_ficticio );
		
	}
	
	this->redibujar_ventana();
	
}

// EVENTOS CDU
void ventana_historial::principal_elegido( wxCommandEvent &_event )  {
	
	int eleccion1 = eleccion_principal->GetSelection();
	eleccion_sub_1->Clear();
	eleccion_sub_2->Clear();
	
	switch ( eleccion1 ) {
		
	case 0:
		eleccion_sub_1->Append( wxT("Proleg�menos. Fundamentos de la ciencia y de la cultura") );
		eleccion_sub_1->Append( wxT("Bibliograf�a y bibliograf�as. Cat�logos") );
		eleccion_sub_1->Append( wxT("Biblioteconom�a, bibliotecolog�a") );
		eleccion_sub_1->Append( wxT("Obras generales de referencia (como materia)") );
		eleccion_sub_1->Append( wxT("Vacante") );
		eleccion_sub_1->Append( wxT("Publicaciones seriadas, publicaciones peri�dicas (como materia)") );
		eleccion_sub_1->Append( wxT("Organizaciones de naturaleza general") );
		eleccion_sub_1->Append( wxT("Peri�dicos. La prensa. Periodismo") );
		eleccion_sub_1->Append( wxT("Poligraf�as. Obras colectivas") );
		eleccion_sub_1->Append( wxT("Manuscritos. Obras raras y notables") );
		break;
		
	case 1:
		eleccion_sub_1->Append( wxT("Naturaleza y papel de la filosof�a") );
		eleccion_sub_1->Append( wxT("Metaf�sica") );
		eleccion_sub_1->Append( wxT("Metaf�sica especial") );
		eleccion_sub_1->Append( wxT("Filosof�a de la mente y del esp�ritu. Metaf�sica de la vida espiritual") );
		eleccion_sub_1->Append( wxT("Sistemas y puntos de vista filos�ficos") );
		eleccion_sub_1->Append( wxT("Psicolog�a") );
		eleccion_sub_1->Append( wxT("L�gica. Epistemolog�a. Teor�a del conocimiento. Metodolog�a de la l�gica") );
		eleccion_sub_1->Append( wxT("Filosof�a moral. �tica. Filosof�a pr�ctica") );
		break;
		
	case 2:
		eleccion_sub_1->Append( wxT("Subdivisiones auxiliares especiales para religi�n") );
		eleccion_sub_1->Append( wxT("Sistemas religiosos. Religiones y confesiones") );
		break;
		
	case 3:
		eleccion_sub_1->Append( wxT("M�todos de las ciencias sociales") );
		eleccion_sub_1->Append( wxT("Cuestiones sociales. Pr�ctica social. Pr�ctica cultural. Modo de vida (Lebensweise)") );
		eleccion_sub_1->Append( wxT("Estudios de g�nero") );
		eleccion_sub_1->Append( wxT("Sociograf�a. Estudios descriptivos de la sociedad (cualitativos y cuantitativos)") );
		eleccion_sub_1->Append( wxT("Estad�stica como ciencia. Teor�a de la estad�stica") );
		eleccion_sub_1->Append( wxT("Sociedad") );
		eleccion_sub_1->Append( wxT("Pol�tica") );
		eleccion_sub_1->Append( wxT("Econom�a. Ciencia econ�mica") );
		eleccion_sub_1->Append( wxT("Derecho. Jurisprudencia") );
		eleccion_sub_1->Append( wxT("Administraci�n p�blica. Gobierno. Asuntos militares") );
		eleccion_sub_1->Append( wxT("Proteccion de las necesidades materiales y mentales de la vida") );
		eleccion_sub_1->Append( wxT("Educaci�n") );
		eleccion_sub_1->Append( wxT("Antropolog�a cultural. Etnograf�a. Usos. Costumbres. Tradiciones. Formas de vida") );
		break;
		
	case 5:
		eleccion_sub_1->Append( wxT("Ciencias del medio ambiente. Conservaci�n de los recursos naturales. Amenazas al medio ambiente y protecci�n contra ellas") );
		eleccion_sub_1->Append( wxT("Matem�ticas") );
		eleccion_sub_1->Append( wxT("Astronom�a. Astrof�sica. Investigaci�n espacial. Geodesia") );
		eleccion_sub_1->Append( wxT("F�sica") );
		eleccion_sub_1->Append( wxT("Qu�mica. Cristalograf�a. Mineralog�a") );
		eleccion_sub_1->Append( wxT("Ciencias de la tierra. Ciencias geol�gicas") );
		eleccion_sub_1->Append( wxT("Paleontolog�a") );
		eleccion_sub_1->Append( wxT("Ciencias biol�gicas en general") );
		eleccion_sub_1->Append( wxT("Bot�nica") );
		eleccion_sub_1->Append( wxT("Zoolog�a") );
		break;
		
	case 6:
		eleccion_sub_1->Append( wxT("Biotecnolog�a") );
		eleccion_sub_1->Append( wxT("Ciencias m�dicas") );
		eleccion_sub_1->Append( wxT("Ingenier�a. Tecnolog�a en general") );
		eleccion_sub_1->Append( wxT("Agricultura y ciencias y t�cnicas relacionadas. Silvicultura. Zootecnia. Explotaci�n de la vida silvestre") );
		eleccion_sub_1->Append( wxT("Econom�a dom�stica. Ciencia dom�stica. Gobierno de la casa") );
		eleccion_sub_1->Append( wxT("Industrias de la comunicaci�n y el transporte. Contabilidad. Organizaci�n empresarial. Relaciones p�blicas") );
		eleccion_sub_1->Append( wxT("Tecnolog�a qu�mica. Industrias qu�micas y afines") );
		eleccion_sub_1->Append( wxT("Industrias, comercios y oficios diversos") );
		eleccion_sub_1->Append( wxT("Industrias, oficios y comercio de art�culos acabados o ensamblados") );
		eleccion_sub_1->Append( wxT("Industria de la construcci�n. Materiales de construcci�n. Pr�cticas y procedimientos de construcci�n") );
		break;
		
	case 7:
		eleccion_sub_1->Append( wxT("Auxiliares especiales para el arte") );
		eleccion_sub_1->Append( wxT("Planificaci�n territorial, urbanismo. Planificaci�n regional, urbana y rural. Paisajes, parques, jardines") );
		eleccion_sub_1->Append( wxT("Arquitectura") );
		eleccion_sub_1->Append( wxT("Artes pl�sticas") );
		eleccion_sub_1->Append( wxT("Dibujo. Dise�o. Artes aplicadas y oficios art�sticos") );
		eleccion_sub_1->Append( wxT("Pintura") );
		eleccion_sub_1->Append( wxT("Artes gr�ficas, grabado. Gr�ficos") );
		eleccion_sub_1->Append( wxT("Fotograf�a y procesos similares") );
		eleccion_sub_1->Append( wxT("M�sica") );
		eleccion_sub_1->Append( wxT("Diversiones. Espect�culos. Juegos. Deportes") );
		break;
		
	case 8:
		eleccion_sub_1->Append( wxT("Cuestiones generales relativas a la ling��stica y a la literatura. Filolog�a") );
		eleccion_sub_1->Append( wxT("Ling��stica y lenguas") );
		eleccion_sub_1->Append( wxT("Literatura") );
		break;
		
	case 9:
		eleccion_sub_1->Append( wxT("Arqueolog�a. Prehistoria. Restos culturales. Estudios regionales") );
		eleccion_sub_1->Append( wxT("Geograf�a. Exploraci�n de la Tierra y de los distintos pa�ses. Viajes. Geograf�a regional") );
		eleccion_sub_1->Append( wxT("Estudios biogr�ficos. Genealog�a. Her�ldica. Banderas") );
		eleccion_sub_1->Append( wxT("Historia") );
		
	}
	
	grilla_libros->ClearGrid();
	grilla_libros->DeleteRows( 0, grilla_libros->GetNumberRows(), true );
	pos_real.clear();
	
	const int tamanyo = libros.size();
	string hist;
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( libros[i].get_ubicacion().c1 == eleccion1 ) {
			
			grilla_libros->AppendRows();
			grilla_libros->SetCellValue( i, 0, libros[i].get_titulo().c_str() );
			grilla_libros->SetCellValue( i, 1, libros[i].get_nombre_autores().c_str() );
			
			for ( int j=0;j<tamanyo;j++ ) { 
				
				if ( historial[j].codigo_libro == libros[i].get_codigo() ) {
					
					hist = historial[j].fecha_prestamo.str_ddmmaaaa();
					hist += " al ";
					hist += historial[j].fecha_devolucion.str_ddmmaaaa();
					break;
					
				}
				
			}
			grilla_libros->SetCellValue( i, 2, hist.c_str() );
			
			pos_real.push_back( i );
			
		}
		
		
	}
	
	this->redibujar_ventana();
	
}

void ventana_historial::sub_1_elegido( wxCommandEvent &_event )  {
	
	eleccion_sub_2->Clear();
	
	int eleccion1 = eleccion_principal->GetSelection();
	int eleccion2 = eleccion_sub_1->GetSelection();
	
	switch ( eleccion1 ) {
		
	case 0:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("Ciencia y conocimiento en general. Organizaci�n del trabajo intelectual") );
			eleccion_sub_2->Append( wxT("Documentaci�n. Libros. Escritos. Autor�a") );
			eleccion_sub_2->Append( wxT("Escritura y sistemas de escritura") );
			eleccion_sub_2->Append( wxT("Ciencia y tecnolog�a de los ordenadores. Inform�tica. Procesamiento de datos") );
			eleccion_sub_2->Append( wxT("Gesti�n") );
			eleccion_sub_2->Append( wxT("Normalizaci�n de productos, operaciones, pesos, medidas y tiempo") );
			eleccion_sub_2->Append( wxT("Actividad y organizaci�n. Teor�a de la comunicaci�n y del control en general (cibern�tica). �Ingenier�a humana�") );
			eleccion_sub_2->Append( wxT("Civilizaci�n. Cultura. Progreso") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Bibliograf�as universales y generales") );
			eleccion_sub_2->Append( wxT("Bibliograf�as de autor. Bibliograf�as individuales") );
			eleccion_sub_2->Append( wxT("Bibliograf�as colectivas") );
			eleccion_sub_2->Append( wxT("Bibliograf�as de obras con caracter�sticas especiales") );
			eleccion_sub_2->Append( wxT("Bibliograf�as seg�n el lugar") );
			eleccion_sub_2->Append( wxT("Bibliograf�as de temas especiales") );
			eleccion_sub_2->Append( wxT("Cat�logos") );
			break;
			
		case 2:
			eleccion_sub_2->Append( wxT("Funci�n, valor, utilidad, creaci�n, desarrollo de las bibliotecas") );
			eleccion_sub_2->Append( wxT("Emplazamiento de bibliotecas, edificios, instalaciones. Equipamiento") );
			eleccion_sub_2->Append( wxT("Administraci�n de bibliotecas. Personal") );
			eleccion_sub_2->Append( wxT("Relaciones con el p�blico. Reglamentos para el uso de bibliotecas") );
			eleccion_sub_2->Append( wxT("Departamentos administrativos de las bibliotecas") );
			eleccion_sub_2->Append( wxT("Bibliotecas especializadas") );
			eleccion_sub_2->Append( wxT("Bibliotecas generales") );
			break;
			
		case 3:
			eleccion_sub_2->Append( wxT("Enciclopedias") );
			eleccion_sub_2->Append( wxT("Diccionarios") );
			eleccion_sub_2->Append( wxT("L�xicos") );
			eleccion_sub_2->Append( wxT("Glosarios") );
			break;
			
		case 5:
			eleccion_sub_2->Append( wxT("Anuarios") );
			eleccion_sub_2->Append( wxT("Directorios") );
			eleccion_sub_2->Append( wxT("Libros de direcciones") );
			eleccion_sub_2->Append( wxT("Almanaques") );
			eleccion_sub_2->Append( wxT("Calendarios") );
			break;
			
		case 6:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para organizaciones y asociaciones") );
			eleccion_sub_2->Append( wxT("Organizaciones y otros tipos de cooperaci�n") );
			eleccion_sub_2->Append( wxT("Museos. Exposiciones permanentes") );
			break;
			
		case 7:
			eleccion_sub_2->Append( wxT("Periodismo") );
			break;
			
		case 8:
			eleccion_sub_2->Append( wxT("Poligraf�as colectivas") );
			eleccion_sub_2->Append( wxT("Material pict�rico") );
			eleccion_sub_2->Append( wxT("Documentos de forma particular") );
			eleccion_sub_2->Append( wxT("Documentos de origen o destino espec�fico") );
			break;
			
		case 9:
			eleccion_sub_2->Append( wxT("Manuscritos") );
			eleccion_sub_2->Append( wxT("Libros xilogr�ficos") );
			eleccion_sub_2->Append( wxT("Incunables") );
			eleccion_sub_2->Append( wxT("Otras obras impresas preciosas, notables o raras") );
			eleccion_sub_2->Append( wxT("Obras notables por su encuadernaci�n") );
			eleccion_sub_2->Append( wxT("Obras notables por sus ilustraciones o por los materiales utilizados") );
			eleccion_sub_2->Append( wxT("Marcas de propiedad u origen") );
			
		}
		break;
		
	case 1:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("La filosof�a como ciencia") );
			eleccion_sub_2->Append( wxT("La filosof�a como arte") );
			eleccion_sub_2->Append( wxT("Posibilidad de la filosof�a") );
			eleccion_sub_2->Append( wxT("�mbito de la filosof�a") );
			eleccion_sub_2->Append( wxT("M�todos para filosofar") );
			eleccion_sub_2->Append( wxT("Otros") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Metaf�sica general. Ontolog�a") );
			eleccion_sub_2->Append( wxT("Cosmolog�a. Filosof�a de la naturaleza") );
			break;
			
		case 2:
			eleccion_sub_2->Append( wxT("Causalidad. Libertad. Necesidad. Teleolog�a. Finitud. Infinitud. Universo. El alma. Naturaleza de la vida y de la muerte") );
			break;
			
		case 3:
			eleccion_sub_2->Append( wxT("Conceptos y leyes generales") );
			eleccion_sub_2->Append( wxT("Filosof�a de la cultura. Sistemas culturales. Teor�a de los conjuntos culturales") );
			eleccion_sub_2->Append( wxT("Metaf�sica de la vida espiritual") );
			eleccion_sub_2->Append( wxT("Lo paranormal. Lo oculto. Fen�menos psi") );
			break;
			
		case 4:
			eleccion_sub_2->Append( wxT("Actitudes filos�ficas posibles. Tipolog�a de los sistemas filos�ficos") );
			eleccion_sub_2->Append( wxT("Tipos de puntos de vista filos�ficos") );
			break;
			
		case 5:
			eleccion_sub_2->Append( wxT("Psicofisiolog�a (psicolog�a fisiol�gica). Fisiolog�a mental") );
			eleccion_sub_2->Append( wxT("Desarrollo y capacidad mental. Psicolog�a comparada") );
			eleccion_sub_2->Append( wxT("Sensaci�n. Percepci�n sensorial") );
			eleccion_sub_2->Append( wxT("Funciones ejecutivas") );
			eleccion_sub_2->Append( wxT("Procesos mentales superiores") );
			eleccion_sub_2->Append( wxT("Estados y procesos mentales especiales") );
			eleccion_sub_2->Append( wxT("Psicopatolog�a") );
			eleccion_sub_2->Append( wxT("Psicolog�a aplicada (psicotecnolog�a) en general") );
			break;
			
		case 6:
			eleccion_sub_2->Append( wxT("Principios fundamentales de la l�gica") );
			eleccion_sub_2->Append( wxT("Log�stica. L�gica simb�lica. L�gica matem�tica. C�lculo l�gico") );
			eleccion_sub_2->Append( wxT("Teor�a del conocimiento. Epistemolog�a") );
			eleccion_sub_2->Append( wxT("Metodolog�a l�gica") );
			break;
			
		case 7:
			eleccion_sub_2->Append( wxT("Moral individual. Deberes del hombre para consigo mismo") );
			eleccion_sub_2->Append( wxT("�tica social. Deberes del hombre para con sus pr�jimos") );
			eleccion_sub_2->Append( wxT("�tica familiar") );
			eleccion_sub_2->Append( wxT("�tica sexual. Moralidad sexual") );
			eleccion_sub_2->Append( wxT("�tica y sociedad") );
			
		}
		break;
		
	case 2:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("Teor�a y filosof�a de la religi�n. Naturaleza de la religi�n. Fen�meno religioso.") );
			eleccion_sub_2->Append( wxT("Evidencias de la religi�n") );
			eleccion_sub_2->Append( wxT("Personas en la religi�n") );
			eleccion_sub_2->Append( wxT("Actividades religiosas. Pr�cticas religiosas") );
			eleccion_sub_2->Append( wxT("Veneraci�n en general. Culto. Ritos y ceremonias") );
			eleccion_sub_2->Append( wxT("Procesos en religi�n") );
			eleccion_sub_2->Append( wxT("Organizaci�n y administraci�n religiosa") );
			eleccion_sub_2->Append( wxT("Religiones caracterizadas por varias propiedades") );
			eleccion_sub_2->Append( wxT("Historia de la fe, religi�n, denominaci�n o iglesia") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Religiones prehist�ricas y primitivas") );
			eleccion_sub_2->Append( wxT("Religiones originadas en el Lejano Oriente") );
			eleccion_sub_2->Append( wxT("Religiones originadas en el subcontinente indio. Religiones hind�es en el m�s amplio sentido") );
			eleccion_sub_2->Append( wxT("Budismo") );
			eleccion_sub_2->Append( wxT("Religiones de la Antig�edad. Cultos y religiones menores") );
			eleccion_sub_2->Append( wxT("Juda�smo") );
			eleccion_sub_2->Append( wxT("Cristiandad") );
			eleccion_sub_2->Append( wxT("Islamismo") );
			eleccion_sub_2->Append( wxT("Movimientos espirituales modernos") );
			
		}
		break;
		
	case 3:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("M�todos de las ciencias sociales") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Cuestiones sociales. Pr�ctica social. Pr�ctica cultural. Modo de vida (Lebensweise)") );
			break;
			
		case 2:
			eleccion_sub_2->Append( wxT("Rol sexual. G�nero. Personas desde un punto de vista interdisciplinario") );
			break;
			
		case 3:
			eleccion_sub_2->Append( wxT("Sociograf�a. Estudios descriptivos de la sociedad (cualitativos y cuantitativos)") );
			break;
			
		case 4:
			eleccion_sub_2->Append( wxT("Fundamentos, bases de la estad�stica") );
			eleccion_sub_2->Append( wxT("T�cnicas de investigaci�n. Preparaci�n. Tabulaci�n") );
			eleccion_sub_2->Append( wxT("Organizaci�n general de las estad�sticas. Estad�stica oficial") );
			eleccion_sub_2->Append( wxT("Estad�sticas privadas") );
			break;
			
		case 5:
			eleccion_sub_2->Append( wxT("Demograf�a. Estudios de poblaci�n") );
			eleccion_sub_2->Append( wxT("Sociolog�a") );
			break;
			
		case 6:
			eleccion_sub_2->Append( wxT("Formas de organizaci�n pol�tica. Estados como poderes pol�ticos") );
			eleccion_sub_2->Append( wxT("Relaciones entre la Iglesia y el Estado. Pol�tica religiosa. Pol�tica de la Iglesia") );
			eleccion_sub_2->Append( wxT("Asuntos internos. Pol�tica interior") );
			eleccion_sub_2->Append( wxT("Elecciones. Plebiscitos. Referendos. Campa�as electorales. Corrupci�n, fraude electoral. Resultados electorales") );
			eleccion_sub_2->Append( wxT("Ocupaci�n de territorios. Colonizaci�n. Colonialismo") );
			eleccion_sub_2->Append( wxT("Esclavitud. Trabajo involuntario, sin libertad") );
			eleccion_sub_2->Append( wxT("Relaciones internacionales. Pol�tica internacional, global. Asuntos internacionales. Pol�tica exterior") );
			eleccion_sub_2->Append( wxT("Parlamentos. Representaci�n del pueblo. Gobiernos") );
			eleccion_sub_2->Append( wxT("Partidos y movimientos pol�ticos") );
			break;
			
		case 7:
			eleccion_sub_2->Append( wxT("Econom�a en general") );
			eleccion_sub_2->Append( wxT("Trabajo. Empleo. Econom�a laboral. Organizaci�n del trabajo") );
			eleccion_sub_2->Append( wxT("Econom�a regional. Econom�a territorial. Econom�a del suelo. Econom�a de la vivienda") );
			eleccion_sub_2->Append( wxT("Formas de organizaci�n y cooperaci�n en la econom�a") );
			eleccion_sub_2->Append( wxT("Finanzas") );
			eleccion_sub_2->Append( wxT("Situaci�n econ�mica. Pol�tica econ�mica. Gesti�n de la econom�a. Planificaci�n econ�mica. Producci�n. Servicios. Precios") );
			eleccion_sub_2->Append( wxT("Comercio. Relaciones econ�micas internacionales. Econom�a mundial") );
			break;
			
		case 8:
			eleccion_sub_2->Append( wxT("Derecho en general. M�todos jur�dicos y ciencias auxiliares del derecho") );
			eleccion_sub_2->Append( wxT("Derecho internacional") );
			eleccion_sub_2->Append( wxT("Derecho p�blico. Derecho constitucional. Derecho administrativo") );
			eleccion_sub_2->Append( wxT("Derecho penal. Delitos") );
			eleccion_sub_2->Append( wxT("Derecho penal especial. Derecho penal militar, de las fuerzas armadas de tierra, mar y aire") );
			eleccion_sub_2->Append( wxT("Derecho econ�mico. Leyes del control gubernamental de la econom�a") );
			eleccion_sub_2->Append( wxT("Derecho civil") );
			eleccion_sub_2->Append( wxT("Derecho eclesi�stico. Derecho can�nico. Derecho religioso (opci�n)") );
			eleccion_sub_2->Append( wxT("Ramas especiales del derecho. Problemas legales diversos") );
			break;
			
		case 9:
			eleccion_sub_2->Append( wxT("Actividades propias de la administraci�n p�blica") );
			eleccion_sub_2->Append( wxT("Niveles de administraci�n. Administraci�n local, regional, central") );
			eleccion_sub_2->Append( wxT("Asuntos militares. Arte de la guerra. Ciencia militar. Defensa. Fuerzas armadas") );
			break;
			
		case 10:
			eleccion_sub_2->Append( wxT("Bienestar social") );
			eleccion_sub_2->Append( wxT("Demanda de vivienda y su consecuci�n. Protecci�n de la vivienda") );
			eleccion_sub_2->Append( wxT("Consumismo") );
			eleccion_sub_2->Append( wxT("Seguros. Provisi�n comunitaria mediante participaci�n en los riesgos") );
			break;
			
		case 11:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para teor�a, principios, m�todos y organizaci�n de la educaci�n") );
			eleccion_sub_2->Append( wxT("Tipos de escuelas que imparten una educaci�n general") );
			eleccion_sub_2->Append( wxT("Ense�anza y educaci�n extraescolares. Formaci�n continua") );
			eleccion_sub_2->Append( wxT("Educaci�n, ense�anza, formaci�n de grupos especiales de personas. Escuelas especiales") );
			eleccion_sub_2->Append( wxT("Educaci�n especializada. Formaci�n vocacional, t�cnica, profesional. Colegios e institutos vocacionales. Escuelas polit�cnicas") );
			eleccion_sub_2->Append( wxT("Ense�anza superior. Universidades. Estudios acad�micos") );
			eleccion_sub_2->Append( wxT("Ocio") );
			break;
			
		case 12:
			eleccion_sub_2->Append( wxT("Vestimenta. Indumentaria. Trajes nacionales. Moda. Adornos") );
			eleccion_sub_2->Append( wxT("Costumbres, maneras, usos en la vida privada") );
			eleccion_sub_2->Append( wxT("Muerte. Tratamiento de los cad�veres. Funerales. Ritos funerarios") );
			eleccion_sub_2->Append( wxT("Vida p�blica. Boato. Vida social. Vida de la gente") );
			eleccion_sub_2->Append( wxT("Ceremonial. Etiqueta. Buenas maneras. F�rmulas de cortes�a. Rango. T�tulo") );
			eleccion_sub_2->Append( wxT("Folclore en sentido estricto") );
			
		}
		break;
		
	case 5:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("El medio ambiente y su protecci�n") );
			eleccion_sub_2->Append( wxT("Amenazas al medio ambiente") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Consideraciones fundamentales y generales de las matem�ticas") );
			eleccion_sub_2->Append( wxT("Teor�a de n�meros") );
			eleccion_sub_2->Append( wxT("�lgebra") );
			eleccion_sub_2->Append( wxT("Geometr�a") );
			eleccion_sub_2->Append( wxT("Topolog�a") );
			eleccion_sub_2->Append( wxT("An�lisis matem�tico") );
			eleccion_sub_2->Append( wxT("An�lisis combinatorio. Teor�a de grafos") );
			eleccion_sub_2->Append( wxT("Probabilidades. Estad�stica matem�tica") );
			eleccion_sub_2->Append( wxT("Matem�ticas computacionales. An�lisis num�rico") );
			eleccion_sub_2->Append( wxT("Cibern�tica matem�tica") );
			eleccion_sub_2->Append( wxT("Investigaci�n operativa: teor�as y m�todos matem�ticos") );
			break;
			
		case 2:
			eleccion_sub_2->Append( wxT("Instrumentos y t�cnicas astron�micas") );
			eleccion_sub_2->Append( wxT("Astronom�a te�rica. Mec�nica celeste") );
			eleccion_sub_2->Append( wxT("El sistema solar") );
			eleccion_sub_2->Append( wxT("Estrellas. Sistemas estelares. El universo") );
			eleccion_sub_2->Append( wxT("Geodesia. Agrimensura. Fotogrametr�a. Medici�n a distancia. Cartograf�a") );
			break;
			
		case 3:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para f�sica") );
			eleccion_sub_2->Append( wxT("Mec�nica") );
			eleccion_sub_2->Append( wxT("�ptica") );
			eleccion_sub_2->Append( wxT("Calor. Termodin�mica. F�sica estad�stica") );
			eleccion_sub_2->Append( wxT("Electricidad. Magnetismo. Electromagnetismo") );
			eleccion_sub_2->Append( wxT("F�sica de la materia condensada. F�sica del estado s�lido") );
			eleccion_sub_2->Append( wxT("Naturaleza f�sica de la materia") );
			break;
			
		case 4:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para estado de sustancias y productos qu�micos") );
			eleccion_sub_2->Append( wxT("Auxiliares especiales para composici�n, producci�n, preparaci�n y an�lisis") );
			eleccion_sub_2->Append( wxT("Qu�mica pr�ctica de laboratorio. Qu�mica preparativa y experimental") );
			eleccion_sub_2->Append( wxT("Qu�mica pr�ctica de laboratorio. Qu�mica preparativa y experimental") );
			eleccion_sub_2->Append( wxT("Qu�mica anal�tica") );
			eleccion_sub_2->Append( wxT("Qu�mica f�sica") );
			eleccion_sub_2->Append( wxT("Qu�mica inorg�nica") );
			eleccion_sub_2->Append( wxT("Qu�mica org�nica") );
			eleccion_sub_2->Append( wxT("Ciencias mineral�gicas. Cristalograf�a. Mineralog�a") );
			break;
			
		case 5:
			eleccion_sub_2->Append( wxT("Ciencias auxiliares de la geolog�a, etc.") );
			eleccion_sub_2->Append( wxT("Geolog�a general. Meteorolog�a. Climatolog�a. Geolog�a hist�rica. Estratigraf�a. Paleogeograf�a") );
			eleccion_sub_2->Append( wxT("Petrolog�a. Petrograf�a") );
			eleccion_sub_2->Append( wxT("Geolog�a econ�mica. Dep�sitos minerales") );
			eleccion_sub_2->Append( wxT("Hidrosfera. Agua en general. Hidrolog�a") );
			break;
			
		case 6:
			eleccion_sub_2->Append( wxT("Paleontolog�a") );
			break;
			
		case 7:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para aspectos te�ricos, caracter�sticas, factores, etc. en biolog�a") );
			eleccion_sub_2->Append( wxT("Antropolog�a f�sica") );
			eleccion_sub_2->Append( wxT("Biolog�a general y te�rica.") );
			eleccion_sub_2->Append( wxT("Ecolog�a general y biodiversidad") );
			eleccion_sub_2->Append( wxT("Gen�tica general. Citogen�tica general") );
			eleccion_sub_2->Append( wxT("Biolog�a celular y subcelular. Citolog�a") );
			eleccion_sub_2->Append( wxT("Bases materiales de la vida. Bioqu�mica. Biolog�a molecular. Biof�sica") );
			eleccion_sub_2->Append( wxT("Virolog�a") );
			eleccion_sub_2->Append( wxT("Microbiolog�a") );
			break;
			
		case 8:
			eleccion_sub_2->Append( wxT("Bot�nica general") );
			eleccion_sub_2->Append( wxT("Bot�nica sistem�tica") );
			break;
			
		case 9:
			eleccion_sub_2->Append( wxT("Zoolog�a general") );
			eleccion_sub_2->Append( wxT("Zoolog�a sistem�tica") );
			
		}
		break;
		
	case 6:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("Conceptos fundamentales") );
			eleccion_sub_2->Append( wxT("Procesos y t�cnicas biotecnol�gicas") );
			eleccion_sub_2->Append( wxT("Productos biotecnol�gicos") );
			eleccion_sub_2->Append( wxT("Aplicaciones de la biotecnolog�a") );
			eleccion_sub_2->Append( wxT("Problemas en biotecnolog�a") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Biolog�a humana") );
			eleccion_sub_2->Append( wxT("Higiene en general. Salud e higiene personal") );
			eleccion_sub_2->Append( wxT("Salud e higiene p�blica. Prevenci�n de accidentes") );
			eleccion_sub_2->Append( wxT("Farmacolog�a. Terap�utica. Toxicolog�a") );
			eleccion_sub_2->Append( wxT("Patolog�a. Medicina cl�nica") );
			eleccion_sub_2->Append( wxT("Cirug�a. Ortopedia. Oftalmolog�a") );
			eleccion_sub_2->Append( wxT("Ginecolog�a. Obstetricia") );
			break;
			
		case 2:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para tecnolog�a en general") );
			eleccion_sub_2->Append( wxT("Ensayo de materiales. Materiales comerciales. Centrales de energ�a. Econom�a de la energ�a") );
			eleccion_sub_2->Append( wxT("Ingenier�a mec�nica en general. Tecnolog�a nuclear. Ingenier�a el�ctrica. Maquinaria") );
			eleccion_sub_2->Append( wxT("Miner�a") );
			eleccion_sub_2->Append( wxT("Ingenier�a militar") );
			eleccion_sub_2->Append( wxT("ngenier�a civil y de la construcci�n en general") );
			eleccion_sub_2->Append( wxT("Ingenier�a civil de transporte terrestre. Ingenier�a ferroviaria. Ingenier�a de carreteras") );
			eleccion_sub_2->Append( wxT("Ingenier�a y construcci�n hidr�ulica. Estructuras hidr�ulicas (acu�ticas)") );
			eleccion_sub_2->Append( wxT("Ingenier�a sanitaria. Agua. Saneamiento. Luminotecnia") );
			eleccion_sub_2->Append( wxT("Ingenier�a de los veh�culos de transporte") );
			break;
			
		case 3:
			eleccion_sub_2->Append( wxT("Silvicultura, ingenier�a forestal") );
			eleccion_sub_2->Append( wxT("Gesti�n de las explotaciones agr�colas. Agronom�a. Horticultura") );
			eleccion_sub_2->Append( wxT("Explotaci�n y cr�a de animales en general. Cr�a de ganado. Cr�a de animales dom�sticos") );
			eleccion_sub_2->Append( wxT("Productos de los animales dom�sticos y de la caza") );
			eleccion_sub_2->Append( wxT("Mantenimiento, cr�a y gesti�n de insectos y otros artr�podos") );
			eleccion_sub_2->Append( wxT("Caza. Pesca. Piscicultura") );
			break;
			
		case 4:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para ciencia dom�stica") );
			eleccion_sub_2->Append( wxT("Tipos de hogares y de gesti�n del hogar") );
			eleccion_sub_2->Append( wxT("Alimentos. Cocina. Platos. Comidas") );
			eleccion_sub_2->Append( wxT("El hogar. Equipamiento y mobiliario dom�stico") );
			eleccion_sub_2->Append( wxT("Necesidades personales. Gesti�n dom�stica") );
			break;
			
		case 5:
			eleccion_sub_2->Append( wxT("Telecomunicaci�n y telecontrol (organizaci�n, servicios)") );
			eleccion_sub_2->Append( wxT("Industrias gr�ficas. Impresi�n. Edici�n. Comercio de libros") );
			eleccion_sub_2->Append( wxT("Servicios postales y de transporte. Organizaci�n y control del tr�fico") );
			eleccion_sub_2->Append( wxT("Contabilidad") );
			eleccion_sub_2->Append( wxT("Gesti�n, administraci�n de empresas. Organizaci�n comercial") );
			eleccion_sub_2->Append( wxT("Publicidad. Trabajo de informaci�n. Relaciones p�blicas") );
			break;
			
		case 6:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para ingenier�a qu�mica") );
			eleccion_sub_2->Append( wxT("Productos qu�micos") );
			eleccion_sub_2->Append( wxT("Explosivos. Combustibles") );
			eleccion_sub_2->Append( wxT("Microbiolog�a industrial. Micolog�a industrial. Cimolog�a, industria de la fermentaci�n. Industria de las bebidas. Industria de los estimulantes") );
			eleccion_sub_2->Append( wxT("Producci�n y conservaci�n de alimentos s�lidos") );
			eleccion_sub_2->Append( wxT("Aceites. Grasas. Ceras. Adhesivos. Gomas. Resinas") );
			eleccion_sub_2->Append( wxT("Industria del vidrio. Cer�mica. Cemento y hormig�n") );
			eleccion_sub_2->Append( wxT("Industrias del color") );
			eleccion_sub_2->Append( wxT("Metalurgia") );
			break;
			
		case 7:
			eleccion_sub_2->Append( wxT("Art�culos de metales preciosos, gemas, piedras preciosas") );
			eleccion_sub_2->Append( wxT("Art�culos de hierro y acero en general") );
			eleccion_sub_2->Append( wxT("Art�culos de metales no f�rreos (excepto metales preciosos)") );
			eleccion_sub_2->Append( wxT("Madera e industria maderera") );
			eleccion_sub_2->Append( wxT("Industria del cuero (incluyendo pieles animales y cuero sint�tico)") );
			eleccion_sub_2->Append( wxT("Industria de la pasta de papel, el papel y el cart�n") );
			eleccion_sub_2->Append( wxT("Industria textil") );
			eleccion_sub_2->Append( wxT("Industrias basadas en materiales macromoleculares. Industria del caucho. Industria de los pl�sticos") );
			eleccion_sub_2->Append( wxT("Industrias basadas en diversos materiales procesables") );
			break;
			
		case 8:
			eleccion_sub_2->Append( wxT("Mecanismos e instrumentos de precisi�n") );
			eleccion_sub_2->Append( wxT("Herrer�a. Forja. Forja de herraduras. Obra de hierro forjada a mano") );
			eleccion_sub_2->Append( wxT("Ferreter�a. Art�culos de ferreter�a. Cerrajer�a. Embotellado. Lampister�a. Calentadores") );
			eleccion_sub_2->Append( wxT("Industrias del mueble y afines. Fabricaci�n de muebles. Tapicer�a") );
			eleccion_sub_2->Append( wxT("Guarnicioner�a. Zapater�a. Fabricaci�n de guantes. Art�culos de viaje, deportes, juegos y otros") );
			eleccion_sub_2->Append( wxT("Encuadernaci�n. Metalizado. Fabricaci�n de espejos. Art�culos de escritorio") );
			eleccion_sub_2->Append( wxT("Industria del vestido. Fabricaci�n de prendas. Cuidado de la belleza") );
			eleccion_sub_2->Append( wxT("Art�culos de fantas�a. Juguetes. Art�culos decorativos") );
			eleccion_sub_2->Append( wxT("Aficiones t�cnicas o manuales. Hobbies t�cnicos") );
			break;
			
		case 9:
			eleccion_sub_2->Append( wxT("Materiales de construcci�n. Elementos de construcci�n") );
			eleccion_sub_2->Append( wxT("Partes y elementos estructurales de edificios") );
			eleccion_sub_2->Append( wxT("Mamposter�a y oficios relacionados") );
			eleccion_sub_2->Append( wxT("Construcci�n con madera. Carpinter�a. Carpinter�a de obra") );
			eleccion_sub_2->Append( wxT("Equipos, servicios e instalaciones en edificios (sanitarios, gas, vapor, electricidad). Montadores de tuber�as. Fontaneros, plomeros. Metalistas. Colocadores de drenajes, desag�es. Electricistas. Otros oficios") );
			eleccion_sub_2->Append( wxT("Calefacci�n, ventilaci�n y aire acondicionado en edificios") );
			eleccion_sub_2->Append( wxT("Oficios de acabado y decoraci�n") );
			
		}
		break;
		
	case 7:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("Teor�a y filosof�a del arte. Principios de dise�o, proporci�n, efecto �ptico") );
			eleccion_sub_2->Append( wxT("T�cnica art�stica. Destreza") );
			eleccion_sub_2->Append( wxT("Per�odos y fases art�sticas. Escuelas, estilos, influencias") );
			eleccion_sub_2->Append( wxT("Temas para la representaci�n art�stica. Iconograf�a. Iconolog�a. Detalles y acabados. Decoraci�n. Ornamentaci�n") );
			eleccion_sub_2->Append( wxT("Aplicaciones del arte (en la industria, en el comercio, en el hogar, en la vida diaria)") );
			eleccion_sub_2->Append( wxT("Cuestiones diversas relativas al arte") );
			eleccion_sub_2->Append( wxT("Ocupaciones y actividades relacionadas con las artes y el entretenimiento") );
			eleccion_sub_2->Append( wxT("Aspectos, formas, combinaciones caracter�sticas (en arte, espect�culos y deportes)") );
			eleccion_sub_2->Append( wxT("Interpretaci�n, presentaci�n (en el medio original)") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Principios y pr�ctica de la ordenaci�n territorial. Planificaci�n regional, urbana y rural") );
			eleccion_sub_2->Append( wxT("Planificaci�n del paisaje (natural y dise�ado). Parques. Jardines") );
			eleccion_sub_2->Append( wxT("Cementerios. Panteones. Crematorios. Otros lugares para la inhumaci�n de los muertos (planificaci�n, dise�o, mantenimiento, etc.)") );
			eleccion_sub_2->Append( wxT("Preservaci�n de servicios rurales y urbanos en general") );
			break;
			
		case 2:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para arquitectura") );
			eleccion_sub_2->Append( wxT("Edificios en general") );
			eleccion_sub_2->Append( wxT("Edificios p�blicos, civiles, comerciales, industriales. Arquitectura civil en general") );
			eleccion_sub_2->Append( wxT("Arquitectura religiosa, eclesi�stica. Edificaciones sacras y funerarias") );
			eleccion_sub_2->Append( wxT("Edificios con fines educativos, cient�ficos y culturales") );
			eleccion_sub_2->Append( wxT("Arquitectura dom�stica. Viviendas. Edificios residenciales") );
			break;
			
		case 3:
			eleccion_sub_2->Append( wxT("Escultura en general. Estatuas") );
			eleccion_sub_2->Append( wxT("Gl�ptica. Sigilograf�a") );
			eleccion_sub_2->Append( wxT("Numism�tica") );
			eleccion_sub_2->Append( wxT("Cer�mica. Alfarer�a") );
			eleccion_sub_2->Append( wxT("Artes del metal") );
			break;
			
		case 4:
			eleccion_sub_2->Append( wxT("Dibujo") );
			eleccion_sub_2->Append( wxT("Artes y oficios industriales y dom�sticos. Artes aplicadas") );
			break;
			
		case 5:
			eleccion_sub_2->Append( wxT("Pintura") );
			break;
			
		case 6:
			eleccion_sub_2->Append( wxT("T�cnicas de impresi�n en relieve") );
			eleccion_sub_2->Append( wxT("T�cnicas de grabado en hueco") );
			eleccion_sub_2->Append( wxT("T�cnicas planogr�ficas. Litograf�a (autolitograf�a)") );
			eleccion_sub_2->Append( wxT("Artes gr�ficas aplicadas. Dise�o gr�fico comercial") );
			break;
			
		case 7:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para fotograf�a") );
			eleccion_sub_2->Append( wxT("Equipo, aparatos y materiales fotogr�ficos") );
			eleccion_sub_2->Append( wxT("Sistemas, procesos fotogr�ficos (especialmente los que utilizan sustancias inorg�nicas o fen�menos f�sicos)") );
			eleccion_sub_2->Append( wxT("Procedimientos fotomec�nicos en general") );
			eleccion_sub_2->Append( wxT("Fotolitograf�a. Producci�n fotogr�fica de planchas planogr�ficas") );
			eleccion_sub_2->Append( wxT("Procedimientos de impresi�n en hueco y en relieve. Fotograbado. Tipograf�a o planchas en relieve (bloques lineales o de semitonos)") );
			eleccion_sub_2->Append( wxT("Aplicaciones y t�cnicas especiales de fotograf�a") );
			break;
			
		case 8:
			eleccion_sub_2->Append( wxT("Teor�a y filosof�a de la m�sica") );
			eleccion_sub_2->Append( wxT("Composici�n de obras musicales") );
			eleccion_sub_2->Append( wxT("Per�odos y fases en la historia de la m�sica. Escuelas, estilos e influencias musicales") );
			eleccion_sub_2->Append( wxT("Temas para representaci�n musical. M�sica program�tica. M�sica ilustrativa, descriptiva o representativa") );
			eleccion_sub_2->Append( wxT("Aplicaciones de la m�sica en la industria y en el comercio, en el hogar y en la vida cotidiana") );
			eleccion_sub_2->Append( wxT("Diversas cuestiones relativas a la m�sica") );
			eleccion_sub_2->Append( wxT("Ocupaciones y actividades asociadas a la m�sica") );
			eleccion_sub_2->Append( wxT("Caracter�sticas, g�neros de obras musicales. Formas musicales") );
			eleccion_sub_2->Append( wxT("Tipos de interpretaci�n o presentaci�n") );
			eleccion_sub_2->Append( wxT("Instrumentos musicales y accesorios") );
			break;
			
		case 9:
			eleccion_sub_2->Append( wxT("Cine. Pel�culas") );
			eleccion_sub_2->Append( wxT("Teatro. Escenotecnia. Representaciones teatrales") );
			eleccion_sub_2->Append( wxT("Diversiones y entretenimientos sociales. Arte del movimiento. Baile") );
			eleccion_sub_2->Append( wxT("Juegos de tablero y mesa (de reflexi�n, de habilidad y de azar)") );
			eleccion_sub_2->Append( wxT("Deportes. Juegos deportivos. Ejercicios f�sicos") );
			eleccion_sub_2->Append( wxT("Deportes acu�ticos. Deportes a�reos") );
			eleccion_sub_2->Append( wxT("Equitaci�n y monta. Deportes con caballos y otros animales") );
			eleccion_sub_2->Append( wxT("Pesca deportiva. Caza deportiva. Deportes de tiro y tiro al blanco") );
			
		}
		break;
		
	case 8:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("Prosodia. Ciencias auxiliares y fuentes de la filolog�a") );
			eleccion_sub_2->Append( wxT("Ret�rica. Uso eficaz del lenguaje") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Escuelas y corrientes en ling��stica") );
			eleccion_sub_2->Append( wxT("Metodolog�a de la ling��stica. M�todos y medios") );
			eleccion_sub_2->Append( wxT("Auxiliares especiales para or�genes y periodos de las lenguas") );
			eleccion_sub_2->Append( wxT("Auxiliares especiales para materias y facetas de la ling��stica y las lenguas") );
			eleccion_sub_2->Append( wxT("Lenguas") );
			break;
			
		case 2:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para formas y g�neros literarios") );
			eleccion_sub_2->Append( wxT("Auxiliares especiales para teor�a, estudio y t�cnica literaria") );
			eleccion_sub_2->Append( wxT("Literaturas de las distintas lenguas y familias ling��sticas") );
			
		}
		break;
		
	case 9:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("Arqueolog�a") );
			eleccion_sub_2->Append( wxT("Prehistoria. Vestigios, artefactos y antig�edades prehist�ricas") );
			eleccion_sub_2->Append( wxT("Vestigios culturales de periodos hist�ricos") );
			eleccion_sub_2->Append( wxT("Estudios regionales. Estudio de una localidad") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Generalidades. La geograf�a como ciencia. Exploraciones. Viajes") );
			eleccion_sub_2->Append( wxT("Geograf�a general. Ciencia de los factores geogr�ficos (geograf�a sistem�tica). Geograf�a te�rica") );
			eleccion_sub_2->Append( wxT("Representaciones no literarias, no textuales de una regi�n") );
			eleccion_sub_2->Append( wxT("Geograf�a regional") );
			break;
			
		case 2:
			eleccion_sub_2->Append( wxT("Estudios biogr�ficos") );
			eleccion_sub_2->Append( wxT("Genealog�a") );
			eleccion_sub_2->Append( wxT("Her�ldica") );
			eleccion_sub_2->Append( wxT("Nobleza. T�tulos. Dignidad de lord") );
			eleccion_sub_2->Append( wxT("Banderas. Estandartes. Pabellones") );
			break;
			
		case 3:
			eleccion_sub_2->Append( wxT("Ciencia de la historia. Historiograf�a") );
			eleccion_sub_2->Append( wxT("Historia general") );
			
		}
		
	}
	
	grilla_libros->ClearGrid();
	grilla_libros->DeleteRows( 0, grilla_libros->GetNumberRows(), true );
	pos_real.clear();
	
	const int tamanyo = libros.size();
	string hist;
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( libros[i].get_ubicacion().c1 == eleccion1 && libros[i].get_ubicacion().c2 == eleccion2 ) {
			
			grilla_libros->AppendRows();
			grilla_libros->SetCellValue( i, 0, libros[i].get_titulo().c_str() );
			grilla_libros->SetCellValue( i, 1, libros[i].get_nombre_autores().c_str() );
			
			for ( int j=0;j<tamanyo;j++ ) { 
				
				if ( historial[j].codigo_libro == libros[i].get_codigo() ) {
					
					hist = historial[j].fecha_prestamo.str_ddmmaaaa();
					hist += " al ";
					hist += historial[j].fecha_devolucion.str_ddmmaaaa();
					break;
					
				}
				
			}
			grilla_libros->SetCellValue( i, 2, hist.c_str() );
			
			pos_real.push_back( i );
			
		}
		
		
	}
	
	this->redibujar_ventana();
	
}

void ventana_historial::sub_2_elegido( wxCommandEvent &_event )  {
	
	int eleccion1 = eleccion_principal->GetSelection();
	int eleccion2 = eleccion_sub_1->GetSelection();
	int eleccion3 = eleccion_sub_2->GetSelection();
	
	grilla_libros->ClearGrid();
	grilla_libros->DeleteRows( 0, grilla_libros->GetNumberRows(), true );
	pos_real.clear();
	
	const int tamanyo = libros.size();
	string hist;
	
	for ( int i=0;i<tamanyo;i++ ) { 
		
		if ( libros[i].get_ubicacion().c1 == eleccion1 && libros[i].get_ubicacion().c2 == eleccion2 && libros[i].get_ubicacion().c3 == eleccion3 ) {
			
			grilla_libros->AppendRows();
			grilla_libros->SetCellValue( i, 0, libros[i].get_titulo().c_str() );
			grilla_libros->SetCellValue( i, 1, libros[i].get_nombre_autores().c_str() );
			
			for ( int j=0;j<tamanyo;j++ ) { 
				
				if ( historial[j].codigo_libro == libros[i].get_codigo() ) {
					
					hist = historial[j].fecha_prestamo.str_ddmmaaaa();
					hist += " al ";
					hist += historial[j].fecha_devolucion.str_ddmmaaaa();
					break;
					
				}
				
			}
			grilla_libros->SetCellValue( i, 2, hist.c_str() );
			
			pos_real.push_back( i );
			
		}
		
		
	}
	
	this->redibujar_ventana();
	
}

// BOTONES VENTANA
void ventana_historial::click_boton_cerrar( wxCommandEvent &_event )  {
	
	EndModal(-1);
	
}

// CARGA DE IMAGEN
void ventana_historial::cargar_imagen ( const string &_path ) {
	
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
	foto_socio->SetBitmap( *imagen );
	
}

// ORDENAR
void ventana_historial::sort_socios ( const int &_criterio ) {
	
	switch ( _criterio ) {
		
	case SociosPorNombre:
		std::sort( socios.begin(), socios.end(), socios_por_nombre );
		break;
		
	case SociosPorEdad:
		std::sort( socios.begin(), socios.end(), socios_por_edad );
		break;
		
	case SociosPorLecturas:
		std::sort( socios.begin(), socios.end(), socios_por_lecturas );
		break;
		
	case SociosPorAlta:
		std::sort( socios.begin(), socios.end(), socios_por_fecha_alta );
		break;
		
	case SociosPorPendientes:
		std::sort( socios.begin(), socios.end(), socios_por_pendientes );
		break;
		
	case SociosPorAntig:
		std::sort( socios.begin(), socios.end(), socios_por_antiguedad );
		
	}
	
}

void ventana_historial::sort_libros ( const int &_criterio ) {
	
	switch ( _criterio ) {
		
	case LibrosPorTitulo:
		std::sort( libros.begin(), libros.end(), libros_por_titulo );
		break;
		
	case LibrosPorPrestamos:
		std::sort( libros.begin(), libros.end(), libros_por_prestamos );
		break;
		
	case LibrosPorAutor:
		std::sort( libros.begin(), libros.end(), libros_por_autor );
		break;
		
	default:
		std::sort( libros.begin(), libros.end(), libros_por_fecha_alta );
		
	}
	
}

// REDIBUJAR
void ventana_historial::redibujar_ventana ( ) {
	
//	wxSize tamanyo = this->GetSize();
//	tamanyo.SetHeight( tamanyo.GetHeight() +1 );
//	this->SetSize( tamanyo );
//	tamanyo.SetHeight( tamanyo.GetHeight() -1 );
//	this->SetSize( tamanyo );
	this->Layout();
	this->Fit();
	
}

