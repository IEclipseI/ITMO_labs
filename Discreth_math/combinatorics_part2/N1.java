import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
 
public class N1 {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("telemetry.in"));
        PrintWriter out = new PrintWriter(new File("telemetry.out"));
        int n = in.nextInt();
        int k = in.nextInt();
        int size = (int)Math.pow(k, n);
        String[] ar = new String[size];
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 0; i ++) {
            sb.append('0');
        }
        for (int i = 0; i < k; i ++) {
            ar[i] = Integer.toString(i);
        }
        for (int i = 1; i < n; i++) {
            size = (int)Math.pow(k, i + 1);
            System.out.println(size);
            for (int j = k * (int)Math.pow(k, i - 1); j < size; j++) {
                if ((j / k) % 2 == 1) {
                    ar[j] = ar[k - 1 - j % k];
                } else {
                    ar[j] = ar[j % k];
                }
                System.out.println(ar[j]);
            }
            for (int j = 0; j < size; j++) {
                System.out.println(j * k / size);
                ar[j] = ar[j] + j * k / size;
            }
        }
        size = (int)Math.pow(k, n);
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