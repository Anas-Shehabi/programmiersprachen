
/**
 *
 * @author Anas Shehabi
 * @version 1.0
 */
import javafx.application.Application;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MainApplication  extends Application {



    Stage primaryStage;
    BenutzerVerwaltungAdmin admin;

    String anmeldung = "Login.fxml";
    String registrierung = "anmeldung.fxml";
    String anwendung = "anwendung.fxml";



    @Override
    public void start(Stage stage) throws Exception {

        primaryStage = stage;
        admin = new BenutzerVerwaltungAdmin();



        System.out.println("Wollen Sie die Datenhaltung initialisieren? ja:0 ,nein:1");

        BufferedReader din = new BufferedReader(new InputStreamReader(System.in));
        int dbInitialisieren = Integer.parseInt(din.readLine());

        if(dbInitialisieren == 0){
            admin.dbInit();
            System.out.println("Datenhaltung wurde initialisiert.");

        }else if(dbInitialisieren == 1){
            admin.clearDb();
            System.err.println("Datenhaltung wird nicht initialisiert.");
        }

        ladeFenster(anmeldung);
        primaryStage.show();


    }

    private void ladeFenster(String myWindow) throws IOException {

        FXMLLoader loader = new FXMLLoader(getClass().getResource(myWindow));
        Parent root = loader.load();

        if(myWindow.equals(anmeldung)){
            LoginController log_con = loader.getController();//getController Gibt den Controller zurück, der dem Stammobjekt zugeordnet ist
            log_con.set_referenz(this);
            primaryStage.setTitle("LogIn");

        }else if(myWindow.equals(registrierung)){
            AnmeldungController reg_con = loader.getController();
            reg_con.set_referenz(this);
            primaryStage.setTitle("Registrierung");
        }else if(myWindow.equals(anwendung)){
            AnwendungsController anw_con = loader.getController();
            anw_con.set_referenz(this);
            primaryStage.setTitle("Anwendung");
        }



        Scene scene = new Scene(root);
        primaryStage.setScene(scene);
        primaryStage.setResizable(false);
        primaryStage.centerOnScreen();


    }


    void neuAnmeldung() throws IOException{


        //Fenster für die Registrierung laden.
        ladeFenster(registrierung);
        primaryStage.show();

    }

    /**
     * Ein neuer Benutzer erstellt, wenn der Benutzer vorher
     * nicht existiert.
     * @param benutzer
     */
    void neuerBenutzer(Benutzer benutzer) throws NutzerIstBereitVorhanden{

        try {
            admin.benutzerEintragen(benutzer);
        } catch (IOException ex) {
            System.err.println("Fehler in der Datenhaltung.");
        }

        try {
            ladeFenster(anmeldung);
        } catch (IOException ex) {
            System.err.println("Fehler in der Datenhaltung.");
        }
        primaryStage.show();

    }

    /**
     * Wenn der
     * @param benutzer
     */
  @FXML boolean benutzerLogin(Benutzer benutzer) {


      try {

            if(admin.benutzer_ist_OK(benutzer)){

                ladeFenster(anwendung);
                primaryStage.show();
                System.out.println("LogIn erfolgreich.");
                return true;
            }

        } catch (IOException ex) {
            System.err.println("Fehler beim Zugriff auf die Datenhaltung.");
            System.err.println("LogIn fehlgeschlagen.");
        }
        return false;
    }



    public static void main(String[] args){
        launch(args);
    }
}
