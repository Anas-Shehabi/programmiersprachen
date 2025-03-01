package aufgabe1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Scanner;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import javafx.scene.layout.Pane;

public class MyApplication extends Application{

    private int id = 0;

    public Stage stage;
    public BenutzerVerwaltungAdmin bv;

    @Override
    public void start(Stage primaryStage) throws Exception {

        stage = primaryStage;

        bv = new BenutzerVerwaltungAdmin();

        System.out.println("Soll die Datenhaltung initialisiert werden?");
        System.out.println("\tja(1)");
        System.out.println("\tnein(0)");
        int dbInitialisieren;
        BufferedReader din = new BufferedReader(
                new InputStreamReader(System.in));
        dbInitialisieren = Integer.parseInt(din.readLine());

        if(dbInitialisieren == 1) {
            System.out.println("Sie initialisieren Ihre Datenhaltung NICHT!.");
            bv.dbReset();
        }
        else {
            System.out.println("Sie initialisieren Ihre Datenhaltung ");

        }
        System.out.println();

        FXMLLoader loader = new FXMLLoader(getClass().getResource("login.fxml"));
        stage.setScene(new Scene((Pane)loader.load()));
        LoginController controller = loader.<LoginController>getController();
        controller.setGui(this);
        stage.show();
    }

    void neuAnmeldung() throws Exception{
        FXMLLoader loader = new FXMLLoader(getClass().getResource("anmeldung.fxml"));
        stage.setScene(new Scene((Pane)loader.load()));
        AnmeldungsController controller = loader.<AnmeldungsController>getController();
        controller.setGui(this);
        stage.show();
    }

    void neuerBenutzer(Benutzer b) throws Exception{
        try {
            bv.benutzerEintragen(b);

            FXMLLoader loader = new FXMLLoader(getClass().getResource("login.fxml"));
            stage.setScene(new Scene((Pane)loader.load()));
            LoginController controller = loader.<LoginController>getController();
            controller.setGui(this);
            stage.show();

        } catch (VorhandenException e) {
            //e.printStackTrace();

            FXMLLoader loader = new FXMLLoader(getClass().getResource("anmeldung.fxml"));
            stage.setScene(new Scene((Pane)loader.load()));
            AnmeldungsController controller = loader.<AnmeldungsController>getController();
            controller.setGui(this);
            stage.show();

            controller.setFehlermeldungUserIDVisible();
        }
    }

    void benutzerLogin(Benutzer b) throws Exception{
        try {
            if(bv.benutzerOk(b)) {

                FXMLLoader loader = new FXMLLoader(getClass().getResource("anwendung.fxml"));
                stage.setScene(new Scene((Pane)loader.load()));
                stage.show();
            }
            else {
                FXMLLoader loader = new FXMLLoader(getClass().getResource("login.fxml"));
                stage.setScene(new Scene((Pane)loader.load()));
                LoginController controller = loader.<LoginController>getController();
                controller.setGui(this);
                stage.show();

                controller.setFehlermeldungLoginVisible();
            }


        } catch (IstLeerException e) {
            //e.printStackTrace();

            FXMLLoader loader = new FXMLLoader(getClass().getResource("login.fxml"));
            stage.setScene(new Scene((Pane)loader.load()));
            LoginController controller = loader.<LoginController>getController();
            controller.setGui(this);
            stage.show();

            controller.setFehlermeldungLoginVisible();
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}
