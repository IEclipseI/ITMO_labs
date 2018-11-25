import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
 
public class N24 {
    static void swap(int[] ar,int i,int j) {
        ar[i] += ar[j];
        ar[j] = ar[i] - ar[j];
        ar[i] = ar[i] - ar[j];
    }
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("nextperm.in"));
        PrintWriter out = new PrintWriter(new File("nextperm.out"));
        int n = in.nextInt();
        if (n == 1) {
            out.println(0);
            out.print(0);
            out.close();
            return;
        }
        int[] ar1 = new int[n];
        int[] ar2 = new int[n];
        for (int  i =  0; i < n; i++) {
            ar1[i] = in.nextInt();
            ar2[i] = ar1[i];
        }
        for (int i = n - 1; i > 0; i--) {
            if (ar1[i - 1] > ar1[i]) {
                for (int j = n - 1; j > 0; j--) {
                    if (ar1[i - 1] > ar1[j]) {
                        swap(ar1, i - 1, j);
                        break;
                    }
                }
                for (int j = 0; j < (n - i) /2; j++) {
                    swap(ar1, i + j, n - 1- j);
                }
                StringBuilder sb = new StringBuilder();
                for (int j = 0; j < n; j++) {
                     sb.append(Integer.toString(ar1[j]) + " ");
                }
                out.println(sb.toString());
                break;
            }
            if (i == 1) {
                StringBuilder sb = new StringBuilder();
                for (int j = 0; j < n; j++) {
                     sb.append("0 ");
                }
                out.println(sb.toString());
            }
        }
        for (int i = n - 1; i > 0; i--) {
            if (ar2[i - 1] < ar2[i]) {
                for (int j = n - 1; j > 0;j--) {
                    if  (ar2[j] > ar2[i - 1]) {
                        swap(ar2, i - 1, j);
                        break;
                    }
                }
                for (int j = 0; j < (n - i) /2; j++) {
                    swap(ar2, i + j, n - 1- j);
                }
                StringBuilder sb = new StringBuilder();
                for (int j = 0; j < n; j++) {
                     sb.append(Integer.toString(ar2[j]) + " ");
                }
                out.print(sb.toString());
                break;
            }
            if (i == 1) {
                StringBuilder sb = new StringBuilder();
                for (int j = 0; j < n; j++) {
                     sb.append("0 ");
                }
                out.print(sb.toString());
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