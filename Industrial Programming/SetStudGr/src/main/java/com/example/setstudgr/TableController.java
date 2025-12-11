package com.example.setstudgr;

import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import java.io.*;
import java.util.Comparator;
import java.util.ArrayList;
import java.util.List;

public class TableController {
    @FXML private TableView<Student> mainTable;
    @FXML private TableColumn<Student, String> nameColumn;
    @FXML private TableColumn<Student, Double> gradeColumn;
    @FXML private TableColumn<Student, Integer> numColumn;
    @FXML private TableColumn<Student, String> statusColumn;

    @FXML private Button vvodButton;
    @FXML private Button otchislitButton;
    @FXML private ComboBox<String> sortComboBox;

    private ObservableList<Student> students;
    private ObservableList<Student> originalStudents;

    @FXML
    public void initialize() {
        students = FXCollections.observableArrayList();
        originalStudents = FXCollections.observableArrayList();

        initializeTableColumns();
        initializeSortComboBox();

        vvodButton.setOnAction(e -> onVvodClicked());
        otchislitButton.setOnAction(e -> onOtchislitClicked());

        sortComboBox.setOnAction(e -> applySorting());

        mainTable.setItems(students);
    }

    private void initializeTableColumns()
    {
        nameColumn.setCellValueFactory(cellData ->
                new javafx.beans.property.SimpleStringProperty(cellData.getValue().getName()));
        gradeColumn.setCellValueFactory(cellData ->
                new javafx.beans.property.SimpleDoubleProperty(cellData.getValue().getGrade()).asObject());
        numColumn.setCellValueFactory(cellData ->
                new javafx.beans.property.SimpleIntegerProperty(cellData.getValue().getNum()).asObject());
        statusColumn.setCellValueFactory(cellData ->
                new javafx.beans.property.SimpleStringProperty(
                        cellData.getValue().getGrade() >= 4.0 ? "Учится" : "На грани"
                ));

        //настройка стилей для колонки статуса
        statusColumn.setCellFactory(column -> new TableCell<Student, String>()
        {
            @Override
            protected void updateItem(String item, boolean empty)
            {
                super.updateItem(item, empty);
                if (empty || item == null)
                {
                    setText(null);
                    setStyle("");
                }
                else
                {
                    setText(item);
                    if ("Учится".equals(item))
                    {
                        setStyle("-fx-background-color: #90EE90; -fx-font-weight: bold;");
                    }
                    else
                    {
                        setStyle("-fx-background-color: #FFB6C1; -fx-font-weight: bold;");
                    }
                }
            }
        });
    }

    private void initializeSortComboBox()
    {
        ObservableList<String> sortOptions = FXCollections.observableArrayList(
                "Без сортировки",
                "По имени (А-Я)",
                "По имени (Я-А)",
                "По группе (возрастание)",
                "По группе (убывание)",
                "По оценке (возрастание)",
                "По оценке (убывание)",
                "По группе и имени",
                "По группе и оценке",
                "По оценке и группе",
                "По статусу и имени"
        );
        sortComboBox.setItems(sortOptions);
        sortComboBox.setValue("Без сортировки");
    }

    private void applySorting()
    {
        String selectedSort = sortComboBox.getValue();
        if (selectedSort == null) return;

        switch (selectedSort)
        {
            case "Без сортировки":
                students.setAll(originalStudents);
                break;

            case "По имени (А-Я)":
                students.sort(Comparator.comparing(Student::getName));
                break;

            case "По имени (Я-А)":
                students.sort(Comparator.comparing(Student::getName).reversed());
                break;

            case "По группе (возрастание)":
                students.sort(Comparator.comparingInt(Student::getNum));
                break;

            case "По группе (убывание)":
                students.sort(Comparator.comparingInt(Student::getNum).reversed());
                break;

            case "По оценке (возрастание)":
                students.sort(Comparator.comparingDouble(Student::getGrade));
                break;

            case "По оценке (убывание)":
                students.sort(Comparator.comparingDouble(Student::getGrade).reversed());
                break;

            case "По группе и имени":
                students.sort(Comparator.comparingInt(Student::getNum)
                        .thenComparing(Student::getName));
                break;

            case "По группе и оценке":
                students.sort(Comparator.comparingInt(Student::getNum)
                        .thenComparingDouble(Student::getGrade).reversed());
                break;

            case "По оценке и группе":
                students.sort(Comparator.comparingDouble(Student::getGrade).reversed()
                        .thenComparingInt(Student::getNum));
                break;

            case "По статусу и имени":
                students.sort((s1, s2) ->
                {
                    String status1 = s1.getGrade() >= 4.0 ? "Учится" : "На грани";
                    String status2 = s2.getGrade() >= 4.0 ? "Учится" : "На грани";
                    int statusCompare = status1.compareTo(status2);
                    if (statusCompare != 0) return statusCompare;
                    return s1.getName().compareTo(s2.getName());
                });
                break;
        }
    }

    @FXML
    private void onVvodClicked()
    {
        List<Student> loadedStudents = loadFromFile("input1.txt");
        originalStudents.setAll(loadedStudents);
        students.setAll(loadedStudents);
        applySorting();
        showAlert("Данные загружены", "Успешно загружено " + loadedStudents.size() + " студентов");
    }

    @FXML
    private void onOtchislitClicked()
    {
        students.clear();
        originalStudents.clear();
        showAlert("Таблица очищена", "Все студенты успешно отчислены!");
    }

    private List<Student> loadFromFile(String filename)
    {
        List<Student> students = new ArrayList<>();
        try (BufferedReader reader = new BufferedReader(new FileReader(filename)))
        {
            String line;
            while ((line = reader.readLine()) != null)
            {
                String[] parts = line.split("\\s+");
                if (parts.length >= 3)
                {
                    try
                    {
                        String name = parts[0];
                        double grade = Double.parseDouble(parts[1]);
                        int num = Integer.parseInt(parts[2]);
                        students.add(new Student(name, grade, num));
                    }
                    catch (NumberFormatException e)
                    {
                        System.err.println("Ошибка формата данных в строке: " + line);
                    }
                }
            }
        } catch (IOException e)
        {
            //файл не найден, создаем демо-данные
            System.err.println("Файл не найден, создаем демо-данные");
            students = createDemoData();
        }
        return students;
    }

    private List<Student> createDemoData()
    {
        List<Student> demoStudents = new ArrayList<>();
        demoStudents.add(new Student("Иванов Иван", 4.5, 1));
        demoStudents.add(new Student("Петров Петр", 3.2, 2));
        demoStudents.add(new Student("Сидорова Анна", 4.8, 1));
        demoStudents.add(new Student("Кузнецов Алексей", 2.9, 3));
        demoStudents.add(new Student("Смирнова Мария", 4.1, 2));
        demoStudents.add(new Student("Васильев Дмитрий", 3.7, 1));
        demoStudents.add(new Student("Николаева Елена", 4.9, 3));
        demoStudents.add(new Student("Орлов Сергей", 3.0, 2));
        return demoStudents;
    }

    private void showAlert(String title, String message)
    {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }
}