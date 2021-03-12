#include <QtWidgets/QApplication>
#include <iostream>
#include "Teste.h"
#include "MasinaGUI.h"
#include "CosWindow.h"
int main(int argc, char *argv[])
{
    run_all_tests();
	QApplication a(argc, argv);
    RepoFile repo{ "date.in" };
    InchiriereMasini srv{ repo };
    MasinaGUI window{ srv };
    window.move(500, 100);
    window.show();
	return a.exec();
}
