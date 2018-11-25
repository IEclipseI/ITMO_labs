import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
 
public class N4 {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("chaincode.in"));
        PrintWriter out = new PrintWriter(new File("chaincode.out"));
        int n = in.nextInt();
        if (n == 1) {
            out.println(0);
            out.println(1);
            out.close();
            return;
        }
        List<String> ar = new ArrayList<String>();
        int size = (int)Math.pow(2, n);
        boolean[] elem = new boolean[size];
        int sum = 0;
        String now = "";
        for (int i = 0; i < n; i++) {
            now = now + "0";
        }
        ar.add(now);
        elem[0] = true;
        for (int i  = 1; i < size; i++) {
            if (elem[Integer.parseInt(now.substring(1, now.length()), 2) * 2 + 1]) {
                elem[Integer.parseInt(now.substring(1, now.length()), 2) * 2 ] = true;
                now = now.substring(1, now.length()) + "0";
                ar.add(now);
            } else {
                elem[Integer.parseInt(now.substring(1, now.length()), 2) * 2 + 1] = true;
                now = now.substring(1, now.length()) + "1";
                ar.add(now);
            }
        }
        for (int i = 0; i < size; i++) {
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