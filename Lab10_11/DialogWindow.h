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
class DialogWindow : public QDialog {
	friend class MasinaGUI;
private:
	string nrInmatriculareM;
	InchiriereMasini& srv;
	QLineEdit* nrInmatriculare = new QLineEdit;
	QLineEdit* producator = new QLineEdit;
	QLineEdit* model = new QLineEdit;
	QLineEdit* tip = new QLineEdit;
	QPushButton* salveaza = new QPushButton{ "Salveaza" };
	void initGUI() {
		QVBoxLayout* lyMain = new QVBoxLayout{};
		setLayout(lyMain);
		QLabel* modif = new QLabel{ "Introduceti modificarile: " };
		QFormLayout* lyModif = new QFormLayout{};
		QLabel* nrText = new QLabel{ "Nr. Inmatriculare" };
		QLabel* producatorText = new QLabel{ "Producator" };
		QLabel* modelText = new QLabel{ "Model" };
		QLabel* tipText = new QLabel{ "Tip" };
		lyModif->addRow(nrText, nrInmatriculare);
		lyModif->addRow(producatorText, producator);
		lyModif->addRow(modelText, model);
		lyModif->addRow(tipText, tip);
		lyMain->addWidget(modif);
		lyMain->addLayout(lyModif);
		lyMain->addWidget(salveaza);

		salveaza->setStyleSheet("font-weight: bold;background-color:#2B4570; color:#A8D0DB");
		nrInmatriculare->setStyleSheet("background-color:#b5c7e3; color:#2B4570");
		producator->setStyleSheet("background-color:#b5c7e3; color:#2B4570");
		model->setStyleSheet("background-color:#b5c7e3; color:#2B4570");
		tip->setStyleSheet("background-color:#b5c7e3; color:#2B4570");
		nrText->setStyleSheet("font-weight: bold;color:#2B4570");
		producatorText->setStyleSheet("font-weight: bold;color:#2B4570");
		modelText->setStyleSheet("font-weight: bold;color:#2B4570");
		tipText->setStyleSheet("font-weight: bold;color:#2B4570");
		modif->setStyleSheet("font-weight: bold;color:#2B4570");
	}

	void initConnect() {
		QObject::connect(salveaza, &QPushButton::clicked, [&]() {
			string nr = nrInmatriculare->text().toStdString();
			string prod = producator->text().toStdString();
			string mod = model->text().toStdString();
			string t = tip->text().toStdString();
			try {
				srv.modificaMasina(nrInmatriculareM, nr, prod, mod, t);
			}
			catch (const RepoException& re) {
				string reMsg = re.getMesaj();
				QMessageBox::information(nullptr, "Eroare modificare.", QString::fromStdString(reMsg));
			}
			nrInmatriculare->clear();
			producator->clear();
			model->clear();
			tip->clear();
		});

	}
public:
	DialogWindow(string nrInmatriculareM, InchiriereMasini& srv) : nrInmatriculareM{ nrInmatriculareM }, srv{ srv }{
		initGUI();
		initConnect();
	}

};
