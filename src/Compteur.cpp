#include "Compteur.hpp"
#include <algorithm>



////////////////////////////////////////////////////////////////////////////
//CLASSE COMPTEUR
//****************************************************************************************************//
compteur::compteur(double duree) noexcept : m_temps_ecoulee(false)  
{
    m_temps_cible = std::chrono::seconds(static_cast<int>(duree));
    m_temps_initial = std::chrono::steady_clock::now();

}

bool compteur::estFini() noexcept
{
    std::chrono::time_point<std::chrono::steady_clock> maintenant = std::chrono::steady_clock::now();
    std::chrono::duration<double> m = maintenant - m_temps_initial;
    
    if(m.count() >= m_temps_cible.count())
    {
        m_temps_ecoulee = true;
        return true;
    }
    return false;
}

void compteur::renitialiser() noexcept
{
    m_temps_initial = std::chrono::steady_clock::now();
    m_temps_ecoulee = false;
    return;
}

void compteur::redef(double duree) noexcept
{
    m_temps_ecoulee = false;
    m_temps_cible = std::chrono::seconds(static_cast<int>(duree));
    m_temps_initial = std::chrono::steady_clock::now();

}

double compteur::actuel() const noexcept
{
    std::chrono::time_point<std::chrono::steady_clock> maintenant =  std::chrono::steady_clock::now();
    std::chrono::duration<double> d = maintenant - m_temps_initial;


    return d.count();
}

//****************************************************************************************************//
////////////////////////////////////////////////////////////////////////////

bool est_duree(const std::string& parametre)
{
    auto fin_chaine = std::end(parametre);
    bool h_fin = (parametre.back() == 'h') || (parametre.back() == 's') || (parametre.back()  == 'n' && *(fin_chaine -2) == 'm');

    bool nombre = std::all_of(std::begin(parametre) , (std::end(parametre) -3 ) , isdigit);

    if(h_fin && nombre)
        return true;
    
    return false;

}

std::chrono::duration<double> conversion_duree(const std::string& parametre)
{
    if(!est_duree(parametre))
        throw std::invalid_argument("Vous n'avez pas ecrit une duree comme argument ");
    
    std::chrono::duration<double> duree;

    auto fin_chaine = std::end(parametre);
    auto debut_chaine = std::begin(parametre);

    std::string nombre = {debut_chaine , fin_chaine - 1};
    int nombre_entier = 0;
    

    if(parametre.back() == 'h')
    {
        nombre_entier = std::stoi(nombre);
        duree = std::chrono::hours(nombre_entier);
    }
    if(parametre.back() == 's' )
    {
        nombre_entier = std::stoi(nombre);
        duree = std::chrono::seconds(nombre_entier);
    }
    if(parametre.back()  == 'n' && *(fin_chaine -2) == 'm')
    {
        nombre_entier = std::stoi(
            std::string{debut_chaine , fin_chaine - 2}
        );
        duree = std::chrono::minutes(nombre_entier);
    }

    
    return duree;
}