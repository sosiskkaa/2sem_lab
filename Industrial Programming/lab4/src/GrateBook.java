import java.util.*;
import java.io.*;

class GradeBook implements Comparable<GradeBook>
{
    private String lastName;
    private String firstName;
    private String middleName;
    private int course;
    private String group;
    private List<Session> sessions;

    private static List<GradeBook> students = new ArrayList<>();
    private static Scanner scanner = new Scanner(System.in);

    public GradeBook(String lastName, String firstName, String middleName, int course, String group)
    {
        this.lastName = lastName;
        this.firstName = firstName;
        this.middleName = middleName;
        this.course = course;
        this.group = group;
        this.sessions = new ArrayList<>();
    }

    @Override
    public int compareTo(GradeBook other)
    {
        int lastNameCompare = this.lastName.compareToIgnoreCase(other.lastName);
        if (lastNameCompare != 0) return lastNameCompare;

        int firstNameCompare = this.firstName.compareToIgnoreCase(other.firstName);
        if (firstNameCompare != 0) return firstNameCompare;

        return this.middleName.compareToIgnoreCase(other.middleName);
    }

    public static class GradeBookComparator implements Comparator<GradeBook>
    {
        @Override
        public int compare(GradeBook s1, GradeBook s2)
        {
            return s1.compareTo(s2);
        }
    }

    public static class AverageComparator implements Comparator<GradeBook>
    {
        @Override
        public int compare(GradeBook s1, GradeBook s2)
        {
            return Double.compare(s2.getOverallAverage(), s1.getOverallAverage());
        }
    }

    public class Session
    {
        private int num;
        private List<Exam> exams;
        private List<Test> tests;

        public Session(int num)
        {
            this.num = num;
            this.exams = new ArrayList<>();
            this.tests = new ArrayList<>();
        }

        public void addExam(String name, int grade)
        {
            exams.add(new Exam(name, grade));
        }

        public void addTest(String name, boolean passed)
        {
            tests.add(new Test(name, passed));
        }

        public int getNum()
        {
            return num;
        }

        public List<Exam> getExams()
        {
            return exams;
        }

        public List<Test> getTests()
        {
            return tests;
        }

        public double getMid()
        {
            if (exams.isEmpty())
            {
                return 0.0;
            }

            int sum = 0;
            for (Exam exam : exams)
            {
                sum += exam.getGrade();
            }
            double average = (double) sum / exams.size();
            return Math.round(average * 100.0) / 100.0;
        }
    }

    public class Exam
    {
        private String name;
        private int grade;

        public Exam(String name, int grade)
        {
            this.name = name;
            this.grade = grade;
        }

        public String getName()
        {
            return name;
        }

        public int getGrade()
        {
            return grade;
        }
    }

    public class Test
    {
        private String name;
        private boolean passed;

        public Test(String name, boolean passed)
        {
            this.name = name;
            this.passed = passed;
        }

        public String getName()
        {
            return name;
        }

        public boolean isPassed()
        {
            return passed;
        }
    }

    public Session addSession(int num)
    {
        Session session = new Session(num);
        sessions.add(session);
        return session;
    }

    public Session getSession(int num)
    {
        for (Session session : sessions)
        {
            if (session.getNum() == num)
            {
                return session;
            }
        }
        return null;
    }

    public double getOverallAverage()
    {
        if (sessions.isEmpty())
        {
            return 0.0;
        }

        int totalSum = 0;
        int totalExams = 0;

        for (Session session : sessions)
        {
            for (Exam exam : session.getExams())
            {
                totalSum += exam.getGrade();
                totalExams++;
            }
        }

        if (totalExams == 0)
        {
            return 0.0;
        }

        double average = (double) totalSum / totalExams;
        return Math.round(average * 100.0) / 100.0;
    }

    public boolean isExcellent()
    {
        for (Session session : sessions)
        {
            for (Test test : session.getTests())
            {
                if (!test.isPassed())
                {
                    return false;
                }
            }

            for (Exam exam : session.getExams())
            {
                if (exam.getGrade() < 9)
                {
                    return false;
                }
            }
        }
        return true;
    }

    public List<String> getExcellentExams()
    {
        List<String> result = new ArrayList<>();
        if (isExcellent())
        {
            for (Session session : sessions)
            {
                for (Exam exam : session.getExams())
                {
                    String info = lastName + " " + firstName + " " + middleName +
                            " | Курс: " + course + " | Группа: " + group +
                            " | " + exam.getName() + ": " + exam.getGrade();
                    result.add(info);
                }
            }
        }
        return result;
    }

    public String getLastName()
    {
        return lastName;
    }

    public String getFirstName()
    {
        return firstName;
    }

    public String getMiddleName()
    {
        return middleName;
    }

    public int getCourse()
    {
        return course;
    }

    public String getGroup()
    {
        return group;
    }

    public List<Session> getSessions()
    {
        return sessions;
    }

    @Override
    public String toString()
    {
        return String.format("%s %s %s, курс: %d, группа: %s",
                lastName, firstName, middleName, course, group);
    }

    public static void readData(String filename)
    {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename)))
        {
            String line;
            GradeBook current = null;
            Session currentSession = null;

            while ((line = reader.readLine()) != null)
            {
                line = line.trim();
                if (line.isEmpty())
                {
                    continue;
                }

                if (line.startsWith("Студент:"))
                {
                    String[] parts = line.split(":");
                    String[] info = parts[1].trim().split(" ");
                    if (info.length >= 5)
                    {
                        current = new GradeBook(info[0], info[1], info[2],
                                Integer.parseInt(info[3]), info[4]);
                        students.add(current);
                    }
                }
                else if (line.startsWith("Сессия:"))
                {
                    if (current != null)
                    {
                        int num = Integer.parseInt(line.split(":")[1].trim());
                        currentSession = current.addSession(num);
                    }
                }
                else if (line.startsWith("Экзамен:"))
                {
                    if (currentSession != null)
                    {
                        String[] parts = line.split(":");
                        String[] examInfo = parts[1].trim().split(" ");
                        if (examInfo.length >= 2)
                        {
                            String name = examInfo[0];
                            int grade = Integer.parseInt(examInfo[1]);
                            currentSession.addExam(name, grade);
                        }
                    }
                }
                else if (line.startsWith("Зачет:"))
                {
                    if (currentSession != null)
                    {
                        String[] parts = line.split(":");
                        String[] testInfo = parts[1].trim().split(" ");
                        if (testInfo.length >= 2)
                        {
                            String name = testInfo[0];
                            boolean passed = testInfo[1].equalsIgnoreCase("сдан");
                            currentSession.addTest(name, passed);
                        }
                    }
                }
            }

            Collections.sort(students, new GradeBookComparator());
        }
        catch (IOException e)
        {
            System.err.println("Ошибка чтения: " + e.getMessage());
        }
        catch (NumberFormatException e)
        {
            System.err.println("Ошибка числа: " + e.getMessage());
        }
    }

    public static void writeExelStud(String filename)
    {
        try (PrintWriter writer = new PrintWriter(new FileWriter(filename, true)))
        {
            writer.println("СТУДЕНТЫ-ОТЛИЧНИКИ");

            int count = 0;
            for (GradeBook student : students)
            {
                if (student.isExcellent())
                {
                    count++;
                    writer.println("ФИО: " + student.getLastName() + " " +
                            student.getFirstName() + " " + student.getMiddleName());
                    writer.println("Курс: " + student.getCourse());
                    writer.println("Группа: " + student.getGroup());
                    writer.println("Экзамены:");

                    for (Session session : student.getSessions())
                    {
                        writer.println("    Сессия " + session.getNum() + ":");
                        for (Exam exam : session.getExams())
                        {
                            writer.println("        " + exam.getName() + ": " + exam.getGrade());
                        }
                        writer.println("  Средний балл за сессию: " + session.getMid());
                    }
                    writer.println();
                }
            }
            writer.println("Всего отличников: " + count);
        }
        catch (IOException e)
        {
            System.err.println("Ошибка записи: " + e.getMessage());
        }
    }

    public static void showAll(String filename)
    {
        try (PrintWriter writer = new PrintWriter(new FileWriter(filename)))
        {
            writer.println("Все студенты:");
            for (GradeBook student : students)
            {
                writer.println(student);
                for (Session session : student.getSessions())
                {
                    writer.println("  Сессия " + session.getNum() + ":");
                    writer.println("    Экзамены:");
                    for (Exam exam : session.getExams())
                    {
                        writer.println("      " + exam.getName() + ": " + exam.getGrade());
                    }
                    writer.println("    Средний балл:" + session.getMid());
                    writer.println("    Зачеты:");
                    for (Test test : session.getTests())
                    {
                        writer.println("      " + test.getName() + ": " +
                                (test.isPassed() ? "сдан" : "не сдан"));
                    }
                }
                writer.println("Отличник: " + (student.isExcellent() ? "ДА" : "НЕТ"));
                writer.println("Общий средний балл: " + student.getOverallAverage());
                writer.println();
            }
        }
        catch (IOException e)
        {
            System.err.println("Ошибка записи: " + e.getMessage());
        }
    }

    public static GradeBook findStudentBinary(String lastName, String firstName, String middleName)
    {
        GradeBook searchKey = new GradeBook(lastName, firstName, middleName, 0, "");
        int index = Collections.binarySearch(students, searchKey, new GradeBookComparator());

        if (index >= 0)
        {
            return students.get(index);
        }
        return null;
    }

    public static void writeStudIm(String filename)
    {
        try (PrintWriter writer = new PrintWriter(new FileWriter(filename, true)))
        {
            writer.println("\nСПИСОК СТУДЕНТОВ");

            List<GradeBook> sortedByAverage = new ArrayList<>(students);
            sortedByAverage.sort(new AverageComparator());

            for (int i = 0; i < sortedByAverage.size(); i++)
            {
                GradeBook student = sortedByAverage.get(i);
                writer.println((i + 1) + ". " + student.getLastName() + " " +
                        student.getFirstName() + " " + student.getMiddleName() +
                        " - Средний балл: " + student.getOverallAverage());
            }
        }
        catch (IOException e)
        {
            System.err.println("Ошибка записи: " + e.getMessage());
        }
    }

    public static void writeSessionAverage(String filename)
    {
        try (PrintWriter writer = new PrintWriter(new FileWriter(filename, true)))
        {
            writer.println("\nЗАПРОС СРЕДНЕГО БАЛЛА ЗА СЕССИЮ");

            System.out.print("Введите фамилию студента, для запроса среднего балла за сессию: ");
            String lastName = scanner.nextLine();
            System.out.print("Введите имя студента: ");
            String firstName = scanner.nextLine();
            System.out.print("Введите отчество студента: ");
            String middleName = scanner.nextLine();
            System.out.print("Введите номер сессии: ");
            int sessionNum = scanner.nextInt();
            scanner.nextLine();

            GradeBook student = findStudentBinary(lastName, firstName, middleName);
            if (student == null)
            {
                writer.println("Студент не найден!");
                return;
            }

            Session session = student.getSession(sessionNum);
            if (session == null)
            {
                writer.println("Сессия " + sessionNum + " не найдена у студента " +
                        lastName + " " + firstName + " " + middleName);
                return;
            }

            writer.println("Студент: " + lastName + " " + firstName + " " + middleName);
            writer.println("Средний балл за сессию " + sessionNum + ": " + session.getMid());
        }
        catch (IOException e)
        {
            System.err.println("Ошибка записи: " + e.getMessage());
        }
    }

    public static void writeOverallAverage(String filename)
    {
        try (PrintWriter writer = new PrintWriter(new FileWriter(filename, true)))
        {
            writer.println("\nЗАПРОС ОБЩЕГО СРЕДНЕГО БАЛЛА");

            System.out.print("Введите фамилию студента, для запроса среднего балла: ");
            String lastName = scanner.nextLine();
            System.out.print("Введите имя студента: ");
            String firstName = scanner.nextLine();
            System.out.print("Введите отчество студента: ");
            String middleName = scanner.nextLine();

            GradeBook student = findStudentBinary(lastName, firstName, middleName);
            if (student == null)
            {
                writer.println("Студент не найден!");
                return;
            }

            writer.println("Студент: " + lastName + " " + firstName + " " + middleName);
            writer.println("Общий средний балл: " + student.getOverallAverage());
        }
        catch (IOException e)
        {
            System.err.println("Ошибка записи: " + e.getMessage());
        }
    }

    public static void closeScanner()
    {
        scanner.close();
    }
}