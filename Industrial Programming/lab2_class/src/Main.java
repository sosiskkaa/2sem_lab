import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

class MyMat
{
    public int n;
    public int m;
    int[][] M;

    public MyMat()
    {
        this.n = 0;
        this.m = 0;
        this.M =null;
    }

    public MyMat(int n, int m)
    {
        this.n = n;
        this.m = m;

        M = new int[n][m];
    }

    public MyMat(MyMat x)
    {
        this.n = x.n;
        this.m = x.m;
        this.M = new int[n][m];

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                this.M[i][j] = x.M[i][j];
            }
        }
    }

    public void printMat(FileWriter writer) throws IOException
    {
        for(int i = 0; i < this.n; i++)
        {
            for(int j = 0; j < this.m; j++)
            {
                writer.write(this.M[i][j] + " ");
            }
            writer.write("\n");
        }
        writer.write("\n");
    }

    public void vvodMat(String filename) throws FileNotFoundException
    {
        File inp = new File(filename);
        Scanner fin = new Scanner(inp);

        this.n = fin.nextInt();
        this.m = fin.nextInt();

        this.M = new int[n][m];

        for(int i = 0; i < this.n; i++)
        {
            for(int j = 0; j < this.m; j++)
            {
                if(fin.hasNextInt())
                {
                    this.M[i][j] = fin.nextInt();
                }
            }
        }
        fin.close();
    }

    public void swapMinMaxStr(FileWriter writer) throws IOException
    {
        int min = 0;
        int max = 0;
        int mini = 0;
        int maxi = 0;

        for(int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (M[i][j] > max)
                {
                    max = M[i][j];
                    maxi = i;
                }
                if (M[i][j] < min)
                {
                    min = M[i][j];
                    mini = i;
                }
            }
        }
        if(mini != maxi)
        {
                int[]temp = M[mini];
                M[mini] = M[maxi];
                M[maxi] = temp;
        }
    }

    public void lookZero(FileWriter writer) throws IOException
    {
        if(n == m)
        {
            for(int i = 0; i < n; i++)
            {
                if(M[i][i] == 0)
                {
                    int lmax = 0;
                    for (int j = 0; j < m; j++)
                    {
                        if (M[i][j] > lmax)
                        {
                            lmax = M[i][j];
                        }
                    }
                    writer.write("naiden 0 na diagonali. " + i + "-aya stroka, element = " + lmax + "\n\n");
                }
            }
        }
        else
        {
            writer.write("matrica ne diagonal'naya\n");
        }
    }

    public int maxMax(FileWriter writer) throws IOException
    {
        List<Integer> nums = new ArrayList<>();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
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

        return res;
    }

    public void sortPoStolb(FileWriter writer) throws IOException
    {
        for(int i = 0; i < m; i++)
        {
            for(int j = 0; j < m - i - 1; j++)
            {
                if(M[0][j] > M[0][j + 1])
                {
                    swapst(j);
                }
            }
        }
    }

    private void swapst(int j)
    {
        for(int i = 0; i < n; i++)
        {
            int temp = M[i][j];
            M[i][j] = M[i][j + 1];
            M[i][j + 1] = temp;
        }
    }
}

public class Main
{
    public static void main(String[] args)
    {
        Scanner cin = new Scanner(System.in);

        MyMat M = new MyMat();
        try
        {
            M.vvodMat("input.txt");
        }
        catch (FileNotFoundException e)
        {
            System.out.println("file not found");
        }

        try
        {
            FileWriter writer = new FileWriter("output.txt");
            writer.write("ishodnaya matrica:\n");
            M.printMat(writer);
            M.swapMinMaxStr(writer);
            writer.write("matrica posle obmena strok:\n");
            M.printMat(writer);
            M.lookZero(writer);
            int res = M.maxMax(writer);
            if (res != -1)
            {
                writer.write("maximum vstrecaushiesya rovno 2 raza = " + res + "\n\n");
            }
            else
            {
                writer.write("nyama maximuma vstrecaushiesya rovno 2 raza\n\n");
            }
            M.sortPoStolb(writer);
            writer.write("otsortirovannaya po 1-im elementam stolbcov matrica:\n");
            M.printMat(writer);
            writer.close();
        }
        catch (IOException e)
        {
            System.out.println("oshibka zapisi v file");
        }
    }
}