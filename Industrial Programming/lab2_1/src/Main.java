import java.io.*;
import java.text.*;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        try
        {
            Scanner cin = new Scanner(System.in);

            System.out.print("vvod razmera: ");
            int n = cin.nextInt();

            int[][] M = new int[n][n];
            int min = 0;
            int max = 0;
            int mini = 0;
            int maxi = 0;

            System.out.println("vvod massiva: ");
            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    M[i][j] = cin.nextInt();
                    if(M[i][j] > max)
                    {
                        max = M[i][j];
                        maxi = i;
                    }
                    if(M[i][j] < min)
                    {
                        min = M[i][j];
                        mini = i;
                    }
                }
                if(M[i][i] == 0)
                {
                    System.out.print(maxi + " stroka, element = ");
                    System.out.println(max);
                }
            }

            printMatr(M, n);

            int temp = 0;
            if(mini != maxi)
            {
                for(int j = 0; j < n; j++)
                {
                    temp = M[mini][j];
                    M[mini][j] = M[maxi][j];
                    M[maxi][j] = temp;
                }
            }

            printMatr(M, n);
        }
        catch (Exception e)
        {
            System.out.println("error!");
        }
    }
    public static void printMatr(int[][] M, int n)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                System.out.print(M[i][j] + " ");
            }
            System.out.println();
        }
    }
}