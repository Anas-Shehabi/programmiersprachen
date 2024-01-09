import java.io.IOException;

/**
 *
 * @author Anas Shehabi
 * @version 1.0
 */


public interface BenutzerVerwaltung {

    /**
     * Füge einen Benutzer hinzu
     * @param benutzer der hinzuzufügene Benutzer
     * @throws NutzerIstBereitVorhanden falls der Benutzer bereits existiert dann gib eine Meldung aus
     */
    void benutzerEintragen(Benutzer benutzer) throws NutzerIstBereitVorhanden, IOException;
    /**
     * Sollte der Benutzer bereits in der Liste sein return true
     * @param benutzer der zu Überprüfende Benutzer
     * @return
     */
    boolean benutzerVorhanden(Benutzer benutzer) throws IOException;
}
