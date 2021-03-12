#include "Repository.h"
//Inchiriere
string RepoException::getMesaj() const {
	return mesaj;
}

void RepoMasini::adauga(const Masina& m) {
	for (const Masina& masina : masini) {
		if (masina.getInmatriculare() == m.getInmatriculare()) {
			throw RepoException("Masina exista deja!");
		}
	}
	masini.push_back(m);
}

const vector<Masina>& RepoMasini::getAll() noexcept {

	return masini;
}

bool RepoMasini::cauta(const Masina& m) {
	auto masina = find_if(masini.begin(), masini.end(), [m](const Masina masina) {return m.getInmatriculare() == masina.getInmatriculare(); });
	if (masina != masini.end()) {
		return true;
	}
	else {
		return false;
	}
}

void RepoMasini::sterge(const Masina& m) {
	if (cauta(m) == false)
		throw RepoException("Masina nu exista!\n");
	unsigned i = 0;
	for (const Masina& masina : masini) {
		if (masina.getInmatriculare() == m.getInmatriculare()) {
			for (unsigned j = i; j < masini.size() - 1; j++) {
				masini.at(j) = masini.at(j + 1);
			}
		}
		i++;
	}
	masini.pop_back();
}

void RepoMasini::modifica(const Masina& m1, const Masina& m2) {
	if (cauta(m1) == false)
		throw RepoException("Masina nu exista!\n");
	for (Masina& masina : masini) {
		if (masina.getInmatriculare() == m1.getInmatriculare()) {
			masina.setInmatriculare(m2.getInmatriculare());
			masina.setProducator(m2.getProducator());
			masina.setModel(m2.getModel());
			masina.setTip(m2.getTip());
		}
	}
}

//Spalatorie
void RepoMasini::adauga_s(const Masina& m) {
	if (cauta(m) == false)
		throw RepoException("Masina nu exista in lista de inchirieri!\n");
	for (const Masina& masina : masini) {
		if (masina.getInmatriculare() == m.getInmatriculare()) {
			modifica(m, masina);
		}
	}
	spalatorie.push_back(m);
}

void RepoMasini::golire_s() noexcept {
	while (spalatorie.size() != 0)
		spalatorie.pop_back();
}

const vector<Masina>& RepoMasini::getAll_s() noexcept {
	return spalatorie;
}

void RepoMasini::sterge_s() {
	for (int i = 0; i < spalatorie.size(); i++) {
		if (!cauta(spalatorie.at(i)))
		{
			for (int j = i; j < spalatorie.size() - 1; j++) {
				spalatorie.at(j) = spalatorie.at(j + 1);
			}
			spalatorie.pop_back();
		}
	}
}

void RepoFile::readFromFile() {
	while (masini.size() != 0)
		masini.pop_back();
	ifstream fin(fileName);
	string nr;
	string prod;
	string mod;
	string tip;
	while (!fin.eof()) {
		fin >> nr >> prod >> mod >> tip;
		Masina m{ nr, prod, mod, tip };
		masini.push_back(m);
	}
	fin.close();
}

void RepoFile::writeToFile() {
	ofstream fout(fileName);
	for (Masina& m : masini)
		fout << m.getInmatriculare() << " " << m.getProducator() << " " << m.getModel() << " " << m.getTip() << endl;
	fout.close();
}
