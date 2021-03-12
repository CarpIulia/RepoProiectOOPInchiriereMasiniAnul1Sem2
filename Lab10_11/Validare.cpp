#include "Validare.h"
string ValidException::getMesaj() const {
	return mesaj;
}

void Validator::validareMasina(Masina m) const {
	if (m.getInmatriculare().length() != 7)
		throw ValidException("Trebuie sa introduceti un nr. de inmatriculare valid! <BV12ABC>");
	if (m.getProducator().length() == 0)
		throw ValidException("Trebuie sa introduceti un nume de producator nevid!");
	if (m.getModel().length() == 0)
		throw ValidException("Trebuie sa introduceti un model nevid!");
	if (m.getTip().length() == 0)
		throw ValidException("Trebuie sa introduceti un tip nevid!");
}