import java.io.*;
import java.text.*;
import java.util.Scanner;
import java.util.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

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

            System.out.println("vvod massiva: ");
            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    M[i][j] = cin.nextInt();
                }
            }

            List<Integer> nums = new ArrayList<>();
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    nums.add(M[i][j]);
                }
            }

            Collections.sort(nums, Collections.reverseOrder());

            int res = -1;
            for (int i = 0; i < nums.size(); i++)
            {
                int temp = nums.get(i);
                int count = 0;

                for (int j = 0; j < nums.size(); j++)
                {
                    if (nums.get(j) == temp)
                    {
                        count++;
                    }
                }
                if (count == 2)
                {
                    res = temp;
                    break;
                }
            }
            if (res != -1)
            {
                System.out.println("otvet: " + res);
            }
            else
            {
                System.out.println("nyama");
            }
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