import java.util.*;
import java.io.*;
import java.text.DecimalFormat;

class Student implements Comparable<Student>
{
    private long id;
    private String name;
    private int group;
    private double grade;

    public Student(long id, String name, int group, double grade)
    {
        this.id = id;
        this.name = name;
        this.group = group;
        this.grade = grade;
    }

    public Student(Student other)
    {
        this.id = other.id;
        this.name = other.name;
        this.group = other.group;
        this.grade = other.grade;
    }

    public long getId()
    {
        return id;
    }

    public String getName()
    {
        return name;
    }

    public int getGroup()
    {
        return group;
    }

    public double getGrade()
    {
        return grade;
    }

    @Override
    public boolean equals(Object obj)
    {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Student student = (Student)obj;
        return id == student.id;
    }

    @Override
    public int hashCode()
    {
        return Objects.hash(id);
    }

    @Override
    public int compareTo(Student other)
    {
        return Long.compare(this.id, other.id);
    }

    @Override
    public String toString()
    {
        return id + " " + name + " " + group + " " + String.format("%.2f", grade);
    }
}

class Students
{
    private ArrayList<Student> studentsList;

    public Students()
    {
        studentsList = new ArrayList<>();
    }

    public void readFrFile(String filename) throws IOException
    {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename)))
        {
            String line;
            while ((line = reader.readLine()) != null)
            {
                line = line.trim();
                if (line.isEmpty()) continue;

                String[] parts = line.split("\\s+");
                if (parts.length == 6)
                {
                    try {
                        long id = Long.parseLong(parts[0]);
                        // ФИО состоит из частей 1, 2, 3
                        String name = parts[1] + " " + parts[2] + " " + parts[3];
                        int group = Integer.parseInt(parts[4]);
                        double grade = Double.parseDouble(parts[5]);

                        studentsList.add(new Student(id, name, group, grade));
                    } catch (NumberFormatException e) {
                        System.out.println("Ошибка parsing строки: " + line);
                    }
                }
                else
                {
                    System.out.println("Неверный формат строки (ожидается 6 частей): " + line);
                }
            }
        }
    }

    public void writeToFile(String filename) throws IOException
    {
        try (PrintWriter writer = new PrintWriter(new FileWriter(filename)))
        {
            for (Student student : studentsList)
            {
                writer.println(student.toString());
            }
        }
    }

    public void sortId()
    {
        Collections.sort(studentsList);
    }

    public void sortGrName()
    {
        Collections.sort(studentsList, new Comparator<Student>()
        {
            @Override
            public int compare(Student s1, Student s2)
            {
                if (s1.getGroup() != s2.getGroup())
                {
                    return Integer.compare(s1.getGroup(), s2.getGroup());
                }
                String surname1 = s1.getName().split(" ")[0];
                String surname2 = s2.getName().split(" ")[0];
                return surname1.compareTo(surname2);
            }
        });
    }

    public ArrayList<Student> getStudentsList()
    {
        return studentsList;
    }

    public int getSize()
    {
        return studentsList.size();
    }
}