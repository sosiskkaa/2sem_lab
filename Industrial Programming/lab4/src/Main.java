public class Main
{
    public static void main(String[] args)
    {
        GradeBook.readData("input.txt");
        GradeBook.showAll("output.txt");
        GradeBook.writeExelStud("output.txt");
        GradeBook.writeStudIm("output.txt");
        GradeBook.writeSessionAverage("output.txt");
        GradeBook.writeOverallAverage("output.txt");

        GradeBook.closeScanner();
    }
}