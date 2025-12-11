module com.example.rpn_calc {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires org.kordamp.bootstrapfx.core;

    opens com.example.rpn_calc to javafx.fxml;
    exports com.example.rpn_calc;
}