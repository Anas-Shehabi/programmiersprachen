package aufgabe1;


import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

public class LoginController {

		MyApplication gui;
		private boolean neuAnmeldung = false;
	
    @FXML private TextField UserID;
    @FXML private PasswordField Passwort;
    @FXML private CheckBox check_NeuAnmeldung;
    @FXML private Button btn_Ausfuehren;
    @FXML private Label fehlermeldungLogin;
    
    @FXML
    void Button_Ausfuehren() {
    	
    	String id = UserID.getText();
    	char[] pw = Passwort.getText().toCharArray();
    	
    	if(!id.equals("") && !pw.equals("")) {
    		Benutzer benutzer = new Benutzer(id, pw);
      	System.out.println(benutzer);
      	
      	// Nicht mehr nötig
      	//Stage stage = (Stage) btn_Ausfuehren.getScene().getWindow();
      	//stage.close();
      	
      	if(neuAnmeldung == true) {
      		try {
						gui.neuAnmeldung();
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
      	}
      	else {
      		try {
						gui.benutzerLogin(benutzer);
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
      	}
    	}
    }

    @FXML
    void Check_NeuAnmeldung() {
    	neuAnmeldung = check_NeuAnmeldung.isSelected();
    	System.out.println(neuAnmeldung);
    }

    void setGui(MyApplication gui) {
      this.gui = gui;
    }

    void setFehlermeldungLoginVisible() {
    	this.fehlermeldungLogin.setVisible(true);
    }
}
