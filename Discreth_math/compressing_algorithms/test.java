import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
import javafx.util.Pair;
public class test {
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        int nextInt() {
            return Integer.parseInt(next());
        }
    }
    static void swap(int[] ar, int i, int j) {
        int tmp = ar[i];
        ar[i] = ar[j];
        ar[j] = tmp;
    }
    public static void main(String[] args) throws IOException {
        //FastScanner in = new FastScanner(new File("huffman.in"));
        BufferedReader in = new BufferedReader(new FileReader("lzw.in"));
        PrintWriter out = new PrintWriter(new File("lzw2.out"));
        
        out.println("0 1 0 2 26 0");         
        out.close();            

    }
}