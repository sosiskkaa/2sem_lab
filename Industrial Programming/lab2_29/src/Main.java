import java.io.*;
import java.text.*;
import java.util.Scanner;
import java.util.*;

public class Main
{
    public static void main(String[] args)
    {
        try
        {
            Scanner cin = new Scanner(System.in);

            System.out.print("vvod razmera: ");
            int n = cin.nextInt();
            int m = cin.nextInt();

            int[][] M = new int[n][m];

            System.out.println("vvod massiva: ");
            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < m; j++)
                {
                    M[i][j] = cin.nextInt();
                }
            }

            for(int i = 0; i < m; i++)
            {
                for(int j = 0; j < m - i - 1; j++)
                {
                    if(M[0][j] > M[0][j + 1])
                    {
                        swapst(M, n, j);
                    }
                }
            }

            printMatr(M, n, m);
        }
        catch (Exception e)
        {
            System.out.println("error!");
        }
    }
    public static void printMatr(int[][] M, int n, int m)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                System.out.print(M[i][j] + " ");
            }
            System.out.println();
        }
    }
    public static void swapst(int[][] M, int n, int j)
    {
        for(int i = 0; i < n; i++)
        {
            int temp = M[i][j];
            M[i][j] = M[i][j + 1];
            M[i][j + 1] = temp;
        }
    }
}