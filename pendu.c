#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define TAILLE_MAX 835

// PSEUDO
int Pseudo();
char pseudo[50];

// MOT A DEVINER
int MotSecret();
char Affiche_Lettre();
void viderBuffer();
char motadev[40];

// TAB_TIRET
char tab_tiret[255];

// TAB_LETTRES
char lettre;
int Reponse();
char Tab_lettres[26];
int Verif_tab();

// COMPTEUR DE VIE
int Try = 0;

// PENDU
int DessinerPendu();
int Gamewin();

int main(int argc, char *argv[])
{
	srand(time(NULL));
	int nb_rand;
	int nb_ligne;
	nb_ligne = 0;
	FILE *fichier = NULL;

	fichier = fopen("words.txt", "r"); 									// Permet d'ouvrir le fichier mot

	if (fichier != NULL)
	{
		nb_rand = rand() % (TAILLE_MAX);							    // Permet de prendre un nombre random et de le stocker dans nb_rand. 

		while (nb_ligne < nb_rand)										//tant que nb_ligne est stictement inférieur à nb_rand.
		{
			nb_ligne++;

			fgets(motadev, TAILLE_MAX, fichier); 						//fgets récupère le mot de la ligne qui suit dans le fichier et le stocke dans motadev. 
		}
		fclose(fichier);

		Pseudo();
		MotSecret();

		while ((Try != 8) && Gamewin() == 0)
		{
			Affiche_Lettre();
			Reponse();
		}

	}
	else
	{
		printf("impossible d'ouvrir le fichier");
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Pseudo() // Demander le pseudo au joueur.
{
	printf("Quel est votre pseudo\n");
	scanf("%c", pseudo);
	viderBuffer();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int MotSecret() // Tableau de tiret
{

	int i;

	for (i = 0; i < strlen(motadev) - 1; i++) 						// Parcours mon tableau de mon mot à deviner
	{
		tab_tiret[i] = '_'; 										// Créer un tableau avec le même nombre de tiret que mon mot à deviner
		printf("%c", tab_tiret[i]);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char Affiche_Lettre() // Récupère caractère par caractère.
{
	int i;
	_Bool Verif_lettre = true;									 // Mettre true pour qu'il rentre obigatoirement dans la boucle.
	while (Verif_lettre == true)
	{
		printf("\nDonnez une lettre en minuscule.\n");
		lettre = getchar(); 									 // permet de mettre la lettre récupérée avec getchar dans lettre
		printf("Vous avez saisie cette lettre : %c\n", lettre);

		viderBuffer();
		Verif_lettre = false;
		for (i = 0; i < strlen(Tab_lettres); i++) 				// Parcours le tableau de lettres déjà données
		{

			if (lettre == Tab_lettres[i])						// Si la lettre a déjà été donnée
			{

				Verif_lettre = true; 						    // Verif_lettre devient vraie.
			}
		}
		if (Verif_lettre == true)
		{
			printf("\n%c a deja ete donnee\n", lettre);
		}

		if ((lettre < 'a') || (lettre > 'z'))
		{
			Verif_lettre = true;								 // le passer à true pour éviter qu'il fasse perdre une vie.
			printf("\n%c n'est pas une lettre\n", lettre);
		}
	}

	Tab_lettres[strlen(Tab_lettres)] = lettre;					// Pour stocker toutes les lettres, les unes après les autres.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Reponse()
{
	int i;
	int verif;

	for (i = 0; i < strlen(motadev) - 1; i++) 						// Parcours le tableau de mon mot à deviner
	{
		if (lettre == motadev[i]) 									// si la lettre donnée est dans mon mot à deviner
		{
			tab_tiret[i] = lettre;								    // le tiret sera remplacer par la lettre
		}
	}
	for (i = 0; i < strlen(motadev) - 1; i++) 						// Pour le tableau de mon mot à deviner
	{
		printf("%c", tab_tiret[i]);								    // printf tableau des tirets avec les lettres trouvées.
	}
	verif = Verif_tab();
	if (verif == 0) 											   // Si return = 0
	{
		Try++;													   // alors le nombre d'essaie augmente de 1
		printf("\nEssaie encore %d/8", Try);
	}

	DessinerPendu();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Verif_tab()
{
	int i;

	for (i = 0; i < strlen(motadev) - 1; i++) 					// Pour le mot à deviner
	{
		if (lettre == motadev[i])							    // si la lettre donnée est dans le mot
		{
			return (1); // on continue
		}
	}
	return (0); 											   // sinon on retourne dans reponse pour augmenter le nombre d'essaie
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void viderBuffer() 											  // Permer de vider le buffer
{
	char c = ' ';
	while (c != '\n' && c != EOF)
	{
		c = getchar();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Gamewin()
{
	int i;

	for (i = 0; i < strlen(motadev) - 1; i++) 				// On parcours le tableau du mot à deviner
	{
		if (motadev[i] != tab_tiret[i])				   	   // si l'indice du tableau à deviner est différent
		{
			return (0);									   // retourner false donc on continue
		}
	}
	printf("\nVICTOIRE\n");
	return (1); 										  // retourner true donc on stop partie gagné.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int DessinerPendu()
{
	printf("\n\n\n");
	if (Try == 1)
	{
		printf("|               |\n|===============|\n");
	}

	if (Try == 2)
	{
		printf("\n|==============|\n|              |               \n|==============|");
	}

	if (Try == 3)
	{
		printf("||\n||\n||\n||\n||\n||\n||\n||\n||\n||\n||\n|==============|\n|              |              \n|==============|");
	}

	if (Try == 4)
	{
		printf("|=============Y=|\n");
		printf("||            |\n");
		printf("||            |\n");
		printf("||\n||\n||\n||\n||\n||\n||\n||\n||\n");
		printf("|==============|\n|              |              \n|==============|");
	}
	if (Try == 5)
	{
		printf("|=============Y=|\n");
		printf("||            |\n");
		printf("||            |\n");
		printf("||            O\n");
		printf("||\n||\n||\n||\n||\n||\n||\n");
		printf("|==============|\n|              |              \n|==============|");
	}

	if (Try == 6)
	{
		printf("|=============Y=|\n");
		printf("||            |\n");
		printf("||            |\n");
		printf("||            O\n");
		printf("||           /|\\\n");
		printf("||\n||\n||\n||\n||\n||\n");
		printf("|==============|\n|              |              \n|==============|");
	}

	if (Try == 7)
	{
		printf("|=============Y=|\n");
		printf("||            |\n");
		printf("||            |\n");
		printf("||            O\n");
		printf("||           /|\\\n");
		printf("||            | \n");
		printf("||\n||\n||\n||\n||\n");
		printf("|==============|\n|              |              \n|==============|");
	}

	if (Try == 8)
	{
		printf("|=============Y=|\n");
		printf("||            |\n");
		printf("||            |\n");
		printf("||            O\n");
		printf("||           /|\\\n");
		printf("||            | \n");
		printf("||           / \\\n");
		printf("||\n||\n||\n||\n||\n");
		printf("|==============|\n|              |              \n|==============|");

		printf("\nDEFAITE\n");
		printf("Le mot à trouver était : %s\n", motadev);
	}
}
