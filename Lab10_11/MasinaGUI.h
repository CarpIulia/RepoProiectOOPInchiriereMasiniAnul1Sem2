#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtableview.h>
#include <QMessageBox>
#include <qcombobox.h>
#include <QGridLayout>
#include <qbrush.h>
#include "Service.h"
#include "DialogWindow.h"
#include "CosWindow.h"
#include "CosReadOnlyGUI.h"

class MasinaGUI : public QWidget{
	friend class CosWindow;
private:
	InchiriereMasini& srv;
	QListWidget* lista = new QListWidget;
	QPushButton* adauga = new QPushButton{ "Adauga" };
	QPushButton* sterge = new QPushButton{ "Sterge" };
	QPushButton* cauta = new QPushButton{ "Cauta" };
	QPushButton* modifica = new QPushButton{ "Modifica" };
	QPushButton* undo = new QPushButton{ "Undo" };
	QLineEdit* nrInmatriculare = new QLineEdit;
	QLineEdit* producator = new QLineEdit;
	QLineEdit* model = new QLineEdit;
	QLineEdit* tip = new QLineEdit;
	QLineEdit* formCauta = new QLineEdit;
	QComboBox* combSort = new QComboBox();
	QPushButton* filtrTip = new QPushButton{ "Filtrare tip" };
	QPushButton* filtrProd = new QPushButton{ "Filtrare producator" };
	QLineEdit* tipF = new QLineEdit;
	QLineEdit* prodF = new QLineEdit;
	QPushButton* cos = new QPushButton{ "Cos" };
	QPushButton* grafic = new QPushButton{ "Grafic" };
	QPushButton* addCos = new QPushButton{ "Adauga in cos" };
	QVBoxLayout* lyBtns = new QVBoxLayout{};
	QPushButton* golire_cos = new QPushButton{ "Goleste cos" };

	void initGUI() {
		QHBoxLayout* lyMain = new QHBoxLayout{};
		setLayout(lyMain);
		lista->setStyleSheet("background-color:#b5c7e3; color:#2B4570");

		QVBoxLayout* lyAdauga = new QVBoxLayout{};
		QLabel* labelAdauga = new QLabel{ "Introduceti datele masinii: " };
		lyAdauga->addWidget(labelAdauga);
		lyAdauga->setContentsMargins(0, 10, 0, 54);
		QFormLayout* lyForm = new QFormLayout{};
		QLabel* nrText = new QLabel{ "Nr. Inmatriculare" };
		QLabel* producatorText = new QLabel{ "Producator" };
		QLabel* modelText = new QLabel{ "Model" };
		QLabel* tipText = new QLabel{ "Tip" };
		lyForm->addRow(nrText, nrInmatriculare);
		lyForm->addRow(producatorText, producator);
		lyForm->addRow(modelText, model);
		lyForm->addRow(tipText, tip);
		lyForm->setContentsMargins(0, 0, 0, 0);
		lyAdauga->addLayout(lyForm);
		lyAdauga->addWidget(adauga);
		lyMain->addLayout(lyAdauga);
		adauga->setStyleSheet("font-weight: bold;background-color:#2B4570; color:#A8D0DB");
		nrInmatriculare->setStyleSheet("background-color:#b5c7e3; color:#2B4570");
		producator->setStyleSheet("background-color:#b5c7e3; color:#2B4570");
		model->setStyleSheet("background-color:#b5c7e3; color:#2B4570");
		tip->setStyleSheet("background-color:#b5c7e3; color:#2B4570");
		nrText->setStyleSheet("font-weight: bold;color:#2B4570");
		producatorText->setStyleSheet("font-weight: bold;color:#2B4570");
		modelText->setStyleSheet("font-weight: bold;color:#2B4570");
		tipText->setStyleSheet("font-weight: bold;color:#2B4570");
		labelAdauga->setStyleSheet("font-weight: bold;color:#2B4570");

		QVBoxLayout* lyList = new QVBoxLayout{};
		QFormLayout* lyFormFind = new QFormLayout{};
		QHBoxLayout* lyFind = new QHBoxLayout{};
		QHBoxLayout* lySort = new QHBoxLayout{};
		QLabel* cautaText = new QLabel{ "Cauta dupa nr. inmatriculare" };
		lyFormFind->addRow(cautaText, formCauta);
		combSort->addItem("-");
		combSort->addItem("Nr. Inmatriculare");
		combSort->addItem("Tip");
		combSort->addItem("Producator & Tip");
		combSort->setStyleSheet("background-color:#b5c7e3; color:#2B4570");
		lyFind->addLayout(lyFormFind);
		lyFind->addWidget(cauta);
		lyList->addLayout(lyFind);
		QLabel* sortare = new QLabel{ "Sorteaza" };
		lySort->addWidget(sortare);
		lySort->addWidget(combSort);
		lySort->setContentsMargins(0, 0, 200, 0);
		lyList->addLayout(lySort);
		lyList->addWidget(lista);
		lyMain->addLayout(lyList);
		cauta->setStyleSheet("font-weight: bold;background-color:#2B4570; color:#A8D0DB");
		formCauta->setStyleSheet("background-color:#b5c7e3; color:#2B4570");
		sortare->setStyleSheet("font-weight: bold;color:#2B4570");
		cautaText->setStyleSheet("font-weight: bold;color:#2B4570");

		QVBoxLayout* lyButtons = new QVBoxLayout{};
		lyButtons->addWidget(sterge);
		lyButtons->addWidget(modifica);
		lyButtons->addWidget(undo);
		lyButtons->addWidget(addCos);
		lyButtons->addWidget(golire_cos);
		lyButtons->addWidget(cos);
		lyButtons->addWidget(grafic);
		lyButtons->setContentsMargins(0, 50, 0, 50);
		lyMain->addLayout(lyButtons);
		sterge->setStyleSheet("font-weight: bold;background-color:#2B4570; color:#A8D0DB");
		modifica->setStyleSheet("font-weight: bold;background-color:#2B4570; color:#A8D0DB");
		undo->setStyleSheet("font-weight: bold;background-color:#2B4570; color:#A8D0DB");
		addCos->setStyleSheet("font-weight: bold;background-color:#2B4570; color:#A8D0DB");
		golire_cos->setStyleSheet("font-weight: bold;background-color:#2B4570; color:#A8D0DB");
		cos->setStyleSheet("font-weight: bold;background-color:#2B4570; color:#A8D0DB");
		grafic->setStyleSheet("font-weight: bold;background-color:#2B4570; color:#A8D0DB");

		QGridLayout* lyFiltr = new QGridLayout{};
		QLabel* t = new QLabel{ "Tip" };
		QLabel* p = new QLabel{ "Producator" };
		lyFiltr->addWidget(filtrTip, 1, 1);
		lyFiltr->addWidget(filtrProd, 1, 3);
		lyFiltr->addWidget(tipF, 0, 1);
		lyFiltr->addWidget(prodF, 0, 3);
		lyFiltr->addWidget(t, 0, 0);
		lyFiltr->addWidget(p, 0, 2);
		lyList->addLayout(lyFiltr);
		t->setStyleSheet("font-weight: bold;color:#2B4570");
		p->setStyleSheet("font-weight: bold;color:#2B4570");
		filtrTip->setStyleSheet("font-weight: bold;background-color:#2B4570; color:#A8D0DB");
		filtrProd->setStyleSheet("font-weight: bold;background-color:#2B4570; color:#A8D0DB");
		tipF->setStyleSheet("background-color:#b5c7e3; color:#2B4570");
		prodF->setStyleSheet("background-color:#b5c7e3; color:#2B4570");

		lyMain->addLayout(lyBtns);
	}

	void loadList(vector<Masina> masini) {
		for (const auto& m : masini) {
			string text = m.getInmatriculare() + " " + m.getProducator() + " " + m.getModel() + " " + m.getTip();
			auto item = new QListWidgetItem(QString::fromStdString(text));
			lista->addItem(item);
		}
	}

	void initConnect() {
		QObject::connect( adauga, &QPushButton::clicked, [&]() {
			string nr = nrInmatriculare->text().toStdString();
			string prod = producator->text().toStdString();
			string mod = model->text().toStdString();
			string t = tip->text().toStdString();
			try {
				srv.srvAdauga(nr, prod, mod, t);
				lista->clear();
				loadList(srv.srvGetAll());
				//adaugaButoane(srv.srvGetAll());
			}
			catch (const RepoException& re) {
				string reMsg = re.getMesaj();
				QMessageBox::information(nullptr, "Eroare adaugare.", QString::fromStdString(reMsg));
			}
			catch (const ValidException& ve) {
				string veMsg = ve.getMesaj();
				QMessageBox::information(nullptr, "Eroare adaugare.", QString::fromStdString(veMsg));
			}
			nrInmatriculare->clear();
			producator->clear();
			model->clear();
			tip->clear();
		} );

		QObject::connect(sterge, &QPushButton::clicked, [&]() {
			QListWidgetItem* item = lista->currentItem();
			string text = item->text().toStdString();
			string nr = text.substr(0, 7);
			try {
				srv.stergeMasina(nr);
 				lista->clear();
				loadList(srv.srvGetAll());
				//adaugaButoane(srv.srvGetAll());
			}
			catch (const RepoException& re) {
				string reMsg = re.getMesaj();
				QMessageBox::information(nullptr, "Eroare stergere.", QString::fromStdString(reMsg));
			}
		});

		QObject::connect(cauta, &QPushButton::clicked, [&]() {
			string nr = formCauta->text().toStdString();
			const bool v = srv.cautaMasina(nr);
			if (v == 1) {
				int poz = -1;
				const auto& masini = srv.srvGetAll();
				for (const auto& masina : masini)
				{
					poz++;
					if (masina.getInmatriculare() == nr)
						break;
				}
				lista->setCurrentRow(poz);
			}
			else {
				string text = "Masina cu numarul " + nr + " nu se afla in lista.";
				QMessageBox::information(nullptr, "Rezultat cautare.", QString::fromStdString(text));
			}
			//nrInmatriculare->clear();
		});
		
		QObject::connect(undo, &QPushButton::clicked, [&]() {
			try {
				srv.undo();
				lista->clear();
				loadList(srv.srvGetAll());
				//adaugaButoane(srv.srvGetAll());
			}
			catch (const UndoException& un) {
				string unMsg = un.getMesaj();
				QMessageBox::information(nullptr, "Eroare undo.", QString::fromStdString(unMsg));
			}
		});

		QObject::connect(combSort, &QComboBox::currentTextChanged, [&]() {
			int ind = combSort->currentIndex();
			vector<Masina> masini;
			switch (ind)
			{
			case 0:
				lista->clear();
				loadList(srv.srvGetAll());
				return;
			case 1:
				masini = srv.sortareNrInmatriculare();
				//adaugaButoane(masini);
				break;
			case 2:
				masini = srv.sortareTip();
				//adaugaButoane(masini);
				break;
			case 3:
				masini = srv.sortareProducatorModel();
				//adaugaButoane(masini);
				break;
			}
			lista->clear();
			loadList(masini);
			
		});

		QObject::connect(filtrTip, &QPushButton::clicked, [&]() {
			string tip = tipF->text().toStdString();
			lista->clear();
			loadList(srv.filtrareTip(tip));
			tipF->clear();
		});

		QObject::connect(filtrProd, &QPushButton::clicked, [&]() {
			string prod = prodF->text().toStdString();
			lista->clear();
			loadList(srv.filtrareProducator(prod));
			prodF->clear();
		});

		QObject::connect(modifica, &QPushButton::clicked, [&]() {
			QListWidgetItem* item = lista->currentItem();
			string text = item->text().toStdString();
			string nr = text.substr(0, 7);
			DialogWindow modifWind{ nr, srv };
			modifWind.exec();
			modifWind.show();
			modifWind.setModal(true);
			lista->clear();
			loadList(srv.srvGetAll());
		});

		QObject::connect(cos, &QPushButton::clicked, [&]() {
			auto spalatorie = new CosWindow{ srv };
			spalatorie->show();
		});

		QObject::connect(grafic, &QPushButton::clicked, [&]() {
			auto graficSpalatorie = new CosReadOnlyGUI{ srv };
			graficSpalatorie->setFixedSize(QSize(700, 110));
			graficSpalatorie->show();
		});

		QObject::connect(addCos, &QPushButton::clicked, [&]() {
			QListWidgetItem* item = lista->currentItem();
			string text = item->text().toStdString();
			string nr = text.substr(0, 7);
			try {
				srv.srvAdauga_s(nr);
			}
			catch (const RepoException& re) {
				string reMsg = re.getMesaj();
				QMessageBox::information(nullptr, "Eroare adaugare cos.", QString::fromStdString(reMsg));
			}
			
		});

		QObject::connect(lista, &QListWidget::itemSelectionChanged, [&]() {
			auto item = lista->selectedItems();
			if (item.isEmpty()) {
				nrInmatriculare->clear();
				producator->clear();
				model->clear();
				tip->clear();
			}
			else {
				auto text = item.at(0);
				auto textNr = text->text().section(" ", 0, 0);
				auto textProd = text->text().section(" ", 1, 1);
				auto textMod = text->text().section(" ", 2, 2);
				auto textTip = text->text().section(" ", 3, 3);
				nrInmatriculare->setText(textNr);
				producator->setText(textProd);
				model->setText(textMod);
				tip->setText(textTip);
			}
		});

		QObject::connect(golire_cos, &QPushButton::clicked, [&]() {
			srv.golire_s();
		});
	}
	/*void adaugaButoane(vector<Masina> masini) {
		while (auto buton = lyBtns->takeAt(0)) {
			delete buton->widget();
			delete buton;
		}
		for (const auto& masina : masini) {
			auto btnStergere = new QPushButton{ QString::fromStdString(masina.getInmatriculare()) };
			lyBtns->addWidget(btnStergere);
			QObject::connect(btnStergere, &QPushButton::clicked, [&masina, this, btnStergere]() {
				string nr = btnStergere->text().toStdString();
				try {
					srv.stergeMasina(nr);
					lista->clear();
					loadList(srv.srvGetAll());
					lyBtns->removeWidget(btnStergere);
					adaugaButoane(srv.srvGetAll());
				}
				catch (const RepoException& re) {
					string reMsg = re.getMesaj();
					QMessageBox::information(nullptr, "Eroare stergere.", QString::fromStdString(reMsg));
				}
				delete btnStergere;
			});
		}
	}*/
public:
	MasinaGUI(InchiriereMasini& srv) : srv{ srv } {
		//srv.srvAdauga("BV12ABC", "Tesla", "3", "AWD");
		//srv.srvAdauga("BV78AGH", "Audi", "A4", "AWD");
		//srv.srvAdauga("CJ64WWR", "Audi", "A5", "AWD");
		//srv.srvAdauga("MS56ATA", "Opel", "Corsa", "AWD");
		//srv.srvAdauga("BV70FGC", "Tesla", "X", "AWD");
		initGUI();
		loadList(srv.srvGetAll());
		initConnect();
		//adaugaButoane(srv.srvGetAll());
	}
};
