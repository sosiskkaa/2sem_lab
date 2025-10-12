import java.util.*;

public class Main
{
    public static void main(String[] args)
    {
        try
        {
            Scanner cin = new Scanner(System.in);

            System.out.println("введите какую по счету букву менять: ");
            int k = cin.nextInt();
            System.out.println("введите на какие символы менять: ");
            String str = cin.next();
            cin.nextLine();

            System.out.println("введите текст, признак конца ввода текста – пустая строка: ");
            StringBuilder text0 = new StringBuilder();
            String line;

            while (!(line = cin.nextLine()).isEmpty())
            {
                text0.append(line).append("\n");
            }

            String originalText = text0.toString();
            MyString myString = new MyString(originalText);
            String result = myString.replacech(k, str);

            System.out.println("результат:");
            System.out.println(result);
        }
        catch (Exception e)
        {
            System.out.println("error!");
        }
    }
}

class MyString
{
    private String ortext;

    public MyString()
    {
        this.ortext = "";
    }

    public MyString(String text)
    {
        this.ortext = text;
    }

    public String getOrtext()
    {
        return ortext;
    }

    public void setOrtext(String text)
    {
        this.ortext = text;
    }

    public String replacech(int k, String replacement)
    {
        if (ortext == null || ortext.isEmpty())
        {
            return ortext;
        }

        String delimiters = " \t\n\r,:-.";
        StringTokenizer tokenizer = new StringTokenizer(ortext, delimiters, true);
        StringBuilder result = new StringBuilder();

        while (tokenizer.hasMoreTokens())
        {
            String token = tokenizer.nextToken();

            if (token.length() == 1 && delimiters.contains(token))
            {
                result.append(token);
            }
            else
            {
                if (token.length() >= k)
                {
                    result.append(token.substring(0, k - 1))
                            .append(replacement)
                            .append(token.substring(k));
                }
                else
                {
                    result.append(token);
                }
            }
        }

        return result.toString();
    }

    @Override
    public String toString()
    {
        return ortext;
    }
}