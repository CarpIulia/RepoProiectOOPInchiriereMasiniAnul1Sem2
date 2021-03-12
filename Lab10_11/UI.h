#pragma once
#include "Service.h"
#include <iostream>
#include <fstream>
#include <numeric>
using namespace std;
class UI
{
	InchiriereMasini& srv;
public:
	//Inchiriere
	UI(InchiriereMasini& srv) noexcept :srv{ srv } {}
	void run();
	void adauga_inchiriere();
	void afisare_inchirieri();
	void cauta_inchiriere();
	void sterge_inchiriere();
	void modifica_inchiriere();
	void sortare();
	void filtrare();
	void undo();

	//Spalatorie
	void manager();
	void golire_s();
	void adauga_s();
	void export_s();
	void random_s();
};