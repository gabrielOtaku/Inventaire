#include "fonctions.h"
#include <iostream>
#include "structure.h"
#include <regex>
#include <fstream>

using namespace std;

void positionnerCurseur(int x, int y)
{
	HANDLE manipConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordonnees;
	coordonnees.X = x; //Lignes
	coordonnees.Y = y; //Colonnes
	SetConsoleCursorPosition(manipConsole, coordonnees);
}

void afficherMenu(bool siEffacerEcran)
{
	if (siEffacerEcran)
	{
		system("cls");
	}
	positionnerCurseur(20, 3);
	cout << "Menu principal";
	positionnerCurseur(25, 5);
	cout << "1 - Ajout d'un article en inventaire";
	positionnerCurseur(25, 7);
	cout << "2 - Ajout d'un nouveau client";
	positionnerCurseur(25, 9);
	cout << "3 - Liste des articles de l'inventaire";
	positionnerCurseur(25, 11);
	cout << "4 - Liste des clients";
	positionnerCurseur(25, 13);
	cout << "5 - Rechercher un article dans l'inventaire";
	positionnerCurseur(25, 15);
	cout << "6 - Rechercher un client";
	positionnerCurseur(25, 27);
	cout << "99 - Pour terminer";
	positionnerCurseur(20, 29);
	cout << "Votre choix : \t";
}

bool siChoixMenuValide(int choixMenu)
{
	bool siValide;
	switch (choixMenu)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 99:
		siValide = true;
		break;

	default:
		siValide = false;
		break;
	}
	return siValide;
}

void afficherMsgErreur(string msg)
{
	system("cls");
	HANDLE manipConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(manipConsole, 12);
	positionnerCurseur(1, 1);
	cout << msg;
	SetConsoleTextAttribute(manipConsole, 7);
}

void ajoutArticle()
{
	Article article;
	bool isValid_codeArticle = true;
	bool isValid_coutUnitaire = true;
	string msgErreur = "";

	do
	{
		system("cls");
		if (!isValid_codeArticle || !isValid_coutUnitaire)
		{
			afficherMsgErreur(msgErreur);
		}

		positionnerCurseur(15, 7);
		cout << "Code de l'article : ";
		if (article.codeArticle == "" || !isValid_codeArticle)
		{
			cin >> article.codeArticle;
			isValid_codeArticle = siCodeArticleValide(article.codeArticle);
			if (!isValid_codeArticle || !isValid_coutUnitaire)
			{
				msgErreur = "ERREUR - le code de l'article (" + article.codeArticle + ") n'est pas valide. ";
			}
		}
		else
		{
			cout << article.codeArticle;
		}

		if (isValid_codeArticle)
		{
			//Description
			positionnerCurseur(15, 9);
			cout << "Description : ";
			if (article.description == "")
			{
				cin.ignore();
				getline(cin, article.description);
			}
			else
			{
				cout << article.description;
			}

			// Cout Unitaire
			positionnerCurseur(15, 11);
			cout << " Cout unitaire :\t";
			if (article.coutUnitaire < 1.0f || !isValid_coutUnitaire)
			{
				cin >> article.coutUnitaire;
				isValid_coutUnitaire = siCoutUnitaireValide(article.coutUnitaire);
				if (!isValid_coutUnitaire)
				{
					msgErreur = "Erreur - le cout unitaire (" + to_string(article.coutUnitaire) + ") n'est pas valide.";
				}
			}

			//Prix de vente
			article.prixDeVente = article.coutUnitaire * 1.4f;

			// Quantite en stock 
			positionnerCurseur(15, 13);
			cout << "Quantit\x82 en stock :";
			cin >> article.qteStock;

			// Seuil de commande
			positionnerCurseur(15, 15);
			cout << "Seuil de commande :";
			cin >> article.seuil;

			// Code de validite
			if (isValid_codeArticle && isValid_coutUnitaire)
			{
				article.codeValide = 1;
			}
		}

		//Enregistrement dans le fichier 
		if (isValid_codeArticle && isValid_coutUnitaire)
		{
			positionnerCurseur(15, 20);
			cout << "Voici les informations de l'article :\t"
				<< article.codeArticle << " | "
				<< article.description << " | "
				<< article.coutUnitaire << " | "
				<< article.prixDeVente << " | "
				<< article.qteStock << " | "
				<< article.seuil
				<< "\n\n";

			positionnerCurseur(15, 22);
			string reponse = "";
			cout << "Voulez-vous ajouter ces informations dans le fichier :\t";
			cin >> reponse;

			regex regexOui("[oO] | oui | Oui | OUI");
			if (regex_match(reponse, regexOui))
			{
				//ouverture fichier inventaire.dat
				ofstream fichierInventaire("inventory.dat", ios::app);

				//Ecriture CSV --> Separateur = ;
				fichierInventaire << article.codeArticle << ";"
					<< article.description << ";"
					<< article.coutUnitaire << ";"
					<< article.prixDeVente << ";"
					<< article.qteStock << ";"
					<< article.seuil << ";"
					<< article.codeValide << "\n";




				// Fermeture du fichier 
				fichierInventaire.close();
				positionnerCurseur(15, 25);
				system("pause");

			}
		}
	} while (!isValid_codeArticle || !isValid_coutUnitaire);
}

void ajoutClient()
{
	Client client;
	bool isValide_codeClient = true;
	bool isValide_Courriel = true;
	bool isValide_typeClient = true;
	bool isValide_typeEscompte = true;
	string msgErreur = "";

	system("cls");
	if (!isValide_codeClient || !isValide_Courriel || !isValide_typeClient || !isValide_typeEscompte)
	{
		afficherMsgErreur(msgErreur);
	}

	do
	{
		system("cls");

		positionnerCurseur(15, 7);
		cout << "Code client (2 lettres minuscule et 4 chiffres ) : ";
		if (client.codeClient == "" || !isValide_codeClient)
		{
			cin >> client.codeClient;
			isValide_codeClient = siCodeClientValide(client.codeClient);
			if (!isValide_codeClient)
			{
				msgErreur = "Errueur - Le code client (" + client.codeClient + ") n'est pas valide";
			}
		}
		else
		{
			cout << client.codeClient;
		}
		positionnerCurseur(15, 9);
		cout << "nom du client : ";
		if (client.nomClient == "")
		{
			cin.ignore();
			getline(cin, client.nomClient);
		}
		else
		{
			cout << client.nomClient;
		}
		positionnerCurseur(15, 11);
		cout << "Courriel du client : ";
		if (client.Courriel == "" || !isValide_Courriel)
		{
			cin >> client.Courriel;
			isValide_Courriel = siCourrielClientValide(client.Courriel);
			if (!isValide_Courriel)
			{
				msgErreur = "Errueur - Le courriel (" + client.Courriel + ") n'est pas valide";
			}
		}
		else
		{
			cout << client.Courriel;
		}
		positionnerCurseur(15, 13);
		cout << "Type de client : ";
		if (client.typeClient == "" || !isValide_typeClient)
		{
			cin >> client.typeClient;
			isValide_typeClient = siTypeClientValide(client.typeClient);
			if (!isValide_typeClient)
			{
				msgErreur = "Errueur - Le type de client (" + client.typeClient + ") n'est pas valide";
			}
		}
		else
		{
			cout << client.typeClient;
		}
		positionnerCurseur(15, 15);
		cout << " Date d'adhesion : ";
		if (client.dateAdhesion == "")
		{
			cin.ignore();
			getline(cin, client.dateAdhesion);
		}
		else
		{
			cout << client.dateAdhesion;
		}

		positionnerCurseur(15, 17);
		cout << "Type d'escompte (1, 2 ou 3) : ";
		if (client.typeEscompte == ' ' || !isValide_typeEscompte)
		{
			cin >> client.typeEscompte;
			isValide_typeEscompte = siTypeEscompteValide(client.typeEscompte);
			if (!isValide_typeEscompte)
			{
				msgErreur = "Errueur - Le type de client (" + string(1, client.typeEscompte) + ") n'est pas valide";
			}
		}
		else
		{
			cout << client.typeEscompte;
		}

		if (isValide_codeClient && isValide_Courriel && isValide_typeClient && isValide_typeEscompte)
		{
			positionnerCurseur(15, 20);
			cout << "Voici les informations du client :\t"
				<< client.codeClient << " | "
				<< client.nomClient << " | "
				<< client.Courriel << " | "
				<< client.typeClient << " | "
				<< client.dateAdhesion << " | "
				<< client.typeEscompte
				<< "\n\n";

			positionnerCurseur(15, 22);
			string reponse = "";
			cout << "Voulez-vous ajouter ces informations dans le fichier :\t";
			cin >> reponse;

			regex regexOui("[oO] | oui | Oui | OUI");
			if (regex_match(reponse, regexOui))
			{
				//ouverture fichier inventaire.dat
				ofstream fichierInventaire("client.dat", ios::app);

				//Ecriture CSV --> Separateur = ;
				fichierInventaire << client.codeClient << ";"
					<< client.nomClient << ";"
					<< client.Courriel << ";"
					<< client.typeClient << ";"
					<< client.dateAdhesion << ";"
					<< client.typeEscompte << ";"
					<< client.codeValiditer << "\n";




				// Fermeture du fichier 
				fichierInventaire.close();
				positionnerCurseur(15, 25);
				system("pause");

			}
		}
	} while (!isValide_codeClient || !isValide_Courriel || !isValide_typeClient || !isValide_typeEscompte);

}

//Validite code client
bool siCodeClientValide(string codeClient)
{
	bool isValid = false;
	regex formatCodeArticle("[a-z] + [a-z] + [0-9]{4}");
	if (regex_match(codeClient, formatCodeArticle))
	{
		string lettres = codeClient.substr(1, 4);
		int codeClientInt = stoi(lettres);
		if (codeClientInt >= 301 && codeClientInt <= 999)
		{
			isValid = true;
		}
	}

	return isValid;
}

//Validite courriel client
bool siCourrielClientValide(string courrielClient)
{
	bool isValid = false;

	regex courriel("[a-z] + [0-9a-z. \\ -_] * [0-9a-z] + @[a-z] + [0-9a-z]*(.[a-z] {2,})+");
	if (regex_match(courrielClient, courriel))
	{
		isValid = true;
	}

	return isValid;
}

//Validite type client 
bool siTypeClientValide(string typeClient)
{
	bool isValid = false;
	regex monTypeClient("[Bronze] | [Argent] | [Or] ");
	if (regex_match(typeClient, monTypeClient))
	{
		isValid = true;
	}

	return isValid;
}

//Validite type d'escompte
bool siTypeEscompteValide(char typeEscompte)
{
	bool isValid = false;

	if (typeEscompte == '1' || typeEscompte == '2' || typeEscompte == '3')
	{
		isValid = true;
	}
	else
	{
		return false;
	}

	return isValid;
}

//Validite code article
bool siCodeArticleValide(string codeArticle)
{
	bool isValid = false;
	regex formatCodeArticle("[a-zA-Z][0-9]{3}");
	if (regex_match(codeArticle, formatCodeArticle))
	{
		string nombre = codeArticle.substr(1, 3);
		int codeArticleInt = stoi(nombre);
		if (codeArticleInt >= 301 && codeArticleInt <= 999)
		{
			isValid = true;
		}
	}

	return isValid;
}

//Validite cout unitaire
bool siCoutUnitaireValide(float coutUnitaire)
{
	bool isValid = false;

	if (coutUnitaire >= 1.0f)
	{
		isValid = true;
	}
	return isValid;
}

void listeArticle()
{
	system("cls");
	Article article;
	int positionX = 10;
	int positionY = 7;
	string nomFichier = "inventory.dat";
	ifstream fichierLecture(nomFichier, ifstream::in);
	if (fichierLecture) // si "fichierLecture" contient quelque chose --> ouverture reussi .
	{
		positionnerCurseur(positionX, positionY);
		cout << "Le contenue du fichier INVENTAIRE";

		positionY += 2;
		positionnerCurseur(positionX, positionY);
		cout << setw(5) << "----"
			<< setw(30) << "-----------"
			<< setw(10) << "----"
			<< setw(10) << "----"
			<< setw(8) << "-----"
			<< setw(8) << "-----"
			<< setw(10) << "------";

		positionY++;
		string ligneLue;
		string champLu;
		stringstream ligneStream;
		do
		{
			getline(fichierLecture, ligneLue);
			if (!fichierLecture.eof())
			{
				ligneStream << ligneLue;
				getline(ligneStream, article.codeArticle, ',');

				getline(ligneStream, article.description, ',');
				article.coutUnitaire = stof(champLu);

				getline(ligneStream, article.description, ',');
				article.prixDeVente = stof(champLu);
				getline(ligneStream, champLu, ',');
				article.qteStock = stoi(champLu);
				getline(ligneStream, champLu, ',');
				article.seuil = stoi(champLu);
				getline(ligneStream, champLu, ',');
				article.codeValide = stoi(champLu);

				ligneStream.clear();

				positionnerCurseur(positionX, positionY);
				cout << setw(5) << article.codeArticle
					<< setw(30) << article.description
					<< setw(10) << article.coutUnitaire
					<< setw(10) << article.prixDeVente
					<< setw(6) << article.qteStock
					<< setw(8) << article.seuil
					<< setw(10) << article.codeValide;
				positionY++;
			}


		} while (!fichierLecture.eof());
		fichierLecture.close();

	}
	else
	{
		afficherMsgErreur("Erreur -Ouverture du fichier -" + nomFichier + "- impossible.");

	}
	positionnerCurseur(positionX, positionY + 2);
	system("pause");
}

void listeClient()
{
}

void rechercherArticle()
{
	system("cls");
	Article article;
	string nomFichier = "inventory.dat";
	ifstream fichierLecture(nomFichier, ios::in);

	if (fichierLecture)
	{
		string choixCodeRecherche = "";
		bool isSuccess = false;

		positionnerCurseur(42, 5);
		cout << "RECHERCHE ARTICLE";

		positionnerCurseur(42, 6);
		cout << " =================";

		positionnerCurseur(10, 9);
		cout << "Entrez le code de l'article cible : \t";
		cin.ignore();
		getline(cin, choixCodeRecherche);

		string ligneLue;
		string champLu;
		stringstream ligneStream;

		do
		{
			getline(fichierLecture, ligneLue);
			if (!fichierLecture.eof())
			{
				ligneStream << ligneLue;
				getline(ligneStream, article.codeArticle, ',');

				if (choixCodeRecherche == article.codeArticle)
				{
					isSuccess = true;
					//code...
				}

				//Valider/ Remplir le stream avec une chaine vide
				ligneStream.clear();
				ligneStream.str("");
			}
		} while (!isSuccess && !fichierLecture.eof());
	}
	else
	{
		afficherMsgErreur("ERREUR - Overture du fichier -" + nomFichier + "- impossible");
	}

	positionnerCurseur(10, 22);
	system("pause");

}

void rechercherClient()
{
}
