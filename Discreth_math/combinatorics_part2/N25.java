import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
 
public class N25 {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("nextchoose.in"));
        PrintWriter out = new PrintWriter(new File("nextchoose.out"));
        int n = in.nextInt();
        boolean[] used = new boolean[n];
        int k = in.nextInt();
        int[] ar = new int[k];
        boolean flag = false;
        for (int i = 0; i < k; i++) {
            used[in.nextInt() - 1] = true;
        }
        int size = k;
        int last = 0;
        for (int i = n - 1; i >=0; i--) {
            if (!flag) {
                if (!used[i]) {
                    flag = true;
                } else {
                    used[i] = false;
                    size--;
                }
            } else {
                if (used[i]) {
                    used[i] = false;
                    used[i + 1] = true;
                    last = i + 2;
                    break;
                }
            } 
        }
        if (size == 0) {
            out.print("-1");
        } else {
            while (k - size > 0) {
                used[last] = true;
                size++;
                last++;
            }
            for (int i = 0; i < n; i ++) {
                if (used[i]) {
                    out.print((i + 1) + " ");
                }
            }
        }                       
        out.println();        
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