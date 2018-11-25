import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
 
public class N13 {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("num2perm.in"));
        PrintWriter out = new PrintWriter(new File("num2perm.out"));
        int n = in.nextInt();
        long k = Long.parseLong(in.next()) + 1L;                       
        StringBuilder sb = new StringBuilder();
        boolean[] ar = new boolean[n];
        //System.out.println(ar[0] +" " +  ar[1]);
        long[] fct = new long[n + 1];
        fct[0] = 1;
        for (int i = 1; i <= n; i++) {
            fct[i] = fct[i - 1]*i;
            //System.out.println(fct[i]);
        }
        for (int i = 0; i < n; i++) {
            int count = 0;
            int ch = 0;
            while (k > fct[n - 1 - i] && k!=1) {
                count++;
                k = k - fct[n - 1 - i];
                       //     System.out.println(k);
            }
            while (count > 0 || ar[ch]) {
                //System.out.println(count);

                if(!ar[ch]) {
                    count--;
                }
                ch++;
            }
            ar[ch] = true;
            sb.append((ch + 1) + " ");
        }
                                      
        out.print(sb.substring(0, sb.length() - 1));        
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