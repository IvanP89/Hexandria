#include "Application.h"
#include <wx/image.h>
#include "ventana_principal.h"

IMPLEMENT_APP(mxApplication)

bool mxApplication::OnInit() {
	wxInitAllImageHandlers();
	new ventana_principal( NULL );
	return true;
}

