#include <iostream>
#include <limits>
#include <string>

#include "Menu.h"

void Menu::clearInput()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.clear();
}

void Menu::commandTestParameters()
{
	// on affiche un prompt à l'utilisateur pour lui demander quelque chose
	std::cout << "Entrez un nombre : ";

	// on demande le paramètre
	int param;
	std::cin >> param;

	// on vérifie que la saisie a bien fonctionné
	if (!std::cin) {
		// l'utilisateur a entré un nombre invalide, on prévient
		// l'utilisateur et on quitte
		std::cout << "Erreur, le paramètre est invalide " << std::endl;

		// on nettoie l'entrée pour remettre l'entrée dans un état
		// correct
		clearInput();
		return;
	}

	std::cout << "Test réussi, vous avez saisi : " << param << std::endl;
}

void Menu::commandQuit()
{
	std::cout << "Merci, à bientôt" << std::endl;
	exit(0);
}

void Menu::run()
{
	// on fait une boucle infinie délibérément
	for (;;) {
		std::cout << "Menu principal\n"
			<< "--------------\n"
			<< "\tt - Commande de test\n"
			<< "\tq - Quitter\n"
			<< std::endl;

		std::string choice;
		std::cin >> choice;

		if (choice == "t") {
			commandTestParameters();
		} else if (choice == "q") {
			commandQuit();
		} else {
			std::cout << "Commande inconnue\n";
		}

		clearInput();
	}
}

int main()
{
	Menu m;
	m.run();
}



