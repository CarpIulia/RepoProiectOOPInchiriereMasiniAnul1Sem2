#pragma once
#include "Domain.h"
#include "Repository.h"
class UndoException
{
	string mesaj;
public:
	UndoException(string msg) :mesaj{ msg } {}
	string getMesaj() const {
		return mesaj;
	}
};
class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};
class UndoAdauga :public ActiuneUndo {
	Masina mAdd;
	RepoMasini& repo;
public:
	UndoAdauga(RepoMasini& repo, const Masina& mAdd) : repo{ repo }, mAdd{ mAdd } {}
	void doUndo() override {
		repo.sterge(mAdd);
	}
};
class UndoSterge : public ActiuneUndo {
	Masina mDel;
	RepoMasini& repo;
public:
	UndoSterge(RepoMasini& repo, const Masina& mDel) : repo{ repo }, mDel{ mDel } {}
	void doUndo() override {
		repo.adauga(mDel);
	}
};
class UndoModifica : public ActiuneUndo {
	Masina m1, m2;
	RepoMasini& repo;
public:
	UndoModifica(RepoMasini& repo, const Masina& m1, const Masina& m2) : repo{ repo }, m1{ m1 }, m2{ m2 } {}
	void doUndo() override {
		repo.sterge(m2);
		repo.adauga(m1);
	}
};
class UndoGolireS : public ActiuneUndo {
	vector<Masina> spalatorie;
	RepoMasini& repo;
public:
	UndoGolireS(RepoMasini& repo, vector<Masina> spalatorie) : repo{ repo }, spalatorie{ spalatorie } {}
	void doUndo() override {
		for (Masina& m : spalatorie)
			repo.adauga_s(m);
	}
};