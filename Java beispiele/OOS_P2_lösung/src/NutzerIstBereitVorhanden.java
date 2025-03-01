/**
 *
 * @author Anas Shehabi
 * @version 1.0
 */

public class NutzerIstBereitVorhanden extends Exception{


    /**
     * konstruktur für NutzerIstBereitVorhanden dürch super damit er Konstruktur des Vaters Exceotion
     * erbt
     * @param ausgabe Details der Fehlermeldung.
     */

    public NutzerIstBereitVorhanden(String ausgabe) {
        super(ausgabe);
    }
}
