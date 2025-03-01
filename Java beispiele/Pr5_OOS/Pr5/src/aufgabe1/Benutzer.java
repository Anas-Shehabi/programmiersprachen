package aufgabe1;

import java.io.Serializable;

/**
 * Diese Klasse definiert die grundlegende Struktur von Benutzern. 
 * Aufgabe a) des Praktikums.
 * 
 * @author Maher
 * @version 1.0
 */
public class Benutzer implements Serializable{	
	
	/**
	 * Attribut zum Spiechern der userId als String
	 */
	String userId;
	/**
	 * Attribut zum Spiechern des Passworts als char-Array
	 */
	char[] passWort;
	
	public Benutzer(){
		userId = null;
		passWort = null;
	}
	public Benutzer(String userId, char[] passWort){
		this.userId = userId;
		this.passWort = passWort.clone();
	}
	
	/**
	 * Getter für UserID
	 * @return liefert die UserID des Objektes
	 */
	public String getUserId() {
		return this.userId;
	}
	/**
	 * Setter für UserID
	 * @param userId setzt den übergebenen Parameter auf userId 
	 */
	public void setUserId(String userId) {
		this.userId = userId;
	}
	/**
	 * Getter für Passwort
	 * @return liefert das Passwort des Objektes
	 */
	public char[] getPassWort() {
		return this.passWort;
	}
	/**
	 * Setter für Passwort
	 * @param userId setzt den übergebenen Parameter auf passWort 
	 */
	public void setPassWort(char[] passWort) {
		this.passWort = passWort;
	}
	
	/**
	 * Standardmethode, die die Inhalte der beiden Attribute in der folgenden Form ausgibt:
	 * (userId/passWort)
	 */
	public String toString() {		
		return("("+userId + "/" + String.copyValueOf(passWort)+")");		
	}
	
	/**
	 * Standardmethode 
	 * @param benutzer liefert das Objekt, mit dem das aktuelle Objekt verglichen werden soll.
	 */
	public boolean equals(Object benutzer) {
		return ((benutzer != null) &&
				(benutzer instanceof Benutzer) &&
				(this.userId.equals(((Benutzer)benutzer).userId)) &&
				(String.copyValueOf(this.passWort).equals(String.copyValueOf(((Benutzer)benutzer).passWort))));
		}
}
