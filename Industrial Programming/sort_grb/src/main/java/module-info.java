module com.example.sort_grb {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires org.kordamp.bootstrapfx.core;

    opens com.example.sort_grb to javafx.fxml;
    exports com.example.sort_grb;
}