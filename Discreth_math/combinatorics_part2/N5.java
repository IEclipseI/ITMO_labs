import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
 
public class N5 {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("telemetry.in"));
        PrintWriter out = new PrintWriter(new File("telemetry.out"));
        int n = in.nextInt();
        int k = in.nextInt();
        int size = (int)Math.pow(k, n);
        String[] ar = new String[size];
        for (int j = 0; j < k; j++) {
            ar[j] = Integer.toString(j);
        }
        for (int i = 2; i <= n; i++) {
            int count = (int)Math.pow(k, i);
            for (int j = count/k; j < count; j++) {
                if (j/(count/k) % 2 == 1) {
                    ar[j] = ar[count/k - 1 - j % (count/k)];
                } else {
                    ar[j] = ar[j % (count/k)];
                }
            }
            for (int j = 0; j < count; j++) {
                ar[j] = ar[j] + j/(count/k);
            }
        }
        for (int i = 0; i < size; i++) {
            out.println(ar[i]);
        }
        out.close();     
    }
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
}