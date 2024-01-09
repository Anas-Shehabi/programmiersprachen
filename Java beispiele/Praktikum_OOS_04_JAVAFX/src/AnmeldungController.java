import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.net.URL;
import java.util.ResourceBundle;

public class AnmeldungController  implements Initializable {

    MainApplication app;
    String defaultStyle = "";

    String green = "-fx-background-color: -fx-focus-color, -fx-text-box-border,#77f441 ;\n" +
            "    -fx-background-insets: -0.4, 1, 2;\n" +
            "    -fx-background-radius: 3.4, 2, 2;\n" +
            "    -fx-prompt-text-fill: transparent;";


    String red = "-fx-background-color: -fx-focus-color, -fx-text-box-border, #f45c42 ;\n" +
            "    -fx-background-insets: -0.4, 1, 2;\n" +
            "    -fx-background-radius: 3.4, 2, 2;\n" +
            "    -fx-prompt-text-fill: transparent;";


    @FXML
    private TextField useridfield;
    @FXML
    private PasswordField passwortfield;
    @FXML
    private PasswordField wiederholungfield;
    @FXML
    private Text text;
    private boolean passEqual = false;


    /**
     * Erstelle einen neuen Benutzer und schließe das Fenster
     *
     * @param event
     */
    @FXML
    public void buttonAction(Event event) {
        if (!useridfield.getText().isEmpty() && reactionsOnField(event)) {
            Benutzer benutzer = new Benutzer(useridfield.getText(), passwortfield.getText().toCharArray());
            try {
                app.neuerBenutzer(benutzer);
            } catch (NutzerIstBereitVorhanden ex) {
                System.err.println("Der Benutzer existiert bereits");
            }
        } else {
            text.setText("“Passwort != Wiederholung”");
        }

    }

    /**
     * Für die Überprüfung der Passwörter
     *
     * @param event
     */

    @FXML public boolean reactionsOnField(Event event){
        if(wiederholungfield.getText().isEmpty() && passwortfield.getText().isEmpty()){
            wiederholungfield.setStyle(defaultStyle);
            passEqual = false;
        }else if(wiederholungfield.getText().equals(passwortfield.getText())){
            wiederholungfield.setStyle(green);
            passwortfield.setStyle(green);
            passEqual = true;
        }else{
            wiederholungfield.setStyle(red);
            passEqual = false;
        }

        return passEqual;
    }


    public void set_referenz(MainApplication main) {
        this.app = main;
    }


    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }

}


