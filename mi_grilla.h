////////////////////////////////////////////////////////////////////////////////
// Esta clase se hizo únicamente para sobreescribir el método DrawCellHighlight.
// Al sobreescribirlo dejando el cuerpo en blanco, se deshabilita el sombreado
// en la "celda actual".
////////////////////////////////////////////////////////////////////////////////

#ifndef MI_GRILLA_H
#define MI_GRILLA_H

#include <wx/grid.h>

class mi_grilla : public wxGrid {

public:
	mi_grilla( wxWindow *_parent,
			   wxWindowID _id,
	           const wxPoint &_pos = wxDefaultPosition,
	           const wxSize &_size = wxDefaultSize,
	           long _style = wxWANTS_CHARS,
	           const wxString &_name = wxPanelNameStr );
	~mi_grilla();
	void DrawCellHighlight(wxDC& _dc, const wxGridCellAttr *_attr);
	
};

#endif

