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
                    char* argv[] , int argc , std::atomic<Acom> & ATCmsg_commutateur , std::mutex & verroux_flux_sortie
                    )
{
    // première partie du thread 

   
    Acom commutateur;  
    std::chrono::duration<double> duree_compteur{};
    std::string liste_commande_exception;
    std::stack<std::string> liste_Parametres{};
    stdComPile pile_Commandes{};
    stdStab liste_Commandes{};
    
    bool exception_arrivee = false;
    while(true) {
    
    try {

    if(!exception_arrivee)
        liste_Commandes = convertir_chaine(argv , argc);
    else
        liste_Commandes = conversion_chaine_caractere(liste_commande_exception);

    pile_Commandes = interpreter_Stab (liste_Commandes);

    liste_Parametres = recup_arg(liste_Commandes);
    
    executeur(duree_compteur , commutateur , pile_Commandes , liste_Parametres);

    break;

    }
    catch(const std::invalid_argument & exception)
    {
        std::cout<<exception.what()<<" \n Reinscrivez votre commande -> ";
        std::getline(std::cin , liste_commande_exception);
        liste_Commandes = {};   
        exception_arrivee = true;
        continue;
    }
}
    ATCmsg_commutateur.store(commutateur , std::memory_order_release);

    //deuxième partie du thread 
    Pmsg_duree_compteur.set_value(duree_compteur);
    
    std::string entree_utilisateur;
     
    while(true)
    {
        verroux_flux_sortie.try_lock();
        std::cout<<"Voulez vous changer de commutauer ou annuler l'arret du system ? \n \n";
        std::cout<<"Votre Commande -> ";
        verroux_flux_sortie.unlock();
        
        
        std::getline(std::cin , entree_utilisateur);
        

         
        std::cout<<"\n/////////////////////////////////////////////////// debut resultat\n";

        
        try{

            liste_Commandes = conversion_chaine_caractere(entree_utilisateur);
            pile_Commandes = interpreter_Stab(liste_Commandes);

        }
        catch(const std::invalid_argument & exception)
        {
            entree_utilisateur = "\n";
            std::cout<<exception.what() << "\n \n";
            std::cin.clear();
            std::cout<<"appuyez sur entrer : ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max() , '\n');
            std::cout<<"\n/////////////////////////////////////////////////////////////// fin resultat\n \n";
            continue;
        }

        liste_Parametres = recup_arg(liste_Commandes);
        
        if(Fmsg_arret_partie_com.wait_for(0s) == std::future_status::ready) // le thread du compteur demande d'arreter , temps écoulé
            break;

        executeur(duree_compteur , commutateur , pile_Commandes , liste_Parametres);
        
        if(commutateur == Acom::ANUL)
        {
            Pmsg_arret_compteur.set_value(true);
            std::cout<<"annulation de l'arret du programme"<<std::endl;
            break;
        }
        
        verroux_flux_sortie.try_lock();
        std::cout<<"Commande validee !\n";
        std::cout<<"/////////////////////////////////////////////////// fin resultat\n \n";
        verroux_flux_sortie.unlock();

        ATCmsg_commutateur.store(commutateur , std::memory_order_release);
    }
    


    verroux_flux_sortie.lock();
    std::cout<<"arret thread commandes "<<std::endl;
    std::cout<<"/////////////////////////////////////////////////// fin resultat\n \n";
    verroux_flux_sortie.unlock();
    return;

}


void thread_compteur(std::promise<bool>&& Pmsg_arret_partie_com ,
                     std::future<std::chrono::duration<double>>&& Fmsg_duree_compteur ,
                     std::future<bool>&& Fmsg_arret_compteur , std::mutex & verroux_flux_sortie
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
    verroux_flux_sortie.try_lock();
    std::cout<<"\nLe temps est ecoule , l'arret du system va s'operer\n\n";
    verroux_flux_sortie.unlock();
    // std::cout<<"arret thread compteur\t \t Veuillez valider votre entree la commande ne s'executera pas , le compteur est arrive a son terme\n ";

}

void fonction_fin_programme(Acom commutateur)
{
    fonction_de_fin();
    arret_systeme(commutateur);
    std::terminate();
}

void arret_systeme(Acom commutateur)
{
    switch (commutateur)
    {
        case Acom::AF : //arrêt forcé  
            std::cout<<"Arret du systeme de maniere forcee : -af \n";
            system("shutdown /f /t 10");
        break;

        case Acom::AN : //arrêt normal 
            std::cout<<"Arret du systeme de maniere normale : -an \n";
            system("shutdown /s /t 10");
        break;

        case Acom::RD : //redemarage
            std::cout<<" le system va redemarage : -rd \n";
            system("shutdown /r /t 10");

        break;

        case Acom::ANUL : // annuler 
            std::cout<<"Le system ne s'arretera pas : -stop \n";

        break;
    
    }
}

void messages()
{
    std::cout<<"\nfin du programme\n\n";

}