package aufgabe1;


import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.stage.Stage;

public class AnwendungsController {
	
	@FXML private Button btn_Abbrechen;
	@FXML
    void Button_Abbrechen() {
    	System.out.println("Der Abbrechen-Button funktioniert");
    	
    	Stage stage = (Stage) btn_Abbrechen.getScene().getWindow();
    	stage.close();
    }

}
