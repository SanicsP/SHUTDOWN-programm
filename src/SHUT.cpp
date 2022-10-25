#include "Commandes.hpp"
#include <cstdlib>
#include <iostream>

std::function<void()> fonction_de_fin = nullptr; 

void definir_class_fin(std::function<void()> ff)
{
    fonction_de_fin = ff;
}




//Threads 

void thread_commande(const std::chrono::duration<double> & t_duree , 
                    std::promise<std::chrono::duration<double>> && Pmsg_duree_compteur ,
                    std::future<bool>&& Fmsg_arret_partie_com ,
                    std::promise<bool>&& Pmsg_arret_compteur ,
                    char* argv[] , int argc 
                    )
{
    // première partie du thread 

    Acom commutateur;  
    std::chrono::duration<double> duree_compteur{};
    
    std::stack<std::string> liste_Parametres{};
    stdComPile pile_Commandes{};
    stdStab liste_Commandes{};
    
    liste_Commandes = convertir_chaine(argv , argc);
    pile_Commandes = interpreter_Stab (liste_Commandes);
    liste_Parametres = recup_arg(liste_Commandes);

    executeur(duree_compteur , commutateur , pile_Commandes , liste_Parametres);

    //deuxième partie du thread 
    Pmsg_duree_compteur.set_value(duree_compteur);
    
    std::string entree_utilisateur;
    
    while(true)
    {
        std::cin>>entree_utilisateur; 
        liste_Commandes = conversion_chaine_caractere(entree_utilisateur);
        pile_Commandes = interpreter_Stab(liste_Commandes);
        liste_Parametres = recup_arg(liste_Commandes);

 
        
    }
    




}


void thread_compteur(std::promise<bool>&& Pmsg_arret_partie_com ,
                     std::future<std::chrono::duration<double>>&& Fmsg_duree_compteur ,
                     std::future<bool>&& Fmsg_arret_compteur 
                    )
{




}
