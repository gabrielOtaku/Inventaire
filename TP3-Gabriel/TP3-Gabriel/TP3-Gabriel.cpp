#include <iostream>
#include "fonctions.h"
using namespace std;

int main()
{
	int choixMenu = -1;
	bool siValide = true;
	do
	{
		if (!siValide)
		{
			afficherMsgErreur("choix invalide");
		}

		afficherMenu(siValide);
		positionnerCurseur(33, 30);
		cin >> choixMenu;
		siValide = siChoixMenuValide(choixMenu);

		if (siValide)
		{
			switch (choixMenu)
			{

			case 1:

				ajoutArticle();
				break;

			case 2:

				ajoutClient();
				break;

			case 3:

				listeArticle();
				break;

			case 4:

				listeClient();
				break;

			case 5:

				rechercherArticle();
				break;

			case 6:

				rechercherClient();
				break;

			}
		}


	} while (choixMenu != 99);

}