package com.example.ek3;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.concurrent.Task;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;
import java.util.Set;

public class ConverterApp extends Application
{
    private static final String PROPERTIES_FILE = "/rates.properties";
    private static Properties rates;
    private ComboBox<String> fromCombo;
    private ComboBox<String> toCombo;
    private TextField amountField;
    private Label resultLabel;
    private Button convertButton;

    @Override
    public void init()
    {
        rates = new Properties();
        try (InputStream is = getClass().getResourceAsStream(PROPERTIES_FILE))
        {
            if (is != null)
            {
                rates.load(is);
            }
            else
            {
                System.err.println("rates.properties не найден!");
            }
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }

    @Override
    public void start(Stage primaryStage)
    {
        primaryStage.setTitle("Конвертер валют");

        Set<String> currencies = FXCollections.observableSet();
        rates.stringPropertyNames().forEach(key ->
        {
            String[] parts = key.split("_TO_");
            if (parts.length == 2)
            {
                currencies.add(parts[0]);
                currencies.add(parts[1]);
            }
        });

        VBox root = new VBox(10);
        root.setStyle("-fx-padding: 20;");

        fromCombo = new ComboBox<>(FXCollections.observableArrayList(currencies));
        toCombo = new ComboBox<>(FXCollections.observableArrayList(currencies));
        amountField = new TextField();
        amountField.setPromptText("Введите сумму");
        convertButton = new Button("Конвертировать");
        resultLabel = new Label("Результат появится здесь");

        convertButton.setOnAction(e -> convert());

        root.getChildren().addAll(
                new Label("Из валюты:"), fromCombo,
                new Label("В валюту:"), toCombo,
                new Label("Сумма:"), amountField,
                convertButton, resultLabel
        );

        Scene scene = new Scene(root, 300, 300);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private void convert()
    {
        String from = fromCombo.getValue();
        String to = toCombo.getValue();
        if (from == null || to == null || from.equals(to))
        {
            resultLabel.setText("Выберите разные валюты!💔");
            return;
        }

        String key = from + "_TO_" + to;
        String rateStr = rates.getProperty(key);
        if (rateStr == null)
        {
            resultLabel.setText("Курс " + key + " не найден!");
            return;
        }

        try
        {
            double amount = Double.parseDouble(amountField.getText());

            Task<Double> task = new Task<>()
            {
                @Override
                protected Double call() throws Exception
                {
                    Thread.sleep(2000);
                    double rate = Double.parseDouble(rateStr);
                    return amount * rate;
                }
            };

            task.setOnSucceeded(e -> Platform.runLater(() ->
            {
                resultLabel.setText(String.format("%.2f %s = %.2f %s",
                        amount, from, task.getValue(), to));
                convertButton.setDisable(false);
            }));

            task.setOnFailed(e -> Platform.runLater(() ->
            {
                resultLabel.setText("Ошибка: " + task.getException().getMessage());
                convertButton.setDisable(false);
            }));

            convertButton.setDisable(true);
            resultLabel.setText("Конвертирую... (2 сек)");
            new Thread(task).start();

        } catch (NumberFormatException ex)
        {
            resultLabel.setText("Неверная сумма!💔");
        }
    }


    public static void main(String[] args)
    {
        launch(args);
    }
}
