package aufgabe1;

import java.awt.event.ActionEvent;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

public class AnmeldungsController {

	MyApplication gui;
	
  @FXML private TextField Anmeldung_UserID;
  @FXML private PasswordField Anmeldung_Passwort;
  @FXML private Button btn_Ausfuehren_Anmeldung;
  @FXML private PasswordField Anmeldung_Passwort_wdh;
  @FXML private Label fehlermeldung;
  @FXML private Label fehlermeldungUserID;

  @FXML
  void Button_Ausfuehren_Anmeldung() {
  	String passwort = Anmeldung_Passwort.getText();
  	String passwort_wdh = Anmeldung_Passwort_wdh.getText(); 
  	
  	if(!passwort.equals(passwort_wdh)) {
  		fehlermeldung.setVisible(true);
  	}
  	else {
  		fehlermeldung.setVisible(false);
  		
  		String id = Anmeldung_UserID.getText();
    	char[] pw = passwort.toCharArray();

    	if(!id.equals("") && !pw.equals("")) {
	    	Benutzer benutzer = new Benutzer(id, pw);
	    	System.out.println(benutzer);
	    	
	    	// Nicht mehr nötig
	    	//Stage stage = (Stage) btn_Ausfuehren_Anmeldung.getScene().getWindow();
	    	//stage.close();
	    	
	    	try {
					gui.neuerBenutzer(benutzer);
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
    	}
  	}
  }
  
  void setGui(MyApplication gui) {
    this.gui = gui;
  }
  
  void setFehlermeldungUserIDVisible() {
  	this.fehlermeldungUserID.setVisible(true);
  }


}