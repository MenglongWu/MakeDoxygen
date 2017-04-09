#include "qt.hpp"
#include "la/liba.h"
#include "lb/libb.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QWidget MainWindow;

	QFont font;
	font.setPointSize(100); //实际上是16的字号，但设成16却不行
	font.setFamily(("wenquanyi"));
	font.setBold(false);

	app.setFont(font);

	MainWindow.setMinimumSize(200, 100);
	MainWindow.setMaximumSize(600, 500);

	QPushButton button("Hello", &MainWindow);
	button.setGeometry(20, 20, 160, 60);

	QPushButton button2("World", &MainWindow);
	button2.setGeometry(20, 90, 160, 60);
	MainWindow.show();

	return app.exec();
}
