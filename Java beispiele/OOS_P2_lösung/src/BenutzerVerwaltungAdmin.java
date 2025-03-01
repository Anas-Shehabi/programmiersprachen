/**
 *
 * @author Anas Shehabi
 * @version 1.0
 */

import java.util.ArrayList;

public class BenutzerVerwaltungAdmin implements BenutzerVerwaltung{
    /**
     * Die Datenstruktur zum abspeichern der User
     */
    private  static ArrayList<Benutzer> lis = new ArrayList<>();

    /**
     * Lösche den nutzer aus der Liste
     * @param benutzer der zu löschende Nutzer
     * @throws BenutzerIstNichtVorhanden falls der Nutzer nicht vorhanden ist gib eine Fehler meldung aus
     */

    void benutzerLoeschen(Benutzer benutzer) throws BenutzerIstNichtVorhanden
    {
        if(benutzerVorhanden(benutzer))
            lis.remove(benutzer);
        else
            throw new BenutzerIstNichtVorhanden("Der Nutzer ist nicht existiert");

    }


    /**
     * Füge die Benutzer der Liste hinzu
     * @param benutzer der Hinzuzufügende Nutzer
     * @throws NutzerIstBereitVorhanden falls der Nutzer bereits existiert dann wird eine Fehler meldung raus
     */
    @Override
    public void benutzerEintragen(Benutzer benutzer) throws NutzerIstBereitVorhanden
    {

        if(benutzerVorhanden(benutzer))
            throw new NutzerIstBereitVorhanden("Der Nuzter ist Bereit Vorhanden !!");
        else
            lis.add(benutzer);

    }

    /**
     * Überprufe ob der Nutzer bereits in der Liste ist
     * @param benutzer der zu Prüfende Nutzer
     * @return true falls ja false falls nein
     */

    @Override
    public boolean benutzerVorhanden(Benutzer benutzer) {

       return lis.contains(benutzer);
    }
}
