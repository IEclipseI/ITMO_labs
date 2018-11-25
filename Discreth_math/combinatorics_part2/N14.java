import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
 
public class N14 {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("perm2num.in"));
        PrintWriter out = new PrintWriter(new File("perm2num.out"));
        int n = in.nextInt();                       
        long[] ar = new long[n];
        //System.out.println(ar[0] +" " +  ar[1]);
        long answer = 0;
        long[] fact = new long[n];
        fact[0] = 1;
        boolean[] cur = new boolean[n];
        for (int i = 1; i < n; i++) {
            fact[i] = fact[i - 1]*i;
            //System.out.println(fct[i]);
        }
        for (int i = 0; i < n; i++) {
            ar[i] = in.nextInt();
        }
        for (int i = 0; i < n; i++) {
            int count = 0;
            int j = 0;
            while(j != ar[i] - 1) {
                if (!cur[j]) {
                    count++;
                }
                j++;
            }
            cur[j] = true;
            answer += count * fact[n - 1 - i];
        }
                                      
        out.print(answer);        
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