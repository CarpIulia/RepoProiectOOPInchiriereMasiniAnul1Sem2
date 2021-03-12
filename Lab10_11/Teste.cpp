#include "Teste.h"
void test_creeaza_masina()
{
	Masina m{ "BV12ABC","Tesla","3","AWD" };
	assert(m.getInmatriculare() == "BV12ABC");
	assert(m.getProducator() == "Tesla");
	assert(m.getModel() == "3");
	assert(m.getTip() == "AWD");
	m.setInmatriculare("CJ13ATA");
	m.setProducator("Audi");
	m.setModel("A4");
	m.setTip("AWD");
	assert(m.getInmatriculare() == "CJ13ATA");
	assert(m.getProducator() == "Audi");
	assert(m.getModel() == "A4");
	assert(m.getTip() == "AWD");
}
void test_repo_adauga_masina()
{
	RepoMasini repo;
	Masina m{ "BV12ABC","Tesla","3","AWD" };
	repo.adauga(m);
	const auto& masini = repo.getAll();
	assert(masini.size() == 1);

	try {
		repo.adauga(m);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMesaj() == "Masina exista deja!");
	}
}
void test_validare_masina()
{
	Validator valid;
	Masina m1{ "","Tesla","3","AWD" };
	try {
		valid.validareMasina(m1);
		assert(false);
	}
	catch (const ValidException& ve) {
		assert(ve.getMesaj() == "Trebuie sa introduceti un nr. de inmatriculare valid! <BV12ABC>");
	}

	Masina m2{ "BV12ABC","","3","AWD" };
	try {
		valid.validareMasina(m2);
		assert(false);
	}
	catch (const ValidException& ve) {
		assert(ve.getMesaj() == "Trebuie sa introduceti un nume de producator nevid!");
	}

	Masina m3{ "BV12ABC","Tesla","","AWD" };
	try {
		valid.validareMasina(m3);
		assert(false);
	}
	catch (const ValidException& ve) {
		assert(ve.getMesaj() == "Trebuie sa introduceti un model nevid!");
	}

	Masina m4{ "BV12ABC","Tesla","3","" };
	try {
		valid.validareMasina(m4);
		assert(false);
	}
	catch (const ValidException& ve) {
		assert(ve.getMesaj() == "Trebuie sa introduceti un tip nevid!");
	}
}
void test_srv_adauga_masina()
{
	RepoMasini repo;
	InchiriereMasini srv{ repo };
	srv.srvAdauga("BV12ABC", "Tesla", "3", "AWD");
	const auto& masini = srv.srvGetAll();
	assert(masini.size() == 1);
	try {
		srv.srvAdauga("BV12ABC", "Tesla", "3", "AWD");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMesaj() == "Masina exista deja!");
	}
	try {
		srv.srvAdauga("", "Tesla", "3", "AWD");
		assert(false);
	}
	catch (const ValidException& ve) {
		assert(ve.getMesaj() == "Trebuie sa introduceti un nr. de inmatriculare valid! <BV12ABC>");
	}
	const auto& masini2 = srv.srvGetAll();
	assert(masini2.size() == 1);
}
void test_repo_cauta_masina()
{
	RepoMasini repo;
	Masina m1{ "BV12ABC","Tesla","3","AWD" };
	Masina m2{ "CJ13ATA","Tesla","X","AWD" };
	repo.adauga(m1);
	assert(repo.cauta(m1) == true);
	assert(repo.cauta(m2) == false);
}
void test_srv_cauta_masina()
{
	RepoMasini repo;
	InchiriereMasini srv{ repo };
	srv.srvAdauga("BV12ABC", "Tesla", "3", "AWD");
	assert(srv.cautaMasina("BV12ABC") == true);
	assert(srv.cautaMasina("CJ13ATA") == false);
}
void test_repo_strege_masina()
{
	RepoMasini repo;
	Masina m1{ "BV12ABC","Tesla","3","AWD" };
	Masina m2{ "CJ13ATA","Tesla","X","AWD" };
	repo.adauga(m1);
	repo.adauga(m2);
	const auto& masini = repo.getAll();
	assert(masini.size() == 2);
	repo.sterge(m1);
	const auto& masini2 = repo.getAll();
	assert(masini2.size() == 1);
	try {
		repo.sterge(m1);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMesaj() == "Masina nu exista!\n");
	}
}
void test_srv_sterge_masina()
{
	RepoMasini repo;
	InchiriereMasini srv{ repo };
	srv.srvAdauga("BV12ABC", "Tesla", "3", "AWD");
	srv.srvAdauga("CJ13ATA", "Tesla", "X", "AWD");
	const auto& masini = srv.srvGetAll();
	assert(masini.size() == 2);
	srv.stergeMasina("BV12ABC");
	const auto& masini2 = srv.srvGetAll();
	assert(masini2.size() == 1);
	try {
		srv.stergeMasina("BV12ABC");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMesaj() == "Masina nu exista!\n");
	}
}
void test_repo_modifica()
{
	RepoMasini repo;
	Masina m1{ "BV12ABC","Tesla","3","AWD" };
	Masina m2{ "CJ13ATA","Tesla","X","AWD" };
	repo.adauga(m1);
	assert(repo.cauta(m1) == true);
	repo.modifica(m1, m2);
	assert(repo.cauta(m1) == false);
	try {
		repo.modifica(m1, m2);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMesaj() == "Masina nu exista!\n");
	}
	assert(repo.cauta(m2) == true);
}
void test_srv_modifica()
{
	RepoMasini repo;
	InchiriereMasini srv{ repo };
	srv.srvAdauga("BV12ABC", "Tesla", "3", "AWD");
	assert(srv.cautaMasina("BV12ABC") == true);
	srv.modificaMasina("BV12ABC", "CJ13ATA", "Tesla", "X", "AWD");
	assert(srv.cautaMasina("BV12ABC") == false);
	try {
		srv.modificaMasina("BV12ABC", "CJ13ATA", "Tesla", "X", "AWD");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMesaj() == "Masina nu exista!\n");
	}
}
void test_srv_sortare()
{
	RepoMasini repo;
	InchiriereMasini srv{ repo };
	srv.srvAdauga("BV12ABC", "Tesla", "3", "ZWD");
	srv.srvAdauga("CJ67ATA", "Audi", "A4", "GWD");
	srv.srvAdauga("MS80KMN", "Opel", "Corsa", "AWD");
	auto masini = srv.sortareNrInmatriculare();
	assert(masini.at(0).getInmatriculare() == "BV12ABC");
	masini = srv.sortareTip();
	assert(masini.at(0).getTip() == "AWD");
	masini = srv.sortareProducatorModel();
	assert(masini.at(0).getProducator() == "Audi");
}
void test_srv_filtrare()
{
	RepoMasini repo;
	InchiriereMasini srv{ repo };
	srv.srvAdauga("BV12ABC", "Tesla", "3", "ZWD");
	srv.srvAdauga("CJ67ATA", "Audi", "A4", "GWD");
	srv.srvAdauga("MS80KMN", "Opel", "Corsa", "AWD");
	auto masini = srv.filtrareProducator("Tesla");
	assert(masini.size() == 1);
	assert(masini.at(0).getProducator() == "Tesla");
	masini = srv.filtrareTip("AWD");
	assert(masini.size() == 1);
	assert(masini.at(0).getTip() == "AWD");
}
void test_repo_adauga_golire_s()
{

	RepoMasini repo;
	vector<Masina> spalatorie;
	Masina m = { "BV12ABC", "Tesla", "3", "AWD" };
	Masina m2 = { "CJ12ATA", "", "", "" };
	repo.adauga(m);
	repo.adauga_s(m);
	spalatorie = repo.getAll_s();
	assert(spalatorie[0].getProducator() == "Tesla");

	try {
		repo.adauga_s(m2);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMesaj() == "Masina nu exista in lista de inchirieri!\n");
	}
	repo.golire_s();
	spalatorie = repo.getAll_s();
	assert(spalatorie.size() == 0);
}
void test_srv_adauga_golire_s()
{
	RepoMasini repo;
	InchiriereMasini srv{ repo };
	vector<Masina> spalatorie;
	srv.srvAdauga("BV12ABC", "Tesla", "3", "AWD");
	srv.srvAdauga_s("BV12ABC");
	try {
		srv.srvAdauga_s("CJ12ABC");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMesaj() == "Masina nu exista in lista de inchirieri!\n");
	}
	srv.golire_s();
	spalatorie = repo.getAll_s();
	assert(spalatorie.size() == 0);
}
void test_random()
{
	RepoMasini repo;
	InchiriereMasini srv{ repo };
	srv.srvAdauga("BV12ABC", "Tesla", "3", "ZWD");
	srv.srvAdauga("CJ67ATA", "Audi", "A4", "GWD");
	srv.srvAdauga("MS80KMN", "Opel", "Corsa", "AWD");
	srv.random(10);
	vector<Masina> spalatorie = repo.getAll_s();
	assert(spalatorie.size() == 10);
}
void test_undo()
{
	RepoMasini repo;
	InchiriereMasini srv{ repo };
	vector<Masina> masini;
	srv.srvAdauga("BV12ABC", "Tesla", "3", "ZWD");
	srv.srvAdauga("CJ67ATA", "Audi", "A4", "GWD");
	srv.srvAdauga("MS80KMN", "Opel", "Corsa", "AWD");
	srv.undo();
	masini = srv.srvGetAll();
	assert(masini.size() == 2);
	srv.stergeMasina("CJ67ATA");
	srv.undo();
	masini = srv.srvGetAll();
	assert(masini.size() == 2);
	srv.modificaMasina("CJ67ATA", "CJ67ABC", "Tesla", "X", "AWD");
	srv.undo();
	masini = srv.srvGetAll();
	assert(srv.cautaMasina("CJ67ABC") == false);
	try {
		srv.undo();
		assert(false);
	}
	catch (const UndoException& un) {
		assert(un.getMesaj() == "Nu se mai poate face undo!\n");
	}
}
void run_all_tests()
{
	test_creeaza_masina();
	test_repo_adauga_masina();
	test_validare_masina();
	test_srv_adauga_masina();
	test_repo_cauta_masina();
	test_srv_cauta_masina();
	test_repo_strege_masina();
	test_srv_sterge_masina();
	test_repo_modifica();
	test_srv_modifica();
	test_srv_sortare();
	test_srv_filtrare();

	test_repo_adauga_golire_s();
	test_srv_adauga_golire_s();
	test_random();
}