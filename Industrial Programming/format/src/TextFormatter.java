import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Queue;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.BufferedReader;

public class TextFormatter
{
    private static ArrayList<String> Compute(Queue<String> words, int width, boolean paragraphStart)
    {
        ArrayList<String> res = new ArrayList<>();
        Queue<String> to_add = new ArrayDeque<>();

        while(!words.isEmpty())
        {
            int whitespaces = 0;
            int word_width = 0;
            String str_to_add = "";

            if(paragraphStart)
            {
                str_to_add = "    ";
                word_width = 4;
                paragraphStart = false;
            }

            if(words.peek().length() >= width - word_width)
            {
                str_to_add += words.remove();
            }
            else
            {
                word_width += words.peek().length();
                to_add.add(words.remove());

                while(!words.isEmpty() && words.peek().length() + word_width + whitespaces + 1 <= width)
                {
                    word_width += words.peek().length();
                    to_add.add(words.remove());
                    whitespaces++;
                }

                if(to_add.size() == 1)
                {
                    str_to_add += to_add.remove();
                }
                else
                {
                    if(words.isEmpty())
                    {
                        while(!to_add.isEmpty())
                        {
                            str_to_add += to_add.remove();
                            if(!to_add.isEmpty())
                            {
                                str_to_add += " ";
                            }
                        }
                    }
                    else
                    {
                        whitespaces += width - word_width - whitespaces;
                        int word_count = to_add.size();
                        int whitespace_index = 0;
                        int left_whitespaces = whitespaces % (word_count - 1);

                        String[] whitespace_array = new String[word_count - 1];
                        for(int i = 0; i < word_count - 1; i++)
                        {
                            whitespace_array[i] = " ".repeat(whitespaces / (word_count - 1));
                        }

                        int left = 0;
                        int right = word_count - 2;
                        while(left_whitespaces != 0)
                        {
                            whitespace_array[left] += " ";
                            left++;
                            left_whitespaces--;
                            if(left_whitespaces == 0) break;
                            whitespace_array[right] += " ";
                            right--;
                            left_whitespaces--;
                        }

                        while(to_add.size() != 1)
                        {
                            str_to_add += to_add.remove();
                            str_to_add += whitespace_array[whitespace_index];
                            whitespace_index++;
                        }
                        str_to_add += to_add.remove();
                    }
                }
            }
            str_to_add += '\n';
            res.add(str_to_add);
        }
        return res;
    }

    public static ArrayList<String> Format(File input_file, int width)
    {
        ArrayList<String> result = new ArrayList<>();
        ArrayList<String> currentParagraph = new ArrayList<>();

        try(BufferedReader in = new BufferedReader(new FileReader(input_file)))
        {
            String line;
            while((line = in.readLine()) != null)
            {
                if(line.startsWith("    "))
                {
                    if(!currentParagraph.isEmpty())
                    {
                        result.addAll(Compute(new ArrayDeque<>(currentParagraph), width, true));
                        currentParagraph.clear();
                    }
                }

                String[] words = line.trim().split("\\s+");
                for(String w : words)
                {
                    if(!w.isEmpty())
                    {
                        currentParagraph.add(w);
                    }
                }
            }

            if(!currentParagraph.isEmpty())
            {
                result.addAll(Compute(new ArrayDeque<>(currentParagraph), width, true));
            }
        }
        catch(IOException e)
        {
            System.err.println(e.toString());
        }

        return result;
    }

    public static void Format(File input_file, File output_file, int width)
    {
        ArrayList<String> computed = Format(input_file, width);
        try(PrintWriter wrtr = new PrintWriter(new FileWriter(output_file)))
        {
            for(String str : computed)
            {
                wrtr.print(str);
            }
        }
        catch(IOException e)
        {
            System.err.println(e.toString());
        }
    }
}
