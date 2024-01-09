import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.stage.Stage;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;

import javafx.scene.control.Button;
import javafx.event.ActionEvent;

import java.awt.*;
import java.net.URL;
import java.util.ResourceBundle;

public class AnwendungsController implements Initializable {

    MainApplication app ;
    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {

    }


    @FXML  Button abbrechen;

    @FXML public void closeApplication(Event event){
        System.out.println("aufwiedersehen");
        Stage stage = (Stage) abbrechen.getScene().getWindow();
        stage.close();

    }

    public void set_referenz(MainApplication main) {
        this.app = main;
    }
}