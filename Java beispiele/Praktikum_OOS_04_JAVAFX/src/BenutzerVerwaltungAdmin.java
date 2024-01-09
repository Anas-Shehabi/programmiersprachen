/**
 *
 * @author Anas Shehabi
 * @version 1.0
 */

import java.util.ArrayList;
import java.io.*;


public class BenutzerVerwaltungAdmin implements BenutzerVerwaltung{
    /**
     * Die Datenstruktur zum abspeichern der User
     */
    private static ArrayList<Benutzer> lis ;




    public BenutzerVerwaltungAdmin(){ lis = new ArrayList<Benutzer>();}



    public void dbInit() throws IOException {
       try {
           dbRead();
       }catch (IOException ex){
           dbWrite();
       }
    }

    /**
     * Lösche den nutzer aus der Liste
     * @param benutzer der zu löschende Nutzer
     * @throws BenutzerIstNichtVorhanden falls der Nutzer nicht vorhanden ist gib eine Fehler meldung aus
     */

    void benutzerLoeschen(Benutzer benutzer) throws BenutzerIstNichtVorhanden,IOException
    {

        if(lis.contains(benutzer))
        {
            lis.remove(benutzer);
            dbWrite();
        }
        else
            throw new BenutzerIstNichtVorhanden("Der Benutzer ist nicht eingetragen,"
                    + "oder der Benutzername und das Passwort stimmen nicht überein.");
        }

    /**
     * Save changes to database
     */
    void dbWrite() throws IOException {

        try {
            FileOutputStream fs  = new FileOutputStream("DB_Users");
            ObjectOutputStream os = new ObjectOutputStream(fs);
            os.writeObject(lis);
            fs.close();
        }catch( IOException e ){
            e.printStackTrace();
        }
    }


    /**
     * Load database if exists or create one if it does not
     */
    void dbRead() throws IOException {
    try {
            FileInputStream fs = new FileInputStream("DB_Users");
            ObjectInputStream os = new ObjectInputStream(fs);
            lis = (ArrayList<Benutzer>) os.readObject();
            fs.close();
    } catch (IOException ex) {
        throw ex;
    }catch (ClassNotFoundException e) {
            System.err.println("Falsche Datei gelesen.");
        }
    }




    /**
     * Füge die Benutzer der Liste hinzu
     * @param benutzer der Hinzuzufügende Nutzer
     * @throws NutzerIstBereitVorhanden falls der Nutzer bereits existiert dann wird eine Fehler meldung raus
     */
    @Override
    public void benutzerEintragen(Benutzer benutzer) throws NutzerIstBereitVorhanden,IOException
    {

        if (benutzerVorhanden(benutzer))
            throw new NutzerIstBereitVorhanden("Der Nuzter ist Bereit Vorhanden !!");

        else{
            lis.add(benutzer);
            dbWrite();
        }

    }

    /**
     * Überprufe ob der Nutzer bereits in der Liste ist
     * @param benutzer der zu Prüfende Nutzer
     * @return true falls ja false falls nein
     */

    @Override
    public boolean benutzerVorhanden(Benutzer benutzer) throws IOException {

        boolean vorhanden = false;
        for(Benutzer liste:lis){
            if(liste.getUserid().equals(benutzer.getUserid())){
                vorhanden = true;
            }
        }
        return vorhanden;
    }

    public boolean benutzer_ist_OK(Benutzer benutzer){

        if (lis.contains(benutzer))
            return true;
        else
            return false;
    }


    public void clearDb(){
        lis.clear();
        try {
            dbWrite();
        } catch (IOException ex) {
            System.err.println("Fehler beim Erstellen der Datei.");
        }
    }
}
