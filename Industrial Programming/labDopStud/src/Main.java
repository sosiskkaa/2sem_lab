import java.util.*;
import java.io.*;

public class Main
{
    public static void main(String[] args)
    {
        try
        {
            Students students1 = new Students();
            Students students2 = new Students();

            students1.readFrFile("input1.txt");
            students2.readFrFile("input2.txt");

            // Отладочный вывод
            System.out.println("Students1: " + students1.getSize() + " записей");
            System.out.println("Students2: " + students2.getSize() + " записей");

            for (Student s : students1.getStudentsList()) {
                System.out.println("S1: " + s);
            }
            for (Student s : students2.getStudentsList()) {
                System.out.println("S2: " + s);
            }

            Students per = peresech(students1, students2);

            System.out.println("Пересечение: " + per.getSize() + " записей");

            per.sortGrName();
            per.writeToFile("output1.txt");

            Students ob = obed(students1, students2);

            System.out.println("Обьединение: " + ob.getSize() + " записей");

            ob.sortGrName();
            ob.writeToFile("output2.txt");

            Students ra = razn(students1, students2);

            System.out.println("Разность: " + ra.getSize() + " записей");

            ra.sortGrName();
            ra.writeToFile("output3.txt");

        }
        catch (IOException e)
        {
            System.out.println("Ошибка при работе с файлами: " + e.getMessage());
            e.printStackTrace();
        }
    }

    public static Students peresech(Students x, Students y)
    {
        Students res = new Students();

        x.sortId();
        y.sortId();

        int i = 0, j = 0;
        while(i < x.getSize() && j < y.getSize())
        {
            Student studentX = x.getStudentsList().get(i);
            Student studentY = y.getStudentsList().get(j);

            int comparison = studentX.compareTo(studentY);
            if(comparison == 0) // ID равны
            {
                res.getStudentsList().add(studentX);
                i++;
                j++;
            }
            else if(comparison < 0)
            {
                i++;
            }
            else
            {
                j++;
            }
        }

        return res;
    }

    public static Students obed(Students x, Students y)
    {
        Students res = new Students();

        x.sortId();
        y.sortId();

        int i = 0, j = 0;
        while(i < x.getSize() && j < y.getSize())
        {
            Student studentX = x.getStudentsList().get(i);
            Student studentY = y.getStudentsList().get(j);

            if(studentX.equals(studentY))
            {
                res.getStudentsList().add(studentX);
                i++;
                j++;
            }
            else if(studentX.compareTo(studentY) < 0)
            {
                res.getStudentsList().add(studentX);
                i++;
            }
            else
            {
                res.getStudentsList().add(studentX);
                j++;
            }
        }

        return res;
    }

    public static Students razn(Students x, Students y)
    {
        Students res = new Students();

        x.sortId();
        y.sortId();

        int i = 0, j = 0;
        while(i < x.getSize() && j < y.getSize())
        {
            Student studentX = x.getStudentsList().get(i);
            Student studentY = y.getStudentsList().get(j);

            if(studentX.equals(studentY))
            {
                i++;
                j++;
            }
            else if(studentX.compareTo(studentY) < 0)
            {
                res.getStudentsList().add(studentX);
                i++;
            }
            else
            {
                j++;
            }
        }

        return res;
    }
}