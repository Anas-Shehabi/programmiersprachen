import javafx.fxml.Initializable;

import java.io.Serializable;

/**
 *
 * @author Anas Shehabi
 * @version 1.0
 */


public class Benutzer implements Serializable {

    private String userid;
    private char [] passWort;

    /**
     *  Initialisiert die Attribute userid und passWort mit "" für userid und char-Array mit zehn Plätze für passWort
     */

    public Benutzer()
    {
        this.userid ="";
        this.passWort=new char[10];
    }

    /**
     * Initialisiert die Attribute mit den übergebenen Parametern.
     * @param Userid ist userid.
     * @param passwort ist passWort.
     */

    public Benutzer(String Userid,char [] passwort)
    {
        this.userid = Userid;
        this.passWort = passwort;
    }

    public void setUserid(String userid) {
        this.userid = userid;
    }
    public String getUserid() {
        return userid;
    }

    public void setPassWort(char[] passWort) {
        this.passWort = passWort;
    }

    public char[] getPassWort() {
        return passWort;
    }

    /**
     * Überpüft ob die Daten vom übergebenen Objekt mit den Daten des ausgewählten Objekt.
     * @param obj das zu überprüfene Objekt.
     * @return Daten gleich -> true, Daten ungleich -> false.
     */
    @Override
    public boolean equals(Object obj)
    {

        return obj != null && obj instanceof Benutzer && this.userid.equals(((Benutzer) obj).userid) && String.copyValueOf(this.passWort)
                .equals(String.copyValueOf(((Benutzer) obj).passWort));
    }

    /**
     * Erstelle einen String als Rückgabe der die Attribute ausgibt
     * @return
     */
    @Override
    public String toString(){
        return "User Id :"+ userid + " Passwort :"+ String.copyValueOf(passWort);
    }





}
