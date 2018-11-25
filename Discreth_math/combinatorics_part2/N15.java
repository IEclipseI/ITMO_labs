import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
 
public class N15 {
    static void next(List<Integer> answer, int[][] choos, int numb, int n, int k, int value) {
        if (k > 0) {
            if (numb > choos[n - 1][k - 1]) {
                next(answer, choos, numb - choos[n - 1][k - 1], n - 1, k, value + 1);
            } else {
                answer.add(value);
                next(answer, choos, numb, n - 1, k - 1, value + 1);
            }
        }
    }
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("num2choose.in"));
        PrintWriter out = new PrintWriter(new File("num2choose.out"));
        int n = in.nextInt();
        int k = in.nextInt();
        int numb = in.nextInt();
        boolean[] used = new boolean[n];
        int[][] choos = new int[n + 1][k + 1];
        for (int i = 0; i < n + 1; i++) {
            choos[i][0] = 1;
        }
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < k + 1; j++) {
                choos[i][j] = choos[i - 1][j - 1] + choos[i - 1][j];
            }
        }
        List<Integer> answer = new  ArrayList<Integer>();
        //System.out.println(choos[0].length);
        next(answer, choos, numb + 1, n, k, 1);
        for (int value : answer) {
            out.print(value + " ");                            
        }                            
        //out.print(sb.substring(0, sb.length() - 1));        
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