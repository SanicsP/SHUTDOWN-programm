#include "Commandes.hpp"
#include "Compteur.hpp"
#include <cstdlib>
#include <iostream>

std::function<void()> fonction_de_fin = nullptr; 

void definir_class_fin(std::function<void()> ff)
{
    fonction_de_fin = ff;
}


 using namespace std::literals::chrono_literals;

//Threads 

void thread_commande(const std::chrono::duration<double> & t_duree , 
                    std::promise<std::chrono::duration<double>> && Pmsg_duree_compteur ,
                    std::future<bool>&& Fmsg_arret_partie_com ,
                    std::promise<bool>&& Pmsg_arret_compteur ,
                    char* argv[] , int argc , std::promise<Acom> && Pmsg_commutateur
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
        std::getline(std::cin , entree_utilisateur); 
        liste_Commandes = conversion_chaine_caractere(entree_utilisateur);
        pile_Commandes = interpreter_Stab(liste_Commandes);
        liste_Parametres = recup_arg(liste_Commandes);
        
        executeur(duree_compteur , commutateur , pile_Commandes , liste_Parametres);
        
        if(commutateur == Acom::ANUL)
        {
            Pmsg_arret_compteur.set_value(true);
            break;
        }
        
        if(Fmsg_arret_partie_com.wait_for(0s) == std::future_status::ready) // le thread du compteur demande d'arreter , temps écoulé
            break;

    }
    


    Pmsg_commutateur.set_value(commutateur);
    std::cout<<"arret thread commandes "<<std::endl;
    return;

}


void thread_compteur(std::promise<bool>&& Pmsg_arret_partie_com ,
                     std::future<std::chrono::duration<double>>&& Fmsg_duree_compteur ,
                     std::future<bool>&& Fmsg_arret_compteur 
                    )
{
    std::chrono::duration<double> duree_compteur = Fmsg_duree_compteur.get();
    compteur compteur_arret(duree_compteur.count());

    while(true)
    {
        if(Fmsg_arret_compteur.wait_for(0s) == std::future_status::ready)
        {
            break;
        }
        if(compteur_arret.estFini())
        {
            Pmsg_arret_partie_com.set_value(true);
            break;
        }
        
    }
    std::cout<<"arret thread compteur "<<std::endl;

}
