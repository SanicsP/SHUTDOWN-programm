#include "Commandes.hpp"
#include "Compteur.hpp"

#include <iostream>


///////////////////////////////////////////////////////
//***************************************************//

// TABLE DES COMMANDES 


comTab TABLE_DES_COMMANDES {
    
    { 
        {"-t"    , 0 },  // commande pour définir la durée avant l'aarêt du système 
        {"-af"   , 1 },  // commande pour définir un commutateur d'arrêt forcé 
        {"-rd"   , 2 },  // commande pour définir un commutateur de redemarage
        {"-an"   , 3 },  // commande pour définir un commutateur d'arrêt normale
        {"-stop" , 4 }   // commande pour arrêter le compteur et d'annuler l'arrêt du système

    }

};

//***************************************************//
///////////////////////////////////////////////////////




stdStab convertir_chaine(char* argv[] , int taille)
{
    stdStab tab;
    
    for(int i = 1; i < taille ; i++)
    {
        tab.push_back(argv[i]);
    }

    if(tab.empty())
        throw std::invalid_argument("aucune commande n'a ete inscrite");
    return tab;

    
}

void afficherStab(const stdStab & tab)
{
    std::cout<<"->";
    for(std::string s : tab)
    {
        std::cout<<s<<" ";
    }
}

std::pair<std::string , bool> est_commande_argument(const std::string & commande)
{
    int nb_crochets_gauche = std::count(std::begin(commande) , std::end(commande) , SEPARATEUR_ARG_OUVRANT);
    int nb_crochets_droit = std::count(std::begin(commande) , std::end(commande) , SEPARATEUR_ARG_FERMANT);

    if(!(nb_crochets_droit == 1))
        return {msgINVALID , false};
    
    if(!(nb_crochets_gauche == 1))
        return {msgINVALID , false};
    
    if(!(commande.back() == SEPARATEUR_ARG_FERMANT))
        return {msgINVALID , false};
    
    if(commande.front() == SEPARATEUR_ARG_OUVRANT)
        return {msgINVALID , false};
    
    std::string::const_iterator emplacement_crochet_gauche = 
    {std::find(std::begin(commande) , std::end(commande) , SEPARATEUR_ARG_OUVRANT)};

    return {{std::begin(commande) , emplacement_crochet_gauche} , true};

}


stdComPile interpreter_Stab(const stdStab& ListeArguments)
{
    std::pair<std::string , bool> drapeau = {"",false};
    stdComPile pile_commadne;
    bool commande_valide = true;

    for(unsigned int i = 0; i < ListeArguments.size() ; i++)
    {
        drapeau = est_commande_argument(ListeArguments[i]);
        
        if(!drapeau.second)
        {
            drapeau.first = ListeArguments[i];
        }

        for(unsigned int j = 0 ; j < TAILLE_TABLE_COMANDES ; j++)
        {
            if(drapeau.first == TABLE_DES_COMMANDES[j].first)
            {   
                pile_commadne.push(TABLE_DES_COMMANDES[j].second);
                commande_valide = true;
                break;
            }
            else
            {
                commande_valide = false;
            }
        }

        if(!commande_valide)
        {
            throw std::invalid_argument("un argument de la commande est invalide ");
        }

    }
    return pile_commadne;
    
}

std::stack<std::string> recup_arg(const stdStab& ListeArguments)
{
    std::string::const_iterator separateur_fermant;
    
    std::string::const_iterator separateur_ouvrant;
    std::string nombre;    
    std::stack<std::string> liste_param {};
    
    for(int i = 0 ; i < ListeArguments.size() ; i++)
    {
        if(est_commande_argument(ListeArguments[i]).second)
        {
            separateur_ouvrant = std::find(std::begin(ListeArguments[i]) , std::end(ListeArguments[i]) , SEPARATEUR_ARG_OUVRANT) + 1;
            separateur_fermant = std::find(std::begin(ListeArguments[i]) , std::end(ListeArguments[i]) , SEPARATEUR_ARG_FERMANT) ;

            nombre = {separateur_ouvrant , separateur_fermant};
            // DEBUG std::cout<<"DEBUG F2 : "<<"arguemnt de "<<ListeArguments[i]<<" : "<<nombre<<std::endl;
            liste_param.push(nombre);

        }
    }
    return liste_param;

}

stdStab conversion_chaine_caractere(const std::string& chaine)
{
    if(chaine.empty()) // verif chaine vide 
        throw std::invalid_argument("Vous n'avez entre aucun argument veuillez ressaisir une commande");

    std::string::const_iterator debut = std::begin(chaine);
    std::string::const_iterator fin = std::begin(chaine);
 
    stdStab tab;
    

    while(fin != std::end(chaine))
    {
        while(*(fin) == ' ') //sauter les occurences d'espaces  
            fin++;

        debut = fin; //remettre les itérateurs au bon ordre 

        fin = std::find(debut , std::end(chaine) , ' ');
        tab.push_back({debut , fin});
        
    }

   

    return tab;

}

void executeur(std::chrono::duration<double> & duree , Acom&  commutateur , stdComPile & pile_commande , 
               std::stack<std::string> & liste_param )
{
    int id_commande = 0;
    int parcour_arg = 0;
    int i = pile_commande.size();

    while(!pile_commande.empty())
    {
        id_commande = pile_commande.top();
        pile_commande.pop();

        switch(id_commande)
        {
            case 0 :
                    duree = conversion_duree(liste_param.top());
                    liste_param.pop();
                 // DEBUG std::cout<<"Executeur j'execute la commande T "<<id_commande<<" ! \n ";
            break;
            
            case 1 :   
                commutateur = Acom::AF;
                //DEBUG std::cout<<"Executeur j'execute la commande "<<id_commande<<" ! \n ";
            break;

            case 2 :
                commutateur = Acom::RD;
                //DEBUG std::cout<<"Executeur j'execute la commande "<<id_commande<<" ! \n ";
            break;

            case 3 :
                commutateur = Acom::AN;
                //DEBUG std::cout<<"Executeur j'execute la commande "<<id_commande<<" ! \n ";
            break;

            case 4 :
                commutateur = Acom::ANUL;
                // DEBUG std::cout<<"Executeur j'execute la commande "<<id_commande<<" ! \n ";
            break;
        
        }
        i--;
        // DEBUG std::cout<<"nombre execution"<<std::endl;
    }

}