#pragma once
#include "Domain.h"
#include "Repository.h"
#include "Validare.h"
#include "Undo.h"
#include <string>
#include <algorithm>
#include <random>
#include "Observer.h"
using std::string;
class InchiriereMasini : public Observable{
private:
	RepoMasini& repo;
	vector<unique_ptr<ActiuneUndo>> undoActions;
public:
	//Inchiriere
	InchiriereMasini(RepoMasini& repo) noexcept :repo{ repo } {}
	InchiriereMasini(const InchiriereMasini& other) = delete;
	InchiriereMasini() = default;
	void srvAdauga(string nrInmatriculare, string producator, string model, string tip);
	const vector<Masina>& srvGetAll() noexcept;
	bool cautaMasina(string nrInmatriculare);
	void stergeMasina(string nrInmatriculare);
	void modificaMasina(string nrInmatriculare, string nrInmatriculare1, string producator1, string model1, string tip1);
	const vector<Masina> sortare(bool (*cmpF)(const Masina, const Masina));
	const vector<Masina> sortareNrInmatriculare();
	const vector<Masina> sortareTip();
	const vector<Masina> sortareProducatorModel();
	const vector<Masina> filtrare(bool (*filtrF)(const Masina, string), string str);
	const vector<Masina> filtrareProducator(string producator);
	const vector<Masina> filtrareTip(string tip);
	void undo();

	//Spalatorie
	void srvAdauga_s(string nrInmatriculare);
	void golire_s() noexcept;
	void random(int nr);
	const vector<Masina> srvGetAll_s();
	void sterge_s();
};
