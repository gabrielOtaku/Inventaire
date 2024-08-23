#pragma once
#include <Windows.h>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

void positionnerCurseur(int x, int y);
void afficherMenu(bool siEffacerEcran);
bool siChoixMenuValide(int choixMenu);
void afficherMsgErreur(string msg);
void ajoutArticle();
bool siCodeArticleValide(string codeArticle);
bool siCoutUnitaireValide(float coutUnitaire);
void ajoutClient();
bool siCodeClientValide(string codeClient);
bool siCourrielClientValide(string courrielClient);
bool siTypeClientValide(string typeClient);
bool siTypeEscompteValide(char typeEscompte);
void listeArticle();
void listeClient();
void rechercherArticle();
void rechercherClient();
