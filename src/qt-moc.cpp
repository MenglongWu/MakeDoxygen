#include "dlg-net.h"


#ifdef __cplusplus
extern "C" {
#endif


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	DlgNet dialog;
	dialog.show();
	app.exec();
}




#ifdef __cplusplus
}
#endif

