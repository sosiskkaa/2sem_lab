import java.io.*;
import java.text.*;
import java.util.Scanner;

class Rzlozh
{
    public double x;
    public double eps;
    public int k;
    public double res;
    public int iter;

    public Rzlozh()
    {
        x = 1;
        eps = 1;
        k = -1;
        res = 0;
        iter = 0;
    }

    public Rzlozh(double x, double eps)
    {
        this.x = x;
        this.eps = eps;
        this.k = -1;
        this.res = 0;
        this.iter = 0;
    }

    public Rzlozh(double x, int k)
    {
        this.x = x;
        this.k = k;
        this.eps = Math.pow(10, -k);
        this.res = 0;
        this.iter = 0;
    }

    public void calcExp()
    {
        double sum = 1.0;
        double term = 1.0;
        int n = 1;
        iter = 0;

        while (Math.abs(term) >= eps)
        {
            term = term * x / n;
            sum += term;
            n++;
            iter++;
        }

        this.res = sum;
    }

    public void calcSin()
    {
        double normx = x;
        while (normx > Math.PI)
        {
            normx -= 2 * Math.PI;
        }
        while (normx < -Math.PI)
        {
            normx += 2 * Math.PI;
        }

        double sum = 0;
        double term = normx;
        int n = 1;
        iter = 0;

        while (Math.abs(term) >= eps)
        {
            sum += term;
            n += 2;
            term = term * (-normx * normx) / ((n - 1) * n);
            iter++;
        }

        this.res = sum;
    }

    public double getStandExp()
    {
        return Math.exp(x);
    }

    public double getStandSin()
    {
        return Math.sin(x);
    }

    public double getDifExp()
    {
        return Math.abs(res - getStandExp());
    }

    public double getDifSin()
    {
        return Math.abs(res - getStandSin());
    }

    public void printResExp()
    {
        NumberFormat formatter = NumberFormat.getNumberInstance();
        formatter.setMaximumFractionDigits(this.k);

        double st = this.getStandExp();
        double dif = this.getDifExp();

        System.out.println("\nresults:");
        System.out.println("x = " + this.x);
        System.out.println("k = " + this.k);
        System.out.println("epsil = " + this.eps);
        System.out.println("iterat = " + this.iter);
        System.out.println("sum: " + formatter.format(this.res));
        System.out.println("st zn: " + formatter.format(st));
        System.out.println("razn: " + formatter.format(dif));
    }

    public void printResSin()
    {
        NumberFormat formatter = NumberFormat.getNumberInstance();
        formatter.setMaximumFractionDigits(this.k);

        double st = this.getStandSin();
        double dif = this.getDifSin();

        System.out.println("\nresults:");
        System.out.println("x = " + this.x);
        System.out.println("k = " + this.k);
        System.out.println("epsil = " + this.eps);
        System.out.println("iterat = " + this.iter);
        System.out.println("sum: " + formatter.format(this.res));
        System.out.println("st zn: " + formatter.format(st));
        System.out.println("razn: " + formatter.format(dif));
    }
}

public class Main
{
    public static void main(String[] args)
    {
        try
        {
            Scanner cin = new Scanner(System.in);

            System.out.print("vvod x: ");
            double x = cin.nextDouble();

            System.out.print("vvod k: ");
            int k = cin.nextInt();

            Rzlozh si = new Rzlozh(x, k);

            si.calcSin();
            si.printResSin();

            cin.close();
        }
        catch (Exception e)
        {
            System.out.println("error! " + e.getMessage());
        }
    }
}