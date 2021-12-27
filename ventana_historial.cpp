//////////////////////////////////////////////////////////////////////////////
// Nombre:      Hexandria/ventana_historial.cpp
// Autor:       Iván Pizarro.
//
// Implementaciones de los métodos y funciones declarados en 
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
	
	// Inicialización de atributos.
	fila = -1;
	historial_socio = HistorialSocio;
	Ayuda = NULL;
	
	Programa *programa = Singleton::get_base_activa();
	
	if ( historial_socio == true ) {
		
		const socio *const soc = &( programa->socios.get_socio_cod( _codigo ) );
		
		string titulo = "Historial de préstamos de ";
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
		
		string titulo = "Historial de préstamos del libro \"";
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
	
	// Inicialización de interfaz.
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
		eleccion_sub_1->Append( wxT("Prolegómenos. Fundamentos de la ciencia y de la cultura") );
		eleccion_sub_1->Append( wxT("Bibliografía y bibliografías. Catálogos") );
		eleccion_sub_1->Append( wxT("Biblioteconomía, bibliotecología") );
		eleccion_sub_1->Append( wxT("Obras generales de referencia (como materia)") );
		eleccion_sub_1->Append( wxT("Vacante") );
		eleccion_sub_1->Append( wxT("Publicaciones seriadas, publicaciones periódicas (como materia)") );
		eleccion_sub_1->Append( wxT("Organizaciones de naturaleza general") );
		eleccion_sub_1->Append( wxT("Periódicos. La prensa. Periodismo") );
		eleccion_sub_1->Append( wxT("Poligrafías. Obras colectivas") );
		eleccion_sub_1->Append( wxT("Manuscritos. Obras raras y notables") );
		break;
		
	case 1:
		eleccion_sub_1->Append( wxT("Naturaleza y papel de la filosofía") );
		eleccion_sub_1->Append( wxT("Metafísica") );
		eleccion_sub_1->Append( wxT("Metafísica especial") );
		eleccion_sub_1->Append( wxT("Filosofía de la mente y del espíritu. Metafísica de la vida espiritual") );
		eleccion_sub_1->Append( wxT("Sistemas y puntos de vista filosóficos") );
		eleccion_sub_1->Append( wxT("Psicología") );
		eleccion_sub_1->Append( wxT("Lógica. Epistemología. Teoría del conocimiento. Metodología de la lógica") );
		eleccion_sub_1->Append( wxT("Filosofía moral. Ética. Filosofía práctica") );
		break;
		
	case 2:
		eleccion_sub_1->Append( wxT("Subdivisiones auxiliares especiales para religión") );
		eleccion_sub_1->Append( wxT("Sistemas religiosos. Religiones y confesiones") );
		break;
		
	case 3:
		eleccion_sub_1->Append( wxT("Métodos de las ciencias sociales") );
		eleccion_sub_1->Append( wxT("Cuestiones sociales. Práctica social. Práctica cultural. Modo de vida (Lebensweise)") );
		eleccion_sub_1->Append( wxT("Estudios de género") );
		eleccion_sub_1->Append( wxT("Sociografía. Estudios descriptivos de la sociedad (cualitativos y cuantitativos)") );
		eleccion_sub_1->Append( wxT("Estadística como ciencia. Teoría de la estadística") );
		eleccion_sub_1->Append( wxT("Sociedad") );
		eleccion_sub_1->Append( wxT("Política") );
		eleccion_sub_1->Append( wxT("Economía. Ciencia económica") );
		eleccion_sub_1->Append( wxT("Derecho. Jurisprudencia") );
		eleccion_sub_1->Append( wxT("Administración pública. Gobierno. Asuntos militares") );
		eleccion_sub_1->Append( wxT("Proteccion de las necesidades materiales y mentales de la vida") );
		eleccion_sub_1->Append( wxT("Educación") );
		eleccion_sub_1->Append( wxT("Antropología cultural. Etnografía. Usos. Costumbres. Tradiciones. Formas de vida") );
		break;
		
	case 5:
		eleccion_sub_1->Append( wxT("Ciencias del medio ambiente. Conservación de los recursos naturales. Amenazas al medio ambiente y protección contra ellas") );
		eleccion_sub_1->Append( wxT("Matemáticas") );
		eleccion_sub_1->Append( wxT("Astronomía. Astrofísica. Investigación espacial. Geodesia") );
		eleccion_sub_1->Append( wxT("Física") );
		eleccion_sub_1->Append( wxT("Química. Cristalografía. Mineralogía") );
		eleccion_sub_1->Append( wxT("Ciencias de la tierra. Ciencias geológicas") );
		eleccion_sub_1->Append( wxT("Paleontología") );
		eleccion_sub_1->Append( wxT("Ciencias biológicas en general") );
		eleccion_sub_1->Append( wxT("Botánica") );
		eleccion_sub_1->Append( wxT("Zoología") );
		break;
		
	case 6:
		eleccion_sub_1->Append( wxT("Biotecnología") );
		eleccion_sub_1->Append( wxT("Ciencias médicas") );
		eleccion_sub_1->Append( wxT("Ingeniería. Tecnología en general") );
		eleccion_sub_1->Append( wxT("Agricultura y ciencias y técnicas relacionadas. Silvicultura. Zootecnia. Explotación de la vida silvestre") );
		eleccion_sub_1->Append( wxT("Economía doméstica. Ciencia doméstica. Gobierno de la casa") );
		eleccion_sub_1->Append( wxT("Industrias de la comunicación y el transporte. Contabilidad. Organización empresarial. Relaciones públicas") );
		eleccion_sub_1->Append( wxT("Tecnología química. Industrias químicas y afines") );
		eleccion_sub_1->Append( wxT("Industrias, comercios y oficios diversos") );
		eleccion_sub_1->Append( wxT("Industrias, oficios y comercio de artículos acabados o ensamblados") );
		eleccion_sub_1->Append( wxT("Industria de la construcción. Materiales de construcción. Prácticas y procedimientos de construcción") );
		break;
		
	case 7:
		eleccion_sub_1->Append( wxT("Auxiliares especiales para el arte") );
		eleccion_sub_1->Append( wxT("Planificación territorial, urbanismo. Planificación regional, urbana y rural. Paisajes, parques, jardines") );
		eleccion_sub_1->Append( wxT("Arquitectura") );
		eleccion_sub_1->Append( wxT("Artes plásticas") );
		eleccion_sub_1->Append( wxT("Dibujo. Diseño. Artes aplicadas y oficios artísticos") );
		eleccion_sub_1->Append( wxT("Pintura") );
		eleccion_sub_1->Append( wxT("Artes gráficas, grabado. Gráficos") );
		eleccion_sub_1->Append( wxT("Fotografía y procesos similares") );
		eleccion_sub_1->Append( wxT("Música") );
		eleccion_sub_1->Append( wxT("Diversiones. Espectáculos. Juegos. Deportes") );
		break;
		
	case 8:
		eleccion_sub_1->Append( wxT("Cuestiones generales relativas a la lingüística y a la literatura. Filología") );
		eleccion_sub_1->Append( wxT("Lingüística y lenguas") );
		eleccion_sub_1->Append( wxT("Literatura") );
		break;
		
	case 9:
		eleccion_sub_1->Append( wxT("Arqueología. Prehistoria. Restos culturales. Estudios regionales") );
		eleccion_sub_1->Append( wxT("Geografía. Exploración de la Tierra y de los distintos países. Viajes. Geografía regional") );
		eleccion_sub_1->Append( wxT("Estudios biográficos. Genealogía. Heráldica. Banderas") );
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
			eleccion_sub_2->Append( wxT("Ciencia y conocimiento en general. Organización del trabajo intelectual") );
			eleccion_sub_2->Append( wxT("Documentación. Libros. Escritos. Autoría") );
			eleccion_sub_2->Append( wxT("Escritura y sistemas de escritura") );
			eleccion_sub_2->Append( wxT("Ciencia y tecnología de los ordenadores. Informática. Procesamiento de datos") );
			eleccion_sub_2->Append( wxT("Gestión") );
			eleccion_sub_2->Append( wxT("Normalización de productos, operaciones, pesos, medidas y tiempo") );
			eleccion_sub_2->Append( wxT("Actividad y organización. Teoría de la comunicación y del control en general (cibernética). “Ingeniería humana”") );
			eleccion_sub_2->Append( wxT("Civilización. Cultura. Progreso") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Bibliografías universales y generales") );
			eleccion_sub_2->Append( wxT("Bibliografías de autor. Bibliografías individuales") );
			eleccion_sub_2->Append( wxT("Bibliografías colectivas") );
			eleccion_sub_2->Append( wxT("Bibliografías de obras con características especiales") );
			eleccion_sub_2->Append( wxT("Bibliografías según el lugar") );
			eleccion_sub_2->Append( wxT("Bibliografías de temas especiales") );
			eleccion_sub_2->Append( wxT("Catálogos") );
			break;
			
		case 2:
			eleccion_sub_2->Append( wxT("Función, valor, utilidad, creación, desarrollo de las bibliotecas") );
			eleccion_sub_2->Append( wxT("Emplazamiento de bibliotecas, edificios, instalaciones. Equipamiento") );
			eleccion_sub_2->Append( wxT("Administración de bibliotecas. Personal") );
			eleccion_sub_2->Append( wxT("Relaciones con el público. Reglamentos para el uso de bibliotecas") );
			eleccion_sub_2->Append( wxT("Departamentos administrativos de las bibliotecas") );
			eleccion_sub_2->Append( wxT("Bibliotecas especializadas") );
			eleccion_sub_2->Append( wxT("Bibliotecas generales") );
			break;
			
		case 3:
			eleccion_sub_2->Append( wxT("Enciclopedias") );
			eleccion_sub_2->Append( wxT("Diccionarios") );
			eleccion_sub_2->Append( wxT("Léxicos") );
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
			eleccion_sub_2->Append( wxT("Organizaciones y otros tipos de cooperación") );
			eleccion_sub_2->Append( wxT("Museos. Exposiciones permanentes") );
			break;
			
		case 7:
			eleccion_sub_2->Append( wxT("Periodismo") );
			break;
			
		case 8:
			eleccion_sub_2->Append( wxT("Poligrafías colectivas") );
			eleccion_sub_2->Append( wxT("Material pictórico") );
			eleccion_sub_2->Append( wxT("Documentos de forma particular") );
			eleccion_sub_2->Append( wxT("Documentos de origen o destino específico") );
			break;
			
		case 9:
			eleccion_sub_2->Append( wxT("Manuscritos") );
			eleccion_sub_2->Append( wxT("Libros xilográficos") );
			eleccion_sub_2->Append( wxT("Incunables") );
			eleccion_sub_2->Append( wxT("Otras obras impresas preciosas, notables o raras") );
			eleccion_sub_2->Append( wxT("Obras notables por su encuadernación") );
			eleccion_sub_2->Append( wxT("Obras notables por sus ilustraciones o por los materiales utilizados") );
			eleccion_sub_2->Append( wxT("Marcas de propiedad u origen") );
			
		}
		break;
		
	case 1:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("La filosofía como ciencia") );
			eleccion_sub_2->Append( wxT("La filosofía como arte") );
			eleccion_sub_2->Append( wxT("Posibilidad de la filosofía") );
			eleccion_sub_2->Append( wxT("Ámbito de la filosofía") );
			eleccion_sub_2->Append( wxT("Métodos para filosofar") );
			eleccion_sub_2->Append( wxT("Otros") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Metafísica general. Ontología") );
			eleccion_sub_2->Append( wxT("Cosmología. Filosofía de la naturaleza") );
			break;
			
		case 2:
			eleccion_sub_2->Append( wxT("Causalidad. Libertad. Necesidad. Teleología. Finitud. Infinitud. Universo. El alma. Naturaleza de la vida y de la muerte") );
			break;
			
		case 3:
			eleccion_sub_2->Append( wxT("Conceptos y leyes generales") );
			eleccion_sub_2->Append( wxT("Filosofía de la cultura. Sistemas culturales. Teoría de los conjuntos culturales") );
			eleccion_sub_2->Append( wxT("Metafísica de la vida espiritual") );
			eleccion_sub_2->Append( wxT("Lo paranormal. Lo oculto. Fenómenos psi") );
			break;
			
		case 4:
			eleccion_sub_2->Append( wxT("Actitudes filosóficas posibles. Tipología de los sistemas filosóficos") );
			eleccion_sub_2->Append( wxT("Tipos de puntos de vista filosóficos") );
			break;
			
		case 5:
			eleccion_sub_2->Append( wxT("Psicofisiología (psicología fisiológica). Fisiología mental") );
			eleccion_sub_2->Append( wxT("Desarrollo y capacidad mental. Psicología comparada") );
			eleccion_sub_2->Append( wxT("Sensación. Percepción sensorial") );
			eleccion_sub_2->Append( wxT("Funciones ejecutivas") );
			eleccion_sub_2->Append( wxT("Procesos mentales superiores") );
			eleccion_sub_2->Append( wxT("Estados y procesos mentales especiales") );
			eleccion_sub_2->Append( wxT("Psicopatología") );
			eleccion_sub_2->Append( wxT("Psicología aplicada (psicotecnología) en general") );
			break;
			
		case 6:
			eleccion_sub_2->Append( wxT("Principios fundamentales de la lógica") );
			eleccion_sub_2->Append( wxT("Logística. Lógica simbólica. Lógica matemática. Cálculo lógico") );
			eleccion_sub_2->Append( wxT("Teoría del conocimiento. Epistemología") );
			eleccion_sub_2->Append( wxT("Metodología lógica") );
			break;
			
		case 7:
			eleccion_sub_2->Append( wxT("Moral individual. Deberes del hombre para consigo mismo") );
			eleccion_sub_2->Append( wxT("Ética social. Deberes del hombre para con sus prójimos") );
			eleccion_sub_2->Append( wxT("Ética familiar") );
			eleccion_sub_2->Append( wxT("Ética sexual. Moralidad sexual") );
			eleccion_sub_2->Append( wxT("Ética y sociedad") );
			
		}
		break;
		
	case 2:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("Teoría y filosofía de la religión. Naturaleza de la religión. Fenómeno religioso.") );
			eleccion_sub_2->Append( wxT("Evidencias de la religión") );
			eleccion_sub_2->Append( wxT("Personas en la religión") );
			eleccion_sub_2->Append( wxT("Actividades religiosas. Prácticas religiosas") );
			eleccion_sub_2->Append( wxT("Veneración en general. Culto. Ritos y ceremonias") );
			eleccion_sub_2->Append( wxT("Procesos en religión") );
			eleccion_sub_2->Append( wxT("Organización y administración religiosa") );
			eleccion_sub_2->Append( wxT("Religiones caracterizadas por varias propiedades") );
			eleccion_sub_2->Append( wxT("Historia de la fe, religión, denominación o iglesia") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Religiones prehistóricas y primitivas") );
			eleccion_sub_2->Append( wxT("Religiones originadas en el Lejano Oriente") );
			eleccion_sub_2->Append( wxT("Religiones originadas en el subcontinente indio. Religiones hindúes en el más amplio sentido") );
			eleccion_sub_2->Append( wxT("Budismo") );
			eleccion_sub_2->Append( wxT("Religiones de la Antigüedad. Cultos y religiones menores") );
			eleccion_sub_2->Append( wxT("Judaísmo") );
			eleccion_sub_2->Append( wxT("Cristiandad") );
			eleccion_sub_2->Append( wxT("Islamismo") );
			eleccion_sub_2->Append( wxT("Movimientos espirituales modernos") );
			
		}
		break;
		
	case 3:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("Métodos de las ciencias sociales") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Cuestiones sociales. Práctica social. Práctica cultural. Modo de vida (Lebensweise)") );
			break;
			
		case 2:
			eleccion_sub_2->Append( wxT("Rol sexual. Género. Personas desde un punto de vista interdisciplinario") );
			break;
			
		case 3:
			eleccion_sub_2->Append( wxT("Sociografía. Estudios descriptivos de la sociedad (cualitativos y cuantitativos)") );
			break;
			
		case 4:
			eleccion_sub_2->Append( wxT("Fundamentos, bases de la estadística") );
			eleccion_sub_2->Append( wxT("Técnicas de investigación. Preparación. Tabulación") );
			eleccion_sub_2->Append( wxT("Organización general de las estadísticas. Estadística oficial") );
			eleccion_sub_2->Append( wxT("Estadísticas privadas") );
			break;
			
		case 5:
			eleccion_sub_2->Append( wxT("Demografía. Estudios de población") );
			eleccion_sub_2->Append( wxT("Sociología") );
			break;
			
		case 6:
			eleccion_sub_2->Append( wxT("Formas de organización política. Estados como poderes políticos") );
			eleccion_sub_2->Append( wxT("Relaciones entre la Iglesia y el Estado. Política religiosa. Política de la Iglesia") );
			eleccion_sub_2->Append( wxT("Asuntos internos. Política interior") );
			eleccion_sub_2->Append( wxT("Elecciones. Plebiscitos. Referendos. Campañas electorales. Corrupción, fraude electoral. Resultados electorales") );
			eleccion_sub_2->Append( wxT("Ocupación de territorios. Colonización. Colonialismo") );
			eleccion_sub_2->Append( wxT("Esclavitud. Trabajo involuntario, sin libertad") );
			eleccion_sub_2->Append( wxT("Relaciones internacionales. Política internacional, global. Asuntos internacionales. Política exterior") );
			eleccion_sub_2->Append( wxT("Parlamentos. Representación del pueblo. Gobiernos") );
			eleccion_sub_2->Append( wxT("Partidos y movimientos políticos") );
			break;
			
		case 7:
			eleccion_sub_2->Append( wxT("Economía en general") );
			eleccion_sub_2->Append( wxT("Trabajo. Empleo. Economía laboral. Organización del trabajo") );
			eleccion_sub_2->Append( wxT("Economía regional. Economía territorial. Economía del suelo. Economía de la vivienda") );
			eleccion_sub_2->Append( wxT("Formas de organización y cooperación en la economía") );
			eleccion_sub_2->Append( wxT("Finanzas") );
			eleccion_sub_2->Append( wxT("Situación económica. Política económica. Gestión de la economía. Planificación económica. Producción. Servicios. Precios") );
			eleccion_sub_2->Append( wxT("Comercio. Relaciones económicas internacionales. Economía mundial") );
			break;
			
		case 8:
			eleccion_sub_2->Append( wxT("Derecho en general. Métodos jurídicos y ciencias auxiliares del derecho") );
			eleccion_sub_2->Append( wxT("Derecho internacional") );
			eleccion_sub_2->Append( wxT("Derecho público. Derecho constitucional. Derecho administrativo") );
			eleccion_sub_2->Append( wxT("Derecho penal. Delitos") );
			eleccion_sub_2->Append( wxT("Derecho penal especial. Derecho penal militar, de las fuerzas armadas de tierra, mar y aire") );
			eleccion_sub_2->Append( wxT("Derecho económico. Leyes del control gubernamental de la economía") );
			eleccion_sub_2->Append( wxT("Derecho civil") );
			eleccion_sub_2->Append( wxT("Derecho eclesiástico. Derecho canónico. Derecho religioso (opción)") );
			eleccion_sub_2->Append( wxT("Ramas especiales del derecho. Problemas legales diversos") );
			break;
			
		case 9:
			eleccion_sub_2->Append( wxT("Actividades propias de la administración pública") );
			eleccion_sub_2->Append( wxT("Niveles de administración. Administración local, regional, central") );
			eleccion_sub_2->Append( wxT("Asuntos militares. Arte de la guerra. Ciencia militar. Defensa. Fuerzas armadas") );
			break;
			
		case 10:
			eleccion_sub_2->Append( wxT("Bienestar social") );
			eleccion_sub_2->Append( wxT("Demanda de vivienda y su consecución. Protección de la vivienda") );
			eleccion_sub_2->Append( wxT("Consumismo") );
			eleccion_sub_2->Append( wxT("Seguros. Provisión comunitaria mediante participación en los riesgos") );
			break;
			
		case 11:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para teoría, principios, métodos y organización de la educación") );
			eleccion_sub_2->Append( wxT("Tipos de escuelas que imparten una educación general") );
			eleccion_sub_2->Append( wxT("Enseñanza y educación extraescolares. Formación continua") );
			eleccion_sub_2->Append( wxT("Educación, enseñanza, formación de grupos especiales de personas. Escuelas especiales") );
			eleccion_sub_2->Append( wxT("Educación especializada. Formación vocacional, técnica, profesional. Colegios e institutos vocacionales. Escuelas politécnicas") );
			eleccion_sub_2->Append( wxT("Enseñanza superior. Universidades. Estudios académicos") );
			eleccion_sub_2->Append( wxT("Ocio") );
			break;
			
		case 12:
			eleccion_sub_2->Append( wxT("Vestimenta. Indumentaria. Trajes nacionales. Moda. Adornos") );
			eleccion_sub_2->Append( wxT("Costumbres, maneras, usos en la vida privada") );
			eleccion_sub_2->Append( wxT("Muerte. Tratamiento de los cadáveres. Funerales. Ritos funerarios") );
			eleccion_sub_2->Append( wxT("Vida pública. Boato. Vida social. Vida de la gente") );
			eleccion_sub_2->Append( wxT("Ceremonial. Etiqueta. Buenas maneras. Fórmulas de cortesía. Rango. Título") );
			eleccion_sub_2->Append( wxT("Folclore en sentido estricto") );
			
		}
		break;
		
	case 5:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("El medio ambiente y su protección") );
			eleccion_sub_2->Append( wxT("Amenazas al medio ambiente") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Consideraciones fundamentales y generales de las matemáticas") );
			eleccion_sub_2->Append( wxT("Teoría de números") );
			eleccion_sub_2->Append( wxT("Álgebra") );
			eleccion_sub_2->Append( wxT("Geometría") );
			eleccion_sub_2->Append( wxT("Topología") );
			eleccion_sub_2->Append( wxT("Análisis matemático") );
			eleccion_sub_2->Append( wxT("Análisis combinatorio. Teoría de grafos") );
			eleccion_sub_2->Append( wxT("Probabilidades. Estadística matemática") );
			eleccion_sub_2->Append( wxT("Matemáticas computacionales. Análisis numérico") );
			eleccion_sub_2->Append( wxT("Cibernética matemática") );
			eleccion_sub_2->Append( wxT("Investigación operativa: teorías y métodos matemáticos") );
			break;
			
		case 2:
			eleccion_sub_2->Append( wxT("Instrumentos y técnicas astronómicas") );
			eleccion_sub_2->Append( wxT("Astronomía teórica. Mecánica celeste") );
			eleccion_sub_2->Append( wxT("El sistema solar") );
			eleccion_sub_2->Append( wxT("Estrellas. Sistemas estelares. El universo") );
			eleccion_sub_2->Append( wxT("Geodesia. Agrimensura. Fotogrametría. Medición a distancia. Cartografía") );
			break;
			
		case 3:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para física") );
			eleccion_sub_2->Append( wxT("Mecánica") );
			eleccion_sub_2->Append( wxT("Óptica") );
			eleccion_sub_2->Append( wxT("Calor. Termodinámica. Física estadística") );
			eleccion_sub_2->Append( wxT("Electricidad. Magnetismo. Electromagnetismo") );
			eleccion_sub_2->Append( wxT("Física de la materia condensada. Física del estado sólido") );
			eleccion_sub_2->Append( wxT("Naturaleza física de la materia") );
			break;
			
		case 4:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para estado de sustancias y productos químicos") );
			eleccion_sub_2->Append( wxT("Auxiliares especiales para composición, producción, preparación y análisis") );
			eleccion_sub_2->Append( wxT("Química práctica de laboratorio. Química preparativa y experimental") );
			eleccion_sub_2->Append( wxT("Química práctica de laboratorio. Química preparativa y experimental") );
			eleccion_sub_2->Append( wxT("Química analítica") );
			eleccion_sub_2->Append( wxT("Química física") );
			eleccion_sub_2->Append( wxT("Química inorgánica") );
			eleccion_sub_2->Append( wxT("Química orgánica") );
			eleccion_sub_2->Append( wxT("Ciencias mineralógicas. Cristalografía. Mineralogía") );
			break;
			
		case 5:
			eleccion_sub_2->Append( wxT("Ciencias auxiliares de la geología, etc.") );
			eleccion_sub_2->Append( wxT("Geología general. Meteorología. Climatología. Geología histórica. Estratigrafía. Paleogeografía") );
			eleccion_sub_2->Append( wxT("Petrología. Petrografía") );
			eleccion_sub_2->Append( wxT("Geología económica. Depósitos minerales") );
			eleccion_sub_2->Append( wxT("Hidrosfera. Agua en general. Hidrología") );
			break;
			
		case 6:
			eleccion_sub_2->Append( wxT("Paleontología") );
			break;
			
		case 7:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para aspectos teóricos, características, factores, etc. en biología") );
			eleccion_sub_2->Append( wxT("Antropología física") );
			eleccion_sub_2->Append( wxT("Biología general y teórica.") );
			eleccion_sub_2->Append( wxT("Ecología general y biodiversidad") );
			eleccion_sub_2->Append( wxT("Genética general. Citogenética general") );
			eleccion_sub_2->Append( wxT("Biología celular y subcelular. Citología") );
			eleccion_sub_2->Append( wxT("Bases materiales de la vida. Bioquímica. Biología molecular. Biofísica") );
			eleccion_sub_2->Append( wxT("Virología") );
			eleccion_sub_2->Append( wxT("Microbiología") );
			break;
			
		case 8:
			eleccion_sub_2->Append( wxT("Botánica general") );
			eleccion_sub_2->Append( wxT("Botánica sistemática") );
			break;
			
		case 9:
			eleccion_sub_2->Append( wxT("Zoología general") );
			eleccion_sub_2->Append( wxT("Zoología sistemática") );
			
		}
		break;
		
	case 6:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("Conceptos fundamentales") );
			eleccion_sub_2->Append( wxT("Procesos y técnicas biotecnológicas") );
			eleccion_sub_2->Append( wxT("Productos biotecnológicos") );
			eleccion_sub_2->Append( wxT("Aplicaciones de la biotecnología") );
			eleccion_sub_2->Append( wxT("Problemas en biotecnología") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Biología humana") );
			eleccion_sub_2->Append( wxT("Higiene en general. Salud e higiene personal") );
			eleccion_sub_2->Append( wxT("Salud e higiene pública. Prevención de accidentes") );
			eleccion_sub_2->Append( wxT("Farmacología. Terapéutica. Toxicología") );
			eleccion_sub_2->Append( wxT("Patología. Medicina clínica") );
			eleccion_sub_2->Append( wxT("Cirugía. Ortopedia. Oftalmología") );
			eleccion_sub_2->Append( wxT("Ginecología. Obstetricia") );
			break;
			
		case 2:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para tecnología en general") );
			eleccion_sub_2->Append( wxT("Ensayo de materiales. Materiales comerciales. Centrales de energía. Economía de la energía") );
			eleccion_sub_2->Append( wxT("Ingeniería mecánica en general. Tecnología nuclear. Ingeniería eléctrica. Maquinaria") );
			eleccion_sub_2->Append( wxT("Minería") );
			eleccion_sub_2->Append( wxT("Ingeniería militar") );
			eleccion_sub_2->Append( wxT("ngeniería civil y de la construcción en general") );
			eleccion_sub_2->Append( wxT("Ingeniería civil de transporte terrestre. Ingeniería ferroviaria. Ingeniería de carreteras") );
			eleccion_sub_2->Append( wxT("Ingeniería y construcción hidráulica. Estructuras hidráulicas (acuáticas)") );
			eleccion_sub_2->Append( wxT("Ingeniería sanitaria. Agua. Saneamiento. Luminotecnia") );
			eleccion_sub_2->Append( wxT("Ingeniería de los vehículos de transporte") );
			break;
			
		case 3:
			eleccion_sub_2->Append( wxT("Silvicultura, ingeniería forestal") );
			eleccion_sub_2->Append( wxT("Gestión de las explotaciones agrícolas. Agronomía. Horticultura") );
			eleccion_sub_2->Append( wxT("Explotación y cría de animales en general. Cría de ganado. Cría de animales domésticos") );
			eleccion_sub_2->Append( wxT("Productos de los animales domésticos y de la caza") );
			eleccion_sub_2->Append( wxT("Mantenimiento, cría y gestión de insectos y otros artrópodos") );
			eleccion_sub_2->Append( wxT("Caza. Pesca. Piscicultura") );
			break;
			
		case 4:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para ciencia doméstica") );
			eleccion_sub_2->Append( wxT("Tipos de hogares y de gestión del hogar") );
			eleccion_sub_2->Append( wxT("Alimentos. Cocina. Platos. Comidas") );
			eleccion_sub_2->Append( wxT("El hogar. Equipamiento y mobiliario doméstico") );
			eleccion_sub_2->Append( wxT("Necesidades personales. Gestión doméstica") );
			break;
			
		case 5:
			eleccion_sub_2->Append( wxT("Telecomunicación y telecontrol (organización, servicios)") );
			eleccion_sub_2->Append( wxT("Industrias gráficas. Impresión. Edición. Comercio de libros") );
			eleccion_sub_2->Append( wxT("Servicios postales y de transporte. Organización y control del tráfico") );
			eleccion_sub_2->Append( wxT("Contabilidad") );
			eleccion_sub_2->Append( wxT("Gestión, administración de empresas. Organización comercial") );
			eleccion_sub_2->Append( wxT("Publicidad. Trabajo de información. Relaciones públicas") );
			break;
			
		case 6:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para ingeniería química") );
			eleccion_sub_2->Append( wxT("Productos químicos") );
			eleccion_sub_2->Append( wxT("Explosivos. Combustibles") );
			eleccion_sub_2->Append( wxT("Microbiología industrial. Micología industrial. Cimología, industria de la fermentación. Industria de las bebidas. Industria de los estimulantes") );
			eleccion_sub_2->Append( wxT("Producción y conservación de alimentos sólidos") );
			eleccion_sub_2->Append( wxT("Aceites. Grasas. Ceras. Adhesivos. Gomas. Resinas") );
			eleccion_sub_2->Append( wxT("Industria del vidrio. Cerámica. Cemento y hormigón") );
			eleccion_sub_2->Append( wxT("Industrias del color") );
			eleccion_sub_2->Append( wxT("Metalurgia") );
			break;
			
		case 7:
			eleccion_sub_2->Append( wxT("Artículos de metales preciosos, gemas, piedras preciosas") );
			eleccion_sub_2->Append( wxT("Artículos de hierro y acero en general") );
			eleccion_sub_2->Append( wxT("Artículos de metales no férreos (excepto metales preciosos)") );
			eleccion_sub_2->Append( wxT("Madera e industria maderera") );
			eleccion_sub_2->Append( wxT("Industria del cuero (incluyendo pieles animales y cuero sintético)") );
			eleccion_sub_2->Append( wxT("Industria de la pasta de papel, el papel y el cartón") );
			eleccion_sub_2->Append( wxT("Industria textil") );
			eleccion_sub_2->Append( wxT("Industrias basadas en materiales macromoleculares. Industria del caucho. Industria de los plásticos") );
			eleccion_sub_2->Append( wxT("Industrias basadas en diversos materiales procesables") );
			break;
			
		case 8:
			eleccion_sub_2->Append( wxT("Mecanismos e instrumentos de precisión") );
			eleccion_sub_2->Append( wxT("Herrería. Forja. Forja de herraduras. Obra de hierro forjada a mano") );
			eleccion_sub_2->Append( wxT("Ferretería. Artículos de ferretería. Cerrajería. Embotellado. Lampistería. Calentadores") );
			eleccion_sub_2->Append( wxT("Industrias del mueble y afines. Fabricación de muebles. Tapicería") );
			eleccion_sub_2->Append( wxT("Guarnicionería. Zapatería. Fabricación de guantes. Artículos de viaje, deportes, juegos y otros") );
			eleccion_sub_2->Append( wxT("Encuadernación. Metalizado. Fabricación de espejos. Artículos de escritorio") );
			eleccion_sub_2->Append( wxT("Industria del vestido. Fabricación de prendas. Cuidado de la belleza") );
			eleccion_sub_2->Append( wxT("Artículos de fantasía. Juguetes. Artículos decorativos") );
			eleccion_sub_2->Append( wxT("Aficiones técnicas o manuales. Hobbies técnicos") );
			break;
			
		case 9:
			eleccion_sub_2->Append( wxT("Materiales de construcción. Elementos de construcción") );
			eleccion_sub_2->Append( wxT("Partes y elementos estructurales de edificios") );
			eleccion_sub_2->Append( wxT("Mampostería y oficios relacionados") );
			eleccion_sub_2->Append( wxT("Construcción con madera. Carpintería. Carpintería de obra") );
			eleccion_sub_2->Append( wxT("Equipos, servicios e instalaciones en edificios (sanitarios, gas, vapor, electricidad). Montadores de tuberías. Fontaneros, plomeros. Metalistas. Colocadores de drenajes, desagües. Electricistas. Otros oficios") );
			eleccion_sub_2->Append( wxT("Calefacción, ventilación y aire acondicionado en edificios") );
			eleccion_sub_2->Append( wxT("Oficios de acabado y decoración") );
			
		}
		break;
		
	case 7:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("Teoría y filosofía del arte. Principios de diseño, proporción, efecto óptico") );
			eleccion_sub_2->Append( wxT("Técnica artística. Destreza") );
			eleccion_sub_2->Append( wxT("Períodos y fases artísticas. Escuelas, estilos, influencias") );
			eleccion_sub_2->Append( wxT("Temas para la representación artística. Iconografía. Iconología. Detalles y acabados. Decoración. Ornamentación") );
			eleccion_sub_2->Append( wxT("Aplicaciones del arte (en la industria, en el comercio, en el hogar, en la vida diaria)") );
			eleccion_sub_2->Append( wxT("Cuestiones diversas relativas al arte") );
			eleccion_sub_2->Append( wxT("Ocupaciones y actividades relacionadas con las artes y el entretenimiento") );
			eleccion_sub_2->Append( wxT("Aspectos, formas, combinaciones características (en arte, espectáculos y deportes)") );
			eleccion_sub_2->Append( wxT("Interpretación, presentación (en el medio original)") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Principios y práctica de la ordenación territorial. Planificación regional, urbana y rural") );
			eleccion_sub_2->Append( wxT("Planificación del paisaje (natural y diseñado). Parques. Jardines") );
			eleccion_sub_2->Append( wxT("Cementerios. Panteones. Crematorios. Otros lugares para la inhumación de los muertos (planificación, diseño, mantenimiento, etc.)") );
			eleccion_sub_2->Append( wxT("Preservación de servicios rurales y urbanos en general") );
			break;
			
		case 2:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para arquitectura") );
			eleccion_sub_2->Append( wxT("Edificios en general") );
			eleccion_sub_2->Append( wxT("Edificios públicos, civiles, comerciales, industriales. Arquitectura civil en general") );
			eleccion_sub_2->Append( wxT("Arquitectura religiosa, eclesiástica. Edificaciones sacras y funerarias") );
			eleccion_sub_2->Append( wxT("Edificios con fines educativos, científicos y culturales") );
			eleccion_sub_2->Append( wxT("Arquitectura doméstica. Viviendas. Edificios residenciales") );
			break;
			
		case 3:
			eleccion_sub_2->Append( wxT("Escultura en general. Estatuas") );
			eleccion_sub_2->Append( wxT("Glíptica. Sigilografía") );
			eleccion_sub_2->Append( wxT("Numismática") );
			eleccion_sub_2->Append( wxT("Cerámica. Alfarería") );
			eleccion_sub_2->Append( wxT("Artes del metal") );
			break;
			
		case 4:
			eleccion_sub_2->Append( wxT("Dibujo") );
			eleccion_sub_2->Append( wxT("Artes y oficios industriales y domésticos. Artes aplicadas") );
			break;
			
		case 5:
			eleccion_sub_2->Append( wxT("Pintura") );
			break;
			
		case 6:
			eleccion_sub_2->Append( wxT("Técnicas de impresión en relieve") );
			eleccion_sub_2->Append( wxT("Técnicas de grabado en hueco") );
			eleccion_sub_2->Append( wxT("Técnicas planográficas. Litografía (autolitografía)") );
			eleccion_sub_2->Append( wxT("Artes gráficas aplicadas. Diseño gráfico comercial") );
			break;
			
		case 7:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para fotografía") );
			eleccion_sub_2->Append( wxT("Equipo, aparatos y materiales fotográficos") );
			eleccion_sub_2->Append( wxT("Sistemas, procesos fotográficos (especialmente los que utilizan sustancias inorgánicas o fenómenos físicos)") );
			eleccion_sub_2->Append( wxT("Procedimientos fotomecánicos en general") );
			eleccion_sub_2->Append( wxT("Fotolitografía. Producción fotográfica de planchas planográficas") );
			eleccion_sub_2->Append( wxT("Procedimientos de impresión en hueco y en relieve. Fotograbado. Tipografía o planchas en relieve (bloques lineales o de semitonos)") );
			eleccion_sub_2->Append( wxT("Aplicaciones y técnicas especiales de fotografía") );
			break;
			
		case 8:
			eleccion_sub_2->Append( wxT("Teoría y filosofía de la música") );
			eleccion_sub_2->Append( wxT("Composición de obras musicales") );
			eleccion_sub_2->Append( wxT("Períodos y fases en la historia de la música. Escuelas, estilos e influencias musicales") );
			eleccion_sub_2->Append( wxT("Temas para representación musical. Música programática. Música ilustrativa, descriptiva o representativa") );
			eleccion_sub_2->Append( wxT("Aplicaciones de la música en la industria y en el comercio, en el hogar y en la vida cotidiana") );
			eleccion_sub_2->Append( wxT("Diversas cuestiones relativas a la música") );
			eleccion_sub_2->Append( wxT("Ocupaciones y actividades asociadas a la música") );
			eleccion_sub_2->Append( wxT("Características, géneros de obras musicales. Formas musicales") );
			eleccion_sub_2->Append( wxT("Tipos de interpretación o presentación") );
			eleccion_sub_2->Append( wxT("Instrumentos musicales y accesorios") );
			break;
			
		case 9:
			eleccion_sub_2->Append( wxT("Cine. Películas") );
			eleccion_sub_2->Append( wxT("Teatro. Escenotecnia. Representaciones teatrales") );
			eleccion_sub_2->Append( wxT("Diversiones y entretenimientos sociales. Arte del movimiento. Baile") );
			eleccion_sub_2->Append( wxT("Juegos de tablero y mesa (de reflexión, de habilidad y de azar)") );
			eleccion_sub_2->Append( wxT("Deportes. Juegos deportivos. Ejercicios físicos") );
			eleccion_sub_2->Append( wxT("Deportes acuáticos. Deportes aéreos") );
			eleccion_sub_2->Append( wxT("Equitación y monta. Deportes con caballos y otros animales") );
			eleccion_sub_2->Append( wxT("Pesca deportiva. Caza deportiva. Deportes de tiro y tiro al blanco") );
			
		}
		break;
		
	case 8:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("Prosodia. Ciencias auxiliares y fuentes de la filología") );
			eleccion_sub_2->Append( wxT("Retórica. Uso eficaz del lenguaje") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Escuelas y corrientes en lingüística") );
			eleccion_sub_2->Append( wxT("Metodología de la lingüística. Métodos y medios") );
			eleccion_sub_2->Append( wxT("Auxiliares especiales para orígenes y periodos de las lenguas") );
			eleccion_sub_2->Append( wxT("Auxiliares especiales para materias y facetas de la lingüística y las lenguas") );
			eleccion_sub_2->Append( wxT("Lenguas") );
			break;
			
		case 2:
			eleccion_sub_2->Append( wxT("Auxiliares especiales para formas y géneros literarios") );
			eleccion_sub_2->Append( wxT("Auxiliares especiales para teoría, estudio y técnica literaria") );
			eleccion_sub_2->Append( wxT("Literaturas de las distintas lenguas y familias lingüísticas") );
			
		}
		break;
		
	case 9:
		switch ( eleccion2 ) {
			
		case 0:
			eleccion_sub_2->Append( wxT("Arqueología") );
			eleccion_sub_2->Append( wxT("Prehistoria. Vestigios, artefactos y antigüedades prehistóricas") );
			eleccion_sub_2->Append( wxT("Vestigios culturales de periodos históricos") );
			eleccion_sub_2->Append( wxT("Estudios regionales. Estudio de una localidad") );
			break;
			
		case 1:
			eleccion_sub_2->Append( wxT("Generalidades. La geografía como ciencia. Exploraciones. Viajes") );
			eleccion_sub_2->Append( wxT("Geografía general. Ciencia de los factores geográficos (geografía sistemática). Geografía teórica") );
			eleccion_sub_2->Append( wxT("Representaciones no literarias, no textuales de una región") );
			eleccion_sub_2->Append( wxT("Geografía regional") );
			break;
			
		case 2:
			eleccion_sub_2->Append( wxT("Estudios biográficos") );
			eleccion_sub_2->Append( wxT("Genealogía") );
			eleccion_sub_2->Append( wxT("Heráldica") );
			eleccion_sub_2->Append( wxT("Nobleza. Títulos. Dignidad de lord") );
			eleccion_sub_2->Append( wxT("Banderas. Estandartes. Pabellones") );
			break;
			
		case 3:
			eleccion_sub_2->Append( wxT("Ciencia de la historia. Historiografía") );
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

