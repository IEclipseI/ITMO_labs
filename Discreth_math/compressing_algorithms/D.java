import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
import javafx.util.Pair;
public class D {
    public static void main(String[] args) throws IOException {
        //FastScanner in = new FastScanner(new File("huffman.in"));
        BufferedReader in = new BufferedReader(new FileReader("lzw.in"));
        PrintWriter out = new PrintWriter(new File("lzw.out"));
        int counter = 26;
        Map<String, Integer> dict = new TreeMap<String, Integer>();
        for (int i = 0; i < 26; i++) {
            dict.put(String.valueOf((char)(i + (int)'a')), i);
        }
        //System.out.println(dict);
        int ch = in.read();
        String tmp = "";
        while (true) {
            tmp = "" + (char)ch; 
            while (dict.containsKey(tmp)) {
                ch = in.read();
                if (ch < (int)'a' || ch > (int)'z') {
                    out.println(dict.get(tmp));
                    out.close();
                    return;
                }
                tmp = tmp + (char)ch;
            }
            out.print(dict.get(tmp.substring(0, tmp.length() -1)) + " ");
            dict.put(tmp, counter++);
        }
                 
        //out.close();            

    }
}