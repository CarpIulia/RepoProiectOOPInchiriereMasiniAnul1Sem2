#pragma once
#include "Service.h"
#include <qpainter.h>
#include <qwidget.h>
class CosReadOnlyGUI : public QWidget, public Observer {
private:
	InchiriereMasini& srv;
public:
	CosReadOnlyGUI(InchiriereMasini& srv) : srv{srv} {
		srv.addObserver(this);
	}
	void paintEvent(QPaintEvent* ev) override {
		srv.sterge_s();
		QPainter p{ this };
		p.drawImage(QRect(0, 0, 100, 100), QImage("C:/Users/Iulia/Desktop/Facultate/Programare orientata obiect/Lab10_11/spalatorie.png"));
		int x = 100;
		for (const auto& masina : srv.srvGetAll_s()) {
			QImage image("C:/Users/Iulia/Desktop/Facultate/Programare orientata obiect/Lab10_11/masina.png");
			p.setFont(QFont("Times", 8, QFont::Bold));
			string nr = masina.getInmatriculare();
			p.drawText(QRect(x+20, 0, 100, 100), 16 , QString::fromStdString(nr));
			p.drawImage(QRect(x, 0, 100, 100), image);
			x += 100;
		}
	}

	void update() override {
		repaint();
	}
};