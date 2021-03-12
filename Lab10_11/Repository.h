#pragma once
#include "Domain.h"
#include <algorithm>
#include <vector>
#include <fstream>
using std::vector;
class RepoAbstract {
protected:
	vector<Masina> masini;
	vector<Masina> spalatorie;
public:
	virtual void adauga(const Masina& m) = 0;
	virtual const vector<Masina>& getAll() noexcept = 0;
	virtual bool cauta(const Masina& m) = 0;
	virtual void sterge(const Masina& m) = 0;
	virtual void modifica(const Masina& m1, const Masina& m2) = 0;

	//Spalatorie
	virtual void adauga_s(const Masina& m) = 0;
	virtual void golire_s() noexcept = 0;
	virtual const vector<Masina>& getAll_s() noexcept = 0;
};
class RepoException {
	string mesaj;
public:
	RepoException(string msg) :mesaj{ msg } {}
	string getMesaj() const;
};
class RepoMasini : public RepoAbstract {
public:
	//Inchiriere
	RepoMasini(RepoMasini& other) = delete;
	RepoMasini() = default;
	virtual void adauga(const Masina& m);
	const vector<Masina>& getAll() noexcept;
	bool cauta(const Masina& m);
	virtual void sterge(const Masina& m);
	virtual void modifica(const Masina& m1, const Masina& m2);

	//Spalatorie
	void adauga_s(const Masina& m);
	void golire_s() noexcept;
	const vector<Masina>& getAll_s() noexcept;
	void sterge_s();
};

class RepoFile : public RepoMasini {
private:
	string fileName;
	void readFromFile();
	void writeToFile();
public:
	RepoFile(string fileName) :RepoMasini(), fileName{ fileName } {
		readFromFile();
	}
	void adauga(const Masina& m) override {
		RepoMasini::adauga(m);
		writeToFile();
	}
	void sterge(const Masina& m) override {
		RepoMasini::sterge(m);
		writeToFile();
	}
	void modifica(const Masina& m1, const Masina& m2) override {
		RepoMasini::modifica(m1, m2);
		writeToFile();
	}
};