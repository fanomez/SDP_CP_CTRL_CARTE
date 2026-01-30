// ........................................................................................................
// Route permettant de modifier l'horodatage 
// ........................................................................................................
  void registerHorodatageRoutes() {

    WR_jour = doc["Jour"].as<int>();
    WR_mois = doc["Mois"].as<int>();
    WR_annee = doc["Annee"].as<int>();

    WR_heure = doc["Heure"].as<int>();
    WR_min = doc["Min"].as<int>();
    WR_sec = doc["Sec"].as<int>();

    *horodotage_cmd = 1; // pas existant encore

  }
// ........................................................................................................
