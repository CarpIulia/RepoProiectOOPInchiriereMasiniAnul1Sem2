#pragma once
#include<iostream>
using namespace std;
#include <string>
using std::string;
class Masina
{
private:
	string nrInmatriculare;
	string producator;
	string model;
	string tip;
	int nr = 1;
public:
	Masina() noexcept = default;
	string getInmatriculare() const;
	string getProducator() const;
	string getModel() const;
	string getTip() const;
	int getNr() const {
		return nr;
	}
	void setInmatriculare(string nr);
	void setProducator(string pr);
	void setModel(string mo);
	void setTip(string t);
	Masina(string nrInmatriculare, string producator, string model, string tip) :nrInmatriculare{ nrInmatriculare }, producator{ producator }, model{ model }, tip{ tip } {}
	Masina(const Masina& m) :nrInmatriculare{ m.nrInmatriculare }, producator{ m.producator }, model{ m.model }, tip{ m.tip } { }
};