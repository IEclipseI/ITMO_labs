import com.sun.javafx.image.IntPixelGetter;

import java.io.*;
import java.util.*;

public class N19 {
    static long countPrefix(int cur, int n) {
        if (n == 0) {
            return 1;
        }
        long[][] dp = new long[n + 1][n + 1];
        dp[n][n] = 1;
        for (int i = 0; i <= n; i++) {
            dp[i][i] = 1;

        }
        for (int i = n - 1; i >= 1 ; i--) {
            for (int j = i + 1; j <= n; j++) {
                dp[j][i] = dp[j - i][i] + dp[j][i + 1];
            }
        }
        if (cur > n) {
            return 0;
        } else {
            return dp[n][cur];
        }
    }
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("num2part.in"));
        PrintWriter out = new PrintWriter(new File("num2part.out"));

        int n = (int)in.nextInt();
        long numb = in.nextInt();
        //System.out.println(countPrefix(4, 4));
        List<Integer> answer = new ArrayList<Integer>();
        int cur = 1;
        //List<Integer> tmp = new ArrayList<Integer>();
        while (n > 0) {
            for (int j = cur; j <= n; j++) {
                //System.out.println(countPrefix(j, n - j));
                if (countPrefix(j, n - j) > numb) {
                    answer.add(j);
                    n -= j;
                    cur = j;
                    break;
                } else {
                    numb -= countPrefix(j, n - j);
                }
            }
        }
        StringBuilder answer1 = new StringBuilder();
        for (int i:answer
             ) {
            answer1.append(i + "+");
        }
        answer1.deleteCharAt(answer1.length() - 1);
        out.print(answer1.toString());
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

        long nextInt() {
            return Long.parseLong(next());
        }
    }
}