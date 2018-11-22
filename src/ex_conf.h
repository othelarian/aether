struct Def_Reseau {
    String ssid;
    String pwd;
};

const int CONF_NB_RESEAUX = 2;

const struct Def_Reseau RESEAU_NAME1 = {"SSID", "PWD"};
const struct Def_Reseau RESEAU_NAME2 = {"SSID", "PWD"};

const struct Def_Reseau CONF_RESEAUX[CONF_NB_RESEAUX] = {
    RESEAU_NAME1
    ,RESEAU_NAME2
}