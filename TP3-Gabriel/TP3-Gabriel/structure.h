#pragma once
#include <string>
using namespace std;

struct Article {
	string codeArticle = "";
	string description = "";
	float coutUnitaire = -1.0f;
	float prixDeVente = -1.0f;
	int qteStock = -1;
	int seuil = -1;
	int codeValide = -1;
};

struct Client
{
	string codeClient = "";
	string nomClient = "";
	string Courriel = "";
	string typeClient = "";
	string dateAdhesion = "";
	char typeEscompte = ' ';
	int codeValiditer = -1;

};

