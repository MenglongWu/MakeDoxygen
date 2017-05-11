/**
 * Copyright 2015-2017 MenglongWoo@aliyun.com
 * @file	src/qt/qt-hello.cpp
 * @brief	example for MakeDoxygen
 *		simple dialog
 *		Qt cpp source and use library which build with C source (la_part1.c)
 * 
*/
#include "qt.hpp"
#include "../la/liba.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QWidget MainWindow;

	QPushButton button("Hello World", &MainWindow);
	button.setGeometry(20, 20, 160, 60);

	QPushButton button2(la_version(), &MainWindow);
	button2.setGeometry(20, 90, 160, 60);

	MainWindow.show();

	return app.exec();
}
