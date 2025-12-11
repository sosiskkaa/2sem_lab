package com.example.setstudgr;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.net.URL;

public class MainApplication extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        URL fxmlUrl = getClass().getResource("/com/example/setstudgr/tabl.fxml");
        if (fxmlUrl == null) {
            throw new RuntimeException("FXML file not found!");
        }

        FXMLLoader loader = new FXMLLoader(fxmlUrl);
        Parent root = loader.load();

        primaryStage.setTitle("tabl");
        primaryStage.setScene(new Scene(root, 800, 594));
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
