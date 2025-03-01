package aufgabe1;

import java.io.*;
import java.util.Vector;

import aufgabe1.Benutzer;

/**
 * Diese Klasse definiert die grundlegende Struktur der BenutzerVerwaltungAdmins aufgrund des Interfaces BenutzerVerwaltung. 
 * Aufgabe c) des Praktikums.
 * 
 * @author Maher
 * @version 1.0
 * 
 * @see BenutzerVerwaltung
 */
public class BenutzerVerwaltungAdmin implements BenutzerVerwaltung, Serializable {

	/**
	 * Attribut zur Speicherung der Daten 
	 */
	private Vector<Benutzer> datenhaltung;
	
	/**
	 * Attribut zur Speicherung des Dateinamens für die Persistenz
	 */
	private String filename = "default";
	
	/**
	 * Default-Konstrukter der speicher alloziiert und die Datenhaltung serealisiert
	 */
	public BenutzerVerwaltungAdmin(String filename) {
		this.filename = filename;
		dbInitialisieren();
	}
	public BenutzerVerwaltungAdmin() {
		dbInitialisieren();
	}
	
	/**
	 * Methode zum erstellen einer neuen leeren Datenhaltung
	 */
	/**
	private void dbInitialisieren() {
		datenhaltung = new Vector<Benutzer>();
		dbSchreiben();
	}
	*/
	public void dbInitialisieren() {
    try {

        File f = new File(filename);
        datenhaltung = new Vector<Benutzer>();
        if(f.exists()) {
            FileInputStream fs = new FileInputStream(filename);
            ObjectInputStream is = new ObjectInputStream(fs);
            datenhaltung = (Vector<Benutzer>) is.readObject();
            is.close();
        }
        
        dbSchreiben();
        
    		} catch (IOException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
	
	
	public void dbReset() {
		datenhaltung = new Vector<Benutzer>();
		dbSchreiben();
	}
	/**
	 * Laden der Datenhaltung, wenn Datei "db" schon exestiert, sonst wird neue erstellt
	 */
	private void dbLesen() {
		this.dbLesen(this.filename);
	}
	private void dbLesen(String filename) {
		try {
			ObjectInputStream in = new ObjectInputStream(new FileInputStream(filename));
			datenhaltung = (Vector<Benutzer>)in.readObject();
			//System.out.println("Lesen:" + datenhaltung);
			in.close();
		} catch (ClassNotFoundException e) {	// Sollte eine Klasse nicht vorhanden sein
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * Schreiben der Datenhaltung in Datei "db"
	 */
	private void dbSchreiben() {
		this.dbSchreiben(this.filename);
	}	
	private void dbSchreiben(String filename) {
		try {
			ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(filename));
			out.writeObject(datenhaltung);
			//System.out.println("Schreiben:" + datenhaltung);
			out.close();
		} catch (IOException e) {}
	}	
	
	public void dbLaden(String filename) {
		this.dbLesen(filename);
	}
	public void dbSpeichern(String filename) {
		this.dbSchreiben(filename);
	}
	public void dbSpeichern() {
		this.dbSchreiben();
	}
	
	/**
	 * Private-Mehtode
	 * 	Prüft, ob bereits eine UserID in der Datenhaltung vorhanden ist	
	 *  
	 * @param userId liefert die zu prüfende UserID
	 * @return true, falls UserID bereits vorhaden
	 * 				 false, sonst
	 */
	private boolean findUserId(String userId) {
		boolean result = false;
		
		for(int i = 0; i < datenhaltung.size(); ++i) {
			if(datenhaltung.elementAt(i).userId.equals(userId)) {
				result = true;
				break;
			}
		}
		
		return result;
	}
	
	/**
	 * Public-Methode des Interfaces 
	 * 	Das Parameterobjekt wird in die Datenhaltung eingetragen
	 * 
	 * @param benutzer liefert das Objekt, das eingetragen werden soll
	 */
	@Override
	public void benutzerEintragen(Benutzer benutzer) throws VorhandenException {
		dbLesen();
		
		// Exception, falls die einzutragende UserID bereits vorhanden ist
		if(findUserId(benutzer.userId))
			throw new VorhandenException("Einzutragende UserID bereits vorhanden!");
		else { 
			datenhaltung.addElement(benutzer);
			dbSchreiben();
		}	
	}
	
	/**
	 * Public-Methode des Interfaces 
	 * 	Prüft, ob ein Benutzer in der Datenhaltung vorhanden ist
	 * 
	 * @param benutzer liefert das Objekt, das geprüft werden soll
	 * @return true, wenn Objekt in der Datenhaltung vorhanden
	 * 				 false, sonst
	 */
	@Override
	public boolean benutzerOk(Benutzer benutzer) throws IstLeerException{
		dbLesen();
		
		// Exception, falls Datenhaltung leer ist
		if (datenhaltung.isEmpty())
			throw new IstLeerException("Datenhaltung ist leer! asdsadasd");

		return datenhaltung.contains(benutzer);
	}
	
	/**
	 * Friendly-Methode 
	 * 	Löschen eines Benutzers aus der Datenhaltung
	 * @param benutzer liefert das Objekt, das aus der Datenhaltung gelöscht werden soll
	 */
	public void benutzerLoeschen(Benutzer benutzer) throws IstLeerException, NichtVorhandenException {
		dbLesen();
		
		// Exception, falls Datenhaltung leer ist
		if(datenhaltung.isEmpty()) 
			throw new IstLeerException("Datenhaltung ist leer!");
		// Exception, falls der zu löschende Benutzer nicht vorhanden ist
		if(!datenhaltung.remove(benutzer)) 
			throw new NichtVorhandenException("Zu löschender Benutzer ist nicht vorhanden!");	
		else 
			dbSchreiben();
	}
	
	/**
	 * Standardmethode, um Datenhaltung darzustellen im folgenden Format:
	 * falls leer:
	 * 	"Datenhaltung ist leer"
	 * sonst:
	 * 	(userID1/passWort1)
	 * 	(userID2/passWort2)
	 * 	...
	 */
	public String toString() {
		String result = "";
		
		if (datenhaltung.isEmpty())
			result = "Datenhaltung ist leer!";
		else {
			for(int i = 0; i < datenhaltung.size(); ++i) {
				if(i != 0)
					result += "\n";
			
				result += "\t" + datenhaltung.elementAt(i).toString();
			}
		}
		return result;
	}
	
	/**
	 * Standardmethode, um 
	 * @param obj Das Object, welches mit this verglichen werden soll
	 * @return true, falls obj und this gleich sind
	 * 				 false, sonst
	 */
	public boolean equals(Object obj) {
		return (obj != null) &&
					(obj instanceof BenutzerVerwaltungAdmin) &&
					(this.toString().equals(obj.toString()));
		
	}
	
}
