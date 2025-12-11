package com.example.setstudgr;

import java.io.Serializable;
import java.util.Objects;

public class Student implements Comparable<Student>, Serializable
{
    private String name;
    private double grade;
    private int num;

    public Student()
    {
        this.name = "";
        this.grade = 0.0;
        this.num = 0;
    }

    public Student(String name, double grade, int num)
    {
        this.name = name;
        this.grade = grade;
        this.num = num;
    }

    public Student(Student other)
    {
        this.name = other.name;
        this.grade = other.grade;
        this.num = other.num;
    }

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }

    public double getGrade() { return grade; }
    public void setGrade(double grade) { this.grade = grade; }

    public int getNum() { return num; }
    public void setNum(int num) { this.num = num; }

    @Override
    public boolean equals(Object o)
    {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Student student = (Student) o;
        return Double.compare(student.grade, grade) == 0 &&
                num == student.num &&
                Objects.equals(name, student.name);
    }

    @Override
    public int hashCode()
    {
        return Objects.hash(name, grade, num);
    }

    @Override
    public int compareTo(Student other)
    {
        if (this.num != other.num)
        {
            return Integer.compare(this.num, other.num);
        }
        return this.name.compareTo(other.name);
    }

    @Override
    public String toString()
    {
        return String.format("Student{name='%s', grade=%.2f, num=%d}", name, grade, num);
    }
}