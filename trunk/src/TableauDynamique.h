#ifndef _TAB_DYN_FLOTTE_
#define _TAB_DYN_FLOTTE_

#include "flotte.h"

struct sTableauDynamique
{
  /*   donnees membres  */
  /*   (ne sont pas censees etre connues par l'utilisateur d'un module :  */
  /*   SI ON AVAIT PU NE PAS LES FAIRE FIGURER DANS L'INTERFACE,
       on l'aurait fait!) */
  unsigned int capacite;
  unsigned int taille_utilisee;
  Flotte * ad;
};
typedef struct sTableauDynamique TableauDynamique;


void initialiserTabDyn(TableauDynamique * t);
/* Precondition : t non prealablement initialise */
/* Postcondition : t initialise a une alveole vide (taille utilisee nulle) */


void testamentTabDyn(TableauDynamique *t);
/* Precondition : t prealablement initialise */
/* Postcondition : t pret a disparaitre. La memoire allouee dynamiquement
   est liberee. On ne pourra plus appeler les sous-programmes qui
   necessitent que t soit initialise. */

unsigned int tailleUtiliseeTabDyn(const TableauDynamique *t);
/* Precondition : t prealablement initialise */
/* Resultat : nombre d'Flottes stockes dans t */


Flotte* valeurIemeElementTabDyn(const TableauDynamique *t, unsigned int i);
/* Precondition : t prealablement initialise, 0 <= i < tailleUtilisee(t) */
/* Resultat : retourne le i+1eme Flotte de t */

void ajouterElementTabDyn(TableauDynamique *t, Flotte* e);
/* Precondition : t prealablement initialise */
/* Postcondition : L'element e est ajoute dans la premiere alveole inutilisee
   du tableau, la taille utilisee est incrementee de 1. Doublement de la
   capacite de t, si necessaire. */


void supprimerElementTabDyn( TableauDynamique *t, int position );
/* Precondition : t prealablement initialise et non vide */
/* Postcondition : la taille utilisee du tableau est decrementee de 1. Si
   tailleUtilisee < capacite/3, alors on divise la capacité par 2. */


void modifierValeurIemeElementTabDyn(TableauDynamique *t, Flotte e, unsigned int i);
/* Precondition : t prealablement initialise et 0 <= i < tailleUtilisee(t) */
/* Postcondition : le i+1eme Flotte de t vaut e */


void insererElementTabDyn(TableauDynamique *t, Flotte e, unsigned int i);
/* Precondition : t prealablement initialise et 0 <= i < tailleUtilisee(t) */
/* Postcondition : e est insere en i+1eme position et tailleUtilisee est incrementee de 1 */


#endif
