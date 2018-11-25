import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;

public class A {
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
        FastScanner in = new FastScanner(new File("huffman.in"));
        PrintWriter out = new PrintWriter(new File("huffman.out"));
        int n = Integer.parseInt(in.next());
        long[] ar1 = new long[n + 1];
        long[] ar2 = new long[n + 1];
        Arrays.fill(ar2, 1000_000_001);
        for (int i = 0; i < n; i++) {
            ar1[i] = Integer.parseInt(in.next());
        }
        ar1[n] = 2000_000_000_004L;
        int k1 = 0;
        int k2 = 0;
        long ans = 0;
        Arrays.sort(ar1);
        if (n == 1){
            out.print(ar1[0]);
            out.close();
            return;
        }
        //System.out.println(n);
        for (int i = 0; i < n - 1; i++) {
            //System.out.println(Arrays.toString(ar1));
            //System.out.println(Arrays.toString(ar2));
            if (k1 > n - 2) {
                //System.out.println(k1);
                //System.out.println(k2);
                if (ar1[k1] + ar2[k2] <= ar2[k2] + ar2[k2 + 1]) {
                    ar2[i] = ar1[k1] + ar2[k2];
                    ans += ar2[i];
                    k2++;
                    k1++;
                    continue;
                }
                ar2[i] = ar2[k2] + ar2[k2 + 1];
                ans += ar2[i];
                k2 += 2;
                continue;
            } 
            if ((ar1[k1] + ar1[k1 + 1] <= ar1[k1] + ar2[k2]) && (ar1[k1] + ar1[k1 + 1] <= ar2[k2] + ar2[k2 + 1])) {
                ar2[i] = ar1[k1] + ar1[k1 + 1];
                ans += ar2[i];
                k1 += 2;
                continue;
            }
            if (ar1[k1] + ar2[k2] <= ar1[k1] + ar1[k1 + 1] && ar1[k1] + ar2[k2] <= ar2[k2] + ar2[k2 + 1]) {
                ar2[i] = ar1[k1] + ar2[k2];
                ans += ar2[i];
                k2++;
                k1++;
                continue;
            }
            ar2[i] = ar2[k2] + ar2[k2 + 1];
            ans += ar2[i];
            k2 += 2;
        }
        //System.out.println(Arrays.toString(ar1));
        //System.out.println(Arrays.toString(ar2)); 
        out.print(ans);
        out.close();            
    }
}