import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;

public class B {
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

    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("bwt.in"));
        PrintWriter out = new PrintWriter(new File("bwt.out"));
        String tmp = in.next();
        int n = tmp.length();
        String[] strs = new String[n];
        strs[0] = tmp;
        for (int i = 1; i < n; i++) {
            strs[i] = tmp.substring(i, n) + tmp.substring(0, i);
        }
        //System.out.println(strs);
        Arrays.sort(strs);
        int k = n - 1;
        for (int i = 0; i < n; i++) {
            out.print(strs[i].charAt(k));
        }
        out.close();            
    }
}