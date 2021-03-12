#pragma once
#include "Domain.h"
#include <string>
using std::string;
class ValidException
{
	string mesaj;
public:
	ValidException(string msg) :mesaj{ msg } {}
	string getMesaj() const;
};
class Validator
{
public:
	void validareMasina(Masina m) const;
};
