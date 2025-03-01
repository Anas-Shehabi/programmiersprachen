/**
 *
 * @author Anas Shehabi
 * @version 1.0
 */

public class BenutzerIstNichtVorhanden extends Exception {

    /**
     * konstruktur für BenutzerIstNichtVorhanden dürch super damit er Konstruktur des Vaters Exceotion
     * erbt
     * @param ausgabe Details der Fehlermeldung.
     */
    public BenutzerIstNichtVorhanden(String ausgabe) {super(ausgabe);}
}
