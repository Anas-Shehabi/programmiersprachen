package aufgabe1;

/**
 * Dieses Interface definiert die zu implementierenden Methoden des BenutzerVerwaltungsAdmins
 * Aufgabe b) des Praktikums
 * 
 * @author Maher
 * @version 1.0
 */
public interface BenutzerVerwaltung {
	
	/**
	 * Public-Methode
	 * 	Das Parameterobjekt wird in die Datenhaltung eingetragen
	 * 
	 * @param benutzer liefert das Objekt, das eingetragen werden soll
	 */
	public void benutzerEintragen(Benutzer benutzer) throws VorhandenException;
	/**
	 * Public-Methode
	 * 	Prüft, ob ein Benutzer in der Datenhaltung vorhanden ist
	 * 
	 * @param benutzer liefert das Objekt, das geprüft werden soll
	 * @return true, wenn Objekt in der Datenhaltung vorhanden
	 * 				 false, sonst
	 */
	public boolean benutzerOk(Benutzer benutzer) throws IstLeerException;
	
}
