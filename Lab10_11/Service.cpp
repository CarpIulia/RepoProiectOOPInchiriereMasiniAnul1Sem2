#include "Service.h"
//Inchiriere
void InchiriereMasini::srvAdauga(string nrInmatriculare, string producator, string model, string tip) {
	Masina m{ nrInmatriculare, producator, model, tip };
	Validator valid;
	valid.validareMasina(m);
	repo.adauga(m);
	undoActions.push_back(make_unique<UndoAdauga>(repo, m));
}

const vector<Masina>& InchiriereMasini::srvGetAll() noexcept {
	return repo.getAll();
}

bool InchiriereMasini::cautaMasina(string nrInmatriculare) {
	Masina m{ nrInmatriculare, "", "", "" };
	return repo.cauta(m);
}

void InchiriereMasini::stergeMasina(string nrInmatriculare) {
	Masina m;
	const auto masini = repo.getAll();
	for (const auto& masina : masini)
		if (masina.getInmatriculare() == nrInmatriculare)
			m = masina;
	repo.sterge(m);
	undoActions.push_back(make_unique<UndoSterge>(repo, m));
	notify();
}

void InchiriereMasini::modificaMasina(string nrInmatriculare, string nrInmatriculare1, string producator1, string model1, string tip1) {
	Masina m1{ nrInmatriculare, "", "", "" };
	Masina m2{ nrInmatriculare1, producator1, model1, tip1 };
	const auto masini = repo.getAll();
	for (const auto& masina : masini)
		if (masina.getInmatriculare() == nrInmatriculare)
			m1 = masina;
	repo.modifica(m1, m2);
	undoActions.push_back(make_unique<UndoModifica>(repo, m1, m2));
}

const vector<Masina> InchiriereMasini::sortare(bool (*cmpF)(const Masina, const Masina)) {
	auto masini = repo.getAll();
	sort(masini.begin(), masini.end(), [cmpF](const Masina& m1, const Masina& m2) { return cmpF(m1, m2); });
	return masini;
}

bool cmpNrInmatriculare(Masina m1, Masina m2) {
	return m1.getInmatriculare() < m2.getInmatriculare();
}

bool cmpTip(Masina m1, Masina m2) {
	return m1.getTip() < m2.getTip();
}

bool cmpProducatorModel(Masina m1, Masina m2) {
	if (m1.getProducator() == m2.getProducator())
		return m1.getModel() < m2.getModel();
	else
		return m1.getProducator() < m2.getProducator();
}

const vector<Masina> InchiriereMasini::sortareNrInmatriculare() {
	return sortare(cmpNrInmatriculare);
}

const vector<Masina> InchiriereMasini::sortareTip() {
	return sortare(cmpTip);
}

const vector<Masina> InchiriereMasini::sortareProducatorModel() {
	return sortare(cmpProducatorModel);
}

const vector<Masina> InchiriereMasini::filtrare(bool (*filtrF)(const Masina, string str), string str) {
	vector<Masina> masini_dest;
	vector<Masina> masini = repo.getAll();
	copy_if(masini.begin(), masini.end(), back_inserter(masini_dest), [filtrF, str](const Masina masina) {return filtrF(masina, str); });
	return masini_dest;
}

bool filtrProd(Masina m, string producator) {
	return m.getProducator() == producator;
}

bool filtrTip(Masina m, string tip) {
	return m.getTip() == tip;
}

const vector<Masina> InchiriereMasini::filtrareProducator(string producator) {
	return filtrare(filtrProd, producator);
}

const vector<Masina> InchiriereMasini::filtrareTip(string tip) {
	return filtrare(filtrTip, tip);
}

void InchiriereMasini::undo() {
	if (undoActions.empty())
		throw UndoException("Nu se mai poate face undo!\n");
	undoActions.back()->doUndo();
	undoActions.pop_back();
	notify();
}

//Spalatorie
void InchiriereMasini::srvAdauga_s(string nrInmatriculare) {
	Masina m{ nrInmatriculare, "", "", "" };
	const auto masini = repo.getAll();
	for (const auto& masina : masini)
		if (masina.getInmatriculare() == nrInmatriculare)
			m = masina;
	repo.adauga_s(m);
	notify();
}

void InchiriereMasini::golire_s() noexcept {
	undoActions.push_back(make_unique<UndoGolireS>(repo, repo.getAll_s()));
	repo.golire_s();
	notify();
}

void InchiriereMasini::random(int nr) {
	vector<Masina> masini = repo.getAll();
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<> const numere(0, masini.size() - 1);
	while (nr != 0)
	{
		const int rndNr = numere(mt);
		repo.adauga_s(masini.at(rndNr));
		nr--;
	}
	notify();
}

const vector<Masina> InchiriereMasini::srvGetAll_s() {
	vector<Masina> masini = repo.getAll_s();
	return masini;
}

void InchiriereMasini::sterge_s() {
	repo.sterge_s();
}