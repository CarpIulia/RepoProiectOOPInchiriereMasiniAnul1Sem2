#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QMessageBox>
#include "Observer.h"
class CosWindow : public QWidget , public Observer{
	friend class MasinaGUI;
private:
	InchiriereMasini& srv;
	QListWidget* spalatorieList = new QListWidget{};
	QPushButton* golire = new QPushButton{ "Golire" };
	QPushButton* randomBtn = new QPushButton{ "Random" };
	QPushButton* exportBtn = new QPushButton{ "Export" };
	QLineEdit* exp = new QLineEdit;
	QLineEdit* random = new QLineEdit;
	void initGUI() {
		QVBoxLayout* lyMain = new QVBoxLayout{};
		setLayout(lyMain);
		lyMain->addWidget(spalatorieList);
		QFormLayout* lyExp = new QFormLayout{};
		QLabel* expTxt = new QLabel{ "Export to " };
		QLabel* rndTxt = new QLabel{ "Numar " };
		lyExp->addRow(expTxt, exp);
		lyExp->addRow(rndTxt, random);
		lyExp->setContentsMargins(0, 3, 0, 0);
		QVBoxLayout* lyRE = new QVBoxLayout{};
		lyRE->addWidget(exportBtn);
		lyRE->addWidget(randomBtn);
		QHBoxLayout* lyOpt = new QHBoxLayout{};
		lyOpt->addLayout(lyExp);
		lyOpt->addLayout(lyRE);
		lyOpt->addWidget(golire);
		lyMain->addLayout(lyOpt);

		spalatorieList->setStyleSheet("background-color:#b5c7e3; color:#2B4570");
		randomBtn->setStyleSheet("font-weight: bold;background-color:#2B4570; color:#A8D0DB");
		golire->setStyleSheet("font-weight: bold;background-color:#2B4570; color:#A8D0DB");
		exportBtn->setStyleSheet("font-weight: bold;background-color:#2B4570; color:#A8D0DB");
		expTxt->setStyleSheet("font-weight: bold;color:#2B4570");
		rndTxt->setStyleSheet("font-weight: bold;color:#2B4570");
		exp->setStyleSheet("background-color:#b5c7e3; color:#2B4570");
		random->setStyleSheet("background-color:#b5c7e3; color:#2B4570");
	}

	void loadList() {
		spalatorieList->clear();
		srv.sterge_s();
		vector<Masina> spalatorie = srv.srvGetAll_s();
		for (const auto& m : spalatorie) {
			string text = m.getInmatriculare() + " " + m.getProducator() + " " + m.getModel() + " " + m.getTip();
			spalatorieList->addItem(QString::fromStdString(text));
		}
	}

	void initConnect() {
		srv.addObserver(this);
		QObject::connect(randomBtn, &QPushButton::clicked, [&]() {
			int nr = random->text().toInt();
			srv.random(nr);
			spalatorieList->clear();
			loadList();
			random->clear();
		});

		QObject::connect(exportBtn, &QPushButton::clicked, [&]() {
			string fis = exp->text().toStdString();
			ofstream fout(fis);
			vector<Masina> spalatorie = srv.srvGetAll_s();
			for (const Masina& masina : spalatorie) {
				fout << "Numar inmatriculare: " << masina.getInmatriculare() << " \\ Producator: " << masina.getProducator() << " \\ Model: " << masina.getModel() << " \\ Tip: " << masina.getTip() << "<br>";
			}
			exp->clear();
		});

		QObject::connect(golire, &QPushButton::clicked, [&]() {
			srv.golire_s();
			spalatorieList->clear();
		});
	}

	void update() override {
		loadList();
	}

public:
	CosWindow(InchiriereMasini& srv) : srv{ srv }{
		initGUI();
		loadList();
		initConnect();
	}
	~CosWindow() {
		srv.removeObserver(this);
	}
};
