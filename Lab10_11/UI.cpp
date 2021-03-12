#include "UI.h"
void UI::adauga_inchiriere()
{
	string nrInmatriculare;
	string producator;
	string model;
	string tip;
	cout << "Numar inmatriculare: ";
	cin >> nrInmatriculare;
	cout << "Producator: ";
	cin >> producator;
	cout << "Model: ";
	cin >> model;
	cout << "Tip: ";
	cin >> tip;
	try {
		srv.srvAdauga(nrInmatriculare, producator, model, tip);
		cout << "Masina a fost adaugata in lista de inchirieri.\n";
	}
	catch (const RepoException& re) {
		cout << re.getMesaj() << "\n";
	}
	catch (const ValidException& ve) {
		cout << ve.getMesaj() << "\n";
	}
}
void UI::afisare_inchirieri()
{
	auto& inchirieri = srv.srvGetAll();
	for (const Masina& masina : inchirieri) {
		cout << "Numar inmatriculare: " << masina.getInmatriculare() << " \\ Producator: " << masina.getProducator() << " \\ Model: " << masina.getModel() << " \\ Tip: " << masina.getTip() << "\n";
	}
}
void UI::cauta_inchiriere()
{
	string nrInmatriculare;
	cout << "Introduceti numarul de inmatriculare: ";
	cin >> nrInmatriculare;
	const bool v = srv.cautaMasina(nrInmatriculare);
	if (v == true)
		cout << "Masina cu numarul " << nrInmatriculare << " se afla in lista de inchirieri.\n";
	else
		cout << "Masina cu numarul " << nrInmatriculare << " nu se afla in lista de inchirieri.\n";
}
void UI::sterge_inchiriere()
{
	string nrInmatriculare;
	cout << "Introduceti numarul de inmatriculare: ";
	cin >> nrInmatriculare;
	try {
		srv.stergeMasina(nrInmatriculare);
		cout << "Masina cu numarul " << nrInmatriculare << " a fost stearsa.\n";
	}
	catch (const RepoException& re) {
		cout << re.getMesaj();
	}
}
void UI::modifica_inchiriere()
{
	string nrInmatriculare;
	string nrInmatriculare1;
	string producator1;
	string model1;
	string tip1;
	cout << "Introduceti nr. masinii pe care doriti sa o modificati: ";
	cin >> nrInmatriculare;
	cout << "Numar nou: ";
	cin >> nrInmatriculare1;
	cout << "Producator nou: ";
	cin >> producator1;
	cout << "Model nou: ";
	cin >> model1;
	cout << "Tip nou: ";
	cin >> tip1;
	try {
		srv.modificaMasina(nrInmatriculare, nrInmatriculare1, producator1, model1, tip1);
		cout << "Datele inchirierii au fost modificate.";
	}
	catch (const RepoException& re) {
		cout << re.getMesaj();
	}
}
void UI::sortare()
{
	cout << "   1)Nr. Inmatriculare\n   2)Tip\n   3)Producator+Tip\nIntroduceti optiunea: ";
	int nr;
	cin >> nr;
	vector<Masina> inchirieri;
	switch (nr)
	{
	case 1:
		inchirieri = srv.sortareNrInmatriculare();
		break;
	case 2:
		inchirieri = srv.sortareTip();
		break;
	case 3:
		inchirieri = srv.sortareProducatorModel();
		break;
	}
	for (const Masina& masina : inchirieri) {
		cout << "Numar inmatriculare: " << masina.getInmatriculare() << " \\ Producator: " << masina.getProducator() << " \\ Model: " << masina.getModel() << " \\ Tip: " << masina.getTip() << "\n";
	}

}
void UI::filtrare()
{
	string tip;
	string producator;
	int nr;
	vector<Masina> inchirieri;
	cout << "   1)Producator\n   2)Tip\nIntroduceti optiunea: ";
	cin >> nr;
	if (nr == 1)
	{
		cout << "Introduceti producatorul: ";
		cin >> producator;
		inchirieri = srv.filtrareProducator(producator);
	}
	else
	{
		cout << "Introduceti tipul: ";
		cin >> tip;
		inchirieri = srv.filtrareTip(tip);
	}
	for (const Masina& masina : inchirieri) {
		cout << "Numar inmatriculare: " << masina.getInmatriculare() << " \\ Producator: " << masina.getProducator() << " \\ Model: " << masina.getModel() << " \\ Tip: " << masina.getTip() << "\n";
	}
}
void UI::undo() {
	try {
		srv.undo();
		cout << "S-a efectuat undo.\n";
	}
	catch (const UndoException& un) {
		cout << un.getMesaj() << "\n";
	}
}
void UI::golire_s()
{
	srv.golire_s();
	cout << "Lista de masini pentru spalatorie a fost golita.\n";
	cout << "Numarul de masini in lista pentru spalatorie: " << srv.srvGetAll_s().size() << endl;
}
void UI::adauga_s()
{
	string nrInmatriculare;
	cout << "Numar inmatriculare: ";
	cin >> nrInmatriculare;
	try {
		srv.srvAdauga_s(nrInmatriculare);
		cout << "Masina a fost adaugata in lista pentru spalatorie.\n";
	}
	catch (const RepoException& re) {
		cout << re.getMesaj() << "\n";
	}
	cout << "Numarul de masini in lista pentru spalatorie: " << srv.srvGetAll_s().size() << endl;
}
void UI::random_s() {
	int nr;
	cout << "Introduceti numarul: ";
	cin >> nr;
	srv.random(nr);
	cout << "Numarul de masini in lista pentru spalatorie: " << srv.srvGetAll_s().size() << endl;
}
void UI::export_s()
{
	string fisier;
	cout << "Introduceti fisierul: ";
	cin >> fisier;
	ofstream fout(fisier);
	vector<Masina> spalatorie;
	spalatorie = srv.srvGetAll_s();
	for (const Masina& masina : spalatorie) {
		fout << "Numar inmatriculare: " << masina.getInmatriculare() << " \\ Producator: " << masina.getProducator() << " \\ Model: " << masina.getModel() << " \\ Tip: " << masina.getTip() << "<br>";
	}
	cout << "Numarul de masini in lista pentru spalatorie: " << accumulate(spalatorie.begin(), spalatorie.end(), 0, [](int nr, Masina m) {return nr + m.getNr(); }) << endl;
	//cout << "Numarul de masini in lista pentru spalatorie: " << srv.srvGetAll_s().size() << endl;
}
void UI::manager()
{
	cout << "Spalatorie:\n  0)Meniu utilizator\n  1)Golire\n  2)Adaugare\n  3)Generare\n  4)Export\n";
	while (true)
	{
		cout << "Introduceti optiunea: ";
		int op = 0;
		cin >> op;
		if (op == 0)
			break;
		switch (op) {
		case 1:
			golire_s();
			break;
		case 2:
			adauga_s();
			break;
		case 3:
			random_s();
			break;
		case 4:
			export_s();
			break;
		}
	}
}
void UI::run() {
	srv.srvAdauga("BV12ABC", "Tesla", "3", "AWD");
	srv.srvAdauga("BV78AGH", "Audi", "A4", "AWD");
	srv.srvAdauga("CJ64WWR", "Audi", "A5", "AWD");
	srv.srvAdauga("MS56ATA", "Opel", "Corsa", "AWD");
	srv.srvAdauga("BV70FGC", "Tesla", "X", "AWD");

	cout << endl;
	cout << "-------------------------------\n";
	cout << "             MENIU             \n";
	cout << "      INCHIRIERE  MASINI       \n";
	cout << "-------------------------------\n";
	cout << "*Meniu Utilizator*\n0.Iesire\n1.Adaugare inchiriere\n2.Afisare inchirieri\n3.Cauta inchiriere\n4.Sterge inchiriere\n5.Modifica inchiriere\n6.Sortare\n7.Filtrare\n8.Undo\n\n-------------------------------\n9.Manager Spalatorie\n";
	cout << "-------------------------------\n";
	while (true)
	{
		cout << "Introduceti comanda: ";
		int cmd = 0;
		cin >> cmd;
		if (cmd == 0)
			break;
		switch (cmd)
		{
		case 1:
			adauga_inchiriere();
			break;
		case 2:
			afisare_inchirieri();
			break;
		case 3:
			cauta_inchiriere();
			break;
		case 4:
			sterge_inchiriere();
			break;
		case 5:
			modifica_inchiriere();
			break;
		case 6:
			sortare();
			break;
		case 7:
			filtrare();
			break;
		case 8:
			undo();
			break;
		case 9:
			manager();
			break;
		}
	}
}