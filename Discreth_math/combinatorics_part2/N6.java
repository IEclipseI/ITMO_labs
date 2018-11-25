import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
 
public class N6 {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("vectors.in"));
        PrintWriter out = new PrintWriter(new File("vectors.out"));
        int n = in.nextInt();
        List<String> ar = new ArrayList<String>();
        int size = (int)Math.pow(2, n);
        int sum = 0;
        for (int i = 0; i < size; i++) {
            StringBuilder sb = new StringBuilder();
            boolean flag = true;
            for (int j = n - 1; j >= 0; j--) {
                int k = (i >> j) & 1;
                if (sb.length() > 0) {
                    if (sb.charAt(sb.length() - 1) == '1' && k == 1) {
                        flag = false;
                        break;
                    } else {
                        sb.append(k);
                    }
                } else {
                        sb.append(k);
                }
            }
            if (flag) {
                ar.add(sb.toString());
                sum++;
            }
        }
        out.println(sum);
        for (int i = 0; i < sum; i++) {
            out.println(ar.get(i));
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