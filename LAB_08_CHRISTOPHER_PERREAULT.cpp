#include <iostream>	// pour le cout
#include <iomanip>	// pour les manipulateurs (setw(), setprecision(), etc
#include <conio.h>	// pour le _getch
#include <string>	//Pour le type string
#include <H:\Programmation\TI\TI\cvm 21.h>
#include <windows.h>

using namespace std;

int main()
{
	//Bool
	bool programmeEnCours = true;						//Indique si le programme est en cours ou non.
	bool dateValide = false;							// Indique si la date est valide ou non.

	//Confirmations
	const int NBQUESTIONPOS = 3;
	int xPosQuestion[NBQUESTIONPOS];
	int yPosQuestion[NBQUESTIONPOS];
	const int NBQUESTIONON = 2;
	char ReponseON[NBQUESTIONON];
	// Mise en page
	const int tab = 8;
	const int grosseurMJ = 2;							//Grosseur du format des jours et mois 01, 02, 03 etc

	string LastMessage;
	int larg_lastMessage;
	int larg_LastMessagex;

	//Input
	const int NBTYPEDATE = 3;							//Nb total de type de date demande
	int date[NBTYPEDATE];
	char spacer[NBTYPEDATE -1];

	//Informations des mois et dates
	const int NBMOIS = 12;
	int JourParMois[NBMOIS] = {	31,			28,				31,		30,			31,		30,		31,			31,		30,				31,			30,				31 };
	string Mois[NBMOIS] = {		"Janvier",	"F/202vrier",	"Mars",	"Avril",	"Mai",	"Juin",	"Juillet",	"Ao�t",	"Septembre",	"Octobre",	"Novembre",		"D / 202cembre" };

	const int NBJOURSEMAINE = 7;
	string JoursDeLaSemaine[NBJOURSEMAINE] = { "Dimanche" ,"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi" };

	int jourDateChoisi;									// Jour a la date choisis (Dim a Sam)
	int joursemaine1er;									// Jour semaine du premier du mois choisis
	int nbTotalJourEcoule;								//Nb total de jours ecoules depuis la date choisis.



	do
	{
		dateValide = false, ReponseON[1] = ReponseON[0] = 'a';
		clrscr();
		gotoxy(tab, 2);
		cout << "Entrez une date (JJ/MM/AAAA) : ";
		xPosQuestion[0] = wherex(), yPosQuestion[0] = wherey();


		do
		{

			gotoxy(xPosQuestion[0], yPosQuestion[0]);
			clreol;

			cin >> date[0] >> spacer[0] >> date[1] >> spacer[1] >> date[2];

			gotoxy(xPosQuestion[0], yPosQuestion[0] + 20);						//Preparer le pos universelle en cas derreur

			if (date[2] % 4 == 0)
				JourParMois[1] = 29;

			if (cin.fail() == true)
			{
				cout << "Vous devez entrer des nombres seulement";
				cin.ignore(cin.rdbuf()->in_avail()), cin.clear();
			}
			else if (date[2] > 2099 || date[2] < 1901)
				cout << "L'ann\202e est erron\202e (de 1901 \205 2099 seulement)";

			else if (12 < date[1] || date[1] <= 0)
				cout << "Le mois est erron\202 (doit \210tre entre 1 et 12 inclusivement)";

			else if (date[0] > 31 || date[0] < 0)
				cout << "Le jour doit \210tre entre 1 et 31 inclusivement";

			else if (spacer[0] != '/' && spacer[0] != '-' && spacer[1] != '/' && spacer[1] != '-')
				cout << "Vous devez utiliser le separateur '/' ou '-' seulement";

			else if (spacer[0] != spacer[1])
				cout << "Vous devez utiliser le m\210me s/202parateur";

			else
				dateValide = true;

		} while (dateValide == false);

		nbTotalJourEcoule = 0;
		for (int i = 0; i <= ((date[1]) - 1); ++i)
		{
			if ((date[1] - 1) == i)
				nbTotalJourEcoule += date[0];

			else
				nbTotalJourEcoule += (JourParMois[i]);
		}

		jourDateChoisi = (nbTotalJourEcoule + (date[2] - 1900) + (date[2] - 1901) / 4) % 7;

		clrscr();

		gotoxy(tab, 4);

		cout	<< setfill('0')
				<< "Le " << setw(grosseurMJ) << date[0] << spacer[0] << setw(grosseurMJ) << date[1] << spacer[1] << date[2] << " est un : " << JoursDeLaSemaine[jourDateChoisi]
				<< setfill(' ');

		gotoxy(tab, 6);
		cout << "Voulez-vous voir le calendrier complet du mois (O/N) ? ";
		xPosQuestion[1] = wherex(), yPosQuestion[1] = wherey();
		
		do
		{
			gotoxy(xPosQuestion[1], yPosQuestion[1]);
			ReponseON[0] = toupper(_getch());
			cout << ReponseON[0];
		} while (ReponseON[0] != 'O' && ReponseON[0] != 'N');

		if (ReponseON[0] == 'O') //Si lutilisateur souhaite utiliser le calendrier
		{
			clrscr();
			int larg_titre = Mois[date[1] - 1].size() + 5;
			int larg_titrex = ((120 - larg_titre) / 2);
			gotoxy(larg_titrex, 2);
			cout << Mois[date[1] - 1] << " " << date[2];

			int larg_calendrier = (tab * 6) + (grosseurMJ*7);
			int larg_calendrierx = ((120 - larg_calendrier) / 2);
			gotoxy(larg_calendrierx, 6);
			cout << setw(larg_calendrier) << setfill('_') << "" << setfill(' ');

			gotoxy(larg_calendrierx, 5);

			for (int i = 0; i <= 6; ++i)
				cout << JoursDeLaSemaine[i][0] << JoursDeLaSemaine[i][1] << setw(tab) << "";

			gotoxy(larg_calendrierx, 9);

			joursemaine1er = 0;
			nbTotalJourEcoule = (nbTotalJourEcoule - date[0]) + 1;
			joursemaine1er = (nbTotalJourEcoule + (date[2] - 1900) + (date[2] - 1901) / 4) % 7;


			int saut = 2;		//Saut á faire aprés chaque 7 jours
			int dateentree = 0;		//Nombre de blanc laisse pour rattraper le jour de la semaine du premier

			for (int i = 1; i < JourParMois[date[1]]; ++i)
			{
				while (joursemaine1er > dateentree)
				{
					cout << setw(grosseurMJ) << "" << setw(tab) << "";
					++dateentree;
				}
				if (dateentree % 7 == 0)
				{
					gotoxy(larg_calendrierx, 9 + saut);
					saut += 2;
				}

				cout << setw(grosseurMJ) << i << setw(tab) << "";
				++dateentree;
			}
		}

		
		gotoxy(tab, 29);
		cout << "Voulez-vous traiter une autre date (O / N) ? ";
		xPosQuestion[2] = wherex(), yPosQuestion[2] = wherey();
		do
		{
			gotoxy(xPosQuestion[2], yPosQuestion[2]);
			ReponseON[1] = toupper(_getch());
			cout << ReponseON[1];

		} while (ReponseON[1] != 'O' && ReponseON[1] != 'N');
		
		if (ReponseON[1] == 'N')
			programmeEnCours = false;

	} while (programmeEnCours == true);

	clrscr();

	LastMessage = "A U  R E V O I R !!";
	larg_lastMessage = LastMessage.size();
	larg_LastMessagex = ((120 - larg_lastMessage) / 2);

	gotoxy(larg_LastMessagex, 15);

	cout << LastMessage;
	Sleep(2000);

}