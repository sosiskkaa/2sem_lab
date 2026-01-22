module com.example.ek3 {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.ek3 to javafx.fxml;
    exports com.example.ek3;
}