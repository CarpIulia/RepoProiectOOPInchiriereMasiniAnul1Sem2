#include "Domain.h"

string Masina::getInmatriculare() const {
	return nrInmatriculare;
}

string Masina::getProducator() const {
	return producator;
}

string Masina::getModel() const {
	return model;
}

string Masina::getTip() const {
	return tip;
}

void Masina::setInmatriculare(string nr) {
	this->nrInmatriculare = nr;
}

void Masina::setProducator(string pr) {
	this->producator = pr;
}

void Masina::setModel(string mo) {
	this->model = mo;
}

void Masina::setTip(string t) {
	this->tip = t;
}