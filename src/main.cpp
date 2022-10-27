#include "TESTS.hpp"


#include <iostream>




int main(int argc , char* argv[])
{
   
    //test unbitaires 
        //tu_Commandes();
        //tu_Compteur();
        //tu_SHUT();
    ///

    definir_class_fin(messages);
    std::mutex verrou_flux_sortie;
    Acom commutateur{};
    std::chrono::duration<double>  t_duree ;
    //initialistaion variable atomique 
    std::atomic<Acom> ATCmsg_retour_commutateur;    
    // initialisation des futures et promesses  
    std::promise<std::chrono::duration<double>>  Pmsg_duree_compteur ;
    std::promise<bool> Pmsg_arret_compteur ;

    std::promise<bool> Pmsg_arret_partie_com ;

    std::future<bool> Fmsg_arret_partie_com = Pmsg_arret_partie_com.get_future(); 
    std::future<std::chrono::duration<double>>Fmsg_duree_compteur = Pmsg_duree_compteur.get_future();
    std::future<bool> Fmsg_arret_compteur = Pmsg_arret_compteur.get_future();
 

    //initialisation des threads 
    std::thread thread_partie_commande(thread_commande, t_duree , std::move(Pmsg_duree_compteur) 
                                     , std::move(Fmsg_arret_partie_com)  , std::move(Pmsg_arret_compteur), 
                                       argv , argc , std::ref(ATCmsg_retour_commutateur) , std::ref(verrou_flux_sortie));
    
    std::thread thread_partie_compteur(thread_compteur , std::move(Pmsg_arret_partie_com ), std::move(Fmsg_duree_compteur) 
                                      , std::move(Fmsg_arret_compteur) , std::ref(verrou_flux_sortie)
      );

    thread_partie_commande.detach();
    thread_partie_compteur.join();

    commutateur = ATCmsg_retour_commutateur.load(std::memory_order_acquire);
    fonction_fin_programme(commutateur);

    std::cin.ignore();
    return 0;
}