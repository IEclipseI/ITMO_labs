import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;

public class C {
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
        BufferedReader in = new BufferedReader(new FileReader("mtf.in"));
        PrintWriter out = new PrintWriter(new File("mtf.out"));
        int[] ar = new int[26];
        for (int i = 0; i < 26; i++) {
            ar[i] = i;
        }
        int ch = in.read() - (int)'a';
        
        while (ch >= 0) {
            //System.out.println(ch);
            int j = 0;
            while (ar[j] != ch) {
                j++;
            }
            out.print(j + 1  + " ");
            for (int i = j; i > 0; i--) {
                swap(ar, i, i - 1);
            }
            ch = in.read() - (int)'a';
        }
        out.close();            
    }
}