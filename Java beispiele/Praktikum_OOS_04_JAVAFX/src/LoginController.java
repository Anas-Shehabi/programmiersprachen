import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;



public class LoginController implements Initializable {


    private MainApplication app;
  //  private final boolean neu_anmeldung = false;


    @FXML private PasswordField passWord;
    @FXML private Button ausführenBu;
    @FXML private TextField userid;
    @FXML private CheckBox neuAnmeldungcheck;


    @FXML public void neuAnmeldungAction(Event event) throws IOException {
        if( neuAnmeldungcheck.isSelected())
            app.neuAnmeldung();}

   // @FXML public void neuAnmeldungAction(Event event){
      //  boolean neuAnmeldung = false;
     //
     //   System.out.println("Neu- Anmeldung: "+ neuAnmeldung);


    @FXML public void doLogInAction(Event event){

        String user = userid.getText();
        String pass = passWord.getText();



        if(user.isEmpty() || pass.isEmpty()){
            System.out.println("Benutzername oder Passwort nicht eingetragen");
        }else
            {

            Benutzer benutzer = new Benutzer(user,pass.toCharArray());
                if(app.benutzerLogin(benutzer)){
                    System.out.println("LogIn erfolgreich.");
                }else{
                    System.err.println("LogIn fehlgeschlagen.");
                }

        }
    }

    public void set_referenz(MainApplication main){
        this.app = main;
    }

    @Override
    public void initialize(URL url, ResourceBundle rb) {

    }

}
